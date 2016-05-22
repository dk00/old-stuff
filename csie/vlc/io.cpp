#include"io.h"

bool Reader::init(const char *name) {
  fp = fopen(name, "r");
  end = false;
  return fp != NULL;
}

int Reader::close() {
  return fclose(fp);
}

unsigned Reader::read(int bit) {
  int r = 0;
  //XXX read text type
  while (bit--) {
    r =(r<<1)|(fgetc(fp)-'0');
    if (feof(fp)) {
      end = true;
      break;
    }
  }
  return r;
}

bool Writer::init(const char *name) {
  fp = fopen(name, "w");
  return fp != NULL;
}

int Writer::write(const char symbol[]) {
  return fprintf(fp, "%s\n", symbol);
}

int Writer::close() {
  return fclose(fp);
}
