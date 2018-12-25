#include <gtk/gtk.h>
#include <cairo.h>
#include <stdlib.h>

#define WIDTH 100
#define HEIGHT 100
#define BPS 8



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
                FALSE, BPS, WIDTH, HEIGHT);
	rowstride = gdk_pixbuf_get_rowstride (pixbuf);
	pixels = gdk_pixbuf_get_pixels(pixbuf);
	x = 0;
	while(x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			pixels[y * rowstride + x * 3] = rand() % 256;
			pixels[y * rowstride + x * 3 + 1] = rand() % 256;
			pixels[y * rowstride + x * 3 + 2] = rand() % 256;
			y++;
		}
		x++;
	}
	GdkPixbuf  *scpixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_NEAREST);
  gdk_cairo_set_source_pixbuf(cr, scpixbuf, 0, 0);
    cairo_paint(cr);
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
 
int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
    GtkWidget       *da;
    time_t t;
    srand((unsigned) time(&t));
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    da = GTK_WIDGET(gtk_builder_get_object(builder, "darea"));
    gtk_builder_connect_signals(builder, NULL);
    g_signal_connect(G_OBJECT (da), "draw", G_CALLBACK (draw_rt) , NULL);
 
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}
 
// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}