TARGET= RT

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall
 
PTHREAD=-pthread
 
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe
 
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
 
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic
 
OBJS=main.o
 
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
	
main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) -o main.o
	
clean:
	rm -f *.o $(TARGET)

# SRCS_DIR    = ./src
# OBJS_DIR    = ./obj
# HEADERS_DIR = ./include
# LIBFT_DIR   = ./libft

# SRCS        = main.c rotate.c light.c add_light.c add_primitive.c intersection.c trace.c vector.c render.c math.c keyboard.c supersampling.c scenes.c consoleout.c object.c color.c fps.c init.c

# OBJS        = $(SRCS:.c=.o)

# VPATH       = $(SRCS_DIR) $(OBJS_DIR)

# INCLUDES    = -I include/
# INCLUDES   += -I libft/
# INCLUDES   += -I frameworks/SDL2.framework/Headers/
# INCLUDES   += -I frameworks/SDL2_image.framework/SDL2_image/Headers
# INCLUDES   += -I /Library/Frameworks/SDL2.framework/Versions/Current/Headers

# LIBFT       = $(LIBFT_DIR)/libft.a

# LIBRARIES   = -lm -framework OpenCL
# LIBRARIES  += -L libft/ -lft -framework AppKit
# LIBRARIES  += -framework AppKit
# LIBRARIES  += -F frameworks/
# LIBRARIES  += -framework SDL2
# LIBRARIES  += -framework SDL2_ttf

# TO_LINKING  = $(addprefix $(OBJS_DIR)/, $(OBJS)) $(INCLUDES) $(LIBRARIES) -rpath frameworks/

# all         : $(NAME)

# $(NAME)     : $(LIBFT) $(LIBJSON) $(OBJS_DIR) $(OBJS) $(HEADERS)
# 	@$(CC) $(CFLAGS) -o $(NAME) $(TO_LINKING)
# 	@printf "\e[38;5;46m./$(NAME)   SUCCESSFUL BUILD 🖥\e[0m\n"
# 	@printf "\e[38;5;5m\\n\
# 	   \t       ██████╗ ████████╗██╗   ██╗ ██╗        ██████╗ ██╗   ██╗  \n\
#        \t       ██╔══██╗╚══██╔══╝██║   ██║███║        ██╔══██╗╚██╗ ██╔╝  \n\
#        \t       ██████╔╝   ██║   ██║   ██║╚██║        ██████╔╝ ╚████╔╝   \n\
#        \t       ██╔══██╗   ██║   ╚██╗ ██╔╝ ██║        ██╔══██╗  ╚██╔╝    \n\
#        \t       ██║  ██║   ██║    ╚████╔╝  ██║        ██████╔╝   ██║     \n\
#        \t       ╚═╝  ╚═╝   ╚═╝     ╚═══╝   ╚═╝        ╚═════╝    ╚═╝     \n\
#          █████╗ ██████╗ ██╗  ██╗██╗██████╗ ██╗███╗   ███╗ ██████╗ ███╗   ██╗\n\
#         ██╔══██╗██╔══██╗██║  ██║██║██╔══██╗██║████╗ ████║██╔═══██╗████╗  ██║\n\
#         ███████║██████╔╝███████║██║██║  ██║██║██╔████╔██║██║   ██║██╔██╗ ██║\n\
#         ██╔══██║██╔══██╗██╔══██║██║██║  ██║██║██║╚██╔╝██║██║   ██║██║╚██╗██║\n\
#         ██║  ██║██║  ██║██║  ██║██║██████╔╝██║██║ ╚═╝ ██║╚██████╔╝██║ ╚████║\n\
#         ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═════╝ ╚═╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝\n\
#         \e[0m\n"



# $(LIBFT)    :
# 	@make -C $(LIBFT_DIR)

# $(LIBJSON)  :
# 	@make -C $(LIBJSON_DIR)

# $(OBJS_DIR) :
# 	@mkdir $(OBJS_DIR)
# 	@printf "\e[38;5;46m$(OBJS_DIR)    FOLDER CREATED\e[0m\n"

# $(OBJS)     : %.o : %.c $(HEADERS)
# 	@$(CC) $(CFLAGS) -c $< -o $(OBJS_DIR)/$@ $(INCLUDES)

# clean       :
# 	@rm -rf $(OBJS_DIR)
# 	@make -C $(LIBFT_DIR) clean
# 	@printf "\e[38;5;226m$(OBJS_DIR)    FOLDER DELETED\e[0m\n"

# fclean      : clean
# 	@rm -f $(NAME)
# 	@make -C $(LIBFT_DIR) fclean
# 	@printf "\e[38;5;226m./$(NAME)   DELETED\e[0m\n"

# re          : fclean all

# norm		:
# 	norminette src/ includes/

# leaks       :
# 	leaks $(NAME)

# test		:
# 	make
# 	./$(NAME) 4

# author		:
# 	cat -e author

# .PHONY: clean fclean re author
# >>>>>>> beac5e82a2c6c8dcd4100f4f70dfebac5514181a
