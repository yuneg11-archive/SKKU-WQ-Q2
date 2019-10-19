CC=gcc
FLAGS= -O3 -g -Wno-unused-result

all: full lite

full: RecurringDecimal.c
	$(CC) RecurringDecimal.c -o RecurringDecimal $(FLAGS)

lite: RecurringDecimalLite.c
	$(CC) RecurringDecimalLite.c -o RecurringDecimalLite $(FLAGS)

clean:
	rm -f RecurringDecimal RecurringDecimalLite
