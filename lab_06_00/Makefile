CC := gcc

CFLAGS := -Wall -Werror -std=c99

OBJS := io.o search.o

ifeq ($(mode), debug)
	CFLAGS += -g3 -O0 -fprofile-arcs -ftest-coverage
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

lab.bin: $(OBJS) main.o
	$(CC) $(CFLAGS) $^ -o $@

test.bin: $(OBJS) test.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

test: test.bin lab.bin
	@echo 'Running unit tests...'
	-@./test.bin
	@echo -e '\nRunning functional tests...'
	-@./test.sh

coverage: $(OBJS) main.o lab.bin
	@echo -e '\nCoverage testing...'
	@gcov $(OBJS) main.o

clean:
	rm -rf *.o lab.bin test.bin *.gcov *.gcda *.gcno
