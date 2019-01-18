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

t_app		*g_app;
char		g_stoprendering;
int			g_ss;

gboolean	keypress(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	key_handler(event->keyval);
	key_handler1();
	render();
	return (TRUE);
}

int			main(int argc, char *argv[])
{
	time_t	t;

	srand((unsigned)time(&t));
	if (argc == 2 && (argv[1][0] >= '1' && argv[1][0] <= '9') &&
		argv[1][1] == 0)
		g_ss = argv[1][0] - '0';
	else
		g_ss = 1;
	initialize_app();
	testscene_4();
	g_app->curobj = g_app->scene.primitives;
	g_app->curlobj = g_app->scene.lights;
	initialize_gtk();
	render();
	gtk_main();
	return (0);
}

void		on_window_main_destroy(void)
{
	while (g_main_context_iteration(NULL, FALSE))
	{
	}
	gtk_main_quit();
}
