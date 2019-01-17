#include "jsmn.h"

/**
 * Allocates a fresh unused token from the token pool.
 */
static jsmntok_t *jsmn_alloc_token(jsmn_parser *parser,
		jsmntok_t *tokens, size_t num_tokens) {
	jsmntok_t *tok;
	if (parser->toknext >= num_tokens) {
		return NULL;
	}
	tok = &tokens[parser->toknext++];
	tok->start = tok->end = -1;
	tok->size = 0;
#ifdef JSMN_PARENT_LINKS
	tok->parent = -1;
#endif
	return tok;
}

/**
 * Fills token type and boundaries.
 */
static void jsmn_fill_token(jsmntok_t *token, jsmntype_t type,
                            int start, int end) {
	token->type = type;
	token->start = start;
	token->end = end;
	token->size = 0;
}

/**
 * Fills next available token with JSON primitive.
 */
static int jsmn_parse_primitive(jsmn_parser *parser, const char *js,
		size_t len, jsmntok_t *tokens, size_t num_tokens) {
	jsmntok_t *token;
	int start;

	start = parser->pos;

	for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++) {
		switch (js[parser->pos]) {
#ifndef JSMN_STRICT
			/* In strict mode primitive must be followed by "," or "}" or "]" */
			case ':':
#endif
			case '\t' : case '\r' : case '\n' : case ' ' :
			case ','  : case ']'  : case '}' :
				goto found;
		}
		if (js[parser->pos] < 32 || js[parser->pos] >= 127) {
			parser->pos = start;
			return JSMN_ERROR_INVAL;
		}
	}
#ifdef JSMN_STRICT
	/* In strict mode primitive must be followed by a comma/object/array */
	parser->pos = start;
	return JSMN_ERROR_PART;
#endif

found:
	if (tokens == NULL) {
		parser->pos--;
		return 0;
	}
	token = jsmn_alloc_token(parser, tokens, num_tokens);
	if (token == NULL) {
		parser->pos = start;
		return JSMN_ERROR_NOMEM;
	}
	jsmn_fill_token(token, JSMN_PRIMITIVE, start, parser->pos);
#ifdef JSMN_PARENT_LINKS
	token->parent = parser->toksuper;
#endif
	parser->pos--;
	return 0;
}

/**
 * Fills next token with JSON string.
 */
static int jsmn_parse_string(jsmn_parser *parser, const char *js,
		size_t len, jsmntok_t *tokens, size_t num_tokens) {
	jsmntok_t *token;

	int start = parser->pos;

	parser->pos++;

	/* Skip starting quote */
	for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++) {
		char c = js[parser->pos];

		/* Quote: end of string */
		if (c == '\"') {
			if (tokens == NULL) {
				return 0;
			}
			token = jsmn_alloc_token(parser, tokens, num_tokens);
			if (token == NULL) {
				parser->pos = start;
				return JSMN_ERROR_NOMEM;
			}
			jsmn_fill_token(token, JSMN_STRING, start+1, parser->pos);
#ifdef JSMN_PARENT_LINKS
			token->parent = parser->toksuper;
#endif
			return 0;
		}

		/* Backslash: Quoted symbol expected */
		if (c == '\\' && parser->pos + 1 < len) {
			int i;
			parser->pos++;
			switch (js[parser->pos]) {
				/* Allowed escaped symbols */
				case '\"': case '/' : case '\\' : case 'b' :
				case 'f' : case 'r' : case 'n'  : case 't' :
					break;
				/* Allows escaped symbol \uXXXX */
				case 'u':
					parser->pos++;
					for(i = 0; i < 4 && parser->pos < len && js[parser->pos] != '\0'; i++) {
						/* If it isn't a hex character we have an error */
						if(!((js[parser->pos] >= 48 && js[parser->pos] <= 57) || /* 0-9 */
									(js[parser->pos] >= 65 && js[parser->pos] <= 70) || /* A-F */
									(js[parser->pos] >= 97 && js[parser->pos] <= 102))) { /* a-f */
							parser->pos = start;
							return JSMN_ERROR_INVAL;
						}
						parser->pos++;
					}
					parser->pos--;
					break;
				/* Unexpected symbol */
				default:
					parser->pos = start;
					return JSMN_ERROR_INVAL;
			}
		}
	}
	parser->pos = start;
	return JSMN_ERROR_PART;
}

