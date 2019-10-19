CC=gcc
FLAGS= -O3 -g -Wno-unused-result

all: RecurringDecimal

RecurringDecimal: RecurringDecimal.c
	$(CC) $(FLAGS) RecurringDecimal.c -o RecurringDecimal

clean:
	rm -f RecurringDecimal
