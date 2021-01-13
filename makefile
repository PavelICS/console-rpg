AM_CFLAGS=-O3

VPATH = src include
TARGET = console-rpg
OBJS =  \
	main.o


all : $(TARGET)
	echo All done

$(TARGET) : $(OBJS)
	gcc -o $@ $^

%.o : %.c
	gcc -o $@ -c $^

clean :
	rm $(TARGET) $(OBJS)
	echo Clean done