/**
 * Parse JSON string and fill tokens.
 */
int jsmn_parse(jsmn_parser *parser, const char *js, size_t len,
		jsmntok_t *tokens, unsigned int num_tokens) {
	int r;
	int i;
	jsmntok_t *token;
	int count = parser->toknext;

	for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++) {
		char c;
		jsmntype_t type;

		c = js[parser->pos];
		switch (c) {
			case '{': case '[':
				count++;
				if (tokens == NULL) {
					break;
				}
				token = jsmn_alloc_token(parser, tokens, num_tokens);
				if (token == NULL)
					return JSMN_ERROR_NOMEM;
				if (parser->toksuper != -1) {
					tokens[parser->toksuper].size++;
#ifdef JSMN_PARENT_LINKS
					token->parent = parser->toksuper;
#endif
				}
				token->type = (c == '{' ? JSMN_OBJECT : JSMN_ARRAY);
				token->start = parser->pos;
				parser->toksuper = parser->toknext - 1;
				break;
			case '}': case ']':
				if (tokens == NULL)
					break;
				type = (c == '}' ? JSMN_OBJECT : JSMN_ARRAY);
#ifdef JSMN_PARENT_LINKS
				if (parser->toknext < 1) {
					return JSMN_ERROR_INVAL;
				}
				token = &tokens[parser->toknext - 1];
				for (;;) {
					if (token->start != -1 && token->end == -1) {
						if (token->type != type) {
							return JSMN_ERROR_INVAL;
						}
						token->end = parser->pos + 1;
						parser->toksuper = token->parent;
						break;
					}
					if (token->parent == -1) {
						if(token->type != type || parser->toksuper == -1) {
							return JSMN_ERROR_INVAL;
						}
						break;
					}
					token = &tokens[token->parent];
				}
#else
				for (i = parser->toknext - 1; i >= 0; i--) {
					token = &tokens[i];
					if (token->start != -1 && token->end == -1) {
						if (token->type != type) {
							return JSMN_ERROR_INVAL;
						}
						parser->toksuper = -1;
						token->end = parser->pos + 1;
						break;
					}
				}
				/* Error if unmatched closing bracket */
				if (i == -1) return JSMN_ERROR_INVAL;
				for (; i >= 0; i--) {
					token = &tokens[i];
					if (token->start != -1 && token->end == -1) {
						parser->toksuper = i;
						break;
					}
				}
#endif
				break;
			case '\"':
				r = jsmn_parse_string(parser, js, len, tokens, num_tokens);
				if (r < 0) return r;
				count++;
				if (parser->toksuper != -1 && tokens != NULL)
					tokens[parser->toksuper].size++;
				break;
			case '\t' : case '\r' : case '\n' : case ' ':
				break;
			case ':':
				parser->toksuper = parser->toknext - 1;
				break;
			case ',':
				if (tokens != NULL && parser->toksuper != -1 &&
						tokens[parser->toksuper].type != JSMN_ARRAY &&
						tokens[parser->toksuper].type != JSMN_OBJECT) {
#ifdef JSMN_PARENT_LINKS
					parser->toksuper = tokens[parser->toksuper].parent;
#else
					for (i = parser->toknext - 1; i >= 0; i--) {
						if (tokens[i].type == JSMN_ARRAY || tokens[i].type == JSMN_OBJECT) {
							if (tokens[i].start != -1 && tokens[i].end == -1) {
								parser->toksuper = i;
								break;
							}
						}
					}
#endif
				}
				break;
#ifdef JSMN_STRICT
			/* In strict mode primitives are: numbers and booleans */
			case '-': case '0': case '1' : case '2': case '3' : case '4':
			case '5': case '6': case '7' : case '8': case '9':
			case 't': case 'f': case 'n' :
				/* And they must not be keys of the object */
				if (tokens != NULL && parser->toksuper != -1) {
					jsmntok_t *t = &tokens[parser->toksuper];
					if (t->type == JSMN_OBJECT ||
							(t->type == JSMN_STRING && t->size != 0)) {
						return JSMN_ERROR_INVAL;
					}
				}
#else
			/* In non-strict mode every unquoted value is a primitive */
			default:
#endif
				r = jsmn_parse_primitive(parser, js, len, tokens, num_tokens);
				if (r < 0) return r;
				count++;
				if (parser->toksuper != -1 && tokens != NULL)
					tokens[parser->toksuper].size++;
				break;

#ifdef JSMN_STRICT
			/* Unexpected char in strict mode */
			default:
				return JSMN_ERROR_INVAL;
#endif
		}
	}

	if (tokens != NULL) {
		for (i = parser->toknext - 1; i >= 0; i--) {
			/* Unmatched opened object or array */
			if (tokens[i].start != -1 && tokens[i].end == -1) {
				return JSMN_ERROR_PART;
			}
		}
	}

	return count;
}

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

