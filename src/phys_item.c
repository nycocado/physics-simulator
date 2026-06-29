#include "phys_item.h"

struct _PhysItem {
    GObject parent_instance;

    PhysItemType type;
    double x;
    double y;
    double vx;
    double vy;
    double ax;
    double ay;
    double mass;
    gboolean checked;

    GListStore* children;
};

G_DEFINE_TYPE(PhysItem, phys_item, G_TYPE_OBJECT)

enum {
    PROP_0,
    PROP_ITEM_TYPE,
    PROP_X,
    PROP_Y,
    PROP_VX,
    PROP_VY,
    PROP_AX,
    PROP_AY,
    PROP_MASS,
    PROP_CHECKED,
    PROP_CHILDREN,
    N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

static void phys_item_set_property(GObject* object, guint property_id, const GValue* value, GParamSpec* pspec)
{
    PhysItem* self = PHYS_ITEM(object);

    switch (property_id) {
        case PROP_ITEM_TYPE:
            self->type = g_value_get_int(value);
            break;
        case PROP_X:
            self->x = g_value_get_double(value);
            break;
        case PROP_Y:
            self->y = g_value_get_double(value);
            break;
        case PROP_VX:
            self->vx = g_value_get_double(value);
            break;
        case PROP_VY:
            self->vy = g_value_get_double(value);
            break;
        case PROP_AX:
            self->ax = g_value_get_double(value);
            break;
        case PROP_AY:
            self->ay = g_value_get_double(value);
            break;
        case PROP_MASS:
            self->mass = g_value_get_double(value);
            break;
        case PROP_CHECKED:
            self->checked = g_value_get_boolean(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void phys_item_get_property(GObject* object, guint property_id, GValue* value, GParamSpec* pspec)
{
    PhysItem* self = PHYS_ITEM(object);

    switch (property_id) {
        case PROP_ITEM_TYPE:
            g_value_set_int(value, self->type);
            break;
        case PROP_X:
            g_value_set_double(value, self->x);
            break;
        case PROP_Y:
            g_value_set_double(value, self->y);
            break;
        case PROP_VX:
            g_value_set_double(value, self->vx);
            break;
        case PROP_VY:
            g_value_set_double(value, self->vy);
            break;
        case PROP_AX:
            g_value_set_double(value, self->ax);
            break;
        case PROP_AY:
            g_value_set_double(value, self->ay);
            break;
        case PROP_MASS:
            g_value_set_double(value, self->mass);
            break;
        case PROP_CHECKED:
            g_value_set_boolean(value, self->checked);
            break;
        case PROP_CHILDREN:
            g_value_set_object(value, self->children);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void phys_item_dispose(GObject* object)
{
    PhysItem* self = PHYS_ITEM(object);

    g_clear_object(&self->children);

    G_OBJECT_CLASS(phys_item_parent_class)->dispose(object);
}

static void phys_item_class_init(PhysItemClass* klass)
{
    GObjectClass* gobject_class = G_OBJECT_CLASS(klass);

    gobject_class->set_property = phys_item_set_property;
    gobject_class->get_property = phys_item_get_property;
    gobject_class->dispose = phys_item_dispose;

    obj_properties[PROP_ITEM_TYPE] = g_param_spec_int(
        "item-type", "Item Type", "Item Type",
        PHYS_ITEM_PARTICLE, PHYS_ITEM_FORCE, PHYS_ITEM_PARTICLE,
        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS
    );

    obj_properties[PROP_X] = g_param_spec_double(
        "x", "X", "X",
        -G_MAXDOUBLE, G_MAXDOUBLE, 0.0,
        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS
    );

    obj_properties[PROP_Y] = g_param_spec_double(
        "y", "Y", "Y",
        -G_MAXDOUBLE, G_MAXDOUBLE, 0.0,
        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS
    );

    obj_properties[PROP_VX] = g_param_spec_double(
        "vx", "VX", "VX",
        -G_MAXDOUBLE, G_MAXDOUBLE, 0.0,
        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS
    );

    obj_properties[PROP_VY] = g_param_spec_double(
        "vy", "VY", "VY",
        -G_MAXDOUBLE, G_MAXDOUBLE, 0.0,
        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS
    );

    obj_properties[PROP_AX] = g_param_spec_double(
        "ax", "AX", "AX",
        -G_MAXDOUBLE, G_MAXDOUBLE, 0.0,
        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS
    );

    obj_properties[PROP_AY] = g_param_spec_double(
        "ay", "AY", "AY",
        -G_MAXDOUBLE, G_MAXDOUBLE, 0.0,
        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS
    );

    obj_properties[PROP_MASS] = g_param_spec_double(
        "mass", "Mass", "Mass",
        -G_MAXDOUBLE, G_MAXDOUBLE, 0.0,
        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS
    );

    obj_properties[PROP_CHECKED] = g_param_spec_boolean(
        "checked", "Checked", "Checked",
        FALSE,
        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS
    );

    obj_properties[PROP_CHILDREN] = g_param_spec_object(
        "children", "Children", "Children",
        G_TYPE_LIST_MODEL,
        G_PARAM_READABLE | G_PARAM_STATIC_STRINGS
    );

    g_object_class_install_properties(gobject_class, N_PROPERTIES, obj_properties);
}

static void phys_item_init(PhysItem* self)
{
    self->children = g_list_store_new(PHYS_TYPE_ITEM);
}

PhysItem* phys_item_new_particle(
    double x, double y, double vx, double vy, double ax, double ay, double mass, gboolean checked
)
{
    return g_object_new(
        PHYS_TYPE_ITEM,
        "item-type", PHYS_ITEM_PARTICLE,
        "x", x,
        "y", y,
        "vx", vx,
        "vy", vy,
        "ax", ax,
        "ay", ay,
        "mass", mass,
        "checked", checked,
        NULL
    );
}

PhysItem* phys_item_new_force(
    double ax, double ay
)
{
    return g_object_new(
        PHYS_TYPE_ITEM,
        "item-type", PHYS_ITEM_FORCE,
        "ax", ax,
        "ay", ay,
        NULL
    );
}

PhysItemType phys_item_get_item_type(PhysItem* item) { return item->type; }

double phys_item_get_x(PhysItem* item) { return item->x; }
void phys_item_set_x(PhysItem* item, double val) {
    if (item->x == val) return;
    item->x = val;
    g_object_notify_by_pspec(G_OBJECT(item), obj_properties[PROP_X]);
}

double phys_item_get_y(PhysItem* item) { return item->y; }
void phys_item_set_y(PhysItem* item, double val) {
    if (item->y == val) return;
    item->y = val;
    g_object_notify_by_pspec(G_OBJECT(item), obj_properties[PROP_Y]);
}

double phys_item_get_vx(PhysItem* item) { return item->vx; }
void phys_item_set_vx(PhysItem* item, double val) {
    if (item->vx == val) return;
    item->vx = val;
    g_object_notify_by_pspec(G_OBJECT(item), obj_properties[PROP_VX]);
}

double phys_item_get_vy(PhysItem* item) { return item->vy; }
void phys_item_set_vy(PhysItem* item, double val) {
    if (item->vy == val) return;
    item->vy = val;
    g_object_notify_by_pspec(G_OBJECT(item), obj_properties[PROP_VY]);
}

double phys_item_get_ax(PhysItem* item) { return item->ax; }
void phys_item_set_ax(PhysItem* item, double val) {
    if (item->ax == val) return;
    item->ax = val;
    g_object_notify_by_pspec(G_OBJECT(item), obj_properties[PROP_AX]);
}

double phys_item_get_ay(PhysItem* item) { return item->ay; }
void phys_item_set_ay(PhysItem* item, double val) {
    if (item->ay == val) return;
    item->ay = val;
    g_object_notify_by_pspec(G_OBJECT(item), obj_properties[PROP_AY]);
}

double phys_item_get_mass(PhysItem* item) { return item->mass; }
void phys_item_set_mass(PhysItem* item, double val) {
    if (item->mass == val) return;
    item->mass = val;
    g_object_notify_by_pspec(G_OBJECT(item), obj_properties[PROP_MASS]);
}

gboolean phys_item_get_checked(PhysItem* item) { return item->checked; }
void phys_item_set_checked(PhysItem* item, gboolean val) {
    if (item->checked == val) return;
    item->checked = val;
    g_object_notify_by_pspec(G_OBJECT(item), obj_properties[PROP_CHECKED]);
}

GListModel* phys_item_get_children(PhysItem* item) {
    return G_LIST_MODEL(item->children);
}

void phys_item_add_child(PhysItem* item, PhysItem* child) {
    g_list_store_append(item->children, child);
}

void phys_item_remove_child(PhysItem* item, PhysItem* child) {
    guint n_items = g_list_model_get_n_items(G_LIST_MODEL(item->children));
    for (guint i = 0; i < n_items; i++) {
        g_autoptr(PhysItem) current = g_list_model_get_item(G_LIST_MODEL(item->children), i);
        if (current == child) {
            g_list_store_remove(item->children, i);
            break;
        }
    }
}

void phys_item_clear_children(PhysItem* item) {
    g_list_store_remove_all(item->children);
}
