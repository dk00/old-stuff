#include<stdio.h>
#include"bigintA03.h"
const int cn=5;
int c[12][6];
bigint s[12][6][cn+1];
main()
{
    int i,j,k,l,n;
    while(1)
    {
        scanf("%d",&n);
        if(n<0)
            break;
        for(i=0;i<12;i++)
            for(j=0;j<6;j++)
            {
                c[i][j]=0;
                for(k=0;k<=cn;k++)
                    s[i][j][k]=0;
            }
        while(n--)
        {
            scanf("%d %d",&i,&j);
            i--,j--;
            c[i][j]=1;
        }
        for(k=0;k<cn;k++)
            s[0][0][k]=1;
        for(i=0;i<12;i++)
            for(j=0;j<6;j++)
            {
                if(i<11 && c[i][j]==1)
                    for(k=0;k<cn;k++)
                        s[i+1][j][k]+=s[i][j][k];
                else if(i<11)
                    for(k=0;k<cn;k++)
                        for(l=0;l<cn;l++)
                            if(l!=k)
                                s[i+1][j][k]+=s[i][j][l];
                if(j<5 && c[i][j]==1)
                    for(k=0;k<cn;k++)
                        s[i][j+1][k]+=s[i][j][k];
                else if(j<5)
                    for(k=0;k<cn;k++)
                        for(l=0;l<cn;l++)
                            if(l!=k)
                                s[i][j+1][k]+=s[i][j][l];
            }
        for(k=0;k<cn;k++)
            s[11][5][cn]+=s[11][5][k];
        printf("%s\n",s[11][5][k].tostr());
    }
}
