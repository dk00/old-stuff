#include<cstdio>
int m,max,p[2097154];
char *s[23],c[2097154][2];
int d,v[2097154],u[2097154];
void go()
{
    v[0]=d=0,u[0]=0;
    while(d>=0)
    {
        if(u[d]==1)goto d1;
        if(u[d]==2)goto d2;
        if(c[v[d]][0])
        {
            u[d]=1;
            c[v[d]][0]=0;
            v[d+1]=v[d]*2%max;
            u[++d]=0;
            continue;
        }
        
    d1: if(c[v[d]][1])
        {
            u[d]=2;
            c[v[d]][1]=0;
            v[d+1]=(v[d]*2+1)%max;
            u[++d]=0;
            continue;
        }
    d2: p[m++]=v[d];
        d--;
    }
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
    for(i=1;i<22;i++)
        gen(i,s[i]);
    s[1][1]='1';
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&i);
        print(s[n]+i,n);
    }
}
