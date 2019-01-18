TARGET= RT

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O3
# warnings
WARN=-Wall
 
PTHREAD=-pthread

.PHONY: clean all default
.PRECIOUS: $(TARGET) $(OBJECTS)

CCFLAGS=$(DEBUG) $(OPT) $(WARN)  -pipe -lm  -rdynamic
 
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
 
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB)  -lm -rdynamic

SRCS_DIR    = ./src

OBJECTS=main.o main2.o keyboard.o rotate.o light.o add_light.o add_primitive.o intersection.o trace.o vector.o render.o math.o  supersampling.o scenes.o object.o color.o  init.o parser.o parser.1.o parser.2.o parser.3.o parser.4.o add_primitive2.o new_intersection.o jsmn.o 
#keyboard.o fps.o consoleout.o
HEADERS = includes/

all: $(TARGET)
 
$(TARGET): $(OBJECTS)
	$(LD) -o $(TARGET) $(OBJECTS) $(LDFLAGS) 2>/dev/null

$(OBJECTS): %.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(CC) $(CCFLAGS) -c $< $(GTKLIB) -o $@ 2>/dev/null

clean:
	rm -f *.o $(TARGET)

re          : clean all
