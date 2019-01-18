NAME	= 	fdf
FLAGS	= 	-Wall -Wextra -Werror
SRC		= 	src/main.c \
			src/magic.c \
			src/draw.c \
			src/color.c \
			src/image.c \
			src/map.c \
			src/info.c \
			src/keys.c \
			src/utils.c \

OBJ		=	$(patsubst src/%.c,obj/%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc $(FLAGS) -L libft/ -lft -lmlx -framework OpenGL -framework AppKit $(SRC) -o $(NAME)

obj/%.o: src/%.c
	mkdir -p obj
	gcc $(FLAGS) -c $< -o $@

clean:
	/bin/rm -rf obj/
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
