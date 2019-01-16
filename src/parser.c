#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "jsmn.h"

#include <stdio.h>

#include "../includes/rtv1.h"

#define FILE_PATH "test.json"
#define MAX_T 1024
# define BUFF_SIZE	32

// LIBFT

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int		ft_hex_to_int(char *hex)
{
	int		result;
	char	tmp;

	result = 0;
	while (*hex)
	{
		tmp = *hex++;
		if (tmp >= '0' && tmp <= '9')
			tmp -= '0';
		else if (tmp >= 'A' && tmp <= 'F')
			tmp = tmp - 'A' + 10;
		else if (tmp >= 'a' && tmp <= 'f')
			tmp = tmp - 'a' + 10;
		result = (result << 4) | tmp;
	}
	return (result);
}

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

int		ft_strcmp(char *s1, char *s2)
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

double	ft_powd(double nbr, int exp)
{
	double	out;

	out = 1.0;
	while (exp > 0 && --exp)
		out *= nbr;
	while (exp < 0 && ++exp)
		out /= nbr;
	return (out);
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

double	ft_atod(const char *str)
{
	double	out;
	double	sign;
	double	exponent;
	char	*p_tmp;

	p_tmp = (char*)str;
	out = 0.0;
	while (ft_isspace(*p_tmp))
		++p_tmp;
	sign = 1.0;
	if (*p_tmp == '+' || *p_tmp == '-')
		sign = (*p_tmp++ == '-') ? -1.0 : 1.0;
	while (ft_isdigit(*p_tmp))
		out = 10.0 * out + (double)(*p_tmp++ - '0');
	if (*p_tmp == '.' && (exponent = 1.0))
		while (ft_isdigit(*++p_tmp) && (exponent /= 10.0))
			out += exponent * (double)(*p_tmp - '0');
	if (*p_tmp == 'e' || *p_tmp == 'E')
		return (sign * out * ft_powd(10.0, (double)ft_atoi(++p_tmp)));
	return (sign * out);
}

// GET_NEXT_LINE

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

/* PARSER */

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

int		ft_check_camera(char *string, jsmntok_t *tokens, int t)
{
	int i, cam, ant;
	char *str, *attr, *x, *y, *z;
	double	xx, yy, zz;

	i = 0;
	cam = 0;
	ant = 0;
	while(i < t) 
	{
		str = ft_strsub(string, tokens[i].start, tokens[i].end - tokens[i].start);
		if (!ft_strcmp(str, "camera"))
		{
			if (tokens[i+1].size == 2) 
			{
				attr = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
				if (!ft_strcmp(attr, "pos") && tokens[i+3].size == 3)
				{
					x = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);
					y = ft_strsub(string, tokens[i+5].start, tokens[i+5].end - tokens[i+5].start);
					z = ft_strsub(string, tokens[i+6].start, tokens[i+6].end - tokens[i+6].start);

					xx = ft_atod(x);
					yy = ft_atod(y);
					zz = ft_atod(z);

					if ((xx < -1000 || xx > 1000) ||  (yy < -1000 || yy > 1000) || (zz < -1000 || zz > 1000))
					{
						free(x);
						free(y);
						free(z);
						free(str);
						return (1);
					}
					/* ADD CAMERA */
					ant += 10;

					free(x);
					free(y);
					free(z);
				}
				free(attr);

				attr = ft_strsub(string, tokens[i+7].start, tokens[i+7].end - tokens[i+7].start);
				if (!ft_strcmp(attr, "dir") && tokens[i+8].size == 3)
				{
					x = ft_strsub(string, tokens[i+9].start, tokens[i+9].end - tokens[i+9].start);
					y = ft_strsub(string, tokens[i+10].start, tokens[i+10].end - tokens[i+10].start);
					z = ft_strsub(string, tokens[i+11].start, tokens[i+11].end - tokens[i+11].start);

					printf("dir x %f\n", ft_atod(x));
					printf("dir y %f\n", ft_atod(y));
					printf("dir z %f\n", ft_atod(z));
					ant += 20;
					free(x);
					free(y);
					free(z);
				}
				free(attr);
			}
			cam++;
		}
		free(str);
		i++;
	}
	if (cam != 1 || ant != 30)
		return (1);
	return (0);
}

int		ft_check_alight(char *string) {
	int		i,t;
	char	*str, *x;

	jsmn_parser parser;
	jsmntok_t tokens[MAX_T];

	i = 0;
	jsmn_init(&parser);
	t = jsmn_parse(&parser, string, ft_strlen(string), tokens, MAX_T);

	while(i < t) 
	{
		str = ft_strsub(string, tokens[i].start, tokens[i].end - tokens[i].start);
		if (!ft_strcmp(str, "intensity") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			add_ambient_light(&(g_app->scene.lights), ft_atod(x));
			free(x);
		}	
		free(str);
		i++;
	}

	free(string);

	return (0);
}

