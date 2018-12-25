/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:13:48 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/07 15:13:51 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstreverse(t_list **begin_list)
{
	t_list	*temp;
	t_list	*head;
	t_list	*buff;

	buff = NULL;
	head = *begin_list;
	while (head != NULL)
	{
		temp = head->next;
		head->next = buff;
		buff = head;
		head = temp;
	}
	*begin_list = buff;
}
