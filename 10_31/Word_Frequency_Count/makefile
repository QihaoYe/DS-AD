CC=gcc
CFLAGS=-Wall
TARGET = Word_Frequency_Count
SRCS = Word_Frequency_Count.c \
		HashTable.c
		
OBJS = $(SRCS:.c=.o) 
$(TARGET) : $(OBJS)

	$(CC) $(CFLAGS)  -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS)  -o $@ -c $^

.PHONY : clean
clean : 
	find . -name "*.o"  | xargs rm -f