#include "../include/gtk_include_all.h"

void on_window_destroy(GtkWidget *widget) // Função chamada quando a janela é fechada
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Obtém o widget da janela

    if (GTK_IS_WINDOW(toplevel)) // Se o widget é uma janela
    {
        gtk_widget_destroy(toplevel); // Fecha a janela
    }
}

void on_renderer_check_toggled(GtkCellRendererToggle *renderer, gchar *path_str) // Função chamada quando o botão de seleção de uma linha é clicado
{
    GtkTreePath *path = gtk_tree_path_new_from_string(path_str);                 // Cria um caminho da árvore
    GtkTreeIter iter;                                                            // Cria um iterador da árvore
    gtk_tree_model_get_iter(GTK_TREE_MODEL(app->tree_store), &iter, path);       // Obtém o iterador da árvore
    gboolean checked;                                                            // Cria uma variável para armazenar o estado do botão de seleção
    gtk_tree_model_get(GTK_TREE_MODEL(app->tree_store), &iter, 7, &checked, -1); // Obtém o estado do botão de seleção
    checked = !checked;                                                          // Inverte o estado do botão de seleção
    gtk_tree_store_set(app->tree_store, &iter, 7, checked, -1);                  // Define o novo estado do botão de seleção
    if (checked)                                                                 // Se o botão de seleção foi marcado
    {
        app->variables->simulation->num_particles_use++; // Incrementa o número de partículas usadas
    }
    else // Se o botão de seleção foi desmarcado
    {
        app->variables->simulation->num_particles_use--; // Decrementa o número de partículas usadas
    }
    gtk_tree_path_free(path); // Libera a memória alocada para o caminho da árvore
}

void on_window_main_add_particle_button_clicked(GtkButton *button) // Função chamada quando o botão de "+" da tela principal é clicado
{
    if (!app->variables->project->is_file_open) // Se não houver um projeto aberto
    {
        create_dialog_error_message("Não é possível adicionar partículas sem um projeto aberto."); // Cria uma mensagem de erro
        return;                                                                                    // Termina a função
    }
    // Se houver um projeto aberto
    create_window_add_particle_normal_widgets();                  // Cria os widgets da janela de adição
    gtk_widget_show_all(app->window_add_particle_normal->window); // Mostra a janela de adição
}

void on_window_add_particle_normal_add_button_clicked(GtkWidget *widget) // Função chamada quando o botão de adição da janela de adição de partícula é clicado
{
    // Obtém os valores dos campos de entrada
    const gchar *xi = gtk_entry_get_text(GTK_ENTRY(app->window_add_particle_normal->spin_buttons->x));      // Posição x
    const gchar *yi = gtk_entry_get_text(GTK_ENTRY(app->window_add_particle_normal->spin_buttons->y));      // Posição y
    const gchar *vx = gtk_entry_get_text(GTK_ENTRY(app->window_add_particle_normal->spin_buttons->vx));     // Velocidade x
    const gchar *vy = gtk_entry_get_text(GTK_ENTRY(app->window_add_particle_normal->spin_buttons->vy));     // Velocidade y
    const gchar *ax = gtk_entry_get_text(GTK_ENTRY(app->window_add_particle_normal->spin_buttons->ax));     // Aceleração x
    const gchar *ay = gtk_entry_get_text(GTK_ENTRY(app->window_add_particle_normal->spin_buttons->ay));     // Aceleração y
    const gchar *mass = gtk_entry_get_text(GTK_ENTRY(app->window_add_particle_normal->spin_buttons->mass)); // Massa

    // Armazena os valores na árvore
    GtkTreeIter iter;                                                                                                                    // Cria um iterador da árvore
    gtk_tree_store_append(app->tree_store, &iter, NULL);                                                                                 // Adiciona uma nova linha à árvore
    gtk_tree_store_set(app->tree_store, &iter, 0, xi, 1, yi, 2, vx, 3, vy, 4, ax, 5, ay, 6, mass, 7, TRUE, 8, TRUE, 9, "Partícula", -1); // Define os valores da nova linha
    app->variables->simulation->num_particles_use++;                                                                                     // Incrementa o número de partículas usadas
    gtk_widget_destroy(app->window_add_particle_normal->window);                                                                         // Fecha a janela de adição
}

