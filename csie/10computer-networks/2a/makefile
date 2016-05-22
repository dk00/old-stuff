all: serv client
serv: serv.c tftp.c tftp.h mysock.c mysock.h
	gcc -o serv serv.c tftp.c tftp.h mysock.c mysock.h -lrt
client: client.c tftp.c tftp.h mysock.c mysock.h
	gcc -o client client.c tftp.c tftp.h mysock.c mysock.h -lrt
test1: test1.c tftp.c tftp.h mysock.c mysock.h
	gcc -o test1 test1.c tftp.c tftp.h mysock.c mysock.h -lrt  
