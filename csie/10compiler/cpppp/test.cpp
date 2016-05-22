#include"db.h"
#include"utils.h"
#include<cstdio>

main()
{
  Item t;
  DB db;
  t.title = "title0";
  t.artist = "artist0";
  t.filename = "0.mp3";
  db += t;
  FILE *fp = fopen("test.db", "w");
  MakeDB(db, fp);
  fclose(fp);
  fopen("test.db", "rb+");
  HashFile(fp, "000A27001D4BD7DA");
  fclose(fp);
}
