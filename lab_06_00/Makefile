CC := gcc

CFLAGS := -Wall -Werror -std=c99

OBJS := io.o search.o

lab.bin: $(OBJS) main.o
	$(CC) $^ -o $@

test.bin: $(OBJS) test.o
	$(CC) $^ -o $@

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

test: test.bin
	./test.bin

clean:
	rm -rf *.o lab.bin lab_test.bin
