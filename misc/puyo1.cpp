#include<stdio.h>
const int cn=3,w=6,h=2;
int c[h][w];
int sum,s[cn+1][h][w];
int n1[cn+1],n2[cn+1];
main()
{
    int i,j,k,l,n,t,p;
    //scanf("%d",&t);
    while(1)
    {
        for(i=0;i<h;i++)
            for(j=0;j<w;j++)
            {
                c[i][j]=0;
                for(k=0;k<cn;k++)
                    s[k][i][j]=0;
            }
        scanf("%d",&n);
        while(n--)
        {
            scanf("%d %d",&i,&j);
            i--,j--;
            c[i][j]=1;
        }
        for(i=0;i<h;i++)
            for(j=0;j<w;j++)
            {
                for(k=0;k<=cn;k++)
                    n1[k]=n2[k]=0;
                if(i>0)
                    for(k=0;k<=cn;k++)
                        n1[k]=s[k][i-1][j];
                else
                    n1[cn]=1;
                if(j>0)
                    for(k=0;k<=cn;k++)
                        n2[k]=s[k][i][j-1];
                else
                    n2[cn]=1;
                if(c[i][j]==1)
                {
                    for(k=0;k<cn;k++)
                        for(l=0;l<cn;l++)
                            s[cn][i][j]+=n1[k]*n2[l];
                    continue;
                }
                for(p=0;p<cn;p++)
                    for(k=0;k<=cn;k++)
                    {
                        if(p==k || n1[k]==0)
                            continue;
                        for(l=0;l<=cn;l++)
                            if(p!=l && n2[l]>0)
                                s[p][i][j]+=n1[k]*n2[l];
                    }
            }
        sum=0;
        if(c[h-1][w-1]==1)
            sum=s[cn][h-1][w-1];
        else
            for(k=0;k<cn;k++)
                sum+=s[k][h-1][w-1];
        printf("%d\n",sum);
    }
}
