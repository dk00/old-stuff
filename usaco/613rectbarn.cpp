/*
PROG: rectbarn
ID: s0000151
LANG: C++
*/
#include<stdio.h>
char map[3000][3000];
int s1[3000],s2[3000],len[3000];
main()
{
    int i,j,k,n,m,max;
    scanf("%d %d %d",&n,&m,&k);
    while(k--)
    {
        scanf("%d %d",&i,&j);
        map[i][j]=1;
    }
    for(i=0;i<n;i++)
    {
        for(j=k=0;j<m;j++)
        {
            if(map[i][j])len[j]=0;
            else len[j]++;
            while(k>0 && len[j]>s2[k])
            {
                k--;
                max>?=(j-s1[k])*s2[k];
            }
        }
        while(k>0)
        {
            k--;
            max>?=(j-s1[k])*s2[k];
        }
    }
    printf("%d\n",max);
}
