#include<cstdio>
int m,max,p[2097154];
char *s[23],c[2097154][2];
void go(int v=0)
{
    if(c[v][0])
        c[v][0]=0,go(v*2%max);
    if(c[v][1])
        c[v][1]=0,go((v*2+1)%max);
    p[m++]=v;
    
}
void gen(int x,char *&s)
{
    int i,j;
    m=0,max=1<<(x-1);
    for(i=(1<<(x-1))-1;i>=0;i--)
        c[i][0]=c[i][1]=1;
    go();
    s=new char[(1<<x)+3*x];
    i=m;
    for(j=0;j<x-2;j++)
        s[j]='0';
    while(i--)
        s[j++]='0'+p[i]%2;
    for(i=0;i<x;i++)
        s[j++]=0;
    s[j]=0;
}
void print(char a[],char n)
{
    int i,j;
    for(i=j=0;i<n;i++)
        j=j*2+a[i]-'0';
    printf("%d\n",j);
}
main()
{
    int i,n,T;
    for(i=1;i<16;i++)
        gen(i,s[i]);
    s[1][1]='1';
    //scanf("%d",&T);
    while(scanf("%d %d",&n,&i) && n+i)
        print(s[n]+i,n);
}
