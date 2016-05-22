#include<cmath>
#include<cstdio>
#include<vector>
#include<complex>
using namespace std;
const double pi=acos(-1);
template<class num> vector<num> FFT(vector<num>& s)
{
    int i,j;
    vector<num> t;
    t.resize(s.size());
    num x,r,w(cos(2*pi/s.size()),sin(2*pi/s.size()));
    for(i=0,r=1;i<s.size();i++,r*=w)
        for(j=0,t[i]=0,x=1;j<s.size();j++,x*=r)
            t[i]+=s[j]*x;
    return t;
}
main()
{
	int n;
    while(scanf("%d",&n)==1 && n){
        int i,r;
        vector<complex<double> > s,t;
        for(i=0;i<n;i++)
            scanf("%d",&r),s.push_back(complex<double>(r,0));
        t=FFT(s);
        for(i=0;i<t.size();i++)
            printf("%s%.2lf %s %.2lfi\n",t[i].real()>-.01?"":"-",fabs(t[i].real()),
            t[i].imag()>-.01?"+":"-",fabs(t[i].imag()));
    }
}
