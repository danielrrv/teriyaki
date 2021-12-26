CC = gcc


default: main.o data_structure.o file.o
	$(CC) main.o data_structure.o file.o $(CFLAGS) -std=c11 -Wall -Werror -o output

main.o: main.c 
	$(CC) -c main.c 
file.o: file.c 
	$(CC) -c file.c
data_structure.o: data_structure.c 
	$(CC) -c data_structure.c

test: test/runner.o data_structure.o file.o data_structure_test.o 
	$(CC) test/runner.o data_structure_test.o data_structure.o file.o  $(CFLAGS) -std=c11 -Wall -Werror -o test/test && (./test/test && make clean)
runner.o:
	$(CC) -c test/runner.c
data_structure_test.o:
	$(CC) -c test/data_structure_test.c

clean:
	rm output test/test *.o test/*.o 2> /dev/null