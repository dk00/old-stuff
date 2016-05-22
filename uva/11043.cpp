#include<cstdio>
char p[256][256],q[256][256];
main()
{
    int i,j,k,n,b,p1,p2;
    char s[100],t[100];
    p1=p2=0;
    while(scanf("%c",s)==1)
    {
        for(n=1;n<6 && scanf("%c",s+n)==1;n++);
        for(i=0,k=1,j=1,b=64;i<n;i++,j*=2)
        {
            if(q[p1][p2])
            {
                if(p[p1][p2]!=s[i])
                    p[p1][p2]=t[k++]=s[i];
                else b|=j;
            }
            else
            {
                q[p1][p2]=1;
                p[p1][p2]=s[i];
                t[k++]=s[i];
            }
            p1=p2,p2=128+s[i];
        }
        t[0]=b,t[k]=0;
        printf("%s",t);
    }
}
