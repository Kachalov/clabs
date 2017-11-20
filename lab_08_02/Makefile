CC := gcc

CFLAGS := -Wall -Werror -std=c99 -g -fno-inline -fno-omit-frame-pointer

OBJS := mtrx.o mtrx_apply.o

ifeq ($(mode), debug)
	CFLAGS += -g3 -O0 -fprofile-arcs -ftest-coverage
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG
endif

main.exe: $(OBJS) main.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

test: main.exe
	@echo 'Running functional tests...'
	-@./test.sh

coverage: $(OBJS) main.o main.exe
	@echo 'Coverage testing...'
	@gcov $(OBJS) main.o

clean:
	rm -rf *.o test.exe main.exe *.gcov *.gcda *.gcno
