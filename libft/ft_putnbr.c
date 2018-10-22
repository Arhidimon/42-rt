/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:46:19 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/04 19:46:20 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int		div;
	int		d;
	char	flag;

	if (n == 0)
	{
		ft_putchar('0');
		return ;
	}
	if (n < 0)
		ft_putchar('-');
	div = 1000000000;
	flag = 0;
	while (div)
	{
		d = n / div;
		n -= div * d;
		if (d && !flag)
			flag = 1;
		if (d || flag)
			ft_putchar((d > 0) ? '0' + d : '0' - d);
		div /= 10;
	}
}
