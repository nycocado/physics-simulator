#pragma once

#include <gtk/gtk.h> // Inclui as bibliotecas do GTK

typedef struct _Window_Main *Window_Main;     // Declaração do ponteiro da janela principal
typedef struct _Cell_Renderer *Cell_Renderer; // Declaração do ponteiro do renderizador de células
typedef struct _Columns *Columns;             // Declaração do ponteiro das colunas
typedef struct _Buttons_Main *Buttons_Main;   // Declaração do ponteiro dos botões principais

struct _Window_Main // Estrutura da janela principal
{
    GtkWidget *window;
    Columns columns;
    Cell_Renderer cell_renderer;
    Buttons_Main buttons;
};

struct _Cell_Renderer // Estrutura do renderizador de células
{
    GtkCellRenderer *type;
    GtkCellRenderer *x;
    GtkCellRenderer *y;
    GtkCellRenderer *vx;
    GtkCellRenderer *vy;
    GtkCellRenderer *ax;
    GtkCellRenderer *ay;
    GtkCellRenderer *mass;
    GtkCellRenderer *check;
};

struct _Columns // Estrutura das colunas
{
    GtkTreeViewColumn *type;
    GtkTreeViewColumn *x;
    GtkTreeViewColumn *y;
    GtkTreeViewColumn *vx;
    GtkTreeViewColumn *vy;
    GtkTreeViewColumn *ax;
    GtkTreeViewColumn *ay;
    GtkTreeViewColumn *mass;
    GtkTreeViewColumn *check;
};

struct _Buttons_Main // Estrutura dos botões principais
{
    GtkWidget *add_particle;
    GtkWidget *add_force;
    GtkWidget *edit;
    GtkWidget *remove;
    GtkWidget *cinematic;
    GtkWidget *dynamic;
};

Window_Main window_main_new();                         // Função de criação da janela principal
void window_main_free(Window_Main window_main);        // Função de liberação da janela principal
Cell_Renderer cell_renderers_new();                    // Função de criação do renderizador de células
void cell_renderers_free(Cell_Renderer cell_renderer); // Função de liberação do renderizador de células
Columns columns_new();                                 // Função de criação das colunas
void columns_free(Columns columns);                    // Função de liberação das colunas
Buttons_Main buttons_main_new();                       // Função de criação dos botões da janela principal
void buttons_main_free(Buttons_Main buttons_main);     // Função de liberação dos botões da janela principal