#ifndef _BIGINT_H
#define _BIGINT_H
const int Size=40;
const long long D=1000000000ll;
char __tmp[(Size+1)*9];
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
  bigint(unsigned long long a){s[1]=a/D,s[0]=a%D,s[2]=0,n=1+!!s[1];}
  bigint(){*this=0;}
  const char *tostr(char *t=__tmp) const {
    int i,j;
    sprintf(t,"%lld",s[n-1]);
    for(i=0;t[i];i++);
    for(j=n-2;j>=0;j--,i+=9)
      sprintf(t+i,"%09lld",s[j]);
    return t;
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
  unsigned operator%(unsigned t) const{
  	long long r = 0;
    for(int i=n-1;i>=0;i--) {
			r *= D;
			r += s[i];
			r %= t;
		}
		return r;
  }
};
#endif
