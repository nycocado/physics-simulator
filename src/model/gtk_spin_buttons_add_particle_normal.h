#pragma once

#include <gtk/gtk.h> // Inclui as bibliotecas do GTK

typedef struct _Spin_Buttons_Add_Particle_Normal *Spin_Buttons_Add_Particle_Normal; // Declaração do ponteiro dos botões de adição

struct _Spin_Buttons_Add_Particle_Normal // Estrutura dos botões de adição
{
    GtkWidget *x;
    GtkWidget *y;
    GtkWidget *vx;
    GtkWidget *vy;
    GtkWidget *ax;
    GtkWidget *ay;
    GtkWidget *mass;
};

Spin_Buttons_Add_Particle_Normal spin_buttons_add_particle_normal_new();                                       // Função de criação dos botões de adição
void spin_buttons_add_particle_normal_free(Spin_Buttons_Add_Particle_Normal spin_buttons_add_particle_normal); // Função de liberação dos botões de adição