/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:09:33 by dbezruch          #+#    #+#             */
/*   Updated: 2017/10/30 16:09:36 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <string.h>

char	*ft_strnew(size_t size)
{
	char	*ptr;

	ptr = NULL;
	ptr = (char*)malloc(size + 1);
	if (ptr)
		ft_bzero((void*)ptr, size + 1);
	return (ptr);
}
