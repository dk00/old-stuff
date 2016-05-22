#include<cstdio>
const int pn=10,p[]={2,3,5,7,11,13,17,19,23,29};
long long s1[2048],s2[2048];
main()
{
    int i,k,n,T;
    long long j,l,z;
    scanf("%d",&T);
    while(T--)
    {
        for(i=z=0;i<2048;i++)s1[i]=s2[i]=0;
        scanf("%d",&n);
        for(l=0;l<n;l++)
        {
            scanf("%lld",&j);
            if(!j)z++;
            if(!j)continue;
            for(i=k=0;i<10;i++,k*=2)
                while(j%p[i]==0)k^=1,j/=p[i];
            if(j<0)k++;
            s1[k]++;
        }
        for(i=l=0;i<2048;i++)
        {
            l+=s1[i]*s2[i];
            if(i && s1[i]>1)l+=s1[0]*s1[i]*(s1[i]-1)/2;
            if(!i && s1[0]>2)l+=s1[0]*(s1[0]-1)*(s1[0]-2)/6;
            if(s1[i]>1)s2[0]+=s1[i]*(s1[i]-1)/2;
            for(j=0;j<i;j++)
                s2[i^j]+=s1[i]*s1[j];
        }
        if(z>1)s2[0]+=z*(z-1)/2;
        if(z>1)l+=z*(z-1)/2*(n-z);
        if(z>2)l+=z*(z-1)*(z/2)/6;
        if(n-z>1)l+=z*(n-z)*(n-z-1)/2;
        s2[0]+=z*(n-z);
        printf("%lld %lld\n",s2[0],l);
    }
}
