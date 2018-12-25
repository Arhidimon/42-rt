/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <dbezruch@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:10:00 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/28 17:10:00 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include "includes/libft.h"

int		str_append(int fd, char **s)
{
	char	buff[BUFF_SIZE + 1];
	char	*stemp;
	ssize_t wr;

	wr = read(fd, buff, BUFF_SIZE);
	if (!s || wr < 0)
		return (ERR_PTRISNULL);
	buff[wr] = '\0';
	if (wr == 0)
		return (REACH_EOF);
	if (!*s)
	{
		*s = ft_strdup(buff);
		return (NO_ERROR);
	}
	if (!(stemp = ft_strjoin(*s, buff)))
		return (ERR_MALLOC);
	free(*s);
	*s = stemp;
	return (NO_ERROR);
}

int		str_remove(int fd, char **s, char **sout)
{
	size_t	i;
	size_t	j;
	char	*spos;
	char	*st;
	int		rcode;

	rcode = NO_ERROR;
	if (!s || !*s)
		return (ERR_PTRISNULL);
	while (!(spos = ft_strchr(*s, '\n')) && (rcode == NO_ERROR))
		rcode = str_append(fd, s);
	i = ft_strlen(*s);
	j = (rcode == NO_ERROR) ? spos - *s : i;
	*sout = ft_strsub(*s, 0, j);
	st = (rcode == NO_ERROR) ? ft_strsub(*s, j + 1, i - j - 1) : NULL;
	free(*s);
	*s = st;
	return (NO_ERROR);
}

t_file	*search_fd(t_file **file, int fd)
{
	t_file *f;

	if (*file == NULL)
	{
		if (!(*file = (t_file*)malloc(sizeof(t_file))))
			return (NULL);
		(*file)->fd = fd;
		(*file)->next = NULL;
		(*file)->is_end = FALSE;
		(*file)->str = NULL;
		return (*file);
	}
	f = *file;
	while (f && f->next && f->fd != fd)
		f = f->next;
	if (f->fd == fd)
		return (f);
	if (!(f->next = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	f->next->fd = fd;
	f->next->next = NULL;
	f->next->is_end = FALSE;
	f->next->str = NULL;
	return (f->next);
}

int		get_next_line(const int fd, char **line)
{
	static t_file	*file = NULL;
	t_file			*cf;
	int				rcode;

	if ((cf = search_fd(&file, fd))->is_end == TRUE)
		return (0);
	if (cf->str == NULL)
	{
		if ((rcode = str_append(cf->fd, &cf->str)) < 0)
			return (-1);
		else if (rcode == REACH_EOF)
		{
			file->is_end = TRUE;
			return (0);
		}
	}
	rcode = str_remove(cf->fd, &(cf->str), line);
	if (rcode < 0)
		return (-1);
	if (rcode == REACH_EOF)
	{
		file->is_end = TRUE;
		return (0);
	}
	return (1);
}
