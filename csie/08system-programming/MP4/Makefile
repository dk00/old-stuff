CC=gcc

all: server client

server: server.c printinfo.c
	$(CC) server.c printinfo.c -o server

client: client.c printinfo.c
	$(CC) client.c printinfo.c -o client

clean:
	rm -f server
	rm -f client
