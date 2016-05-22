all: serv client
serv: serv.c tftp.c tftp.h mysock.c mysock.h nset.c nset.h
	gcc -o serv serv.c tftp.c tftp.h mysock.c mysock.h nset.c nset.h -lrt
client: client.c tftp.c tftp.h mysock.c mysock.h nset.c nset.h
	gcc -o client client.c tftp.c tftp.h mysock.c mysock.h nset.c nset.h -lrt
test1: test1.c tftp.c tftp.h mysock.c mysock.h nset.c nset.h
	gcc -o test1 test1.c tftp.c tftp.h mysock.c mysock.h nset.c nset.h -lrt  
