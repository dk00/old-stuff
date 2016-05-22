CC=gcc
src=hash.c strutil.c far.c main.c
main=far

all: $(main)

$(main): $(src)
	$(CC) $(src) -o $(main)

clean:
	rm -f $(main)
