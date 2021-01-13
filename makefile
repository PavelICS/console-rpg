AM_CFLAGS=-O0

VPATH = src include
TARGET = console-rpg
OBJS =  \
	main.o


all : $(TARGET)
	echo All done

$(TARGET) : $(OBJS)
	gcc $(AM_CFLAGS) -o $@ $^ -lm

%.o : %.c
	gcc $(AM_CFLAGS) -o $@ -c $^

clean :
	rm -f $(TARGET) $(OBJS)
	echo Clean done
