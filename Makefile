.POSIX:

PREFIX = /usr/local

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

# for pkg-config
mint.pc: mint.pc.in
	echo 'prefix=$(PREFIX)' > $@
	cat mint.pc.in >> mint.pc

libmint.a: $(LIB_OBJ)
	ar -rcs $@ $(LIB_OBJ)

install: mint.pc mint.h pitch.h transpose.h libmint.a
	install -m755 -d $(DESTDIR)$(PREFIX)/include/mint
	install -m755 -d $(DESTDIR)$(PREFIX)/lib/pkgconfig
	install -m755 libmint.a $(DESTDIR)$(PREFIX)/lib/
	install -m644 mint.h pitch.h transpose.h $(DESTDIR)$(PREFIX)/include/mint/
	install -m644 mint.pc $(DESTDIR)$(PREFIX)/lib/pkgconfig/

uninstall:
	rm -rf $(DESTDIR)$(PREFIX)/include/mint/
	rm -f $(DESTDIR)$(PREFIX)/lib/libmint.a
	rm -f $(DESTDIR)$(PREFIX)/lib/pkgconfig/mint.pc

clean:
	rm -f $(BIN) *.o *.a mint.pc

.PHONY: run clean install uninstall
