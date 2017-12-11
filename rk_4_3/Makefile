CC := gcc

CFLAGS := -Wall -std=c99 -g

OBJS := list.o student.o

main.exe: $(OBJS) main.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

