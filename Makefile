CFLAGS= -Wall -W -ggdb3 -O0
NC_FLAGS= -lncurses -lform
CC=gcc
OUT=lail

main: lail.o
	$(CC) $(CFLAGS) main.c -o $(OUT) lail.o $(NC_FLAGS)

lail.o: lail.c
	$(CC) $(CFLAGS) -c lail.c $(NC_FLAGS)

clean: 
	rm -rf $(OUT)

run:
	./$(OUT)

