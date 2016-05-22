#include<cstdio>
#include<cstdarg>
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
//#define DEBUG
inline void Message(const char format[], ...) {
#ifdef DEBUG  
  va_list arg;
  va_start(arg, format);
  vfprintf(stderr, format, arg);
  va_end(arg);
#endif  
}
