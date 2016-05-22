const int N=100001;
void rsort(int x[],int t0[],int t1[],int n,int m)
{
    static int i,num[N];
    for(i=0;i<=m;i++)num[i]=0;
    for(i=0;i<n;i++)num[x[t0[i]]+1]++;
    for(i=1;i<=m;i++)num[i]+=num[i-1];
    for(i=0;i<n;i++)t1[num[x[t0[i]]]++]=t0[i];
}
void suffixarray(char text[],int t[],int m)
{
    static int i,j,k,n,s[N*2],tmp[N+2];
    for(n=0;text[n];n++)s[n]=text[n],t[n]=n;
    for(i=n;i<n*2;i++)s[i]=0,t[i]=n;
    for(i=1;i<n;i*=2)
    {
        rsort(s+i,t,tmp,n,m);
        rsort(s,tmp,t,n,m);
        for(j=0,m=1;j<n;j++)
        {
            tmp[t[j]]=m;
            if(s[t[j]]!=s[t[j+1]] || s[t[j]+i]!=s[t[j+1]+i])m++;
        }
        if(m>n)break;
        for(j=0;j<n;j++)s[j]=tmp[j];
    }
}
void deptharray(char s[],int t[],int d[],int n)
{
    int i,j,k,x[N];
    for(i=0;i<n;i++)x[t[i]]=i;
    for(i=j=0;i<n;i++)
    {
        if(x[i]==n-1)
        {j=d[x[i]]=0;continue;}
        k=t[x[i]+1];
        while(s[i+j]==s[k+j])j++;
        d[x[i]]=j;
        j-=(j>0);
    }
}
char find(char x[],int n,char s[],int t[],int d[])
{
    int i,j;
    for(i=j=0;x[j];j++)
    {
        while(x[j]!=s[i+j] && i<n && (!j || j==d[i]))i++;
        if(i>=n || x[j]!=s[i+j])return 0;
    }
    return 1;
}
#include<cstdio>
char s[N],tmp[1001];
int t[N],d[N];
main()
{
    int i,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s);
        for(n=0;s[n];n++);
        suffixarray(s,t,128);
        deptharray(s,t,d,n);
        scanf("%d",&i);
        while(i--)
        {
            scanf("%s",tmp);
            puts(find(tmp,n,s,t,d)?"y":"n");
        }
    }
}
