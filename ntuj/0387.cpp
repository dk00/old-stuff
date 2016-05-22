#include<cstdio>
int x[9999],y[9999],p[99];
int abs(int x){return x<0?-x:x;}
main()
{
    int i,j,k,sum,max,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=max=sum=0;i<n;i++)
            for(j=p[i]=0;j<m;j++)
            {
                scanf("%d",&k);
                if(k>=0)
                {
                    x[k]=i;
                    y[k]=j;
                    max>?=k;
                }
            }
        for(i=1;i<=max;i++)
        {
            sum+=x[i]*20+(abs(y[i]-p[x[i]])<?abs(y[i]+m-p[x[i]])<?abs(y[i]-m-p[x[i]]))*5;
            p[x[i]]=y[i];
        }
        printf("%d\n",sum);
    }
}
