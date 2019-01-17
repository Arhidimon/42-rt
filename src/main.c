/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:46:56 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/30 13:46:59 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cairo.h>
#include <stdlib.h>
#include "../includes/rtv1.h"

#define WIDTH 300
#define HEIGHT 300
#define BPS 8

t_app *g_app;
char g_stoprendering;

void free_scene()
{
	t_primitive *temppr;
	t_primitive *templ;
	
	while(g_app->scene.primitives)
	{
		temppr = g_app->scene.primitives->next;
		g_app->scene.primitives = g_app->scene.primitives->next;
		free(temppr);
	}
	g_app->scene.lights == NULL;
	while(g_app->scene.lights)
	{
		templ = g_app->scene.lights->next;
		g_app->scene.lights = g_app->scene.lights->next;
		free(templ);
	}
	g_app->scene.lights == NULL;
}

void menu_open(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkWidget *dialog;
	GtkFileChooserAction action;
	gint res;
	char *filename;

	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new ("Open File", g_app->window,
                                      action, "_Cancel", GTK_RESPONSE_CANCEL,
                                      "_Open", GTK_RESPONSE_ACCEPT,
                                      NULL);
	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		filename = gtk_file_chooser_get_filename (chooser);
		free_scene();
		ft_parser(filename);
		render();
		g_free (filename);
	}
	gtk_widget_destroy (dialog);
}

void menu_quit(GtkMenuItem *menuitem, gpointer user_data)
{
	gtk_window_close(g_app->window);
}

gboolean draw_rt(GtkWidget *widget, cairo_t *cr, gpointer data)
{
  guint width, height;
  GdkRGBA color;
  GtkStyleContext *context;
 
  	guchar *pixels;
	int rowstride;
	unsigned int x, y;

  context = gtk_widget_get_style_context (widget);

  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);
 	GdkPixbuf* pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB,
                FALSE, BPS, SCREEN_WIDTH, SCREEN_HEIGHT);
	rowstride = gdk_pixbuf_get_rowstride (pixbuf);
	pixels = gdk_pixbuf_get_pixels(pixbuf);
	

	x = 0;
	while(x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			pixels[y * rowstride + x * 3] = g_app->screen.pixels[x + y * SCREEN_WIDTH] % 256;
			pixels[y * rowstride + x * 3 + 1] = g_app->screen.pixels[x + y * SCREEN_WIDTH] >> 8 % 256;
			pixels[y * rowstride + x * 3 + 2] = g_app->screen.pixels[x + y * SCREEN_WIDTH] >> 16% 256;
			y++;
		}
		x++;
	}
	GdkPixbuf  *scpixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_NEAREST);
  gdk_cairo_set_source_pixbuf(cr, scpixbuf, 0, 0);
    cairo_paint(cr);
    g_object_unref(G_OBJECT(scpixbuf));
    g_object_unref(G_OBJECT(pixbuf));
  gtk_render_background (context, cr, 0, 0, width, height);
  gtk_style_context_get_color (context,
                               gtk_style_context_get_state (context),
                               &color);
  gdk_cairo_set_source_rgba (cr, &color);
  cairo_fill (cr);
 return FALSE;
}
 
gboolean keypress (GtkWidget *widget, GdkEventKey *event, gpointer data)
{
  	key_handler(event->keyval);
  	key_handler1();
  	render();
    return TRUE;
}

int main(int argc, char *argv[])
{ 
    time_t t;
    
    srand((unsigned) time(&t));
 	initialize_app();
	testscene_5();
	//free_scene();
	//testscene_4();
	
	g_app->curobj = g_app->scene.primitives;
	g_app->curlobj = g_app->scene.lights;
	initialize_gtk();
    render();              
    gtk_main();
 
    return 0;
}
 
void on_window_main_destroy()
{
    gtk_main_quit();
}
