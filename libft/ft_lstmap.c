/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:56:53 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/06 19:56:55 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;

	if (lst == NULL || f == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (f(lst));
	temp = ft_lstmap(lst->next, f);
	ft_lstadd(&temp, f(lst));
	return (temp);
}
