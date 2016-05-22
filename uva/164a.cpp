#include<cstdio>
const int inf=2007;
char *s1,*s2,tmp[1000];
int s[25][25],p[25][25];
int go(int a,int b)
{
    if(!s1[a] && !s2[b])return 0;
    if(s[a][b]<inf)return s[a][b];
    if(s1[a]==s2[b])
    {
        if(go(a+1,b+1)<s[a][b])
            s[a][b]=s[a+1][b+1],p[a][b]=0;
    }
    else if(s1[a] && s2[b] && 1+go(a+1,b+1)<s[a][b])
        s[a][b]=1+s[a+1][b+1],p[a][b]='C';
    if(s1[a] && 1+go(a+1,b)<s[a][b])
        s[a][b]=1+s[a+1][b],p[a][b]='D';
    if(s2[b] && 1+go(a,b+1)<s[a][b])
        s[a][b]=1+s[a][b+1],p[a][b]='I';
    return s[a][b];
}
void print(int a,int b,int d=1)
{
    if(!s1[a] && !s2[b])
    {
        puts("E");
        return;
    }
    if(!p[a][b])
        print(a+1,b+1,d+1);
    if(p[a][b]=='C')
        printf("C%c%02d",s2[b],d),print(a+1,b+1,d+1);
    if(p[a][b]=='D')
        printf("D%c%02d",s1[a],d),print(a+1,b,d);
    if(p[a][b]=='I')
        printf("I%c%02d",s2[b],d),print(a,b+1,d+1);
}
main()
{
    int i,j;
    while(gets(tmp) && tmp[0]!='#')
    {
        s1=tmp;
        for(i=0;tmp[i]!=' ';i++);
        tmp[i]=0;
        s2=tmp+i+1;
        for(i=0;s1[i];i++)
            for(j=0;s2[j];j++)
                s[i][j]=inf;
        for(int k=0;s1[k];k++)s[k][j]=inf;
        for(int k=0;s2[k];k++)s[i][k]=inf;
        go(0,0);
        print(0,0);
    }
}
