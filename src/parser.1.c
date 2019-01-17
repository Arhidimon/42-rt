/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavelko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:55:38 by apavelko          #+#    #+#             */
/*   Updated: 2019/01/17 18:55:43 by apavelko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jsmn.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dt;
	const char	*sc;
	size_t		i;

	dt = dst;
	sc = src;
	i = 0;
	while (i < n)
	{
		dt[i] = sc[i];
		i++;
	}
	return (dst);
}

int		ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)s)[i] = '\0';
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
