#pragma once

#include <gtk/gtk.h>

void get_window_size(GtkWidget *widget);                                                                                           // Função para obter o tamanho da janela
void draw_axes(cairo_t *cr, int x_center, int y_bottom);                                                                           // Função para desenhar os eixos
void draw_arrow(cairo_t *cr, double start_x, double start_y, double end_x, double end_y, double arrow_length, double arrow_angle); // Função para desenhar uma seta
void set_background_color(cairo_t *cr, double r, double g, double b);                                                              // Função para definir a cor de fundo
void draw_particle(cairo_t *cr, float start_x, float start_y, float radius);                                                       // Função para desenhar uma partícula
void draw_title(cairo_t *cr, const char *title, float x, float y);                                                                 // Função para desenhar um título
void draw_time(cairo_t *cr, float time, float x, float y);                                                                         // Função para desenhar o tempo