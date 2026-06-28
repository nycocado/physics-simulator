# Refactoring Plan — physics-simulator

## Already done

| Change | Files |
| ------ | ----- |
| Removed all source comments | all `src/**/*.c` and `src/**/*.h` |
| `.gitignore`, `.clang-format`, `clang-format -i` applied | root |
| Bilingual README (EN + PT) | `README.md`, `README.pt.md` |
| `-Wall -Wextra -Wno-unused-parameter` enabled; `clear` → `clean` target | `Makefile` |
| Fixed typo `firts_time` → `first_time` | `gtk_variables.h/c`, simulation files |
| `CINEMATIC`/`DYNAMIC` → `SimulationMode` enum (`SIMULATION_CINEMATIC`/`SIMULATION_DYNAMIC`) | `gtk_include_all.h` + all call sites |
| TreeStore column indices (0–9) → `ParticleColumn` enum (`COL_X` … `COL_TYPE`) | `gtk_include_all.h`, `gtk_project.c`, `gtk_collection.c`, `gtk_callbacks.c` |
| `on_window_cinematic_destroy` / `on_window_dynamic_destroy` deduplicated via `simulation_window_destroy()` | `simulation_commun.c/h`, both simulation files |
| Fixed double-gravity bug in `forces_dynamic_apply` — gravity applied to `force_resultant` before acceleration is derived | `simulation_dynamic.c` |
| Fixed double-gravity in dynamic CSV log — `ay - g` → `ay` (acceleration already includes gravity) | `gtk_log.c` |
| Forces no longer dropped on open — parser branches by type before null-check | `gtk_project.c` |
| Buffer underflow on blank line — `strlen` guard before `line[len-1] = '\0'` | `gtk_project.c` |
| `free(line)` after `getline` loop (was leaking) | `gtk_project.c` |
| Mass validation in parser — `g_ascii_strtod(mass) <= 0` skips the line | `gtk_project.c` |
| Mass spin button minimum unified to `0.001` in both add and edit dialogs (was `0.01`/`1e-30`) | `gtk_create_window.c` |
| `#define M_PI` → `#ifndef M_PI` guard (avoids collision with `<math.h>`; no GLib in physics files) | `phy_forms_cinematics.c`, `phy_forms_dynamics.c`, `phy_tests.c` |
| `g_timeout_add` source ID saved in `timeout_id`; removed before destroy and on stop | `gtk_variables.h`, `simulation_commun.c`, both simulation files |
| `on_timeout_*` return `FALSE` immediately at natural end — clears `timeout_id` cleanly | `simulation_cinematic.c`, `simulation_dynamic.c` |
| Shared helpers extracted: `simulation_read_controls()`, `simulation_stop()`, `simulation_start_timer()` | `simulation_commun.c/h` |
| `on_*_start_button_clicked` deduplicated (~30 lines each removed) | both simulation files |
| `on_*_stop_button_clicked` and `on_*_refresh_button_clicked` now call `simulation_stop()` | both simulation files |
| `malloc`/`free` → `g_new`/`g_free` in `particle.c` | `particle.c` |
| `g_slice_new`/`g_slice_free` → `g_new`/`g_free` across all model files (deprecated in GLib 2.76) | all `src/model/*.c` |
| `pow(t, 2)` → `t * t` and `pow(bx/by, 2)` → `bx*bx`/`by*by` (no-op function call for trivial squares) | `phy_forms_cinematics.c` |
| `particle.h` now includes `<glib.h>` directly — `GList *` field no longer requires caller to include GLib first | `particle.h` |
| Simulation window made modal (`gtk_window_set_modal`) — prevents mutating `num_particles_use` while simulation runs | `gtk_create_window.c` |
| `simulation_window_destroy` sets `window = NULL` after destroy; `run_simulation_*` checks for non-NULL before opening — prevents leaking the first window when both modes are opened | `simulation_commun.c`, `simulation_cinematic.c`, `simulation_dynamic.c` |
| `.sabino` now saves a `SETTINGS gravity=… time=… step=… frames=…` line; values are not wiped on destroy and are restored to spin buttons when the simulation window reopens | `gtk_variables.c`, `gtk_project.c`, `gtk_create_window.c` |
| Particle checked state saved as 8th field on `Partícula` lines; restored on load — defaults to `1` (TRUE) for old files; `num_particles_use` only incremented for checked particles | `gtk_project.c` |
| `atof` → `g_ascii_strtod` in all tree-store reads (collection, callbacks); literal `0–6` force column indices → `COL_*` enum in collection and callbacks; remaining `atof` in edit-dialog prefill also replaced | `gtk_collection.c`, `gtk_callbacks.c` |
| `test_simulation.c` (7 tests), `test_locale.c` (4 tests), `test_validation.c` (4 tests) added; `GLIBFLAGS` + per-suite targets in Makefile; `all_tests` runs 33 tests total | `test/`, `Makefile` |

