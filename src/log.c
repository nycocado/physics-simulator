#include "log.h"
#include "app.h"
#include "collection.h"
#include "particles/particle.h"
#include "physics/dynamics.h"
#include "physics/kinematics.h"
#include "project.h"
#include "simulation/dynamic_sim.h"
#include "ui/builder.h"
#include <gtk/gtk.h>
#include <stdio.h>

char* generate_log_name_for_simulation(const char* base_name, GtkApp app)
{
    int index = 1;
    gchar* filename = NULL;
    gchar* path = g_path_get_dirname(app->variables->project.file_path);
    gchar* new_path = NULL;
    gboolean exists;
    do
    {
        filename = g_strdup_printf("%s_%d.csv", base_name, index);
        new_path = g_build_filename(path, filename, NULL);
        exists = g_file_test(new_path, G_FILE_TEST_EXISTS);
        if (exists)
        {
            g_free(filename);
            g_free(new_path);
        }
        index++;
    } while (exists);

    g_free(filename);
    g_free(path);
    return new_path;
}

void save_simulation_cinematic_log(
    Particle_Cinematic_Collection particle_collection,
    double time,
    double time_step,
    double gravity,
    GtkApp app
)
{
    gchar* filename =
        generate_log_name_for_simulation("simulacao_cinematica", app);
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        create_dialog_error_message("Erro ao salvar o log da simulação", app);
        return;
    }

    fprintf(file, "\"Simulacao Cinematica\"\n");
    fprintf(
        file,
        "\"Tempo Total: %.2f - Passos de Tempo: %.2f - Gravidade: %.2f\"\n",
        time,
        time_step,
        gravity
    );
    fprintf(file, "\n");
    fprintf(
        file, "Particula;t;x;y;vx;vy;v;v angle;ax;ay;a;a angle;deslocamento\n"
    );

    for (int i = 0; i < app->variables->simulation.num_particles_use; i++)
    {
        Particle_Cinematic particle = particle_collection->particles[i];

        double xi = particle->position_i->x;
        double yi = particle->position_i->y;
        double vxi = particle->velocity_i->x;
        double vyi = particle->velocity_i->y;
        double ax = particle->acceleration->x;
        double ay = particle->acceleration->y;
        double g = gravity;
        for (double t = 0; t <= time; t += time_step)
        {
            double x = phyc_position(xi, vxi, ax, t);
            double y = phyc_position(yi, vyi, ay - g, t);
            double vx = phyc_velocity(vxi, ax, t);
            double vy = phyc_velocity(vyi, ay - g, t);
            double v = phyc_magnitude_velocity(vx, vy);
            double v_angle = phyc_radian_to_degree(phyc_angle(vx, vy));
            double a = phyc_magnitude_acceleration(ax, ay);
            double a_angle = phyc_radian_to_degree(phyc_angle(ax, ay));
            double deslocamento = phyc_displacement_x_y(xi, x, yi, y);

            gchar* line = g_strdup_printf(
                "%d;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%."
                "2f",
                i,
                t,
                x,
                y,
                vx,
                vy,
                v,
                v_angle,
                ax,
                ay,
                a,
                a_angle,
                deslocamento
            );
            g_strdelimit(line, ".", ',');
            fprintf(file, "%s\n", line);
            g_free(line);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

static int
calc_num_forces_max(Particle_Dynamic_Collection particle_collection, GtkApp app)
{
    int max_forces = 0;
    for (int i = 0; i < app->variables->simulation.num_particles_use; i++)
    {
        Particle_Dynamic particle = particle_collection->particles[i];
        int num_forces = g_list_length(particle->forces);
        if (num_forces > max_forces)
        {
            max_forces = num_forces;
        }
    }
    return max_forces;
}

void save_simulation_dynamic_log(
    Particle_Dynamic_Collection particle_collection,
    double time,
    double time_step,
    double gravity,
    GtkApp app
)
{
    gchar* filename =
        generate_log_name_for_simulation("simulacao_dinamica", app);
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        create_dialog_error_message("Erro ao salvar o log da simulação", app);
        return;
    }

    fprintf(file, "\"Simulacao Dinamica\"\n");
    fprintf(
        file,
        "\"Tempo Total: %.2f - Passos de Tempo: %.2f - Gravidade: %.2f\"\n",
        time,
        time_step,
        gravity
    );
    fprintf(file, "\n");
    fprintf(file, "Particula;t;x;y;vx;vy;v;v angle;ax;ay;a;a angle;m;");

    int max_forces = calc_num_forces_max(particle_collection, app);
    for (int i = 1; i <= max_forces; i++)
    {
        fprintf(file, "fx%d;fy%d;f%d;f%d angle;", i, i, i, i);
    }
    fprintf(file, "frx;fry;fr;fr angle\n");

    for (int i = 0; i < app->variables->simulation.num_particles_use; i++)
    {
        Particle_Dynamic particle = particle_collection->particles[i];

        double xi = particle->position_i->x;
        double yi = particle->position_i->y;
        double vxi = particle->velocity_i->x;
        double vyi = particle->velocity_i->y;
        double ax = particle->acceleration->x;
        double ay = particle->acceleration->y;
        double m = particle->mass;
        double g = gravity;

        for (double t = 0; t <= time; t += time_step)
        {
            double x = phyc_position(xi, vxi, ax, t);
            double y = phyc_position(yi, vyi, ay, t);
            double vx = phyc_velocity(vxi, ax, t);
            double vy = phyc_velocity(vyi, ay, t);
            double v = phyc_magnitude_velocity(vx, vy);
            double v_angle = phyc_radian_to_degree(phyc_angle(vx, vy));
            double a = phyc_magnitude_acceleration(ax, ay);
            double a_angle = phyc_radian_to_degree(phyc_angle(ax, ay));
            double frx = 0;
            double fry = -phyd_force_p(m, g);

            GString* line = g_string_new("");
            g_string_printf(
                line,
                "%d;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%."
                "2f;",
                i,
                t,
                x,
                y,
                vx,
                vy,
                v,
                v_angle,
                ax,
                ay,
                a,
                a_angle,
                m
            );
            GList* forces = particle->forces;
            for (GList* l = forces; l != NULL; l = l->next)
            {
                Vector force = l->data;
                double fx = force->x;
                double fy = force->y;
                frx += fx;
                fry += fy;
                g_string_append_printf(
                    line,
                    "%.2f;%.2f;%.2f;%.2f;",
                    fx,
                    fy,
                    phyc_magnitude(fx, fy),
                    phyc_radian_to_degree(phyc_angle(fx, fy))
                );
            }

            for (int k = g_list_length(forces); k < max_forces; k++)
            {
                g_string_append(line, "0.00;0.00;0.00;0.00;");
            }
            g_string_append_printf(
                line,
                "%.2f;%.2f;%.2f;%.2f",
                frx,
                fry,
                phyc_magnitude_velocity(frx, fry),
                phyc_radian_to_degree(phyc_angle(frx, fry))
            );
            g_strdelimit(line->str, ".", ',');
            fprintf(file, "%s\n", line->str);
            g_string_free(line, TRUE);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}