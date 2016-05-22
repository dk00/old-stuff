#include<map>
#include<string>
#include<cstdio>
struct Color {

};
struct BMPheader {
  
};
struct Bitmap {
  FILE *fp;
  int w, h, bit, start;
  void init(char *name) {
    fp = fopen("name", "rb");
    fseek(fp, 10, SEEK_SET);
    fread(&start, 4, 1, fp);
  }
  Color getpixel(int x, int y) {
    
  }
};

void readbmp() {
}

int main(int argn, char **arg) {
  map<stringnn>  

}