void on_window_edit_particle_normal_edit_button_clicked() // Função chamada quando o botão de edição da janela de edição de partícula é clicado
{
    // Obtém os valores dos campos de entrada
    const gchar *xi = gtk_entry_get_text(GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->x));      // Posição x
    const gchar *yi = gtk_entry_get_text(GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->y));      // Posição y
    const gchar *vx = gtk_entry_get_text(GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->vx));     // Velocidade x
    const gchar *vy = gtk_entry_get_text(GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->vy));     // Velocidade y
    const gchar *ax = gtk_entry_get_text(GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->ax));     // Aceleração x
    const gchar *ay = gtk_entry_get_text(GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->ay));     // Aceleração y
    const gchar *mass = gtk_entry_get_text(GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->mass)); // Massa

    // Armazena os valores na árvore
    GtkTreeIter iter;                                                                                  // Cria um iterador da árvore
    GtkTreeModel *model;                                                                               // Cria um modelo de árvore
    gtk_tree_selection_get_selected(gtk_tree_view_get_selection(app->tree_view), &model, &iter);       // Obtém a linha selecionada
    gtk_tree_store_set(app->tree_store, &iter, 0, xi, 1, yi, 2, vx, 3, vy, 4, ax, 5, ay, 6, mass, -1); // Define os valores da linha selecionada
    gtk_widget_destroy(app->window_edit_particle_normal->window);                                      // Fecha a janela de edição
}

void on_window_main_add_force_button_clicked(GtkButton *button) // Função chamada quando o botão de "↓" da tela principal é clicado
{
    if (!app->variables->project->is_file_open) // Se não houver um projeto aberto
    {
        create_dialog_error_message("Não é possível adicionar forças sem um projeto aberto."); // Cria uma mensagem de erro
        return;                                                                                // Termina a função
    }
    // Se houver um projeto aberto
    GtkTreeModel *model;                                                       // Cria um modelo de árvore
    GtkTreeIter iter;                                                          // Cria um iterador de árvore
    GtkTreeSelection *selection = gtk_tree_view_get_selection(app->tree_view); // Obtém a seleção da árvore
    if (!gtk_tree_selection_get_selected(selection, &model, &iter))            // Se não houver uma linha selecionada
    {
        create_dialog_error_message("Não é possível adicionar uma força sem uma partícula selecionada."); // Cria uma mensagem de erro
        return;                                                                                           // Termina a função
    }
    // Se houver uma linha selecionada
    GtkTreeIter testIter;                                    // Cria um iterador de teste
    if (gtk_tree_model_iter_parent(model, &testIter, &iter)) // Se a linha selecionada for uma força (ou seja, se ela tiver um pai)
    {
        create_dialog_error_message("Não é possível adicionar uma força em outra força."); // Cria uma mensagem de erro
        return;                                                                            // Termina a função
    }
    // Se a linha selecionada for uma partícula (ou seja, se ela não tiver um pai)
    create_window_add_force_normal_widgets();                  // Cria os widgets da janela de adição
    gtk_widget_show_all(app->window_add_force_normal->window); // Mostra a janela de adição
}

void on_window_add_force_normal_add_button_clicked(GtkWidget *widget) // Função chamada quando o botão de adição da janela de adição de força é clicado
{
    // Obtém os valores dos campos de entrada
    const gchar *fx = gtk_entry_get_text(GTK_ENTRY(app->window_add_force_normal->spin_buttons->fx)); // Força x
    const gchar *fy = gtk_entry_get_text(GTK_ENTRY(app->window_add_force_normal->spin_buttons->fy)); // Força y

    // Armazena os valores na árvore
    GtkTreeModel *model;                                                                                                                  // Cria um modelo de árvore
    GtkTreeIter parentIter, childIter, testIter;                                                                                          // Cria iteradores de árvore
    gtk_tree_selection_get_selected(gtk_tree_view_get_selection(app->tree_view), &model, &parentIter);                                    // Obtém a linha selecionada
    gtk_tree_store_append(app->tree_store, &childIter, &parentIter);                                                                      // Adiciona uma nova linha à árvore
    gtk_tree_store_set(app->tree_store, &childIter, 0, fx, 1, fy, 2, "", 3, "", 4, "", 5, "", 6, "", 7, FALSE, 8, FALSE, 9, "Força", -1); // Define os valores da nova linha

    // Expande a linha selecionada (para mostrar a força sem o usuário precisar expandir manualmente)
    GtkTreePath *path = gtk_tree_model_get_path(GTK_TREE_MODEL(app->tree_store), &parentIter); // Obtém o caminho da linha selecionada
    gtk_tree_view_expand_row(app->tree_view, path, FALSE);                                     // Expande a linha selecionada
    gtk_tree_path_free(path);                                                                  // Libera a memória alocada para o caminho
    gtk_widget_destroy(app->window_add_force_normal->window);                                  // Fecha a janela de adição
}

