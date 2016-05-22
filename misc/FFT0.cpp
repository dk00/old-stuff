#include<cmath>
#include<vector>
#include<cstdio>
#include<complex>
#include<algorithm>
using namespace std;
main()
{
    int i,j,k,l,m,n;
    double r,pi=acos(-1);
    while(scanf("%d",&n)==1 && n){
        vector<complex<double> > s;
        for(i=0;i<n;i++)
            scanf("%lf",&r),s.push_back(complex<double>(r,0));
        complex<double> x,y,w[20],wn(cos(2*pi/s.size()),sin(2*pi/s.size()));
        for(m=0;(1<<m)<s.size();m++)w[m]=m?w[m-1]*w[m-1]:wn;
        for(i=0;i<s.size();i++){
            for(k=i,j=l=0;l<m;l++,k>>=1)(j<<=1)|=k&1;
            if(i<j)swap(s[i],s[j]);
        }
        for(j=0,k=m;k--;j++)
            for(i=l=0,x=1;i<s.size();i++){
                if(i&(1<<j))continue;
                s[i]+=s[i+(1<<j)]*=x;
                (s[i+(1<<j)]*=-2)+=s[i];
                if(++l%(1<<j)==0)x=1;
                else x*=w[k];
            }
        for(i=0;i<n;i++)
            printf("%s%.2lf %s %.2lfi\n",s[i].real()>-.01?"":"-",fabs(s[i].real()),s[i].imag()>-.01?"+":"-",fabs(s[i].imag()));
    }
}
