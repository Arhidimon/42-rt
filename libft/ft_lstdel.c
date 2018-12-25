/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:38:12 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/06 18:38:13 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (alst != NULL || *alst != NULL || del != NULL)
	{
		if ((*alst)->next != NULL)
			ft_lstdel(&((*alst)->next), del);
		del((*alst)->content, (*alst)->content_size);
		ft_memdel((void **)alst);
	}
}
