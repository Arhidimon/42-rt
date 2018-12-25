/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:25:28 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/03 17:25:32 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static char		*nword(char *str, char c, int n)
{
	int i;
	int issep;

	i = 1;
	issep = 0;
	while (*str == c)
		str++;
	while (*str != '\0')
	{
		if (i == n)
			return (str);
		while (*str == c)
		{
			issep = 1;
			str++;
		}
		if (issep && *str != '\0')
		{
			issep = 0;
			i++;
			str--;
		}
		str++;
	}
	return (NULL);
}

static int		countworlds(char *str, char c)
{
	int i;
	int issep;

	i = 0;
	issep = 1;
	while (*str != '\0')
	{
		while (*str == c)
		{
			issep = 1;
			str++;
		}
		while (issep && *str != '\0' && *str != c)
		{
			issep = 0;
			i++;
			str++;
		}
		while (!issep && *str != '\0' && *str != c)
			str++;
	}
	return (i);
}

static char		*aword(char *str, char c)
{
	int		l;
	int		i;
	char	*word;

	word = 0;
	l = 0;
	while (*(str + l) != c && *(str + l) != '\0')
		l++;
	word = (char*)malloc(sizeof(char) * (l + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < l)
	{
		*(word + i) = *(str + i);
		i++;
	}
	*(word + l) = '\0';
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	int		words;
	int		i;
	char	**ptr;

	if (s == NULL)
		return (NULL);
	i = 0;
	words = countworlds((char*)s, c);
	ptr = (char**)malloc(sizeof(char*) * (words + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[words] = NULL;
	while (i < words)
	{
		ptr[i] = aword(nword((char*)s, c, i + 1), c);
		if (ptr[i] == NULL)
			return (NULL);
		i++;
	}
	return (ptr);
}
