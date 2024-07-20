#include "../include/gtk_include_all.h"

char *generate_log_name_for_simulation(const char *base_name) // Função de gerar o nome do log da simulação
{
    int index = 1;                                                        // Declara o índice
    gchar *filename = NULL;                                               // Declara o nome do arquivo
    gchar *path = g_path_get_dirname(app->variables->project->file_path); // Obtém o diretório do projeto
    gchar *new_path = NULL;                                               // Declara o novo caminho
    FILE *file;                                                           // Declara o arquivo

    do
    {
        filename = g_strdup_printf("%s_%d.csv", base_name, index); // Gera o nome do arquivo
        new_path = g_build_filename(path, filename, NULL);         // Gera o caminho do arquivo
        file = fopen(new_path, "r");                               // Abre o arquivo
        if (file != NULL)                                          // Verifica se o arquivo foi aberto
        {
            fclose(file); // Fecha o arquivo
            // Libera a memória do nome do arquivo e do caminho
            g_free(filename);
            g_free(new_path);
        }
        index++; // Incrementa o índice
    } while (file != NULL); // Repete enquanto o arquivo existir

    g_free(filename); // Libera a memória do nome do arquivo
    g_free(path);     // Libera a memória do diretório
    return new_path;  // Retorna o caminho do arquivo
}

void replace_dot_with_comma(char *str) // Função de substituir ponto por vírgula
{
    for (char *p = str; *p != '\0'; p++) // Itera sobre a string
    {
        if (*p == '.') // Verifica se é um ponto
        {
            *p = ','; // Substitui por vírgula
        }
    }
}

void save_simulation_cinematic_log(Particle_Cinematic_Collection particle_collection, float time, float time_step, float gravity) // Função de salvar o log da simulação cinemática
{
    gchar *filename = generate_log_name_for_simulation("simulacao_cinematica"); // Gera o nome do arquivo
    FILE *file = fopen(filename, "w");                                          // Abre o arquivo
    if (file == NULL)                                                           // Verifica se o arquivo foi aberto corretamente
    {
        create_dialog_error_message("Erro ao salvar o log da simulação"); // Cria uma mensagem de erro
        return;                                                           // Termina a função
    }
    // Cabeçalho
    fprintf(file, "\"Simulacao Cinematica\"\n");                                                                  // Escreve o tipo de simulação
    fprintf(file, "\"Tempo Total: %.2f - Passos de Tempo: %.2f - Gravidade: %.2f\"\n", time, time_step, gravity); // Escreve as informações da simulação
    fprintf(file, "\n");                                                                                          // Pula uma linha
    fprintf(file, "Particula;t;x;y;vx;vy;v;v angle;ax;ay;a;a angle;deslocamento\n");                              // Escreve o cabeçalho

    for (int i = 0; i < app->variables->simulation->num_particles_use; i++) // Itera sobre as partículas
    {
        Particle_Cinematic particle = particle_collection->particles[i]; // Obtém a partícula
        // Obtém as variáveis da partícula
        float xi = particle->position_i->x;
        float yi = particle->position_i->y;
        float vxi = particle->velocity_i->x;
        float vyi = particle->velocity_i->y;
        float ax = particle->acceleration->x;
        float ay = particle->acceleration->y;
        float g = gravity;
        for (float t = 0; t <= time; t += time_step) // Faz calculos para cada passo de tempo
        {
            float x = phyc_position(xi, vxi, ax, t);                   // Calcula a posição x
            float y = phyc_position(yi, vyi, ay - g, t);               // Calcula a posição y
            float vx = phyc_velocity(vxi, ax, t);                      // Calcula a velocidade x
            float vy = phyc_velocity(vyi, ay - g, t);                  // Calcula a velocidade y
            float v = phyc_magnitude_velocity(vx, vy);                 // Calcula a magnitude da velocidade
            float v_angle = phyc_radian_to_degree(phyc_angle(vx, vy)); // Calcula o ângulo da velocidade em graus
            float a = phyc_magnitude_acceleration(ax, ay);             // Calcula a magnitude da aceleração
            float a_angle = phyc_radian_to_degree(phyc_angle(ax, ay)); // Calcula o ângulo da aceleração em graus
            float deslocamento = phyc_displacement_x_y(xi, x, yi, y);  // Calcula o deslocamento

            gchar *line = g_strdup_printf("%d;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f", i, t, x, y, vx, vy, v, v_angle, ax, ay, a, a_angle, deslocamento); // Gera a linha
            replace_dot_with_comma(line);                                                                                                                                      // Substitui o ponto por vírgula
            fprintf(file, "%s\n", line);                                                                                                                                       // Escreve a linha no arquivo
            g_free(line);                                                                                                                                                      // Libera a memória da linha
        }
        fprintf(file, "\n"); // Pula uma linha
    }
    fclose(file); // Fecha o arquivo
}

int calc_num_forces_max(Particle_Dynamic_Collection particle_collection) // Função de calcular o número total de forças
{
    int max_forces = 0;                                                     // Declara o número total de forças
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++) // Itera sobre as partículas
    {
        Particle_Dynamic particle = particle_collection->particles[i]; // Obtém a partícula
        int num_forces = g_list_length(particle->forces);              // Calcula o número de forças
        if (num_forces > max_forces)                                   // Verifica se o número de forças é maior que o máximo
        {
            max_forces = num_forces; // Atualiza o máximo
        }
    }
    return max_forces; // Retorna o número total de forças
}

