/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:46:19 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/04 19:46:20 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putfnbr(float n, size_t p)
{
	float	fp;
	int		rp;

	rp = (int)n;
	fp = ((n >= 0) ? n - rp : rp - n);
	if ((n < 0) && (rp == 0))
		ft_putchar('-');
	ft_putnbr(rp);
	if (p == 0)
		return ;
	ft_putchar('.');
	while (p-- > 0)
	{
		fp *= 10;
		if (((int)fp) == 0)
			ft_putchar('0');
	}
	if (((int)fp) != 0)
		ft_putnbr((int)fp);
}
