#include<cstdio>
char c[4][50][50];
int s[101][50];
main()
{
    int i,j,l,m;
    char tmp[999],to[128];
    char &x=tmp[0];
    to['R']=0,to['G']=1,to['B']=2,to['Y']=3;
    scanf("%d",&m);
    for(l=0;l<m;l++)
    {
        scanf("%s %d %d",tmp,&i,&j);
        x=to[x],i--,j--;
        c[x][i][j]=1;
    }
    scanf("%d",&m);
    for(l=0;l<=m;l++)
        for(i=0;i<50;i++)
            s[l][i]=-2147483647;
    s[0][0]=0;
    for(l=0;l<m;l++)
    {
        scanf("%s",tmp);
        x=to[x];
        for(i=0;i<50;i++)
            for(j=0;j<50;j++)
                if(c[x][i][j])
                    s[l+1][j]>?=s[l][i]+j+1;
    }
    printf("%d\n",s[m][0]>?0);
}
