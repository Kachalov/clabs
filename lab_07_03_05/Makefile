CC := gcc

CFLAGS := -Wall -Werror -std=c99 -pedantic

OBJS :=

ifeq ($(mode), debug)
	CFLAGS += -g3 -O0 -fprofile-arcs -ftest-coverage
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

main.exe: $(OBJS) main.o
	$(CC) $(CFLAGS) $^ -o $@

test.exe: $(OBJS) test.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

test: test.exe main.exe
	@echo 'Running unit tests...'
	-@./test.exe
	@echo -e '\nRunning functional tests...'
	-@./test.exe

coverage: $(OBJS) main.o main.exe
	@echo -e '\nCoverage testing...'
	@gcov $(OBJS) main.o

clean:
	rm -rf *.o test.exe main.exe *.gcov *.gcda *.gcno