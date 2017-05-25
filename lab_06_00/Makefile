CC := gcc

CFLAGS := -Wall -Werror -std=c99

OBJS := io.o search.o

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

lab.bin: $(OBJS) main.o
	$(CC) $^ -o $@

test.bin: $(OBJS) test.o
	$(CC) $^ -o $@

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

test: test.bin
	./test.bin

clean:
	rm -rf *.o lab.bin test.bin
