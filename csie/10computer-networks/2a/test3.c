#include<stdio.h>
#include<fcntl.h>
main() {
  int fd = open("test4", O_RDONLY);
  printf("%d\n", fd);
}
