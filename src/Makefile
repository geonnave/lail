CFLAGS= -Wall -W -ggdb3 -O0
L_FLAGS= -lncurses -lform -lpthread -lrt
CC=gcc
OBJ=lail.o cmdl.o buffer.o
OUT=lail

main: $(OBJ)
	$(CC) $(CFLAGS) main.c -o $(OUT) $(OBJ) $(L_FLAGS)

lail.o: lail.c
	$(CC) $(CFLAGS) -c lail.c $(L_FLAGS)

cmdl.o: cmdl.c
	$(CC) $(CFLAGS) -c cmdl.c $(L_FLAGS)

buffer.o: buffer.c
	$(CC) $(CFLAGS) -c buffer.c $(L_FLAGS)

clean: 
	rm -rf $(OUT) $(OBJ)

run:
	./$(OUT)

