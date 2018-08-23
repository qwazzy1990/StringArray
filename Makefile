CC = gcc
CFLAGS = -Wall -std=c99 -Iinclude -g -pedantic
BIN = bin/
SRC = src/
TST = test/

program: makeprogram runprogram

makeprogram:
	$(CC) $(CFLAGS) -Iinclude $(SRC)DynamicString.c $(SRC)utilities.c $(SRC)StringArray.c $(TST)testmain.c -o $(BIN)prog1

runprogram:
	./bin/prog1

test: makeprogram valgrind

valgrind: leak-check mem-err

mem-leak: makeprogram
	valgrind --leak-check=full ./bin/prog1

mem-err: makeprogram
	valgrind -v ./bin/prog1

clean:
	rm -f $(BIN)*o $(BIN)*a $(BIN)prog1