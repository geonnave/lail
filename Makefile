CFLAGS= -Wall -W -ggdb3 -O0
NC_FLAGS= -lncurses -lform -lpthread
CC=gcc
OBJ=lail.o body.o
OUT=lail

main: $(OBJ)
	$(CC) $(CFLAGS) main.c -o $(OUT) $(OBJ) $(NC_FLAGS)

lail.o: lail.c
	$(CC) $(CFLAGS) -c lail.c $(NC_FLAGS)

body.o: body.c
	$(CC) $(CFLAGS) -c body.c $(NC_FLAGS)

clean: 
	rm -rf $(OUT)

run:
	./$(OUT)

