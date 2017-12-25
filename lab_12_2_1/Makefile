CC := gcc

CFLAGS := -Wall -Werror -std=c99 -fPIC -g

OBJS := array.o errors.o

ifeq ($(mode), debug)
	CFLAGS += -g3 -O0
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG
endif

libarr.so: $(OBJS)
	gcc -shared -fPIC -o $@ $^

clean:
	rm -rf *.o test.exe main.exe *.gcov *.gcda *.gcno
