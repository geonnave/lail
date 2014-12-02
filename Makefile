CFLAGS=
CC=clang
OUT=lail

main: lail.o
	$(CC) main.c -o $(OUT) lail.o window.o -lncurses

lail.o: window.o lail.c
	$(CC) $(CFLAGS) -c lail.c -lncurses

window.o: window.c
	$(CC) $(CFLAGS) -c window.c -lncurses

clean: 
	rm -rf $(OUT)

run:
	./$(OUT)

