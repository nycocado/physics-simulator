#include "../include/gtk_include_all.h"

void particle_cinematic_collection_start() // Inicia a coleção de partículas cinemáticas
{
    Particle_Cinematic_Collection particle_collection = particle_cinematic_collection_new(app->variables->simulation->num_particles_use); // Cria uma coleção de partículas
    GtkTreeIter iter;                                                                                                                     // Iterador para percorrer a árvore
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(app->tree_store), &iter);                                               // Pega o primeiro elemento da árvore
    int i = 0;                                                                                                                            // Contador de partículas
    while (valid)                                                                                                                         // Enquanto houver elementos na árvore
    {
        gboolean checked;                                                            // Variável para verificar se a partícula está marcada
        gtk_tree_model_get(GTK_TREE_MODEL(app->tree_store), &iter, 7, &checked, -1); // Pega o valor do campo de seleção
        if (checked)                                                                 // Se a partícula estiver marcada
        {
            gchar *x, *y, *vx, *vy, *ax, *ay;                                                                             // Variáveis para armazenar os valores dos campos de entrada
            gtk_tree_model_get(GTK_TREE_MODEL(app->tree_store), &iter, 0, &x, 1, &y, 2, &vx, 3, &vy, 4, &ax, 5, &ay, -1); // Pega os valores dos campos de entrada

            // Converte os valores para float
            float x_float = atof(x);
            float y_float = atof(y);
            float vx_float = atof(vx);
            float vy_float = atof(vy);
            float ax_float = atof(ax);
            float ay_float = atof(ay);

            Particle_Cinematic particle = particle_cinematic_new(x_float, y_float, vx_float, vy_float, ax_float, ay_float); // Cria uma partícula
            particle_collection->particles[i] = particle;                                                                   // Adiciona a partícula à coleção
            i++;                                                                                                            // Incrementa o contador

            // Libera a memória
            g_free(x);
            g_free(y);
            g_free(vx);
            g_free(vy);
            g_free(ax);
            g_free(ay);
        }
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(app->tree_store), &iter); // Pega o próximo elemento da árvore
    }
    app->variables->simulation->particle_cinematic_collection = particle_collection; // Adiciona a coleção de partículas à variável de simulação
}

void particle_dynamic_collection_start() // Inicia a coleção de partículas dinâmicas
{
    Particle_Dynamic_Collection particle_dynamic_collection = particle_dynamic_collection_new(app->variables->simulation->num_particles_use); // Cria uma coleção de partículas
    GtkTreeIter iter;                                                                                                                         // Iterador para percorrer a árvore
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(app->tree_store), &iter);                                                   // Pega o primeiro iterador da árvore
    int i = 0;                                                                                                                                // Contador de partículas
    while (valid)                                                                                                                             // Enquanto houver elementos na árvore
    {
        gboolean checked;                                                            // Variável para verificar se a partícula está marcada
        gtk_tree_model_get(GTK_TREE_MODEL(app->tree_store), &iter, 7, &checked, -1); // Pega o valor do campo de seleção
        if (checked)                                                                 // Se a partícula estiver marcada
        {
            gchar *x, *y, *vx, *vy, *ax, *ay, *mass;                                                                                // Variáveis para armazenar os valores dos campos de entrada
            gtk_tree_model_get(GTK_TREE_MODEL(app->tree_store), &iter, 0, &x, 1, &y, 2, &vx, 3, &vy, 4, &ax, 5, &ay, 6, &mass, -1); // Pega os valores dos campos de entrada

            // Converte os valores para float
            float x_float = atof(x);
            float y_float = atof(y);
            float vx_float = atof(vx);
            float vy_float = atof(vy);
            float ax_float = atof(ax);
            float ay_float = atof(ay);
            float mass_float = atof(mass);

            Particle_Dynamic particle = particle_dynamic_new(x_float, y_float, vx_float, vy_float, ax_float, ay_float, mass_float); // Cria uma partícula
            GtkTreeIter child_iter;                                                                                                 // Iterador para percorrer os filhos
            gboolean child_valid = gtk_tree_model_iter_children(GTK_TREE_MODEL(app->tree_store), &child_iter, &iter);               // Pega o primeiro filho e verifica se é válido
            while (child_valid)                                                                                                     // Enquanto houver filhos
            {
                gchar *force_x, *force_y;                                                                       // Variáveis para armazenar os valores dos campos de entrada dos filhos
                gtk_tree_model_get(GTK_TREE_MODEL(app->tree_store), &child_iter, 0, &force_x, 1, &force_y, -1); // Pega os valores dos campos de entrada dos filhos

                // Converte os valores para float
                float force_x_float = atof(force_x);
                float force_y_float = atof(force_y);

                Vector force = create_vector(force_x_float, force_y_float); // Cria uma força
                particle->forces = g_list_append(particle->forces, force);  // Adiciona a força à partícula

                // Libera a memória alocada para os valores dos campos de entrada dos filhos
                g_free(force_x);
                g_free(force_y);

                child_valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(app->tree_store), &child_iter); // Obtém o próximo iterador dos filhos
            }
            particle_dynamic_collection->particles[i] = particle; // Adiciona a partícula à coleção
            i++;                                                  // Incrementa o contador de partículas

            // Libera a memória alocada para os valores dos campos de entrada
            g_free(x);
            g_free(y);
            g_free(vx);
            g_free(vy);
            g_free(ax);
            g_free(ay);
            g_free(mass);
        }
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(app->tree_store), &iter); // Obtém o próximo iterador
    }
    app->variables->simulation->particle_dynamic_collection = particle_dynamic_collection; // Adiciona a coleção de partículas à variável de simulação
}