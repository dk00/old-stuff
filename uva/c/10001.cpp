#include<cstdio>
char t[100][8];
main()
{
    int i,j,k,n,r;
    char s[100];
    while(scanf("%d %d %s",&r,&n,s)==3)
    {
        for(k=0;k<8;k++)
        {
            if(!!(r&(1<<k))!=s[0]-'0')continue;
            t[0][k]=1;
            for(j=1;j<n;j++)
                for(i=0;i<8;i++)
                    if((t[j-1][i/2] || t[j-1][i/2+4]) && !!(r&(1<<i))==s[j]-'0')
                        t[j][i]=1;
                    else t[j][i]=0;
            t[0][k]=0;
            for(i=0;i<8;i++)
                if(t[n-1][i] && (i&3)==k/2)
                    break;
            if(i<8)break;
        }
        if(k<8)puts("REACHABLE");
        else puts("GARDEN OF EDEN");
    }
}
