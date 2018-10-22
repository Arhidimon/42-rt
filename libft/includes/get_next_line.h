/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <dbezruch@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:10:00 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/28 17:10:00 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 8

# define TRUE 1
# define FALSE 0
# define ERR_MALLOC (-2)
# define NO_ERROR 1
# define REACH_EOF 2
# define ERR_PTRISNULL (-3)

# include <unistd.h>

int					get_next_line(const int fd, char **line);

typedef struct		s_file
{
	int				fd;
	int				is_end;
	char			*str;
	struct s_file	*next;

}					t_file;
#endif
