CFLAGS= -Wall -W -ggdb3 -O0
CC=clang
OUT=lail

main: lail.o
	$(CC) $(CFLAGS) main.c -o $(OUT) lail.o -lncurses

lail.o: lail.c
	$(CC) $(CFLAGS) -c lail.c -lncurses

clean: 
	rm -rf $(OUT)

run:
	./$(OUT)

