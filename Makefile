CC := gcc

CFLAGS := -g #-Wall -Wextra

LDLIBS := -lncurses

skating: main.o skatingModules.o
	gcc $(CFLAGS) main.o skatingModules.o -o skating

main.o : setting.h skatingModules.h

clean:
	$(RM) *.o
	$(RM) skating