int		ft_check_plight(char *string) {
	int		ant,i,t;
	char	*str, *x, *y, *z;
	double	xx, yy, zz, intensity;

	jsmn_parser parser;
	jsmntok_t tokens[MAX_T];

	i = 0;
	ant = 0;
	jsmn_init(&parser);
	t = jsmn_parse(&parser, string, ft_strlen(string), tokens, MAX_T);

	while(i < t) 
	{
		str = ft_strsub(string, tokens[i].start, tokens[i].end - tokens[i].start);
		if (!ft_strcmp(str, "intensity") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			xx = ft_atod(x);
			if (xx < 0 || xx > 1)
			{
				free(x);
				free(str);
				return (1);
			}
			intensity = xx;
			ant += 10;
			free(x);
		}
		free(str);	
		i++;
	}
	i = 0;
	while(i < t) 
	{
		str = ft_strsub(string, tokens[i].start, tokens[i].end - tokens[i].start);
		if (!ft_strcmp(str, "pos") && tokens[i+1].size == 3)
		{
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			xx = ft_atod(x);
			yy = ft_atod(y);
			zz = ft_atod(z);

			if ((xx < -1000 || xx > 1000) ||  (yy < -1000 || yy > 1000) || (zz < -1000 || zz > 1000))
			{
				free(x);
				free(y);
				free(z);
				free(str);
				return (1);
			}

			add_point_light(&(g_app->scene.lights), (t_vector) {xx, yy, zz}, intensity);
			ant += 20;

			free(x);
			free(y);
			free(z);
		}
		
		free(str);
		i++;
	}

	free(string);

	if (ant != 30)
		return (1);
	return (0);
}

int		ft_check_plane(char *string, t_primitive *p) {
	int		i,t;
	char	*str, *x, *y, *z;

	p = add_plane(A_PR, (t_vector) {0, 0, 0},
			(t_vector) {0, 0, 0}, 0xFF00FF);

	jsmn_parser parser;
	jsmntok_t tokens[MAX_T];

	i = 0;
	jsmn_init(&parser);
	t = jsmn_parse(&parser, string, ft_strlen(string), tokens, MAX_T);
	while(i < t) 
	{
		str = ft_strsub(string, tokens[i].start, tokens[i].end - tokens[i].start);
		if (!ft_strcmp(str, "pos") && tokens[i+1].size == 3) {
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			p->p.plane.position = (t_vector) {ft_atod(x), ft_atod(y), ft_atod(z)};

			printf("plane_pos x %f\n", ft_atod(x));
			printf("plane_pos y %f\n", ft_atod(y));
			printf("plane_pos z %f\n", ft_atod(z));


			free(x);
			free(y);
			free(z);
		}
		if (!ft_strcmp(str, "normal") && tokens[i+1].size == 3) {
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			p->p.plane.normal = (t_vector) {ft_atod(x), ft_atod(y), ft_atod(z)};

			printf("plane_n x %f\n", ft_atod(x));
			printf("plane_n y %f\n", ft_atod(y));
			printf("plane_n z %f\n", ft_atod(z));


			free(x);
			free(y);
			free(z);
		}
		if (!ft_strcmp(str, "dir") && tokens[i+1].size == 3) {
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			printf("plane_dir x %f\n", ft_atod(x));
			printf("plane_dir y %f\n", ft_atod(y));
			printf("plane_dir z %f\n", ft_atod(z));
			free(x);
			free(y);
			free(z);
		}
		if (!ft_strcmp(str, "rot") && tokens[i+1].size == 3) {
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			printf("sph_rot x %f\n", ft_atod(x));
			printf("sph_rot y %f\n", ft_atod(y));
			printf("sph_rot z %f\n", ft_atod(z));

			p->rotation = (t_vector){ft_atod(x), ft_atod(y), ft_atod(z)};

			free(x);
			free(y);
			free(z);
		}
		if (!ft_strcmp(str, "color") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			p->color = ft_hex_to_int(x);
			free(x);
		}
		if (!ft_strcmp(str, "refl") && tokens[i].size == 1) {
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);

			printf("plane_refl %f\n", ft_atod(x));
			p->reflection = ft_atod(x);

			free(x);
		}
		if (!ft_strcmp(str, "spec") && tokens[i].size == 1) {
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);

			printf("plane_spec %f\n", ft_atod(x));
			p->specular = ft_atod(x);

			free(x);
		}
		free(str);
		i++;
	}

	free(string);

	return (0);
}


