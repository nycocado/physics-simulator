#include "../include/gtk_include_all.h"

char* generate_log_name_for_simulation(const char* base_name)
{
    int index = 1;
    gchar* filename = NULL;
    gchar* path = g_path_get_dirname(app->variables->project->file_path);
    gchar* new_path = NULL;
    FILE* file;

    do
    {
        filename = g_strdup_printf("%s_%d.csv", base_name, index);
        new_path = g_build_filename(path, filename, NULL);
        file = fopen(new_path, "r");
        if (file != NULL)
        {
            fclose(file);

            g_free(filename);
            g_free(new_path);
        }
        index++;
    } while (file != NULL);

    g_free(filename);
    g_free(path);
    return new_path;
}

void replace_dot_with_comma(char* str)
{
    for (char* p = str; *p != '\0'; p++)
    {
        if (*p == '.')
        {
            *p = ',';
        }
    }
}

void save_simulation_cinematic_log(
    Particle_Cinematic_Collection particle_collection,
    float time,
    float time_step,
    float gravity
)
{
    gchar* filename = generate_log_name_for_simulation("simulacao_cinematica");
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        create_dialog_error_message("Erro ao salvar o log da simulação");
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

    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)
    {
        Particle_Cinematic particle = particle_collection->particles[i];

        float xi = particle->position_i->x;
        float yi = particle->position_i->y;
        float vxi = particle->velocity_i->x;
        float vyi = particle->velocity_i->y;
        float ax = particle->acceleration->x;
        float ay = particle->acceleration->y;
        float g = gravity;
        for (float t = 0; t <= time; t += time_step)
        {
            float x = phyc_position(xi, vxi, ax, t);
            float y = phyc_position(yi, vyi, ay - g, t);
            float vx = phyc_velocity(vxi, ax, t);
            float vy = phyc_velocity(vyi, ay - g, t);
            float v = phyc_magnitude_velocity(vx, vy);
            float v_angle = phyc_radian_to_degree(phyc_angle(vx, vy));
            float a = phyc_magnitude_acceleration(ax, ay);
            float a_angle = phyc_radian_to_degree(phyc_angle(ax, ay));
            float deslocamento = phyc_displacement_x_y(xi, x, yi, y);

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
            replace_dot_with_comma(line);
            fprintf(file, "%s\n", line);
            g_free(line);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int calc_num_forces_max(Particle_Dynamic_Collection particle_collection)
{
    int max_forces = 0;
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)
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
    float time,
    float time_step,
    float gravity
)
{
    gchar* filename = generate_log_name_for_simulation("simulacao_dinamica");
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        create_dialog_error_message("Erro ao salvar o log da simulação");
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

    int max_forces = calc_num_forces_max(particle_collection);
    for (int i = 1; i <= max_forces; i++)
    {
        fprintf(file, "fx%d;fy%d;f%d;f%d angle;", i, i, i, i);
    }
    fprintf(file, "frx;fry;fr;fr angle\n");

    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)
    {
        Particle_Dynamic particle = particle_collection->particles[i];

        float xi = particle->position_i->x;
        float yi = particle->position_i->y;
        float vxi = particle->velocity_i->x;
        float vyi = particle->velocity_i->y;
        float ax = particle->acceleration->x;
        float ay = particle->acceleration->y;
        float m = particle->mass;
        float g = gravity;

        for (float t = 0; t <= time; t += time_step)
        {
            float x = phyc_position(xi, vxi, ax, t);
            float y = phyc_position(yi, vyi, ay - g, t);
            float vx = phyc_velocity(vxi, ax, t);
            float vy = phyc_velocity(vyi, ay - g, t);
            float v = phyc_magnitude_velocity(vx, vy);
            float v_angle = phyc_radian_to_degree(phyc_angle(vx, vy));
            float a = phyc_magnitude_acceleration(ax, ay);
            float a_angle = phyc_radian_to_degree(phyc_angle(ax, ay));
            float frx = 0;
            float fry = -phyd_force_p(m, g);

            gchar* line = g_strdup_printf(
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
                float fx = force->x;
                float fy = force->y;
                frx += fx;
                fry += fy;
                gchar* force_line = g_strdup_printf(
                    "%.2f;%.2f;%.2f;%.2f;",
                    fx,
                    fy,
                    phyc_magnitude(fx, fy),
                    phyc_radian_to_degree(phyc_angle(fx, fy))
                );
                gchar* new_line = g_strconcat(line, force_line, NULL);
                g_free(line);
                g_free(force_line);
                line = new_line;
            }

            for (int k = g_list_length(forces); k < max_forces; k++)
            {
                gchar* force_line = g_strdup_printf("0.00;0.00;0.00;0.00;");
                gchar* new_line = g_strconcat(line, force_line, NULL);
                g_free(line);
                g_free(force_line);
                line = new_line;
            }
            gchar* force_result_line = g_strdup_printf(
                "%.2f;%.2f;%.2f;%.2f",
                frx,
                fry,
                phyc_magnitude_velocity(frx, fry),
                phyc_radian_to_degree(phyc_angle(frx, fry))
            );
            gchar* new_line = g_strconcat(line, force_result_line, NULL);
            replace_dot_with_comma(new_line);
            fprintf(file, "%s\n", new_line);
            g_free(force_result_line);
            g_free(new_line);
            g_free(line);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}