/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:58:03 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/04 19:58:05 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		div;
	int		d;
	char	flag;

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n < 0)
		ft_putchar_fd('-', fd);
	div = 1000000000;
	flag = 0;
	while (div)
	{
		d = n / div;
		n -= div * d;
		if (d && !flag)
			flag = 1;
		if (d || flag)
			ft_putchar_fd((d > 0) ? '0' + d : '0' - d, fd);
		div /= 10;
	}
}
