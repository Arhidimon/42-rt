/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavelko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:55:58 by apavelko          #+#    #+#             */
/*   Updated: 2019/01/17 18:56:00 by apavelko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jsmn.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char				*str;
	char				*pstr;
	size_t				len1;
	size_t				len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		len1 = 0;
	else
		len1 = ft_strlen(s1);
	if (!s2)
		len2 = 0;
	else
		len2 = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(*str) * (len1 + len2 + 1))))
		return (NULL);
	pstr = str;
	while (len1--)
		*str++ = *s1++;
	while (len2--)
		*str++ = *s2++;
	*str = '\0';
	return (pstr);
}

int		ft_atoi(const char *str)
{
	int					i;
	int					f;
	unsigned long int	result;

	i = 0;
	f = 1;
	result = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-')
		f = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if (result >= 9223372036854775807 && f == 1)
			return (-1);
		else if (result > 9223372036854775807 && f == -1)
			return (0);
		i++;
	}
	return ((int)(result * f));
}

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list			*new;

	if (!(new = (t_list *)malloc(sizeof(*new))))
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		if (!(new->content = malloc(content_size)))
		{
			free(new);
			return (NULL);
		}
		ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}

int		ft_isspace(int c)
{
	return (c == ' ' || (c > 8 && c < 14));
}
