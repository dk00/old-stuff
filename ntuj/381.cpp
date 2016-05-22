#include<cstdio>
int dx[]={-1,-1,-1,0,0,0,1,1,1},dy[]={-1,0,1,-1,0,1,-1,0,1};
int x[1001000],y[1001000];
char p[1001000];
main()
{
    int n,T;
    long long i,j;
    scanf("%d ",&T);
    while(T--)
    {
        gets(p);
        for(n=i=j=0;p[n]!='5';n++)
            x[n]=i+=dx[p[n]-'1'],
            y[n]=j+=dy[p[n]-'1'];
        x[n]=x[0];
        y[n]=y[0];
        for(i=j=0;i<n;i++)
            j+=x[i]*y[i+1]-x[i+1]*y[i];
        if(j<0)j=-j;
        printf("%lld.%lld\n",j/2,j%2*5);
    }
}