int		jsmn_cam(char *string, jsmntok_t *tokens, int t)
{
	int				i, cam, ant;
	char			*str, *attr, *x, *y, *z;
	double			xx, yy, zz;

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

					free(x);
					free(y);
					free(z);

					if ((xx < -1000 || xx > 1000) ||  (yy < -1000 || yy > 1000) || (zz < -1000 || zz > 1000))
					{
						free(attr);
						free(str);
						return (1);
					}
					g_app->camera.position = (t_vector) {xx, yy, zz};
					ant += 10;
				}
				free(attr);
				attr = ft_strsub(string, tokens[i+7].start, tokens[i+7].end - tokens[i+7].start);
				if (!ft_strcmp(attr, "dir") && tokens[i+8].size == 3)
				{
					x = ft_strsub(string, tokens[i+9].start, tokens[i+9].end - tokens[i+9].start);
					y = ft_strsub(string, tokens[i+10].start, tokens[i+10].end - tokens[i+10].start);
					z = ft_strsub(string, tokens[i+11].start, tokens[i+11].end - tokens[i+11].start);

					xx = ft_atod(x);
					yy = ft_atod(y);
					zz = ft_atod(z);

					free(x);
					free(y);
					free(z);
					
					if ((xx < -1 || xx > 1) ||  (yy < -1 || yy > 1) || (zz < -1 || zz > 1))
					{
						free(attr);
						free(str);
						return (1);
					}
					g_app->camera.direction = (t_vector) {xx, yy, zz};
					ant += 20;
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

int		jsmn_al(char *string) 
{
	int				ant,i,t;
	char			*str, *x;
	double			xx;
	jsmntok_t		tokens[MAX_T];
	jsmn_parser		parser;

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

			free(x);
			if (xx < 0 || xx > 1)
			{
				free(str);
				free(string);
				return (1);
			}
			add_ambient_light(&(g_app->scene.lights), xx);
			ant += 10;
		}
		free(str);
		i++;
	}
	free(string);
	if (ant != 10)
		return (1);
	return (0);
}

int		jsmn_pl(char *string) 
{
	int				ant,i,t;
	char			*str, *x, *y, *z;
	double			xx, yy, zz, intensity;
	jsmntok_t		tokens[MAX_T];
	jsmn_parser		parser;

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
			
			free(x);
			if (xx < 0 || xx > 1)
			{
				free(str);
				free(string);
				return (1);
			}
			intensity = xx;
			ant += 10;
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

			free(x);
			free(y);
			free(z);

			if ((xx < -1000 || xx > 1000) ||  (yy < -1000 || yy > 1000) || (zz < -1000 || zz > 1000))
			{
				free(str);
				free(string);
				return (1);
			}
			add_point_light(&(g_app->scene.lights), (t_vector) {xx, yy, zz}, intensity);
			ant += 20;
		}
		free(str);
		i++;
	}
	free(string);

	if (ant != 30)
		return (1);
	return (0);
}

int		jsmn_dl(char *string) 
{
	int				ant,i,t;
	char			*str, *x, *y, *z;
	double			xx, yy, zz, intensity;
	jsmntok_t		tokens[MAX_T];
	jsmn_parser		parser;

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

			free(x);

			if (xx < 0 || xx > 1)
			{
				free(str);
				free(string);
				return (1);
			}
			intensity = xx;
			ant += 10;
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

			free(x);
			free(y);
			free(z);

			if ((xx < -1000 || xx > 1000) ||  (yy < -1000 || yy > 1000) || (zz < -1000 || zz > 1000))
			{
				free(str);
				free(string);
				return (1);
			}
			add_directional_light(&(g_app->scene.lights), (t_vector) {xx, yy, zz}, intensity);
			ant += 20;
		}
		free(str);
		i++;
	}
	free(string);

	if (ant != 30)
		return (1);
	return (0);
}

