#include<cmath>
#include<cstdio>

typedef double FLOAT;

const FLOAT pi = acos(-1), 
  B0 = 1,
  B1 = cos(pi*1/16)*sqrt(2), 
  B2 = cos(pi*2/16)*sqrt(2), 
  B3 = cos(pi*3/16)*sqrt(2), 
  B4 = cos(pi*4/16)*sqrt(2), 
  B5 = cos(pi*5/16)*sqrt(2), 
  B6 = cos(pi*6/16)*sqrt(2), 
  B7 = cos(pi*7/16)*sqrt(2), 
  A2 = cos(pi*2/16),
  A4 = cos(pi*4/16);

const FLOAT prescale[64]={
  B0*B0/8, B0*B1/8, B0*B2/8, B0*B3/8, B0*B4/8, B0*B5/8, B0*B6/8, B0*B7/8,
  B1*B0/8, B1*B1/8, B1*B2/8, B1*B3/8, B1*B4/8, B1*B5/8, B1*B6/8, B1*B7/8,
  B2*B0/8, B2*B1/8, B2*B2/8, B2*B3/8, B2*B4/8, B2*B5/8, B2*B6/8, B2*B7/8,
  B3*B0/8, B3*B1/8, B3*B2/8, B3*B3/8, B3*B4/8, B3*B5/8, B3*B6/8, B3*B7/8,
  B4*B0/8, B4*B1/8, B4*B2/8, B4*B3/8, B4*B4/8, B4*B5/8, B4*B6/8, B4*B7/8,
  B5*B0/8, B5*B1/8, B5*B2/8, B5*B3/8, B5*B4/8, B5*B5/8, B5*B6/8, B5*B7/8,
  B6*B0/8, B6*B1/8, B6*B2/8, B6*B3/8, B6*B4/8, B6*B5/8, B6*B6/8, B6*B7/8,
  B7*B0/8, B7*B1/8, B7*B2/8, B7*B3/8, B7*B4/8, B7*B5/8, B7*B6/8, B7*B7/8
};

inline void _idct(FLOAT c[64], int x, int y){
  int i;
  FLOAT s04, d04, s17, d17, s26, d26, s53, d53;
  FLOAT os07, os16, os25, os34;
  FLOAT od07, od16, od25, od34;

  for (i = 0; i < y*8; i += y) {
    s17 = c[1*x + i] + c[7*x + i];
    d17 = c[1*x + i] - c[7*x + i];
    s53 = c[5*x + i] + c[3*x + i];
    d53 = c[5*x + i] - c[3*x + i];

    od07 = s17 + s53;
    od25 = (s17 - s53)*(2*A4);

    od34 = d17*(2*(B6-A2)) - d53*(2*A2);
    od16 = d53*(2*(A2-B2)) + d17*(2*A2);

    od16 -= od07;
    od25 -= od16;
    od34 += od25;

    s26 = c[2*x + i] + c[6*x + i];
    d26 = c[2*x + i] - c[6*x + i];
    d26 *= 2*A4;
    d26 -= s26;

    s04 = c[0*x + i] + c[4*x + i];
    d04 = c[0*x + i] - c[4*x + i];

    os07 = s04 + s26;
    os34 = s04 - s26;
    os16 = d04 + d26;
    os25 = d04 - d26;

    c[0*x + i] = os07 + od07;
    c[1*x + i] = os16 + od16;
    c[2*x + i] = os25 + od25;
    c[3*x + i] = os34 - od34;
    c[4*x + i] = os34 + od34;
    c[5*x + i] = os25 - od25;
    c[6*x + i] = os16 - od16;
    c[7*x + i] = os07 - od07;
  }
}

void idct(FLOAT c[64]){
  for (int i = 0; i < 64; ++i)
    c[i] *= prescale[i];
  _idct(c, 1, 8);
  _idct(c, 8, 1);
}

double c[64];

main() {
  int i, j;
  for (i = 0; i < 8; ++i)
    for (j = 0; j < 8; ++j)
      scanf("%lf", &c[i*8+j]);
  idct(c);
  for (i = 0; i < 8; ++i, puts(""))
    for (j = 0; j < 8; ++j)
      printf("%lf ", c[i*8+j]);
}
