/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavelko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:56:05 by apavelko          #+#    #+#             */
/*   Updated: 2019/01/17 18:56:06 by apavelko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jsmn.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s)
	{
		str = (char *)malloc(sizeof(*str) * (len + 1));
		if (str == NULL)
			return (NULL);
		while (i < len)
		{
			str[i] = s[start];
			i++;
			start++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

t_list	*get_elem(int fd, t_list **head)
{
	t_list *ptr;

	ptr = *head;
	while (ptr && (int)ptr->content_size != fd)
		ptr = ptr->next;
	return (ptr);
}

int		get_more(int fd, char *buf, t_list **head)
{
	t_list	*ptr;
	char	*str;

	if ((ptr = get_elem(fd, head)) == NULL)
	{
		ptr = ft_lstnew(buf, ft_strlen(buf) + 1);
		ptr->content_size = fd;
		ft_lstadd(head, ptr);
	}
	else
	{
		str = ft_strjoin(ptr->content, buf);
		free(ptr->content);
		ptr->content = str;
	}
	if (ft_strchr(ptr->content, '\n'))
		return (1);
	return (0);
}

char	*get_line(int fd, t_list **head)
{
	t_list	*ptr;
	char	*point;
	char	*tmp;
	char	*str;
	int		len;

	if (!(ptr = get_elem(fd, head)) || !ptr->content)
		return (NULL);
	tmp = ptr->content;
	if ((point = ft_strchr(ptr->content, '\n')))
	{
		len = point - (char*)ptr->content;
		str = ft_strnew(len);
		ft_strncpy(str, ptr->content, len);
		ptr->content = *(++point) ? ft_strdup(point) : NULL;
	}
	else
	{
		if (!(str = ft_strdup(ptr->content)))
			return (NULL);
		ptr->content = NULL;
		ptr->content_size = 0;
	}
	free(tmp);
	return (str);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*head;
	char			buf[BUFF_SIZE + 1];
	int				ret;

	while ((ret = read(fd, buf, BUFF_SIZE)) != 0)
	{
		if (ret < 0 || fd < 0 || !line)
			return (-1);
		buf[ret] = '\0';
		if (get_more(fd, buf, &head))
		{
			*line = get_line(fd, &head);
			return (1);
		}
	}
	if ((*line = get_line(fd, &head)))
		return (1);
	return (0);
}