---

## Pending

### 1. GTK4 migration

GTK 4.22 is installed (`pkg-config --modversion gtk4`). Dev headers are available.

#### 1.1 Makefile — switch to GTK4 and drop `-rdynamic`

```makefile
# before
GTKFLAGS = `pkg-config --cflags --libs gtk+-3.0` -rdynamic

# after
GTKFLAGS = `pkg-config --cflags --libs gtk4`
```

`-rdynamic` is only needed for `gtk_builder_connect_signals` symbol lookup (see 1.2). Once signal wiring is explicit, it serves no purpose.

#### 1.2 Signal wiring — `gtk_builder_connect_signals` removed

**This is the largest single missing item.** GTK4 removes `gtk_builder_connect_signals` entirely. Every window-creation function in `gtk_create_window.c` ends with a call to it (lines 68, 180, 232, 349, 401, 492), resolving callback names to function symbols at runtime via `-rdynamic`. In GTK4 this does not exist.

```c
/* GTK3 — resolves by symbol name at runtime */
gtk_builder_connect_signals(builder, NULL);

/* GTK4 option A — explicit g_signal_connect per widget */
GtkWidget *btn = GTK_WIDGET(gtk_builder_get_object(builder, "add_button"));
g_signal_connect(btn, "clicked", G_CALLBACK(on_add_button_clicked), NULL);

/* GTK4 option B — register symbols with GtkBuilderCScope */
GtkBuilderCScope *scope = gtk_builder_cscope_new();
gtk_builder_cscope_add_callback_symbol(scope, "on_add_button_clicked",
    G_CALLBACK(on_add_button_clicked));
gtk_builder_set_scope(builder, GTK_BUILDER_SCOPE(scope));
```

Option B is closer to the GTK3 model and integrates better with Blueprint (where signals are declared in `.blp`).

#### 1.3 Draw signal → `gtk_drawing_area_set_draw_func`

GTK4 removes the `"draw"` signal. Signature changes; `gboolean` return removed.

```c
/* GTK3 */
gboolean on_draw_cinematic(GtkWidget *widget, cairo_t *cr) { ...; return FALSE; }

/* GTK4 */
void on_draw_cinematic(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer data)
{
    // width/height replace gtk_widget_get_allocation — get_window_size() can be deleted
}
gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), on_draw_cinematic, NULL, NULL);
```

`get_window_size()` in `simulation_commun.c` becomes dead code and should be removed.

Affected: `simulation_cinematic.c`, `simulation_dynamic.c`, `simulation_commun.c`.

#### 1.4 `GtkFileChooserDialog` + `gtk_dialog_run` → `GtkFileDialog` (async)

GTK4 removes both. All three file dialogs (`gtk_main.c:128`, `gtk_callbacks.c:432`, `gtk_callbacks.c:491`) must become async.

```c
static void on_open_response(GObject *source, GAsyncResult *result, gpointer data)
{
    GFile *file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(source), result, NULL);
    if (!file) return;
    char *path = g_file_get_path(file);
    open_project(path);
    g_free(path);
    g_object_unref(file);
}

GtkFileDialog *dialog = gtk_file_dialog_new();
gtk_file_dialog_open(dialog, GTK_WINDOW(parent), NULL, on_open_response, NULL);
g_object_unref(dialog);
```

**Lost functionality:** `on_selection_change_abrir` (`gtk_callbacks.c:401`) enables/disables the open button based on `.sabino` extension. `GtkFileDialog` has no in-dialog validation hook — use `GtkFileFilter` via `gtk_file_dialog_set_filters` instead.

#### 1.5 `GtkMessageDialog` + `gtk_dialog_run` → `GtkAlertDialog` (async)

`create_dialog_error_message` (`gtk_create_window.c:515`) is called ~15 times in `gtk_callbacks.c`, each followed by `return` — relying on the synchronous block. Both `GtkMessageDialog` and `gtk_dialog_run` are removed in GTK4.

```c
/* GTK4 */
GtkAlertDialog *dialog = gtk_alert_dialog_new("%s", message);
gtk_alert_dialog_show(dialog, GTK_WINDOW(parent));
g_object_unref(dialog);
```

Each of the ~15 callers must be restructured so the post-error logic runs inside the response callback instead of after a blocking call.

#### 1.6 `gtk_main` / `gtk_init` → `GtkApplication`

```c
static void on_activate(GtkApplication *gtk_app, gpointer data)
{
    run_gtk_inner(GTK_APPLICATION(gtk_app));
}

int main(int argc, char *argv[])
{
    GtkApplication *gtk_app = gtk_application_new(
        "pt.iade.physics-simulator", G_APPLICATION_DEFAULT_FLAGS
    );
    g_signal_connect(gtk_app, "activate", G_CALLBACK(on_activate), NULL);
    int status = g_application_run(G_APPLICATION(gtk_app), argc, argv);
    g_object_unref(gtk_app);
    return status;
}
```

