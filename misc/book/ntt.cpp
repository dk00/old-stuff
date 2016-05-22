#include<cstdio>
#include<cstdlib>
int pow(long long n,int k,int m)
{
    if(k==0)return 1;
    if(k%2)return pow(n,k-1,m)*n%m;
    n=pow(n,k/2,m);
    return n*n%m;
}
void go(int n,int w,int p,int s[],int t[])
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=t[i]=0;j<n;j++)
        {
            t[i]=(t[i]+1ll*s[j]*pow(w,i*j,p)%p)%p;
            printf("%d ",pow(w,i*j,p)%p);
        }
        puts("");
    }
}
void inv(int n,int w,int p,int s[],int t[])
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=t[i]=0;j<n;j++)
            t[i]=(t[i]+1ll*s[j]*pow(w%p,i*j,p)%p)%p;
        t[i]=t[i]*1ll*pow(n,p-2,p)%p;
    }
}
main()
{
    int s[]={1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},t[99];
    int n=16,p=17,r,w;
    //int n=8,p=17,r=6;
    //int n=8,p=8209,r=2;
    r=3;
    go(n,pow(r,(p-1)/n,p),p,s,t);
    for(int i=0;i<n;i++)
        printf("%d ",s[i]=t[i]);
    puts("");
    inv(n,pow(r,p-1-(p-1)/n,p),p,s,t);
    for(int i=0;i<n;i++)
        printf("%d ",t[i]);
    puts("");
    scanf(" ");
    
}
