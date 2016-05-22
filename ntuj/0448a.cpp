#include<cstdio>
const int maxn=200000;
inline bool leq(int a1,int a2,int b1,int b2)
{return(a1<b1||a1==b1 && a2<=b2);}
inline bool leq(int a1,int a2,int a3,int b1,int b2,int b3)
{return(a1<b1 || a1==b1 && leq(a2,a3, b2,b3));}
int c[maxn+50];
static void radixPass(int a[],int b[],int r[],int n,int K)
{
    for(int i=0;i<=K;i++)c[i]=0;
    for(int i=0;i<n;i++)c[r[a[i]]]++;
    for(int i=0,sum=0;i<=K;i++)
    {int t=c[i];c[i]=sum;sum+=t;}
    for(int i=0;i<n;i++)b[c[r[a[i]]]++]=a[i];
}
void suffixArray(int s[],int SA[],int n,int K)
{
    int n0=(n+2)/3,n1=(n+1)/3,n2=n/3,n02=n0+n2;
    int *s12 =new int[n02+3];s12[n02]=s12[n02+1]=s12[n02+2]=0;
    int *SA12=new int[n02+3];SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
    int *s0  =new int[n0];
    int *SA0 =new int[n0];
    for(int i=0,j=0;i<n+(n0-n1);i++)if(i%3!=0)s12[j++]=i;
    radixPass(s12,SA12,s+2,n02,K);
    radixPass(SA12,s12,s+1,n02,K);
    radixPass(s12,SA12,s,n02,K);
    int name=0,c0=-1,c1=-1,c2=-1;
    for(int i=0;i<n02;i++){
        if(s[SA12[i]]!=c0 || s[SA12[i]+1]!=c1 || s[SA12[i]+2]!=c2)
           {name++;c0=s[SA12[i]];c1=s[SA12[i]+1];c2=s[SA12[i]+2];}
        if(SA12[i]%3==1)s12[SA12[i]/3]=name;
        else s12[SA12[i]/3+n0]=name;
    }
    if(name<n02){
        suffixArray(s12,SA12,n02,name);
        for(int i=0;i<n02;i++)s12[SA12[i]]=i+1;
    }else
        for(int i=0;i<n02;i++)SA12[s12[i]-1]=i;
    for(int i=0,j=0;i<n02;i++)if(SA12[i]<n0)s0[j++]=3*SA12[i];
    radixPass(s0,SA0,s,n0,K);

    for(int p=0,t=n0-n1,k=0;k<n;k++){
#define GetI() (SA12[t] < n0 ? SA12[t]*3+1: (SA12[t] - n0)*3+2)
        int i=GetI();
        int j=SA0[p];
        if(SA12[t]<n0?
            leq(s[i],s12[SA12[t]+n0],s[j],s12[j/3]):
            leq(s[i],s[i+1],s12[SA12[t]-n0+1],s[j],s[j+1],s12[j/3+n0]))
        {
            SA[k]=i;t++;
            if(t==n02)
            for(k++;p<n0;p++,k++)SA[k]=SA0[p];
        }else{
            SA[k]=j;p++;
            if(p==n0)
            for(k++;t<n02;t++,k++)SA[k]=GetI();
        }
    }
    delete[] s12; delete[] SA12; delete[] SA0; delete[] s0;
}

int n,s[maxn],t[maxn],d[maxn],x[maxn];
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
int num[maxn],next[maxn],p[maxn],u[maxn];
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
        l>?=j;
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
char tmp[maxn+1];
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
        suffixArray(s,t,n,26+j);
        go(s,t,d,n);
        solve(s,t,d,num,n,m);
    }
}
