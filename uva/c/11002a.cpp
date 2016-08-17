#include<cstdio>
bool s[2][40][3000];
int abs(int a){return a<0?-a:a;}
main()
{
    int i,j,k,p,q,n,num,st[100],ed[100];
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
        {
            st[i]=0,ed[i]=i+1;
            st[i+n-1]=i,ed[i+n-1]=n;
        }
        for(j=0;j<40;j++)
            for(k=0;k<3000;k++)
                s[0][j][k]=0;
        s[0][0][0]=1;
        for(i=p=0,q=1;i<n*2-1;i++,p=!p,q=!q)
        {
            for(j=0;j<40;j++)
                for(k=0;k<3000;k++)
                    s[q][j][k]=0;
            for(j=st[i];j<ed[i];j++)
            {
                scanf("%d",&num);
                for(k=0;k<3000;k++)
                    if(s[p][j][k])
                    {
                        s[q][j][abs(k+num)]=1;
                        s[q][j][abs(k-num)]=1;
                        s[q][j+1][abs(k+num)]=1;
                        s[q][j+1][abs(k-num)]=1;
                    }
            }
            for(j=0;j<40;j++)
                for(k=0;k<3000;k++)
                    s[p][j][k]=s[q][j][k];
        }
        for(k=0;!s[p][n-1][k];k++);
        printf("%d\n",k);
    }
}
