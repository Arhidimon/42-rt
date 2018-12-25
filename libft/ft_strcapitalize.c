/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezruch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:28:17 by dbezruch          #+#    #+#             */
/*   Updated: 2017/11/07 15:28:19 by dbezruch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcapitalize(char *str)
{
	char	*strcopy;
	int		doupper;
	int		t;

	doupper = 1;
	strcopy = str;
	while (*strcopy != '\0')
	{
		if (*strcopy >= 'A' && *strcopy <= 'Z')
			t = 1;
		else if (*strcopy >= 'a' && *strcopy <= 'z')
			t = -1;
		else if (*strcopy >= '0' && *strcopy <= '9')
			t = 0;
		else
			t = 2;
		if ((doupper == 0 && t == 1) || (t == -1 && doupper == 1))
			*strcopy += t * 32;
		if (t == 2)
			doupper = 1;
		else
			doupper = 0;
		strcopy++;
	}
	return (str);
}
