#include"db.h"
#include"utils.h"
#include<cstdio>
extern int yyparse();
extern FILE *yyin;
DB myDB;
void usage(const char *name) {
  printf("Usage: %s FWGUID file...\n", name);
}
main(int argc, char **argv) {
  if (argc < 3) {
    usage(argv[0]);
    return 0;
  }
  for (int i = 2;i < argc;++i) {
    yyin = fopen(argv[i], "r");
    yyparse();
    fclose(yyin);
  }
  //myDB.showAll();
  FILE *fp = fopen("iTunesDB", "w+");
  MakeDB(myDB, fp);
  puts(argv[1]);
  HashFile(fp, argv[1]);
  fclose(fp);
}