#### 1.7 `GtkMenuBar` / `GtkMenu` / `GtkMenuItem` → `GMenu` + `GtkPopoverMenuBar`

GTK4 removes the old menu widgets. Replace `window_main.glade` menu with a `GMenu` model and `GtkPopoverMenuBar`. Each item becomes a `GSimpleAction` registered on the `GtkApplication`.

```c
GMenu *menu = g_menu_new();
GMenu *file_menu = g_menu_new();
g_menu_append(file_menu, "New",  "app.new");
g_menu_append(file_menu, "Open", "app.open");
g_menu_append(file_menu, "Save", "app.save");
g_menu_append_submenu(menu, "File", G_MENU_MODEL(file_menu));
GtkWidget *bar = gtk_popover_menu_bar_new_from_model(G_MENU_MODEL(menu));
```

#### 1.8 Miscellaneous removed symbols

| Removed in GTK4 | Replacement | Where used |
|---|---|---|
| `gtk_widget_destroy(window)` | `gtk_window_destroy(GTK_WINDOW(window))` | `simulation_commun.c` |
| `gtk_widget_show_all(window)` | `gtk_widget_set_visible` / `gtk_window_present` | all create functions |
| `gtk_entry_get_text` | `gtk_editable_get_text`; prefer `gtk_spin_button_get_value()` for spin buttons | `gtk_callbacks.c` |
| `gtk_widget_get_toplevel` | `gtk_widget_get_root` / `gtk_widget_get_native` | `gtk_callbacks.c:5` |
| `gtk_window_set_position(GTK_WIN_POS_CENTER_ON_PARENT)` | remove; use `gtk_window_set_transient_for` | `gtk_create_window.c:512` |
| `gtk_widget_get_allocation` | removed — use `width`/`height` draw func params | `simulation_commun.c` |

#### 1.9 `GtkTreeView` deprecated since GTK 4.10

`GtkTreeView`, `GtkTreeStore`, `GtkListStore`, and all `GtkCellRenderer*` are deprecated from GTK 4.10. They still compile but will eventually be removed. Modern replacement: `GtkColumnView` + `GListModel`. Keeping `GtkTreeView` is a deliberate scope decision — document it explicitly so it is not treated as an oversight.

---

### 2. Blueprint — replace Glade XML

Blueprint (`blueprint-compiler`) is the modern GTK4 UI definition language. Compiles `.blp` → GtkBuilder XML (`.ui`), readable by `gtk_builder_new_from_file` unchanged.

Install: `sudo dnf install blueprint-compiler`

For each `.glade` file in `src/view/ui/`:

1. Convert: `blueprint-compiler migrate src/view/ui/window_main.glade > src/view/ui/window_main.blp` (manual cleanup needed)
2. Compile at build time:
   ```makefile
   %.ui: %.blp
       blueprint-compiler compile $< --output $@
   ```
3. Update `gtk_create_window.c` to load `.ui` instead of `.glade`.
4. Add `*.ui` to `.gitignore` (generated files).

Blueprint example:
```
using Gtk 4.0;

ApplicationWindow main_window {
  title: "Physics Simulator";
  Box {
    orientation: vertical;
    PopoverMenuBar { menu-model: app_menu; }
    ScrolledWindow {
      TreeView particles_view { model: particles_store; }
    }
  }
}

menu app_menu {
  submenu {
    label: "File";
    item { label: "New";  action: "app.new"; }
    item { label: "Open"; action: "app.open"; }
    item { label: "Save"; action: "app.save"; }
  }
}
```

---

### 3. Global state — remove `extern GtkApp app`

All source files reach application state through a global `app` variable via `gtk_include_all.h`. This makes function dependencies invisible and prevents unit testing beyond physics formulas.

Proposed change: pass `GtkApp *` as the first parameter to every function that needs it. This is the largest change in scope — every signature and call site must be updated — but it is a prerequisite for meaningful unit testing.

---

### 4. Locale safety — store numbers as native types in TreeStore

`atof` is fully removed from the project. All tree-store string reads now use `g_ascii_strtod` (locale-independent). The remaining locale issue is deeper: all numeric columns are still `gchararray`.

Remaining:
1. Change numeric TreeStore columns to `G_TYPE_DOUBLE` (requires Glade column-type edits and cascading changes in `gtk_callbacks.c`, `gtk_collection.c`, `gtk_project.c`).
2. `replace_dot_with_comma` in `gtk_log.c` is intentional — the CSV uses `;` separator and `,` decimal for pt_BR spreadsheet compatibility. If the output format is ever changed to standard CSV (dot decimal), remove it.
3. Add/edit particle dialogs still call `gtk_entry_get_text(GTK_ENTRY(spin_button))` instead of `gtk_spin_button_get_value` — minor style, harmless since values are stored as strings anyway.

