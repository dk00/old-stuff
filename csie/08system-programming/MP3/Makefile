CC=gcc

all: fib fbench

fib: fib.c
	$(CC) fib.c -o fib

fbench: fbench.c
	$(CC) fbench.c -o fbench -lm -lrt -O2

clean:
	rm -f fib
	rm -f fbench
