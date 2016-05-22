const int N=1000002;
int s[N*2],t[N],d[N],num[N],*p=s+N;
void rsort(int x[],int t0[],int t1[],int n,int m)
{
    int i;
    for(i=0;i<=m;i++)num[i]=0;
    for(i=0;i<n;i++)num[x[t0[i]]+1]++;
    for(i=1;i<=m;i++)num[i]+=num[i-1];
    for(i=0;i<n;i++)t1[num[x[t0[i]]]++]=t0[i];
}
void suffixarray(int s[],int t[],int m)
{
    int i,j,k,n,*tmp=d;
    for(n=0;s[n];n++)t[n]=n;
    for(t[n]=i=n;i<n*2;i++)s[i]=0;
    for(i=1;i<n;i*=2)
    {
        rsort(s+i,t,tmp,n,m);
        rsort(s,tmp,t,n,m);
        for(j=0;j<n;j++)tmp[j]=s[j];
        for(j=0,m=1;j<n;j++)
        {
            s[t[j]]=m;
            if(tmp[t[j]]!=tmp[t[j+1]] || tmp[t[j]+i]!=tmp[t[j+1]+i])m++;
        }
    }
}
void go(char a[],int t[],int d[],int n)
{
    int i,j,k,*x=s;
    for(i=0;i<n;i++)x[t[i]]=i;
    for(i=j=0;i<n;i++)
    {
        if(t[i])p[i]=x[t[i]-1];
        if(x[i]==n-1)
        {j=d[x[i]]=0;continue;}
        k=t[x[i]+1];
        while(a[i+j]==a[k+j])j++;
        d[x[i]]=j;
        j-=(j>0);
    }
}
int find(int i,int j,char str[],char x)
{
    while(i<m && str[t[i]+j]!=x && j==d[i])
        i=num[i];
    return i;
}
void go(int m,char s0[],char s1[])
{
    int i,j,k,l;
    for(i=0;i<m;i++)s[i]=-s[i];
    for(i=k=0,j=t[0];s1[i];i++)
    {
        while((l=find(j,k,s0,s1[i]))>=m && k)
            k--,j=p[j];
    }
    for(i=0;i<m;i++)
        if(s[i]<0)s[i]=0;
}
#include<cstdio>
char data[N],tmp[N*2];
int main()
{
    int i,j,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        scanf("%s",data);
        for(m=0;data[m];m++)s[m]=data[m];
        s[m]=0;
        suffixarray(s,t,'T'+1);
        go(data,t,d,m);
        for(i=j=0;i<m;i++)num[i]=m+1;
        for(i=j=0;i<m;i++)
        {
            while(j && d[i-1]<=(s[j-1]?d[s[j-1]-1]:0))
            {
                j--;
                if(d[i-1]==(s[j]?d[s[j]-1]:0))
                    num[s[j]]=i;
            }
            s[j++]=i;
        }
        for(i=0;i<m;i++)s[i]=n-t[i];
        for(i=1;i<n;i++)
        {
            scanf("%s",tmp);
            go(m,data,tmp);
        }
        for(i=n=0;i<m;i++)if(s[i]>n)n=s[i];
        printf("%d\n",n);
    }
}
