#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<unistd.h>
char tmp[999];
const char *name = "test";
void getcmd(char *cmd) {
  sprintf(tmp, "wget w.csie.org/~b96120/test0/%s -q -O cmd", name);
  system(tmp);
  FILE *fp = fopen("cmd", "r");
  fgets(cmd, 999, fp);
  fclose(fp);
}
main(int argc, char **argv) {
  int t, n, id;
  char cmd[999], type[999];
  if (argc > 1) name = argv[1];
  while (1) {
    getcmd(cmd);
    puts(cmd);
    sscanf(cmd, "%s %d %d", type, &id, &n);
    if (type[0] == 's') {
      usleep(n);
      continue;
    }
    if (type[0] == 't') {
      //sprintf(tmp, "./pi %d", n);
      t = clock();
      //system(tmp);
      sleep(n);
      t = clock() - t;
      sprintf(tmp, "wget -q w.csie.org/~b96120/test0/%s/%d/%d", name, id, t);
      puts(tmp);
      system(tmp);
    }
  }
}
