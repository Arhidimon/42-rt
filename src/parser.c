/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavelko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:56:13 by apavelko          #+#    #+#             */
/*   Updated: 2019/01/17 18:56:15 by apavelko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jsmn.h"

char	*ft_read_file(char *filepath)
{
	int		fd;
	char	*line;
	char	*string;
	char	*ptr;

	string = ft_strnew(1);
	if ((fd = open(filepath, O_RDONLY)) < 0)
	{
		free(string);
		return (NULL);
	}
	while (get_next_line(fd, &line) > 0)
	{
		ptr = string;
		string = ft_strjoin(string, line);
		free(ptr);
		free(line);
	}
	close(fd);
	return (string);
}

char	*ft_strnew(size_t size)
{
	char *str;

	size++;
	str = (char*)malloc(sizeof(*str) * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, size);
	return (str);
}

int		ft_parse_json(char *filepath)
{
	int				i;
	int				t;
	char			*string;
	jsmntok_t		tokens[MAX_T];
	jsmn_parser		parser;

	if (!(string = ft_read_file(filepath)))
		return (1);
	i = 0;
	jsmn_init(&parser);
	t = jsmn_parse(&parser, string, ft_strlen(string), tokens, MAX_T);
	if (jsmn_cam(string, tokens, t) || jsmn_sc(string, tokens, t))
		return (1);
	return (0);
}

char	*ft_parser(char *filepath)
{
	if (ft_parse_json(filepath))
	{
		printf("ERROR!!!!11");
		return ("Hello!");
	}
	else
	{
		printf("OK!");
		return (NULL);
	}
}
