#ifndef __JSMN_H_
#define __JSMN_H_
#define MAX_T 1024
#define BUFF_SIZE	32
#define FILE_PATH "test.json"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/rtv1.h"
#include "../libft/includes/libft.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * JSON type identifier. Basic types are:
 * 	o Object
 * 	o Array
 * 	o String
 * 	o Other primitive: number, boolean (true/false) or null
 */
typedef enum {
	JSMN_UNDEFINED = 0,
	JSMN_OBJECT = 1,
	JSMN_ARRAY = 2,
	JSMN_STRING = 3,
	JSMN_PRIMITIVE = 4
} jsmntype_t;

// typedef struct		s_list
// {
// 	void			*content;
// 	size_t			content_size;
// 	struct s_list	*next;
// }					t_list;

enum jsmnerr {
	/* Not enough tokens were provided */
	JSMN_ERROR_NOMEM = -1,
	/* Invalid character inside JSON string */
	JSMN_ERROR_INVAL = -2,
	/* The string is not a full JSON packet, more bytes expected */
	JSMN_ERROR_PART = -3
};

/**
 * JSON token description.
 * type		type (object, array, string etc.)
 * start	start position in JSON data string
 * end		end position in JSON data string
 */
typedef struct {
	jsmntype_t type;
	int start;
	int end;
	int size;
#ifdef JSMN_PARENT_LINKS
	int parent;
#endif
} jsmntok_t;

/**
 * JSON parser. Contains an array of token blocks available. Also stores
 * the string being parsed now and current position in that string
 */
typedef struct {
	unsigned int pos; /* offset in the JSON string */
	unsigned int toknext; /* next token to allocate */
	int toksuper; /* superior token node, e.g parent object or array */
} jsmn_parser;

/**
 * Create JSON parser over an array of tokens
 */
void	jsmn_init(jsmn_parser *parser);
int		jsmn_sc(char *string, jsmntok_t *tokens, int t);
int		jsmn_obj(char *string);
int		jsmn_sph(char *string, t_primitive *p);
int		jsmn_cone(char *string, t_primitive *p);
int		jsmn_cyl(char *string, t_primitive *p);
int		jsmn_plane(char *string, t_primitive *p);
int		jsmn_dl(char *string);
int		jsmn_pl(char *string);
int		jsmn_al(char *string);
int		jsmn_cam(char *string, jsmntok_t *tokens, int t);

/**
 * Run JSON parser. It parses a JSON data string into and array of tokens, each describing
 * a single JSON object.
 */
int jsmn_parse(jsmn_parser *parser, const char *js, size_t len,
		jsmntok_t *tokens, unsigned int num_tokens);

#ifdef __cplusplus
}
#endif

#endif /* __JSMN_H_ */
