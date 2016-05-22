#include<ctime>
#include<cstdio>
#include<string>
#include<cstdlib>
#include<cstring>
#include<cstdarg>
#include<unistd.h>
using namespace std;
const char *master;
inline void systemf(const char *fmt, ...) {
  va_list arg;
  static char cmd[4096];
  va_start(arg, fmt);
  vsprintf(cmd, fmt, arg);
  va_end(arg);
  system(cmd);
}
int Sync() {
  systemf("rm -fr .tmp", master);
  systemf("wget %s/fetch -O .tmp -q", master);
  const char *tmp = ".tmp";
  char file_name[99], base[99], action[99];
  FILE *fp = fopen(tmp, "r");
  file_name[0] = 0;
  fscanf(fp, "%s", file_name);
  fclose(fp);
  int t = 8, mode = 0, pid = 1;
  if (strlen(file_name) < 1) return 1;
  if(mode == 1) {
    fflush(stdout);
    pid = fork();
    if (pid) return 0;
  }
  systemf("convert -geometry 400x300 %s t_%s", file_name, file_name);
  printf("Process %s\n", file_name);
  systemf("./dip %s r_%s", file_name, file_name);
  puts("Done");
  systemf("chmod o+r ?_%s", file_name);
  systemf("wget %s/done --post-data \'file=%s&res=r_%s\' -O .tmp -q", master, file_name, file_name);
  if (mode == 1) _exit(0);
  return 0;
}
main(int argn, char **arg) {
  if(argn < 2) master="w.csie.org/~b96120/dip";
  else master = arg[1];
  while (1) {
    int t = Sync();
    if (t > 0) sleep(t);
  }
}
