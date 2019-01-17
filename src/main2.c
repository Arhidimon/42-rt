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

void		free_scene(void)
{
	t_primitive *temppr;
	t_primitive *templ;

	while (g_app->scene.primitives)
	{
		temppr = g_app->scene.primitives->next;
		g_app->scene.primitives = g_app->scene.primitives->next;
		free(temppr);
	}
	g_app->scene.lights = NULL;
	while (g_app->scene.lights)
	{
		templ = g_app->scene.lights->next;
		g_app->scene.lights = g_app->scene.lights->next;
		free(templ);
	}
	g_app->scene.lights = NULL;
}

void		menu_open(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action;
	gint					res;
	char					*filename;
	GtkFileChooser			*chooser;

	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new("Open File", g_app->window,
		action, "_Cancel", GTK_RESPONSE_CANCEL,
		"_Open", GTK_RESPONSE_ACCEPT, NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		free_scene();
		ft_parser(filename);
		g_app->curobj = g_app->scene.primitives;
		g_app->curlobj = g_app->scene.lights;
		render();
		g_free(filename);
	}
	gtk_widget_destroy(dialog);
}

void		menu_quit(GtkMenuItem *menuitem, gpointer user_data)
{
	gtk_window_close(g_app->window);
}

void		draw(GdkPixbuf *pixbuf)
{
	unsigned int	x;
	unsigned int	y;
	guchar			*pixels;
	int				rowstride;

	rowstride = gdk_pixbuf_get_rowstride(pixbuf);
	pixels = gdk_pixbuf_get_pixels(pixbuf);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			pixels[y * rowstride + x * 3] =
			g_app->screen.pixels[x + y * SCREEN_WIDTH] % 256;
			pixels[y * rowstride + x * 3 + 1] =
			g_app->screen.pixels[x + y * SCREEN_WIDTH] >> 8 % 256;
			pixels[y * rowstride + x * 3 + 2] =
			g_app->screen.pixels[x + y * SCREEN_WIDTH] >> 16 % 256;
			y++;
		}
		x++;
	}
}

gboolean	draw_rt(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	GdkRGBA			color;
	GtkStyleContext *context;
	GdkPixbuf		*pixbuf;
	GdkPixbuf		*scpixbuf;

	context = gtk_widget_get_style_context(widget);
	pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB,
		FALSE, BPS, SCREEN_WIDTH, SCREEN_HEIGHT);
	draw(pixbuf);
	scpixbuf = gdk_pixbuf_scale_simple(pixbuf,
		gtk_widget_get_allocated_width(widget),
		gtk_widget_get_allocated_height(widget), GDK_INTERP_NEAREST);
	gdk_cairo_set_source_pixbuf(cr, scpixbuf, 0, 0);
	cairo_paint(cr);
	g_object_unref(G_OBJECT(scpixbuf));
	g_object_unref(G_OBJECT(pixbuf));
	gtk_render_background(context, cr, 0, 0,
		gtk_widget_get_allocated_width(widget),
		gtk_widget_get_allocated_height(widget));
	gtk_style_context_get_color(context,
		gtk_style_context_get_state(context), &color);
	gdk_cairo_set_source_rgba(cr, &color);
	cairo_fill(cr);
	return (FALSE);
}
