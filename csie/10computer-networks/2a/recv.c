#include<stdio.h>
#include<socket.h>

int main (int argc,char **argv) {
  if (argc != 2 || sscanf(argv[1],"%d",&port) != 1) {
    return 0;
  }
  
}