int		ft_check_sphere(char *string, t_primitive *p) 
{
	int		ant,i,t;
	char	*str, *x, *y, *z;
	double	xx, yy, zz;
	jsmn_parser parser;
	jsmntok_t tokens[MAX_T];

	i = 0;
	ant = 0;
	p = add_sphere(A_PR, (t_vector) {0, 0, 0}, 1, 0xFFFFFF);
	jsmn_init(&parser);
	t = jsmn_parse(&parser, string, ft_strlen(string), tokens, MAX_T);
	while(i < t) 
	{
		str = ft_strsub(string, tokens[i].start, tokens[i].end - tokens[i].start);
		if (!ft_strcmp(str, "pos") && tokens[i+1].size == 3)
		{
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			xx = ft_atod(x);
			yy = ft_atod(y);
			zz = ft_atod(z);

			if ((xx < -1000 || xx > 1000) ||  (yy < -1000 || yy > 1000) || (zz < -1000 || zz > 1000))
			{
				free(x);
				free(y);
				free(z);
				free(str);
				return (1);
			}
			p->p.sphere.position = (t_vector) {xx, yy, zz};
			ant += 10;

			free(x);
			free(y);
			free(z);
		}
		if (!ft_strcmp(str, "dir") && tokens[i+1].size == 3) {
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			printf("sph_dir x %f\n", ft_atod(x));
			printf("sph_dir y %f\n", ft_atod(y));
			printf("sph_dir z %f\n", ft_atod(z));
			ant += 20;

			free(x);
			free(y);
			free(z);
		}
		if (!ft_strcmp(str, "rot") && tokens[i+1].size == 3) {
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			xx = ft_atod(x);
			yy = ft_atod(y);
			zz = ft_atod(z);

			if ((xx < -180 || xx > 180) || (yy < -180 || yy > 180) || (zz < -180 || zz > 180))
			{
				free(x);
				free(y);
				free(z);
				free(str);
				return (1);
			}

			p->rotation = (t_vector){xx, yy, zz};
			ant += 30;

			free(x);
			free(y);
			free(z);
		}
		if (!ft_strcmp(str, "color") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			p->color = ft_hex_to_int(x);
			ant += 40;

			free(x);
		}
		if (!ft_strcmp(str, "size") && tokens[i].size == 1) {
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);

			xx = ft_atod(x);
			if (xx <= 0 || xx >= 1000)
			{
				free(x);
				free(str);
				return (1);
			}

			p->p.sphere.radius = xx;
			p->p.sphere.radius2 = xx * xx;
			ant += 50;

			free(x);
		}
		if (!ft_strcmp(str, "refl") && tokens[i].size == 1) {
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);

			xx = ft_atod(x);
			if (xx < 0 || xx >= 1)
			{
				free(x);
				free(str);
				return (1);
			}
			p->reflection = xx;
			ant += 60;

			free(x);
		}
		if (!ft_strcmp(str, "spec") && tokens[i].size == 1) {
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);

			xx = ft_atod(x);
			if (xx < 0 && xx != -1)
			{
				free(x);
				free(str);
				return (1);
			}
			p->specular = xx;
			ant += 70;

			free(x);
		}
		free(str);
		i++;
	}

	free(string);

	if (ant != 280)
		return (1);
	return (0);
}

int		ft_check_scene(char *string, jsmntok_t *tokens, int t)
{
	int i;
	int scene;
	char *str;
    t_primitive *p;
	g_app->scene.primitives = NULL;
	g_app->scene.lights = NULL;

	i = 0;
	scene = 0;
	while(i < t) 
	{
		str = ft_strsub(string, tokens[i].start, tokens[i].end - tokens[i].start);
		if (!ft_strcmp(str, "scene"))
			scene++;
		if (scene == 1 && !ft_strcmp(str, "sphere") && tokens[i+1].size == 7)
		{
			if (ft_check_sphere(ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start), p))
				return (1);
		}
		if (scene == 1 && !ft_strcmp(str, "plane") && tokens[i+1].size == 7)
		{
			if (ft_check_plane(ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start), p))
				return (1);
		}
		if (scene == 1 && !ft_strcmp(str, "point_light") && tokens[i+1].size == 2)
		{
			if (ft_check_plight(ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start)))
				return (1);
		}
		if (scene == 1 && !ft_strcmp(str, "ambient_light") && tokens[i+1].size == 1)
		{
			if (ft_check_alight(ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start)))
				return (1);
		}
		free(str);
		i++;
	}

	if (scene != 1)
		return (1);
	return (0);
}

int		ft_parse_JSON(char *filepath)
{
	int		i;
	int		t;
	char	*string;

	//jsmn
	jsmn_parser parser;
	jsmntok_t tokens[MAX_T];

	i = 0;
	if (!(string = ft_read_file(filepath)))
		return (1);

	printf("JSON: %s\n", string);


	jsmn_init(&parser);
	// string - pointer to JSON string
	// tokens - an array of tokens available
	// MAX_T - number of tokens available
	t = jsmn_parse(&parser, string, ft_strlen(string), tokens, MAX_T);
	// if (ft_check_camera(string, tokens, t) || ft_check_camera_attr(string, tokens, t))
	if (ft_check_camera(string, tokens, t) || ft_check_scene(string, tokens, t))
	{
		return (1);
	}
	
	return (0);
}

char	*ft_parser(void)
{
	if (ft_parse_JSON(FILE_PATH))
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