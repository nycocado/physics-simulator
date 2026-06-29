#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PHYS_TYPE_ITEM phys_item_get_type()

G_DECLARE_FINAL_TYPE(PhysItem, phys_item, PHYS, ITEM, GObject)

typedef struct _PhysItem PhysItem;
typedef enum
{
    PHYS_ITEM_PARTICLE = 0,
    PHYS_ITEM_FORCE = 1
} PhysItemType;

PhysItem* phys_item_new_particle(
    double x,
    double y,
    double vx,
    double vy,
    double ax,
    double ay,
    double mass,
    gboolean checked
);

PhysItem* phys_item_new_force(double ax, double ay);

PhysItemType phys_item_get_item_type(PhysItem* item);

double phys_item_get_x(PhysItem* item);
void phys_item_set_x(PhysItem* item, double val);

double phys_item_get_y(PhysItem* item);
void phys_item_set_y(PhysItem* item, double val);

double phys_item_get_vx(PhysItem* item);
void phys_item_set_vx(PhysItem* item, double val);

double phys_item_get_vy(PhysItem* item);
void phys_item_set_vy(PhysItem* item, double val);

double phys_item_get_ax(PhysItem* item);
void phys_item_set_ax(PhysItem* item, double val);

double phys_item_get_ay(PhysItem* item);
void phys_item_set_ay(PhysItem* item, double val);

double phys_item_get_mass(PhysItem* item);
void phys_item_set_mass(PhysItem* item, double val);

gboolean phys_item_get_checked(PhysItem* item);
void phys_item_set_checked(PhysItem* item, gboolean val);

GListModel* phys_item_get_children(PhysItem* item);
void phys_item_add_child(PhysItem* item, PhysItem* child);
void phys_item_remove_child(PhysItem* item, PhysItem* child);
void phys_item_clear_children(PhysItem* item);

G_END_DECLS
