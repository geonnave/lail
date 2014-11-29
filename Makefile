CFLAGS=
ACFLAGS=-lncurses
CC=gcc
OUT=lail
FILE=lail.c

main: clean 
	$(CC) $(FILE) -o $(OUT) -lncurses

clean: 
	rm -rf $(OUT)

run:
	./$(OUT)

