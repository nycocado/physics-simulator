#include "../include/gtk_include_all.h"

void set_columns_attribute() // Define as configurações das colunas da tabela
{
    // Define o tamanho da coluna type
    gtk_tree_view_column_set_fixed_width(app->window_main->columns->type, 100);
    // Centraliza as colunas
    gtk_tree_view_column_set_alignment(app->window_main->columns->type, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->x, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->y, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->vx, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->vy, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->ax, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->ay, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->mass, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->check, 0.5);
    // Centraliza os textos das células
    gtk_cell_renderer_set_alignment(app->window_main->cell_renderer->x, 0.5, 0.5);
    gtk_cell_renderer_set_alignment(app->window_main->cell_renderer->y, 0.5, 0.5);
    gtk_cell_renderer_set_alignment(app->window_main->cell_renderer->vx, 0.5, 0.5);
    gtk_cell_renderer_set_alignment(app->window_main->cell_renderer->vy, 0.5, 0.5);
    gtk_cell_renderer_set_alignment(app->window_main->cell_renderer->ax, 0.5, 0.5);
    gtk_cell_renderer_set_alignment(app->window_main->cell_renderer->ay, 0.5, 0.5);
    gtk_cell_renderer_set_alignment(app->window_main->cell_renderer->mass, 0.5, 0.5);
    gtk_cell_renderer_set_alignment(app->window_main->cell_renderer->check, 0.5, 0.5);
    // Define os renderizadores das células das colunas
    gtk_tree_view_column_add_attribute(app->window_main->columns->type, app->window_main->cell_renderer->type, "text", 9);
    gtk_tree_view_column_add_attribute(app->window_main->columns->x, app->window_main->cell_renderer->x, "text", 0);
    gtk_tree_view_column_add_attribute(app->window_main->columns->y, app->window_main->cell_renderer->y, "text", 1);
    gtk_tree_view_column_add_attribute(app->window_main->columns->vx, app->window_main->cell_renderer->vx, "text", 2);
    gtk_tree_view_column_add_attribute(app->window_main->columns->vy, app->window_main->cell_renderer->vy, "text", 3);
    gtk_tree_view_column_add_attribute(app->window_main->columns->ax, app->window_main->cell_renderer->ax, "text", 4);
    gtk_tree_view_column_add_attribute(app->window_main->columns->ay, app->window_main->cell_renderer->ay, "text", 5);
    gtk_tree_view_column_add_attribute(app->window_main->columns->mass, app->window_main->cell_renderer->mass, "text", 6);
    gtk_tree_view_column_add_attribute(app->window_main->columns->check, app->window_main->cell_renderer->check, "active", 7);
    gtk_tree_view_column_add_attribute(app->window_main->columns->check, app->window_main->cell_renderer->check, "visible", 8);
}

void gtk_response_projetos_abrir(GtkDialog *dialog, gint response_id) // Função de resposta do diálogo de abrir projeto
{
    if (response_id == GTK_RESPONSE_ACCEPT) // Se o usuário clicou no botão de abrir
    {
        GtkWidget *file_chooser = GTK_WIDGET(dialog);                                    // Pega o widget do diálogo
        gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)); // Pega o nome do arquivo selecionado
        if (filename != NULL)                                                            // Se o nome do arquivo não for nulo
        {
            app->variables->project->file_path = g_strdup(filename); // Copia o nome do arquivo para a variável do projeto
            app->variables->project->is_file_open = TRUE;            // Define que o arquivo está aberto
            g_free(filename);                                        // Libera a memória alocada para o nome do arquivo
        }
        open_project(); // Abre o projeto
    }
    gtk_widget_destroy(GTK_WIDGET(dialog)); // Fecha o diálogo
}

