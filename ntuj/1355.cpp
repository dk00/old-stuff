#include<cstdio>
const int Size=22;
const long long D=1000000000ll;
char __tmp[(Size+5)*9];
class bigint {
  void fix() {
    s[n]=0;
    for(int i=0;i<n;i++)
      s[i+1]+=s[i]/D,s[i]%=D;
    if(s[n])n++;
    s[n]=0;
  }
  public:
  int n;
  long long s[Size];
  bigint(const long long &a){s[1]=a/D,s[0]=a%D,s[2]=0,n=1+!!s[1];}
  bigint(const int &a){*this=0ll+a;}
  bigint(){*this=0;}
  const char *tostr(char *t=__tmp) const {
    int i,j;
    sprintf(t,"%lld",s[n-1]);
    for(i=0;t[i];i++);
    for(j=n-2;j>=0;j--,i+=9)
      sprintf(t+i,"%09lld",s[j]);
    return t;
  }
  bigint& operator+=(const bigint &t) {
    for(int i=n;i<=t.n;i++)s[i]=0;
    if(n<t.n)n=t.n;
    for(int i=0;i<t.n;i++)
      s[i]+=t.s[i];
    fix();
    return *this;
  }
  bigint& operator*=(const bigint &t) {
    bigint tmp=*this;
    const long long *a=tmp.s,*b=t.s;
    if(b==s)b=a;
    n+=t.n;
    for(int i=0;i<=n;i++)s[i]=0;
    for(int i=0;i<tmp.n;i++) {
      for(int j=0;j<t.n;j++)
        s[i+j]+=a[i]*b[j];
      for(int j=0;j<n;j++)
        s[j+1]+=s[j]/D,s[j]%=D;
    }
    while(n>1 && !s[n-1])n--;
    return *this;
  }
  bigint operator+(const bigint& a) const{
    bigint tmp = *this;
    tmp += a;
    return tmp;
  }
  bigint operator*(const bigint& a) const{
    bigint tmp = *this;
    tmp *= a;
    return tmp;
  }
};

typedef bigint numtype;
const int N = 55;
numtype s0[55][55], s1[55][55];
main() {
  int i, j, k;
  numtype sum;
  for (i = 0; i < N; ++i)
    s0[i][0] = s1[i][0] = 1;
  for (j = 1; j < N; ++j)
    for (i = j; i < N; ++i) {
      k = i - 1 + i%2;
      k -= j - 1;
      s0[i][j] = s0[i-1][j-1]*k + s0[i-1][j];
      k = i - i%2;
      k -= j - 1;
      s1[i][j] = s1[i-1][j-1]*k + s1[i-1][j];
    }
  while (scanf("%d %d", &i, &k) == 2) {
    for (sum = 0, j = 0; j <= k; ++j) {
      if (j >= N || k-j >= N) continue;
      sum += s0[i][j] * s1[i][k-j];
    }
    puts(sum.tostr());
  }
}

