#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "jsmn.h"

#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dt;
	const char	*sc;
	size_t		i;

	dt = dst;
	sc = src;
	i = 0;
	while (i < n)
	{
		dt[i] = sc[i];
		i++;
	}
	return (dst);
}

int		ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)s)[i] = '\0';
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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

int		ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (!*s++)
			return (NULL);
	return ((char *)s);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char *str;

	if (!(str = (char*)malloc(sizeof(*str) * (ft_strlen(s1) + 1))))
		return (NULL);
	ft_strcpy(str, s1);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*pstr;
	size_t	len1;
	size_t	len2;

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
	t_list *new;

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

int	ft_isspace(int c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

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

char	*ft_parser(void)
{
	if (ft_parse_json(FILE_PATH))
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
