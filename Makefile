.POSIX:

CFLAGS = -Wall -Wextra -std=c99 -g3 -pedantic
LIB_OBJ = transpose.o pitch.o mint.o
BIN = test_mint test_pitch test_transpose trx

run: test_mint test_pitch test_transpose
	@./test_mint
	@./test_pitch
	@./test_transpose

trx: $(LIB_OBJ) trx.o
	$(CC) $(CFLAGS) -o $@ trx.o $(LIB_OBJ)

test_mint: mint.o test_mint.o
	$(CC) $(CFLAGS) -o $@ test_mint.o mint.o

test_pitch: pitch.o test_pitch.o
	$(CC) $(CFLAGS) -o $@ test_pitch.o pitch.o

test_transpose: $(LIB_OBJ) test_transpose.o
	$(CC) $(CFLAGS) -o $@ test_transpose.o $(LIB_OBJ)

mint.o: mint.h
test_mint.o: mint.h test.h
pitch.o: pitch.h
test_pitch.o: pitch.h test.h
transpose.o trx.o: mint.h pitch.h transpose.h
test_transpose.o: test.h mint.h pitch.h transpose.h

clean:
	rm -f $(BIN) *.o

.PHONY: run clean
