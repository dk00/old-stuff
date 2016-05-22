#include"io.h"
#include<vector>
using namespace std;
const int dH = 256, dW = 256, mH = 256, mW = 256;
unsigned char data[mH][mW], s[mH][mW];
struct pt {
  int x, y;
};
int H, W;
void Init() {
  freopen("sample.raw", "r", stdin);
  LoadImage(dH*dW, data);
}

void Split() {
}

int main(int argc, char **argv) {
  int i, j;
  H = W = 256;
  if (argc > 2) {
    sscanf(argv[2], "%d", &H);
    sscanf(argv[3], "%d", &W);
  }  
  LoadImage(H*W, s);
  Init();
  Split(t);
}

