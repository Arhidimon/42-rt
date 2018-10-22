/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:38:39 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/04 14:38:43 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		i;
	int		div;
	int		d;
	char	buff[12];
	char	flag;

	i = 0;
	if (n < 0)
		buff[i++] = '-';
	div = 1000000000;
	flag = 0;
	while (div)
	{
		d = n / div;
		n -= div * d;
		if (d && !flag)
			flag = 1;
		if (d || flag)
			buff[i++] = ((d > 0) ? '0' + d : '0' - d);
		div /= 10;
	}
	if (i == 0)
		buff[i++] = '0';
	buff[i] = '\0';
	return (ft_strdup(buff));
}
