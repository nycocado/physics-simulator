#include "../include/gtk_include_all.h"

void get_window_size(GtkWidget *widget)
{
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    app->variables->window_size->width = allocation.width;
    app->variables->window_size->height = allocation.height;
}

void draw_axes(cairo_t *cr, int x_center, int y_bottom)
{
    // Configurações dos eixos
    cairo_set_source_rgb(cr, 1, 1, 1); // Cor dos eixos (branca)
    cairo_set_line_width(cr, 2);

    // Desenha o eixo X
    cairo_move_to(cr, 0, y_bottom);
    cairo_line_to(cr, app->variables->window_size->width, y_bottom);
    cairo_stroke(cr);

    // Desenha o eixo Y (segmento pequeno para baixo)
    cairo_move_to(cr, x_center, 0);                                   // Desenha o eixo Y para cima
    cairo_line_to(cr, x_center, app->variables->window_size->height); // Desenha o eixo Y para baixo
    cairo_stroke(cr);
}

void draw_arrow(cairo_t *cr, double start_x, double start_y, double end_x, double end_y, double arrow_length, double arrow_angle)
{
    // Calcular o ângulo da linha
    double angle = phyc_angle(end_x - start_x, end_y - start_y);

    // Calcular as coordenadas das pontas da seta
    double x1 = end_x - phyc_decompose_x(arrow_length, angle - arrow_angle);
    double y1 = end_y - phyc_decompose_y(arrow_length, angle - arrow_angle);
    double x2 = end_x - phyc_decompose_x(arrow_length, angle + arrow_angle);
    double y2 = end_y - phyc_decompose_y(arrow_length, angle + arrow_angle);

    // Desenhar a linha principal
    cairo_move_to(cr, start_x, start_y);
    cairo_line_to(cr, end_x, end_y);
    cairo_stroke(cr);

    // Desenhar as linhas da seta
    cairo_move_to(cr, end_x, end_y);
    cairo_line_to(cr, x1, y1);
    cairo_stroke(cr);

    cairo_move_to(cr, end_x, end_y);
    cairo_line_to(cr, x2, y2);
    cairo_stroke(cr);
}

void set_background_color(cairo_t *cr, double r, double g, double b)
{
    cairo_set_source_rgb(cr, r, g, b);
    cairo_paint(cr);
}

void draw_particle(cairo_t *cr, float start_x, float start_y, float radius)
{
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_arc(cr, start_x, start_y, radius, 0, 2 * G_PI);
    cairo_fill(cr);
}

void draw_title(cairo_t *cr, const char *text, float x, float y)
{
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, x, y);
    cairo_show_text(cr, text);
}

void draw_time(cairo_t *cr, float time, float x, float y)
{
    char *str;
    str = g_strdup_printf("Tempo: %.2f s", time);
    draw_title(cr, str, x, y);
    g_free(str);
}