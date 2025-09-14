CC = gcc
CFLAGS = -Wall -Wextra #-std=c99
LDFLAGS = -lncurses

OBJS = main.o game.o assets.o

tetris2: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o tetris2