---

### 5. File naming — remove `gtk_` prefix from project code

GTK uses `gtk_` as its own namespace. Applying it to project-specific files creates confusion.

| Current name | Proposed name |
| ------------ | ------------- |
| `gtk_project.c/h` | `project.c/h` |
| `gtk_app.c/h` | `app.c/h` |
| `gtk_log.c/h` | `log.c/h` |
| `gtk_collection.c/h` | `collection.c/h` |
| `gtk_variables.c/h` | `variables.c/h` |
| `gtk_window_main.c/h` | `window_main.c/h` |
| `gtk_window_add_particle_normal.c/h` | `particle_dialog.c/h` (merge add + edit) |
| `gtk_window_add_force_normal.c/h` | `force_dialog.c/h` (merge add + edit) |
| `gtk_window_edit_particle_normal.c/h` | merged into `particle_dialog.c/h` |
| `gtk_window_edit_force_normal.c/h` | merged into `force_dialog.c/h` |
| `gtk_button_add.c/h` | `buttons.c/h` (merge add + edit) |
| `gtk_callbacks.c` | `callbacks.c` |
| `gtk_main.c` | `main_window.c` |
| `gtk_create_window.c` | `builder.c` |
| `gtk_include_all.h` | `app.h` (scoped includes, not a mega-header) |

---

### 6. Directory layout

```
src/
├── app.c / app.h
├── project.c / project.h      (save/load .sabino)
├── collection.c
├── log.c / log.h              (CSV export)
├── physics/
│   ├── kinematics.c/h
│   └── dynamics.c/h
├── particles/
│   ├── particle.c/h
│   ├── particle_dialog.c/h    (add + edit — merged)
│   └── force_dialog.c/h
├── simulation/
│   ├── simulation.c/h         (shared: start, stop, destroy, wipe, read_controls)
│   ├── kinematic_sim.c/h
│   └── dynamic_sim.c/h
└── ui/
    ├── builder.c/h
    ├── callbacks.c/h
    ├── main_window.c/h
    └── windows/
        ├── *.blp
        └── *.ui               (compiled, gitignored)
```

---

### 7. Tests

`test_simulation.c`, `test_locale.c`, and `test_validation.c` are done (see "Already done").

Remaining:
| Test | What to verify |
|------|---------------|
| `test_project_io.c` | save + load round-trip with forces; forces must survive the round-trip (regression for the dropped-forces bug). **Blocked**: `save_project`/`open_project` are coupled to `GtkTreeStore` — requires GTK or a refactor to extract I/O logic from the UI layer. |

---

## GTK4 migration checklist

- [ ] `Makefile` — `gtk+-3.0` → `gtk4`; remove `-rdynamic`
- [ ] Signal wiring — replace `gtk_builder_connect_signals` with explicit `g_signal_connect` or `GtkBuilderCScope`
- [ ] Draw callbacks — change signature, register via `gtk_drawing_area_set_draw_func`; delete `get_window_size()`
- [ ] File dialogs — replace `GtkFileChooserDialog` + `gtk_dialog_run` with `GtkFileDialog` async; use `GtkFileFilter` for `.sabino` validation
- [ ] Error dialogs — replace `GtkMessageDialog` + `gtk_dialog_run` with `GtkAlertDialog`; restructure ~15 caller callbacks for async
- [ ] Entry point — wrap in `GtkApplication`, move `gtk_init`/`gtk_main` to `g_application_run`
- [ ] Menu bar — replace `GtkMenuBar`/`GtkMenuItem` with `GMenu` + `GtkPopoverMenuBar` + `GSimpleAction`
- [ ] `gtk_widget_destroy(window)` → `gtk_window_destroy(GTK_WINDOW(window))`
- [ ] `gtk_widget_show_all` → `gtk_widget_set_visible` / `gtk_window_present`
- [ ] `gtk_entry_get_text` → `gtk_editable_get_text`; prefer `gtk_spin_button_get_value()` for spin buttons
- [ ] `gtk_widget_get_toplevel` → `gtk_widget_get_root` / `gtk_widget_get_native`
- [ ] `gtk_window_set_position(GTK_WIN_POS_CENTER_ON_PARENT)` → remove or use `gtk_window_set_transient_for`
- [ ] Blueprint — run `blueprint-compiler migrate` on each `.glade`; clean up `.blp`; add Makefile compile rule; gitignore `.ui`
- [x] `malloc`/`free` → `g_new`/`g_free`; `g_slice_new`/`g_slice_free` → `g_new`/`g_free`
- [ ] Document `GtkTreeView` as deliberately kept despite being deprecated since GTK 4.10