int		jsmn_plane(char *string, t_primitive *p) 
{
	int				ant,i,t;
	char			*str, *x, *y, *z;
	double			xx, yy, zz;
	jsmntok_t		tokens[MAX_T];
	jsmn_parser		parser;

	p = add_plane(A_PR, (t_vector) {0, 0, 0},
			(t_vector) {0, 0, 0}, 0xFF00FF);
	i = 0;
	ant = 0;
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

			free(x);
			free(y);
			free(z);

			if ((xx < -1000 || xx > 1000) ||  (yy < -1000 || yy > 1000) || (zz < -1000 || zz > 1000))
			{
				free(str);
				free(string);
				return (1);
			}
			p->p.plane.position = (t_vector) {xx, yy, zz};
			ant += 10;
		}
		if (!ft_strcmp(str, "dir") && tokens[i+1].size == 3)
		{
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			xx = ft_atod(x);
			yy = ft_atod(y);
			zz = ft_atod(z);

			free(x);
			free(y);
			free(z);

			if ((xx < -1 || xx > 1) ||  (yy < -1 || yy > 1) || (zz < -1 || zz > 1))
			{
				free(str);
				free(string);
				return (1);
			}
			p->p.plane.normal = (t_vector) {xx, yy, zz};
			ant += 20;
		}
		if (!ft_strcmp(str, "rot") && tokens[i+1].size == 3) 
		{
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			xx = ft_atod(x);
			yy = ft_atod(y);
			zz = ft_atod(z);

			free(x);
			free(y);
			free(z);

			if ((xx * xx) + (yy * yy) + (zz * zz)) != 1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->rotation = (t_vector){xx, yy, zz};
			ant += 30;
		}
		if (!ft_strcmp(str, "color") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			p->color = ft_hex_to_int(x);
			ant += 40;

			free(x);
		}
		if (!ft_strcmp(str, "refl") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			xx = ft_atod(x);

			free(x);
			
			if (xx < 0 || xx >= 1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->reflection = xx;
			ant += 50;
		}
		if (!ft_strcmp(str, "spec") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			xx = ft_atod(x);

			free(x);

			if (xx < 0 && xx != -1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->specular = xx;
			ant += 60;
		}
		free(str);
		i++;
	}
	free(string);

	if (ant != 210)
		return (1);
	return (0);
}

int		jsmn_cyl(char *string, t_primitive *p) 
{
	int				ant,i,t;
	char			*str, *x, *y, *z;
	double			xx, yy, zz;
	jsmntok_t		tokens[MAX_T];
	jsmn_parser		parser;

	i = 0;
	ant = 0;
	p = add_cylinder(A_PR, (t_ray){{0, 0, 0}, {0, 0, 0}}, 1, 0xFFFFFF);
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

			free(x);
			free(y);
			free(z);
		
			if ((xx < -1000 || xx > 1000) ||  (yy < -1000 || yy > 1000) || (zz < -1000 || zz > 1000))
			{
				free(str);
				free(string);
				return (1);
			}
			p->p.cylinder.position = (t_vector) {xx, yy, zz};
			ant += 10;
		}
		if (!ft_strcmp(str, "rot") && tokens[i+1].size == 3) 
		{
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			xx = ft_atod(x);
			yy = ft_atod(y);
			zz = ft_atod(z);

			free(x);
			free(y);
			free(z);
	
			if ((xx * xx) + (yy * yy) + (zz * zz)) != 1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->rotation = (t_vector){xx, yy, zz};
			ant += 20;
		}
		if (!ft_strcmp(str, "color") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			p->color = ft_hex_to_int(x);
			ant += 30;

			free(x);
		}
		if (!ft_strcmp(str, "size") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			xx = ft_atod(x);
				
			free(x);

			if (xx <= 0 || xx >= 1000)
			{
				free(str);
				free(string);
				return (1);
			}
			p->p.cylinder.radius = xx;
			p->p.cylinder.radius2 = xx * xx;
			ant += 40;
		}
		if (!ft_strcmp(str, "refl") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			xx = ft_atod(x);

			free(x);

			if (xx < 0 || xx >= 1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->reflection = xx;
			ant += 50;
		}
		if (!ft_strcmp(str, "spec") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			xx = ft_atod(x);

			free(x);

			if (xx < 0 && xx != -1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->specular = xx;
			ant += 60;
		}
		if (!ft_strcmp(str, "dir") && tokens[i+1].size == 3)
		{
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			xx = ft_atod(x);
			yy = ft_atod(y);
			zz = ft_atod(z);

			free(x);
			free(y);
			free(z);
	
			if ((xx < -1 || xx > 1) ||  (yy < -1 || yy > 1) || (zz < -1 || zz > 1))
			{
				free(str);
				free(string);
				return (1);
			}
			p->p.cylinder.normal = (t_vector) {xx, yy, zz};
			ant += 70;
		}
		free(str);
		i++;
	}
	free(string);

	if (ant != 280)
		return (1);
	return (0);
}

