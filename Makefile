CFLAGS= -Wall -W -ggdb3 -O0
L_FLAGS= -lncurses -lform -lpthread -lrt
CC=gcc
OBJ=buffer.o cmd_line.o
OUT=lail

main: $(OBJ)
	$(CC) $(CFLAGS) main.c -o $(OUT) $(OBJ) $(L_FLAGS)

buffer.o: buffer.c
	$(CC) $(CFLAGS) -c buffer.c $(L_FLAGS)

cmd_line.o: cmd_line.c
	$(CC) $(CFLAGS) -c cmd_line.c $(L_FLAGS)

clean: 
	rm -rf $(OUT) $(OBJ)

run:
	./$(OUT)