void on_window_edit_force_normal_edit_button_clicked() // Função chamada quando o botão de edição da janela de edição de força é clicado
{
    // Obtém os valores dos campos de entrada
    const gchar *fx = gtk_entry_get_text(GTK_ENTRY(app->window_edit_force_normal->spin_buttons->fx)); // Força x
    const gchar *fy = gtk_entry_get_text(GTK_ENTRY(app->window_edit_force_normal->spin_buttons->fy)); // Força y

    // Armazena os valores na árvore
    GtkTreeIter iter;                                                                            // Cria um iterador da árvore
    GtkTreeModel *model;                                                                         // Cria um modelo de árvore
    gtk_tree_selection_get_selected(gtk_tree_view_get_selection(app->tree_view), &model, &iter); // Obtém a linha selecionada
    gtk_tree_store_set(app->tree_store, &iter, 0, fx, 1, fy, -1);                                // Define os valores da linha selecionada
    gtk_widget_destroy(app->window_edit_force_normal->window);                                   // Fecha a janela de edição
}

void on_window_main_edit_button_clicked(GtkWidget *widget) // Função chamada quando o botão de edição da tela principal é clicado
{
    // Essa função serve para abrir a janela de edição de partículas ou forças, e preencher os campos de entrada com os valores da linha selecionada
    if (!app->variables->project->is_file_open) // Se não houver um projeto aberto
    {
        create_dialog_error_message("Não é possível editar partículas sem um projeto aberto."); // Cria uma mensagem de erro
        return;                                                                                 // Termina a função
    }
    // Se houver um projeto aberto
    GtkTreeModel *model;                                                                              // Cria um modelo de árvore
    GtkTreeIter iter;                                                                                 // Cria um iterador de árvore
    if (!gtk_tree_selection_get_selected(gtk_tree_view_get_selection(app->tree_view), &model, &iter)) // Se não houver uma linha selecionada
    {
        create_dialog_error_message("Não é possível editar uma partícula sem uma partícula selecionada."); // Cria uma mensagem de erro
        return;                                                                                            // Termina a função
    }
    // Se houver uma linha selecionada
    GtkTreeIter testIter;                                     // Cria um iterador de teste
    if (!gtk_tree_model_iter_parent(model, &testIter, &iter)) // Se a linha selecionada for uma partícula (ou seja, se ela não tiver um pai)
    {
        create_window_edit_particle_normal_widgets();                                                   // Cria os widgets da janela de edição
        gchar *xi, *yi, *vx, *vy, *ax, *ay, *mass;                                                      // Cria variáveis para armazenar os valores dos campos de entrada
        gtk_tree_model_get(model, &iter, 0, &xi, 1, &yi, 2, &vx, 3, &vy, 4, &ax, 5, &ay, 6, &mass, -1); // Obtém os valores da linha selecionada
        // Preenche os campos de entrada com os valores obtidos
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->x), atof(xi));
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->y), atof(yi));
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->vx), atof(vx));
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->vy), atof(vy));
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->ax), atof(ax));
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->ay), atof(ay));
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->mass), atof(mass));
        // Libera a memória alocada para os valores dos campos de entrada
        g_free(xi);
        g_free(yi);
        g_free(vx);
        g_free(vy);
        g_free(ax);
        g_free(ay);
        g_free(mass);
        gtk_widget_show_all(app->window_edit_particle_normal->window); // Mostra a janela de edição
    }
    else // Se a linha selecionada for uma força (ou seja, se ela tiver um pai)
    {
        create_window_edit_force_normal_widgets();            // Cria os widgets da janela de edição
        gchar *fx, *fy;                                       // Cria variáveis para armazenar os valores dos campos de entrada
        gtk_tree_model_get(model, &iter, 0, &fx, 1, &fy, -1); // Obtém os valores da linha selecionada
        // Preenche os campos de entrada com os valores obtidos
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(app->window_edit_force_normal->spin_buttons->fx), atof(fx));
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(app->window_edit_force_normal->spin_buttons->fy), atof(fy));
        // Libera a memória alocada para os valores dos campos de entrada
        g_free(fx);
        g_free(fy);
        gtk_widget_show_all(app->window_edit_force_normal->window); // Mostra a janela de edição
    }
}

