#include "../include/gtk_include_all.h"

void save_project() // Função de salvar o projeto
{
    FILE *file = fopen(app->variables->project->file_path, "w"); // Abre o arquivo do projeto
    if (file == NULL)                                            // Verifica se o arquivo foi aberto corretamente
    {
        create_dialog_error_message("Erro ao salvar o projeto"); // Cria uma mensagem de erro
        return;                                                  // Termina a função
    }
    // Se o arquivo foi aberto corretamente, escreve as informações das partículas e forças no arquivo
    GtkTreeIter iter;                                                                       // Declara a iteração da árvore
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(app->tree_store), &iter); // Verifica se a iteração é válida (se existe algum elemento)
    while (valid)                                                                           // Se for válida
    {
        gchar *x, *y, *vx, *vy, *ax, *ay, *mass;                                                                                // Declara as variáveis de texto
        gtk_tree_model_get(GTK_TREE_MODEL(app->tree_store), &iter, 0, &x, 1, &y, 2, &vx, 3, &vy, 4, &ax, 5, &ay, 6, &mass, -1); // Obtém os valores da árvore
        fprintf(file, "Partícula %s %s %s %s %s %s %s\n", x, y, vx, vy, ax, ay, mass);                                          // Escreve as informações da partícula no arquivo
        // Libera a memória das variáveis de texto
        g_free(x);
        g_free(y);
        g_free(vx);
        g_free(vy);
        g_free(ax);
        g_free(ay);
        g_free(mass);
        // Verifica se a partícula tem forças
        GtkTreeIter childIter;
        if (gtk_tree_model_iter_children(GTK_TREE_MODEL(app->tree_store), &childIter, &iter)) // Verifica se a partícula tem forças
        {
            do // Se tiver forças (usamos o do while porque ja sabemos que tem pelo menos uma força, então pode executar pelo menos uma vez)
            {
                gchar *fx, *fy;                                                                      // Declara as variáveis de texto
                gtk_tree_model_get(GTK_TREE_MODEL(app->tree_store), &childIter, 0, &fx, 1, &fy, -1); // Obtém os valores da árvore
                fprintf(file, "Força %s %s\n", fx, fy);                                              // Escreve as informações da força no arquivo
                // Libera a memória das variáveis de texto
                g_free(fx);
                g_free(fy);
            } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(app->tree_store), &childIter)); // Itera sobre as forças
        }
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(app->tree_store), &iter); // Itera sobre as partículas
    }
    fclose(file); // Fecha o arquivo
}

void open_project() // Função de abrir o projeto
{
    FILE *file = fopen(app->variables->project->file_path, "r"); // Abre o arquivo do projeto
    if (file == NULL)                                            // Verifica se o arquivo foi aberto corretamente
    {
        create_dialog_error_message("Erro ao abrir o projeto"); // Cria uma mensagem de erro
        return;                                                 // Termina a função
    }
    char *line = NULL;                       // Declara a linha do arquivo
    size_t len = 0;                          // Declara o tamanho da linha
    while (getline(&line, &len, file) != -1) // Lê o arquivo linha por linha
    {
        char *type, *x, *y, *vx, *vy, *ax, *ay, *mass; // Declara as variáveis de texto
        line[strlen(line) - 1] = '\0';                 // Remove o \n do final da linha
        // Separa a linha em partes
        type = strtok(line, " ");           // Recebe o tipo
        x = strtok(NULL, " ");              // Recebe a posição x
        y = strtok(NULL, " ");              // Recebe a posição y
        vx = strtok(NULL, " ");             // Recebe a velocidade x
        vy = strtok(NULL, " ");             // Recebe a velocidade y
        ax = strtok(NULL, " ");             // Recebe a aceleração x
        ay = strtok(NULL, " ");             // Recebe a aceleração y
        mass = strtok(NULL, " ");           // Recebe a massa
        GtkTreeIter iter, childIter;        // Declara a iteração da árvore
        if (strcmp(type, "Partícula") == 0) // Verifica se é uma partícula
        {
            gtk_tree_store_append(app->tree_store, &iter, NULL);                                                                        // Adiciona uma partícula na árvore
            gtk_tree_store_set(app->tree_store, &iter, 0, x, 1, y, 2, vx, 3, vy, 4, ax, 5, ay, 6, mass, 7, TRUE, 8, TRUE, 9, type, -1); // Define os valores da partícula
            app->variables->simulation->num_particles_use++;                                                                            // Incrementa o número de partículas
        }
        else if (strcmp(type, "Força") == 0) // Verifica se é uma força
        {
            gtk_tree_store_append(app->tree_store, &childIter, &iter);                                    // Adiciona uma força na árvore
            gtk_tree_store_set(app->tree_store, &childIter, 0, x, 1, y, 7, FALSE, 8, FALSE, 9, type, -1); // Define os valores da força
        }
    }
    fclose(file); // Fecha o arquivo
}

void close_project() // Função de fechar o projeto
{
    variables_project_wipe(app->variables->project);   // Limpa as variáveis do projeto
    app->variables->simulation->num_particles_use = 0; // Reseta o número de partículas
    gtk_tree_store_clear(app->tree_store);             // Limpa a árvore
}