CC=gcc
FLAGS= -O3 -g -Wno-unused-result

all: RecurringDecimal

RecurringDecimal: RecurringDecimal.c
	$(CC) RecurringDecimal.c -o RecurringDecimal $(FLAGS)

clean:
	rm -f RecurringDecimal