void on_window_main_remove_button_clicked(GtkWidget *widget) // Função chamada quando o botão de "x" da tela principal é clicado
{
    if (!app->variables->project->is_file_open) // Se não houver um projeto aberto
    {
        create_dialog_error_message("Não é possível remover partículas sem um projeto aberto."); // Cria uma mensagem de erro
        return;                                                                                  // Termina a função
    }
    // Se houver um projeto aberto
    GtkTreeModel *model;                                                       // Cria um modelo de árvore
    GtkTreeIter iter;                                                          // Cria um iterador de árvore
    GtkTreeSelection *selection = gtk_tree_view_get_selection(app->tree_view); // Obtém a seleção da árvore
    if (!gtk_tree_selection_get_selected(selection, &model, &iter))            // Se não houver uma linha selecionada
    {
        create_dialog_error_message("Não é possível remover uma partícula sem uma partícula selecionada."); // Cria uma mensagem de erro
        return;                                                                                             // Termina a função
    }
    // Se houver uma linha selecionada
    gboolean checked;                                                            // Cria uma variável para armazenar o estado do botão de seleção
    gtk_tree_model_get(GTK_TREE_MODEL(app->tree_store), &iter, 7, &checked, -1); // Obtém o estado do botão de seleção
    if (checked)                                                                 // Se a linha selecionada for uma partícula
    {
        app->variables->simulation->num_particles_use--; // Decrementa o número de partículas usadas
    }
    gtk_tree_store_remove(app->tree_store, &iter); // Remove a linha selecionada
}

void on_selection_change_abrir(GtkFileChooser *chooser) // Função chamada quando a seleção do arquivo é alterada no diálogo de abrir
{
    // Essa função serve para habilitar ou desabilitar o botão de seleção do diálogo de abrir, consoante se o arquivo selecionado é válido ou não
    GtkWidget *dialog = GTK_WIDGET(chooser);                                                                // Obtém o widget do diálogo
    GtkWidget *select_button = gtk_dialog_get_widget_for_response(GTK_DIALOG(dialog), GTK_RESPONSE_ACCEPT); // Obtém o botão de seleção

    gchar *filename = gtk_file_chooser_get_filename(chooser);                                                                                                            // Obtém o nome do arquivo selecionado
    gboolean is_valid = filename && g_file_test(filename, G_FILE_TEST_IS_REGULAR) && g_file_test(filename, G_FILE_TEST_EXISTS) && g_str_has_suffix(filename, ".sabino"); // Verifica se o arquivo é válido
    // O arquivo é válido se ele existir, for um arquivo regular e tiver a extensão ".sabino"

    gtk_widget_set_sensitive(select_button, is_valid); // Define se o botão de seleção está habilitado ou não

    if (filename) // Se o nome do arquivo não for nulo
    {
        g_free(filename); // Libera a memória alocada para o nome do arquivo
    }
}

