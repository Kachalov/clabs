CC := gcc

CFLAGS := -Wall -Werror -std=c99 -g -fno-omit-frame-pointer

OBJS := list.o

ifeq ($(mode), debug)
	CFLAGS += -g3 -O0 -fprofile-arcs -ftest-coverage -DDEBUG
endif

ifeq ($(mode), release)
	CFLAGS += -g0 -O3 -DNDEBUG
endif

main.exe: $(OBJS) main.c
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

test: main.exe
	@echo 'Running tests...'

clean:
	rm -rf main.exe *.o *.gcov *.gcda *.gcno