int		jsmn_cone(char *string, t_primitive *p) 
{
	int				ant,i,t;
	char			*str, *x, *y, *z;
	double			xx, yy, zz;
	jsmntok_t		tokens[MAX_T];
	jsmn_parser		parser;

	i = 0;
	ant = 0;
	p = add_cone(A_PR, (t_vector) {0, 0, 0}, (t_vector) {0, 0, 0}, 0xFFFFFF);
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

			free(x);
			free(y);
			free(z);
	
			if ((xx < -1000 || xx > 1000) ||  (yy < -1000 || yy > 1000) || (zz < -1000 || zz > 1000))
			{
				free(str);
				free(string);
				return (1);
			}
			p->p.cone.position = (t_vector) {xx, yy, zz};
			ant += 10;
		}
		if (!ft_strcmp(str, "rot") && tokens[i+1].size == 3) 
		{
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			xx = ft_atod(x);
			yy = ft_atod(y);
			zz = ft_atod(z);

			free(x);
			free(y);
			free(z);
	
			if ((xx * xx) + (yy * yy) + (zz * zz)) != 1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->rotation = (t_vector){xx, yy, zz};
			ant += 20;
		}
		if (!ft_strcmp(str, "color") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			p->color = ft_hex_to_int(x);
			ant += 30;

			free(x);
		}
		if (!ft_strcmp(str, "angle") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			xx = ft_atod(x);

			free(x);
			
			if (xx < 0 || xx > 1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->p.cone.angle = xx;
			ant += 40;
		}
		if (!ft_strcmp(str, "refl") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			xx = ft_atod(x);
			free(x);
			
			if (xx < 0 || xx >= 1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->reflection = xx;
			ant += 50;
		}
		if (!ft_strcmp(str, "spec") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			xx = ft_atod(x);

			free(x);
			
			if (xx < 0 && xx != -1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->specular = xx;
			ant += 60;
		}
		if (!ft_strcmp(str, "dir") && tokens[i+1].size == 3)
		{
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			xx = ft_atod(x);
			yy = ft_atod(y);
			zz = ft_atod(z);

			free(x);
			free(y);
			free(z);
			
			if ((xx < -1 || xx > 1) ||  (yy < -1 || yy > 1) || (zz < -1 || zz > 1))
			{
				free(str);
				free(string);
				return (1);
			}
			p->p.cone.normal = (t_vector) {xx, yy, zz};
			ant += 70;
		}
		free(str);
		i++;
	}
	free(string);

	if (ant != 280)
		return (1);
	return (0);
}

int		jsmn_sph(char *string, t_primitive *p) 
{
	int				ant,i,t;
	char			*str, *x, *y, *z;
	double			xx, yy, zz;
	jsmntok_t		tokens[MAX_T];
	jsmn_parser		parser;

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

			free(x);
			free(y);
			free(z);
		
			if ((xx < -1000 || xx > 1000) ||  (yy < -1000 || yy > 1000) || (zz < -1000 || zz > 1000))
			{
				free(str);
				free(string);
				return (1);
			}
			p->p.sphere.position = (t_vector) {xx, yy, zz};
			ant += 10;
		}
		if (!ft_strcmp(str, "rot") && tokens[i+1].size == 3) 
		{
			x = ft_strsub(string, tokens[i+2].start, tokens[i+2].end - tokens[i+2].start);
			y = ft_strsub(string, tokens[i+3].start, tokens[i+3].end - tokens[i+3].start);
			z = ft_strsub(string, tokens[i+4].start, tokens[i+4].end - tokens[i+4].start);

			xx = ft_atod(x);
			yy = ft_atod(y);
			zz = ft_atod(z);

			free(x);
			free(y);
			free(z);

			if ((xx * xx) + (yy * yy) + (zz * zz)) != 1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->rotation = (t_vector){xx, yy, zz};
			ant += 20;
		}
		if (!ft_strcmp(str, "color") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			p->color = ft_hex_to_int(x);
			ant += 30;

			free(x);
		}
		if (!ft_strcmp(str, "size") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			xx = ft_atod(x);

			free(x);

			if (xx <= 0 || xx >= 1000)
			{
				free(str);
				free(string);
				return (1);
			}
			p->p.sphere.radius = xx;
			p->p.sphere.radius2 = xx * xx;
			ant += 40;
		}
		if (!ft_strcmp(str, "refl") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			xx = ft_atod(x);
			
			free(x);
			
			if (xx < 0 || xx >= 1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->reflection = xx;
			ant += 50;
		}
		if (!ft_strcmp(str, "spec") && tokens[i].size == 1) 
		{
			x = ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);
			xx = ft_atod(x);

			free(x);
			
			if (xx < 0 && xx != -1)
			{
				free(str);
				free(string);
				return (1);
			}
			p->specular = xx;
			ant += 60;
		}
		free(str);
		i++;
	}
	free(string);

	if (ant != 210)
		return (1);
	return (0);
}


