TARGET= RT

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O3
# warnings
WARN=-Wall -Werror -Wextra
 
PTHREAD=-pthread

.PHONY: clean all default
.PRECIOUS: $(TARGET) $(OBJECTS)

CCFLAGS=$(DEBUG) $(OPT) $(FLAGS)  -pipe -lm  -rdynamic
 
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
 
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB)  -lm -rdynamic

SRCS_DIR    = ./src

DN=2>/dev/null
JSMN_DIR=jsmn
JSMN=jsmn.o 
OBJECTS=main.o main2.o keyboard.o rotate.o light.o add_light.o add_primitive.o intersection.o trace.o vector.o render.o math.o  supersampling.o scenes.o object.o color.o  init.o parser.o parser.1.o parser.2.o parser.3.o parser.4.o add_primitive2.o new_intersection.o 
HEADERS = includes/

all: $(TARGET)
	@echo "Compiled"
 
$(TARGET): $(OBJECTS) $(JSMN)
	@$(LD) -o $(TARGET) $(OBJECTS) $(JSMN) $(LDFLAGS) $(DN)
$(OBJECTS): %.o: $(SRCS_DIR)/%.c $(HEADERS)
	@$(CC) $(CCFLAGS) -c $< $(GTKLIB) -o $@ $(DN)
$(JSMN): %.o: $(JSMN_DIR)/%.c
	@$(CC) $(CCFLAGS) -c $< $(GTKLIB) -o $@ $(DN)
fclean:
	@rm -f *.o $(TARGET)
	@echo "Cleaned"
clean:
	@rm -f *.o 
	@echo "Cleaned"
re          : fclean all

locale:
	export LC_ALL=en_US.UTF-8
	export LANG=en_US.UTF-8