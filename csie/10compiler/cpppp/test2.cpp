#include"hash58.cpp"
#include<cstdio>
main(){
  uint8_t buf[9999];
  scanf("%s", buf);
  int i, n = strlen((char *)buf);
  Sha1(buf, n);
  for (i = 0;i < 20;++i)
    printf("%02X ", buf[i]);
  puts("");
}
