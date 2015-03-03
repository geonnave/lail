CFLAGS= -Wall -W -ggdb3 -O0
L_FLAGS= -lncurses -lform -lpthread -lrt
CC=gcc
OBJ=
OUT=lail

main: $(OBJ)
	$(CC) $(CFLAGS) main.c -o $(OUT) $(OBJ) $(L_FLAGS)

clean: 
	rm -rf $(OUT) $(OBJ)

run:
	./$(OUT)