int		jsmn_obj(char *string) 
{
	int				i,t;
	char			*str;
	jsmntok_t		tokens[MAX_T];
	t_primitive		*p;
	jsmn_parser		parser;

	i = 0;
	jsmn_init(&parser);
	t = jsmn_parse(&parser, string, ft_strlen(string), tokens, MAX_T);
	g_app->scene.primitives = NULL;
	g_app->scene.lights = NULL;
	while(i < t) 
	{
		str = ft_strsub(string, tokens[i].start, tokens[i].end - tokens[i].start);
		if (!ft_strcmp(str, "sphere"))
		{
			if (tokens[i+1].size != 6 || 
				jsmn_sph(ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start), p))
			{
				free(str);
				free(string);
				return (1);
			}
		}
		if (!ft_strcmp(str, "cylinder"))
		{
			if (tokens[i+1].size != 7 || 
				jsmn_cyl(ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start), p))
			{
				free(str);
				free(string);
				return (1);
			}
		}
		if (!ft_strcmp(str, "cone"))
		{
			if (tokens[i+1].size != 7 ||
				jsmn_cone(ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start), p))
			{
				free(str);
				free(string);
				return (1);
			}
		}
		if (!ft_strcmp(str, "plane"))
		{
			if (tokens[i+1].size != 6 ||
				jsmn_plane(ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start), p))
			{
				free(str);
				free(string);
				return (1);
			}
		}
		if (!ft_strcmp(str, "point_light"))
		{
			if (tokens[i+1].size != 2 || 
				jsmn_pl(ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start)))
			{
				free(str);
				free(string);
				return (1);
			}
		}
		if (!ft_strcmp(str, "ambient_light"))
		{
			if (tokens[i+1].size != 1 || 
				jsmn_al(ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start)))
			{
				free(str);
				free(string);
				return (1);
			}
		}
		if (!ft_strcmp(str, "directional_light"))
		{
			if (tokens[i+1].size != 2 || 
				jsmn_dl(ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start)))
			{
				free(str);
				free(string);
				return (1);
			}
		}
		free(str);
		i++;
	}
	free(string);
	return (0);
}


int		jsmn_sc(char *string, jsmntok_t *tokens, int t)
{
	int		i, scene;
	char	*str;

	i = 0;
	scene = 0;
	while(i < t) 
	{
		str = ft_strsub(string, tokens[i].start, tokens[i].end - tokens[i].start);
		if (!ft_strcmp(str, "scene"))
		{
			if (!scene)
			{
				if (jsmn_obj(ft_strsub(string, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start)))
				{
					free(str);
					free(string);
					return (1);
				}
			}
			scene++;
		}
		free(str);
		i++;
	}
	free(string);

	if (scene > 1)
		return (1);
	return (0);
}

/**
 * Creates a new parser based over a given  buffer with an array of tokens
 * available.
 */
void jsmn_init(jsmn_parser *parser) {
	parser->pos = 0;
	parser->toknext = 0;
	parser->toksuper = -1;
}

