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

void menu_open (GtkMenuItem *menuitem, gpointer user_data)
{
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Open File", g_app->window,
                                      action, "_Cancel", GTK_RESPONSE_CANCEL,
                                      "_Open", GTK_RESPONSE_ACCEPT,
                                      NULL);

res = gtk_dialog_run (GTK_DIALOG (dialog));
	printf("%i\n", res);
if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);
    if (ft_parser(filename) == NULL)
    	render();
    g_free (filename);
  }

gtk_widget_destroy (dialog);
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
	//GdkPixbuf  *scpixbuf;
	//gdk_pixbuf_scale (pixbuf, scpixbuf,0,0, width, height, 0, 0, 1 , 1, GDK_INTERP_NEAREST);
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

