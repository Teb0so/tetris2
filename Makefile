CC = gcc
CFLAGS = -Wall -Wextra #-std=c99
LDFLAGS = -lncurses
SRC-PATH = ./src

OBJS = $(SRC-PATH)/main.o $(SRC-PATH)/game.o $(SRC-PATH)/assets.o

tetris2: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC-PATH)/*.o tetris2

