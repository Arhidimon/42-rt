/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:38:10 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/07 14:38:12 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *element)
{
	t_list	*last;

	if (alst == NULL || element == NULL)
		return ;
	last = ft_lstlast(*alst);
	if (last == NULL)
		*alst = element;
	else
		last->next = element;
}
