const int N=800000;
void rsort(int x[],int t0[],int t1[],int n,int m)
{
    static int i,num[N];
    for(i=0;i<=m;i++)num[i]=0;
    for(i=0;i<n;i++)num[x[t0[i]]+1]++;
    for(i=1;i<=m;i++)num[i]+=num[i-1];
    for(i=0;i<n;i++)t1[num[x[t0[i]]]++]=t0[i];
}
void suffixarray(int text[],int t[],int m)
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
int n,s[N],t[N],d[N],x[N];
void go(int s[],int t[],int d[],int n)
{
    int i,j,k;
    for(i=0;i<n;i++)x[t[i]]=i;
    for(i=j=0;i<n;i++)
    {
        if(x[i]==n-1)
        {j=d[x[i]]=0;continue;}
        k=t[x[i]+1];
        while(s[i+j]==s[k+j])
            j++;
        d[x[i]]=j;
        j-=(j>0);
    }
}
#include<cstdio>
int num[N],next[N],p[N],u[N];
void solve(int ch[],int sa[],int len[],int num[],int n,int m)
{
    int i,j,k,l,max=0,ans;
    for(i=j=0;i<n;i++)
    {
        while(j && len[i]<len[p[j-1]])
            next[p[--j]]=i;
        p[j++]=i;
    }
    while(j--)next[p[j]]=i;
    for(i=0;i<m;i++)u[i]=0;
    for(i=k=0;k<m;i++)
        if(!u[num[sa[i]]]++)k++;
    for(j=l=0,i--;ch[sa[j]]<27;j++)
    {
        for(;i<n && k<m;)
            if(!u[num[sa[++i]]]++)
                if(++k>=m)break;
        if(i>=n)break;
		if(j>l)l=j;
        while(next[l]<i)
            l=next[l];
        if(len[l]>max)
            max=len[l],ans=sa[l];
        if(!--u[num[sa[j]]])k--;
    }
    if(max)
	{
		putchar('[');
        for(i=0;i<max;i++)
            printf("%c",ch[i+ans]+'a'-1);
		putchar(']');
	}
    else
        printf("[ID]ENTITY LOST");
    puts("");
}
char tmp[N+1];
main()
{
    int i,j,m;
    while(scanf("%d",&m) && m)
    {
        for(i=n=0;i<m;i++)
        {
            scanf("%s",tmp+n);
            for(;tmp[n];n++)
                num[n]=i;
            tmp[n++]='z'+1;
        }
        if(m==1)
        {
            tmp[n-1]=0;
            puts(tmp);
            continue;
        }
        for(i=j=0;i<n;i++)
        {
            s[i]=tmp[i]-'a'+1;
            if(tmp[i]=='z'+1)
                s[i]+=j++;
        }
        s[i]=0;
        suffixarray(s,t,26+m+1);
        go(s,t,d,n);
        solve(s,t,d,num,n,m);
    }
}
