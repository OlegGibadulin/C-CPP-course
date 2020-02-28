CC := gcc

CFLAGS := -std=c99 -Wall -pedantic

OBJ := ticket.o input.o

main.exe: $(OBJ) main.o
	$(CC) $^ -o $@

%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe