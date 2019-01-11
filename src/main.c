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

void menu_open (GtkMenuItem *menuitem, gpointer user_data)
{
	gtk_widget_set_visible (g_app->opendialog, TRUE);
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
	// static GdkPixbuf* pixbuf = NULL;
	// guchar *pixels;
	// int rowstride;
	// unsigned int x, y;

	// if (!pixbuf)
	// 	pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB,
 //                FALSE, BPS, WIDTH, HEIGHT);
	// rowstride = gdk_pixbuf_get_rowstride (pixbuf);
	// x = 0;
	// while(x < WIDTH)
	// {
	// 	y = 0;
	// 	while (y < HEIGHT)
	// 	{
	// 		pixels[y * rowstride + x * 3] = rand() % 256;
	// 		pixels[y * rowstride + x * 3 + 1] = rand() % 256;
	// 		pixels[y * rowstride + x * 3 + 2] = rand() % 256;
	// 		y++;
	// 	}
	// 	x++;
	// }
	// //cairo_t *cr;
 //    //cr = gdk_cairo_create(gtk_widget_get_window(widget));
 //    //    cr = gdk_cairo_create (da->window);
 //    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
 //    cairo_paint(cr);
 //    //    cairo_fill (cr);
 //    //cairo_destroy (cr);
	// return FALSE;
}
 
gboolean keypress (GtkWidget *widget, GdkEventKey *event, gpointer data)
{
  	key_handler(event->keyval);
  	key_handler1();
    return TRUE;
}

int main(int argc, char *argv[])
{ 
    time_t t;
    srand((unsigned) time(&t));
 
	
    gtk_init(&argc, &argv);
 	initialize_app();
		testscene_4();
	
	
    g_app->builder = gtk_builder_new();
    gtk_builder_add_from_file(g_app->builder, "glade/window_main.glade", NULL);
 
    g_app->window = GTK_WIDGET(gtk_builder_get_object(g_app->builder, "window_main"));
    g_app->progressbar = GTK_WIDGET(gtk_builder_get_object(g_app->builder, "progressbar"));
    g_app->da = GTK_WIDGET(gtk_builder_get_object(g_app->builder, "darea"));
    g_app->opendialog = GTK_WIDGET(gtk_builder_get_object(g_app->builder, "opendialog"));

    gtk_builder_connect_signals(g_app->builder, NULL);
   
 
    g_object_unref(g_app->builder);
 	
    gtk_widget_show(g_app->window);
    render();              
    gtk_main();
 
    return 0;
}
 
void on_window_main_destroy()
{
    gtk_main_quit();
}
// =======


// 

// int		event_handler(t_app *app)
// {
// 	SDL_Event event;

// 	key_handler(KEY_NONE);
// 	while (SDL_PollEvent(&event))
// 	{
// 		if (event.type == SDL_QUIT)
// 			return (1);
// 		else if (event.type == SDL_KEYDOWN)
// 		{
// 			if (event.key.keysym.sym == SDLK_ESCAPE)
// 				return (1);
// 			else
// 				key_handler(event.key.keysym.scancode);
// 		}
// 	}
// 	key_handler1(app);
// 	return (0);
// }

// void	main_loop(t_app *app)
// {
// 	app->framecount = 0;
// 	app->frametimelast = SDL_GetTicks();
// 	while (1)
// 	{
// 		if (event_handler(app))
// 			break ;
// 		clearinfo();
// 		printinfo(app);
// 		SDL_RenderClear(app->renderer);
// 		SDL_UpdateTexture(app->maintexture, NULL, app->screen.pixels,
// 		(int)SCREEN_WIDTH * sizeof(Uint32));
// 		SDL_RenderCopy(app->renderer, app->maintexture, NULL, NULL);
// 		print_fps(app, count_fps(app));
// 		SDL_RenderPresent(app->renderer);
// 	}
// }

// int		main(int argc, char **argv)
// {
// 	t_app *app;

// 	app = initialize_app();
// 	initialize_sdl(app);
// 	if (argc > 1 && argv[1][0] == '1' && argv[1][1] == '\0')
// 		testscene_1(app);
// 	else if (argc > 1 && argv[1][0] == '2' && argv[1][1] == '\0')
// 		testscene_2(app);
// 	else if (argc > 1 && argv[1][0] == '3' && argv[1][1] == '\0')
// 		testscene_3(app);
// 	else if (argc > 1 && argv[1][0] == '4' && argv[1][1] == '\0')
// 		testscene_4(app);
// 	else
// 		testscene_5(app);
// 	printcontrols();
// 	app->curobj = app->scene.primitives;
// 	app->curlobj = app->scene.lights;
// 	printinfo(app);
// 	render(app);
// 	main_loop(app);
// 	SDL_DestroyTexture(app->maintexture);
// 	SDL_DestroyRenderer(app->renderer);
// 	SDL_DestroyWindow(app->window);
// 	SDL_Quit();
// 	return (0);
// }

