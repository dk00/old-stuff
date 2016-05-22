#include<cstdio>
const int N=60;
long long s[999999],c[N+1];
int m,id[256];
void rm()
{
    int i,j;
    char tmp[99];
    scanf("%s",tmp);
    for(i=0;tmp[i];i++)
        for(j=0;tmp[j];j++)
            if(tmp[i]!=tmp[j])
                c[id[tmp[i]]]&=~(1ll<<id[tmp[j]]);
}
void go(int d,int i,long long u,long long v)
{
    if(d>=6){
        m++;
        return;
    }
    for(;i<N;i++)
        if((v&(1ll<<i)&~u) && (c[i]&u)==u)
            go(d+1,i,u|(1ll<<i),v&c[i]);
}
main()
{
    int i;
    for(m=0,i='a';i<='z';i++)id[i]=m++;
    for(i='A';i<='Z';i++)id[i]=m++;
    for(i='0';i<='7';i++)id[i]=m++;
    while(scanf("%d",&m)>0){
        for(i=0;i<N;i++)c[i]=(1ll<<N)-1;
        while(m--)rm();
        m=0;
        go(0,0,0,(1ll<<N)-1);
        printf("%d\n",m);
    }
}
