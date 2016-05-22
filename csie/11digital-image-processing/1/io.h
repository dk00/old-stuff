#include<cstdio>
inline bool LoadImage(int n, void *p) {
  if (fread(p, 1, n, stdin) < n) {
    fprintf(stderr, "Can't read.\n");
    return false;
  }
  return true;
}

inline bool SaveImage(int n, const void *p) {
  if (fwrite(p, 1, n, stdout) < n) {
    fprintf(stderr, "Can't write.\n");
    return false;
  }
  return true;
}
