#include<math.h>
#include<cstdio>
unsigned long long seed;
const unsigned long long _S=(1ull<<32)-1;
const long double Z=(long double)1.0/(1LL<<32);
long double gen()
{
    return (((seed>>=16)&=_S)*=seed)*Z;
}
main()
{

}
