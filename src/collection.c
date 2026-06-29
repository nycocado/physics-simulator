#include "collection.h"
#include "app.h"
#include "particles/particle.h"
#include "phys_item.h"
#include "simulation/dynamic_sim.h"
#include <gtk/gtk.h>

void particle_cinematic_collection_start(GtkApp app)
{
    Particle_Cinematic_Collection particle_collection =
        particle_cinematic_collection_new(
            app->variables->simulation.num_particles_use
        );

    guint num_items = g_list_model_get_n_items(G_LIST_MODEL(app->root_store));
    int i = 0;
    for (guint idx = 0; idx < num_items; idx++)
    {
        g_autoptr(PhysItem) item =
            g_list_model_get_item(G_LIST_MODEL(app->root_store), idx);

        if (phys_item_get_checked(item))
        {
            gdouble x = phys_item_get_x(item);
            gdouble y = phys_item_get_y(item);
            gdouble vx = phys_item_get_vx(item);
            gdouble vy = phys_item_get_vy(item);
            gdouble ax = phys_item_get_ax(item);
            gdouble ay = phys_item_get_ay(item);

            Particle_Cinematic particle =
                particle_cinematic_new(x, y, vx, vy, ax, ay);
            particle_collection->particles[i] = particle;
            i++;
        }
    }
    app->variables->simulation.particle_cinematic_collection =
        particle_collection;
}

void particle_dynamic_collection_start(GtkApp app)
{
    Particle_Dynamic_Collection particle_dynamic_collection =
        particle_dynamic_collection_new(
            app->variables->simulation.num_particles_use
        );

    guint num_items = g_list_model_get_n_items(G_LIST_MODEL(app->root_store));
    int i = 0;
    for (guint idx = 0; idx < num_items; idx++)
    {
        g_autoptr(PhysItem) item =
            g_list_model_get_item(G_LIST_MODEL(app->root_store), idx);

        if (phys_item_get_checked(item))
        {
            gdouble x = phys_item_get_x(item);
            gdouble y = phys_item_get_y(item);
            gdouble vx = phys_item_get_vx(item);
            gdouble vy = phys_item_get_vy(item);
            gdouble ax = phys_item_get_ax(item);
            gdouble ay = phys_item_get_ay(item);
            gdouble mass = phys_item_get_mass(item);

            Particle_Dynamic particle =
                particle_dynamic_new(x, y, vx, vy, ax, ay, mass);

            GListModel* children = phys_item_get_children(item);
            guint num_children = g_list_model_get_n_items(children);
            for (guint j = 0; j < num_children; j++)
            {
                g_autoptr(PhysItem) child = g_list_model_get_item(children, j);
                gdouble force_x = phys_item_get_ax(child);
                gdouble force_y = phys_item_get_ay(child);

                Vector* force = g_new(Vector, 1);
                force->x = force_x; force->y = force_y;
                particle->forces = g_list_append(particle->forces, force);
            }
            particle_dynamic_collection->particles[i] = particle;
            i++;
        }
    }
    app->variables->simulation.particle_dynamic_collection =
        particle_dynamic_collection;
}