CC := gcc

CFLAGS := -Wall -Werror -std=c99 -g -fno-inline -fno-omit-frame-pointer

OBJS := mystr.o

ifeq ($(mode), debug)
	CFLAGS += -g3 -O0 -fprofile-arcs -ftest-coverage -DDEBUG
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG
endif

main.exe: $(OBJS) main.o
	$(CC) $(CFLAGS) $^ -o $@

test.exe: $(OBJS) test.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

test: test.exe
	@echo 'Running unit tests...'
	-@./test.exe

clean:
	rm -rf *.o test.exe main.exe *.gcov *.gcda *.gcno