void gtk_response_projetos_novo(GtkDialog *dialog, gint response_id) // Função de resposta do diálogo de novo projeto
{
    if (response_id == GTK_RESPONSE_ACCEPT) // Se o usuário clicou no botão de criar
    {
        gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)); // Pega o nome do arquivo selecionado
        if (filename != NULL)                                                      // Se o nome do arquivo não for nulo
        {
            if (!g_str_has_suffix(filename, ".sabino")) // Se o nome do arquivo não terminar com ".sabino"
            {
                gchar *new_filename = g_strdup_printf("%s.sabino", filename); // Adiciona a extensão ".sabino" ao nome do arquivo
                g_free(filename);                                             // Libera a memória alocada para o nome do arquivo
                filename = new_filename;                                      // Copia o novo nome do arquivo para a variável do nome do arquivo
            }
            FILE *file = fopen(filename, "w+"); // Abre o arquivo para escrita
            if (file != NULL)                   // Se o arquivo foi aberto com sucesso
            {
                fclose(file);                                            // Fecha o arquivo (não precisa escrever nada nele, só precisa criar o arquivo)
                app->variables->project->file_path = g_strdup(filename); // Copia o nome do arquivo para a variável do projeto
                app->variables->project->is_file_open = TRUE;            // Define que o arquivo está aberto
            }
            g_free(filename); // Libera a memória alocada para o nome do arquivo
        }
    }
    gtk_widget_destroy(GTK_WIDGET(dialog)); // Fecha o diálogo
}

int run_gtk(int argc, char *argv[]) // Função principal do GTK
{
    gtk_app_new(); // Cria uma nova aplicação GTK

    gtk_init(&argc, &argv); // Inicializa o GTK

    create_window_main_widgets(app); // Cria os widgets da janela principal

    set_columns_attribute(app); // Define as configurações das colunas da tabela

    gtk_widget_show(app->window_main->window); // Mostra a janela principal
    gtk_main();                                // Inicia o loop principal do GTK

    gtk_app_free(); // Libera a memória alocada para a aplicação GTK
    return 0;       // Retorna 0 para indicar que a aplicação foi encerrada com sucesso
}

/*
Informações adicionais para entenderem o GTK:
GtkListStore: É uma lista encadeada duplamente ligada do GTK, serve para armazenar os dados da tabela (a vantagem é poder inserir varios tipos de dados em uma mesma linha)
GtkTreeStore: É uma árvore do GTK, serve para armazenar os dados da tabela (a vantagem é poder criar sublinhas, onde vai ficar nossas forças)
GtkTreeView: É a tabela do GTK, serve para exibir os dados da lista de armazenamento
GtkBuilder: É um construtor de widgets do GTK, serve para criar os widgets a partir de um arquivo .glade (é um arquivo XML que contém a descrição dos widgets)
GtkWidget: É um widget do GTK, serve para criar janelas, botões, campos de entrada, etc
GtkButton: É um botão do GTK, serve para criar botões
GtkEntry: É um campo de entrada do GTK, serve para criar campos de entrada
GtkSpinButton: É um campo de entrada do GTK, serve para criar campos de entrada com botões de incremento e decremento
GtkCellRenderer: É um renderizador de células do GTK, serve para renderizar o texto das células da tabela
GtkTreeViewColumn: É uma coluna da tabela do GTK, serve para definir as colunas da tabela
GtkTreeIter: É um iterador da árvore do GTK, serve para adicionar uma nova linha na tabela (ele consegue encontrar qualquer linha da tabela)

O GTK tem também uma integração com uma biblioteca chamada GObject ou Glib, que serve para criar objetos e classes em C
Por exemplo o GtkBuilder é um objeto da GObject
E também, as funções como g_slice_new e g_slice_free são funções da Glib, que servem para alocar e liberar memória de forma eficiente
Ele também permite usar tipos diferentes de dados, como o gchar (que é um caractere da GLib) e o GList (que é uma lista encadeada do GLib), e fora isso tem mais uma porrada, como gfloat, gboolean, gint, gpointer, etc
GTK em geral tem integrações muito malucas, como o Cairo que serve para manipular desenhos, e o Box2D que serve para simular física
Mas para essa parte de simulação de física, vamos tentar usar o SDL, que é mais simples e intuitivo para esse tipo de implementação
*ATUALIZACAO*
Vamos usar cairo ao inves do sdl, pois o cairo já é integrado ao gtk e é mais simples de usar, para implementar o sdl no gtk é um trabalho muito grande e desnecessário
*/