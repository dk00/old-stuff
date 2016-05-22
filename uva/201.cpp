#include<cstdio>
int s[10],v[10][10],h[10][10];
bool check(int i,int j,int k)
{
    return(h[i][j+k]-h[i][j-1]+h[i+k][j+k]-h[i+k][j-1]+
           v[i+k][j]-v[i-1][j]+v[i+k][j+k]-v[i-1][j+k]==4*k);
}
main()
{
    int i,j,k,n,m,C=0;
    char c[1000];
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<n;i++)
            for(j=s[i]=0;j<n;j++)
                h[i][j]=v[i][j]=0;
        while(m--)
        {
            scanf("%s %d %d",c,&i,&j);
            if(c[0]=='H')
                h[i][j+1]++;
            else
                v[i+1][j]++;
        }
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
            {
                if(i)
                    v[i][j]+=v[i-1][j];
                if(j)
                    v[i][j]+=v[i][j-1];
            }
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                for(k=1;i+k<=n && j+k<=n;k++)
                    if(check(i,j,k))
                        s[k]++;
        if(C++)
            puts("\n**********************************\n");
        printf("Problem #%d\n\n",C);
        for(j=0,i=1;i<n;i++)
            if(s[i])
                j++,printf("%d square (s) of size %d\n",s[i],i);
        if(!j)
            puts("No completed squares can be found.");
    }
}
