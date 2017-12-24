CC := gcc

CFLAGS := -Wall -Werror -std=c99 -fPIC -g -fno-inline -fno-omit-frame-pointer

OBJS := array.o filter.o sort.o swap.o errors.o time.o

ifeq ($(mode), debug)
	CFLAGS += -g3 -O0 -fprofile-arcs -ftest-coverage
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG
endif

libarr.a: $(OBJS)
	ar rc $@ $^
	ranlib $@

libarr.so: $(OBJS)
	gcc -shared -fPIC -o $@ $^

main.exe: libarr.a
	$(CC) $(CFLAGS) main.c $^ -o $@

so_main.exe: libarr.so
	$(CC) $(CFLAGS) main.c $^ -o $@

dso_main.exe: errors.o
	$(CC) $(CFLAGS) dso_main.c $^ -ldl -o $@

test.exe: $(OBJS) test.o test_filter.o test_sort.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

test: test.exe main.exe
	@echo 'Running unit tests...'
	-@./test.exe
	@echo 'Running functional tests...'
	-@./test.sh

coverage: $(OBJS) main.o main.exe
	@echo 'Coverage testing...'
	@gcov $(OBJS) main.o

clean:
	rm -rf *.o test.exe main.exe *.gcov *.gcda *.gcno
