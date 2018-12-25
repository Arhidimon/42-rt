/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consoleout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:02:44 by dbezruch          #+#    #+#             */
/*   Updated: 2018/09/30 13:02:46 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	printcontrols(void)
{
	ft_putstr("\x1b[33mFDF\t\tby\tdbezruch\n\n");
	ft_putstr("Controls:\n\n");
	ft_putstr("\x1b[31mw a s d      \t\x1b[34mrotate\n");
	ft_putstr("\x1b[31m← ↑ → ↓      \t\x1b[34mmove\n");
	ft_putstr("\x1b[31mSPACE        \t\x1b[34mmove up\n");
	ft_putstr("\x1b[31mTAB          \t\x1b[34mmove down\n");
	ft_putstr("\x1b[31mBACKSPACE    \t\x1b[34mtogle shadows\n");
	ft_putstr("\x1b[31mHOME\\END    \t\x1b[34mselect object type\n");
	ft_putstr("\x1b[31mPAGE UP\\DOWN\t\x1b[34mselect object\n");
	ft_putstr("\x1b[31m+ -          \t\x1b[34mset iterations of reflection\n");
	ft_putstr("\x1b[31mZ            \t\x1b[34madd plane\n");
	ft_putstr("\x1b[31mX            \t\x1b[34madd cone\n");
	ft_putstr("\x1b[31mC            \t\x1b[34madd cylinder\n");
	ft_putstr("\x1b[31mV            \t\x1b[34madd sphere\n");
	ft_putstr("\n");
	printinfoheader();
}

void	printinfoheader(void)
{
	ft_putstr("\x1b[33mInfo:\n");
	ft_putstr("\t\t\x1b[34mPosition\t\t\x1b[36mRotation\n");
}

void	printvector(t_vector vector)
{
	ft_putstr("(");
	ft_putfnbr(vector[0], 1);
	ft_putstr(", ");
	ft_putfnbr(vector[1], 1);
	ft_putstr(", ");
	ft_putfnbr(vector[2], 1);
	ft_putstr(")");
}

void	printinfo(t_app *app)
{
	ft_putstr("\x1b[31mCamera\t\t\x1b[34m");
	printvector(app->camera.position);
	ft_putstr("\t\x1b[36m");
	printvector(app->camera.direction);
	ft_putstr("\n\x1b[31mObject\t\t\x1b[34m");
	printvector(*(get_curobj_pos(app)));
	ft_putstr("  \t\x1b[36m");
	printvector(*(get_curobj_dir(app)));
	ft_putstr("\n");
}

void	clearinfo(void)
{
	ft_putstr("\x1b[2A\x1b[100D\x1b[J");
}
