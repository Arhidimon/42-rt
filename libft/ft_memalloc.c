/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 12:29:06 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/30 12:29:07 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <string.h>

void	*ft_memalloc(size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (size)
	{
		ptr = malloc(size);
		if (ptr)
			ft_bzero(ptr, size);
	}
	return (ptr);
}