void on_menu_projetos_abrir_activate() // Função chamada quando o item de menu "Abrir" é clicado
{
    if (app->variables->project->is_file_open) // Se já houver um projeto aberto
    {
        create_dialog_error_message("Já existe um projeto aberto, feche-o antes de abrir outro."); // Cria uma mensagem de erro
        return;                                                                                    // Termina a função
    }
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Abrir Arquivo", GTK_WINDOW(app->window_main->window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancelar", GTK_RESPONSE_CANCEL, "_Abrir", GTK_RESPONSE_ACCEPT, NULL); // Cria um diálogo de abrir arquivo
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);                                                                                                                                                              // Define o diálogo como modal (ou seja, ele bloqueia a interação com a janela principal)
    g_signal_connect(G_OBJECT(dialog), "response", G_CALLBACK(gtk_response_projetos_abrir), app);                                                                                                                // Conecta o sinal de resposta do diálogo à função de resposta
    g_signal_connect(G_OBJECT(dialog), "selection-changed", G_CALLBACK(on_selection_change_abrir), NULL);                                                                                                        // Conecta o sinal de mudança de seleção do diálogo à função de mudança de seleção
    gtk_widget_show_all(dialog);                                                                                                                                                                                 // Mostra o diálogo
}

void on_menu_projetos_salvar_activate() // Função chamada quando o item de menu "Salvar" é clicado
{
    if (!app->variables->project->is_file_open) // Se não houver um projeto aberto
    {
        create_dialog_error_message("Não existe um projeto aberto."); // Cria uma mensagem de erro
        return;                                                       // Termina a função
    }
    save_project(); // Salva o projeto
}

void on_menu_projetos_novo_activate() // Função chamada quando o item de menu "Novo" é clicado
{
    if (app->variables->project->is_file_open) // Se já houver um projeto aberto
    {
        create_dialog_error_message("Já existe um projeto aberto, feche-o antes de abrir outro."); // Cria uma mensagem de erro
        return;                                                                                    // Termina a função
    }
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Salvar Arquivo", GTK_WINDOW(app->window_main->window), GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancelar", GTK_RESPONSE_CANCEL, "_Salvar", GTK_RESPONSE_ACCEPT, NULL); // Cria um diálogo de salvar arquivo
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);                                                                                                                                                                // Define o diálogo como modal (ou seja, ele bloqueia a interação com a janela principal)
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);                                                                                                                                // Define que o diálogo deve pedir confirmação para sobrescrever um arquivo
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "andre.sabino");                                                                                                                                   // Define o nome padrão do arquivo
    g_signal_connect(G_OBJECT(dialog), "response", G_CALLBACK(gtk_response_projetos_novo), app);                                                                                                                   // Conecta o sinal de resposta do diálogo à função de resposta
    // Não é necessário conectar o sinal de mudança de seleção do diálogo à função de mudança de seleção, pois o diálogo de salvar arquivo não precisa verificar a validade do arquivo
    gtk_widget_show_all(dialog); // Mostra o diálogo
}

void on_menu_projetos_fechar_activate() // Função chamada quando o item de menu "Fechar" é clicado
{
    if (!app->variables->project->is_file_open) // Se não houver um projeto aberto
    {
        create_dialog_error_message("Não existe um projeto aberto."); // Cria uma mensagem de erro
        return;                                                       // Termina a função
    }
    close_project(); // Fecha o projeto
}

void on_window_main_cinematic_button_clicked(GtkButton *button) // Função chamada quando o botão de simulação cinemática é clicado
{
    if (!app->variables->project->is_file_open) // Se não houver um projeto aberto
    {
        create_dialog_error_message("Não é possível iniciar a simulação sem um projeto aberto."); // Cria uma mensagem de erro
        return;                                                                                   // Termina a função
    }
    if (app->variables->simulation->num_particles_use == 0) // Se não houver partículas selecionadas
    {
        create_dialog_error_message("Não é possível iniciar a simulação sem partículas."); // Cria uma mensagem de erro
        return;                                                                            // Termina a função
    }
    run_simulation_cinematic(); // Executa a simulação cinemática
}

void on_window_main_dynamic_button_clicked(GtkButton *button) // Função chamada quando o botão de simulação dinâmica é clicado
{
    if (!app->variables->project->is_file_open) // Se não houver um projeto aberto
    {
        create_dialog_error_message("Não é possível iniciar a simulação sem um projeto aberto."); // Cria uma mensagem de erro
        return;                                                                                   // Termina a função
    }
    if (app->variables->simulation->num_particles_use == 0) // Se não houver partículas selecionadas
    {
        create_dialog_error_message("Não é possível iniciar a simulação sem partículas."); // Cria uma mensagem de erro
        return;                                                                            // Termina a função
    }
    run_simulation_dynamic(); // Executa a simulação dinâmica
}