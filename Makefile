.POSIX:

CFLAGS = -Wall -Wextra -std=c99 -g3 -pedantic
OBJ = test.o mint.o

run: test
	./test

test: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJ): mint.h

clean:
	rm -f test *.o

.PHONY: run clean
