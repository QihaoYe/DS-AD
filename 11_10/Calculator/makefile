CC=gcc
CFLAGS=-Wall
TARGET = Calculator
SRCS = Main.c \
		stack_char.c \
		stack_float.c \
		
OBJS = $(SRCS:.c=.o) 
$(TARGET) : $(OBJS)

	$(CC) $(CFLAGS)  -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS)  -o $@ -c $^

.PHONY : clean
clean : 
	find . -name "*.o"  | xargs rm -f