void save_simulation_dynamic_log(Particle_Dynamic_Collection particle_collection, float time, float time_step, float gravity) // Função de salvar o log da simulação dinâmica
{
    gchar *filename = generate_log_name_for_simulation("simulacao_dinamica"); // Gera o nome do arquivo
    FILE *file = fopen(filename, "w");                                        // Abre o arquivo
    if (file == NULL)                                                         // Verifica se o arquivo foi aberto corretamente
    {
        create_dialog_error_message("Erro ao salvar o log da simulação"); // Cria uma mensagem de erro
        return;                                                           // Termina a função
    }

    // Cabeçalho
    fprintf(file, "\"Simulacao Dinamica\"\n");                                                                    // Escreve o tipo de simulação
    fprintf(file, "\"Tempo Total: %.2f - Passos de Tempo: %.2f - Gravidade: %.2f\"\n", time, time_step, gravity); // Escreve as informações da simulação
    fprintf(file, "\n");                                                                                          // Pula uma linha
    fprintf(file, "Particula;t;x;y;vx;vy;v;v angle;ax;ay;a;a angle;m;");                                          // Escreve o cabeçalho

    // Calcular o número total de forças para o cabeçalho
    int max_forces = calc_num_forces_max(particle_collection);
    for (int i = 1; i <= max_forces; i++) // Itera sobre o número total de forças
    {
        fprintf(file, "fx%d;fy%d;f%d;f%d angle;", i, i, i, i); // Escreve o cabeçalho das forças
    }
    fprintf(file, "frx;fry;fr;fr angle\n"); // Escreve o cabeçalho da força resultante

    for (int i = 0; i < app->variables->simulation->num_particles_use; i++) // Itera sobre as partículas
    {
        Particle_Dynamic particle = particle_collection->particles[i]; // Obtém a partícula
        // Obtém as variáveis da partícula
        float xi = particle->position_i->x;
        float yi = particle->position_i->y;
        float vxi = particle->velocity_i->x;
        float vyi = particle->velocity_i->y;
        float ax = particle->acceleration->x;
        float ay = particle->acceleration->y;
        float m = particle->mass;
        float g = gravity;

        for (float t = 0; t <= time; t += time_step) // Faz calculos para cada passo de tempo
        {
            float x = phyc_position(xi, vxi, ax, t);                   // Calcula a posição x
            float y = phyc_position(yi, vyi, ay - g, t);               // Calcula a posição y
            float vx = phyc_velocity(vxi, ax, t);                      // Calcula a velocidade x
            float vy = phyc_velocity(vyi, ay - g, t);                  // Calcula a velocidade y
            float v = phyc_magnitude_velocity(vx, vy);                 // Calcula a magnitude da velocidade
            float v_angle = phyc_radian_to_degree(phyc_angle(vx, vy)); // Calcula o ângulo da velocidade em graus
            float a = phyc_magnitude_acceleration(ax, ay);             // Calcula a magnitude da aceleração
            float a_angle = phyc_radian_to_degree(phyc_angle(ax, ay)); // Calcula o ângulo da aceleração em graus
            float frx = 0;                                             // Inicializa a força resultante x
            float fry = -phyd_force_p(m, g);                           // Calcula a força resultante y

            gchar *line = g_strdup_printf("%d;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;", i, t, x, y, vx, vy, v, v_angle, ax, ay, a, a_angle, m); // Gera a linha
            GList *forces = particle->forces;                                                                                                                        // Obtém a lista de forças
            for (GList *l = forces; l != NULL; l = l->next)                                                                                                          // Percorre a lista de forças
            {
                Vector force = l->data;                                                                                                                 // Obtém a força
                float fx = force->x;                                                                                                                    // Obtém a força x
                float fy = force->y;                                                                                                                    // Obtém a força y
                frx += fx;                                                                                                                              // Atualiza a força resultante x
                fry += fy;                                                                                                                              // Atualiza a força resultante y
                gchar *force_line = g_strdup_printf("%.2f;%.2f;%.2f;%.2f;", fx, fy, phyc_magnitude(fx, fy), phyc_radian_to_degree(phyc_angle(fx, fy))); // Gera a linha da força
                gchar *new_line = g_strconcat(line, force_line, NULL);                                                                                  // Concatena as linhas
                g_free(line);                                                                                                                           // Libera a memória da linha
                g_free(force_line);                                                                                                                     // Libera a memória da linha da força
                line = new_line;                                                                                                                        // Atualiza a linha
            }
            // Adicionar zeros para forças ausentes
            for (int k = g_list_length(forces); k < max_forces; k++) // Itera sobre as forças ausentes
            {
                gchar *force_line = g_strdup_printf("0.00;0.00;0.00;0.00;"); // Gera a linha da força
                gchar *new_line = g_strconcat(line, force_line, NULL);       // Concatena as linhas
                g_free(line);                                                // Libera a memória da linha
                g_free(force_line);                                          // Libera a memória da linha da força
                line = new_line;                                             // Atualiza a linha
            }
            gchar *force_result_line = g_strdup_printf("%.2f;%.2f;%.2f;%.2f", frx, fry, phyc_magnitude_velocity(frx, fry), phyc_radian_to_degree(phyc_angle(frx, fry))); // Gera a linha da força resultante
            gchar *new_line = g_strconcat(line, force_result_line, NULL);                                                                                                // Concatena as linhas (LINHA FINAL)
            replace_dot_with_comma(new_line);                                                                                                                            // Substitui o ponto por vírgula
            fprintf(file, "%s\n", new_line);                                                                                                                             // Escreve a linha no arquivo
            g_free(force_result_line);                                                                                                                                   // Libera a memória da linha da força resultante
            g_free(new_line);                                                                                                                                            // Libera a memória da linha
            g_free(line);                                                                                                                                                // Libera a memória da linha
        }
        fprintf(file, "\n"); // Pula uma linha
    }
    fclose(file); // Fecha o arquivo
}