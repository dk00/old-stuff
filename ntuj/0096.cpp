#include<cstdio>
const int maxn=200000;
inline bool leq(int a1,int a2,int b1,int b2) // lexicographic order
{return(a1<b1||a1==b1 && a2<=b2);} // for pairs
inline bool leq(int a1,int a2,int a3,int b1,int b2,int b3)
{return(a1<b1 || a1==b1 && leq(a2,a3, b2,b3));} // and triples
// stably sort a[0..n-1] to b[0..n-1] with keys in 0..K from r
int c[maxn+50];
static void radixPass(int a[],int b[],int r[],int n,int K)
{// count occurrences
    for(int i=0;i<=K;i++)c[i]=0; // reset counters
    for(int i=0;i<n;i++)c[r[a[i]]]++; // count occurrences
    for(int i=0,sum=0;i<=K;i++) // exclusive prefix sums
    {int t=c[i];c[i]=sum;sum+=t;}
    for(int i=0;i<n;i++)b[c[r[a[i]]]++]=a[i]; // sort
}
// find the suffix array SA of s[0..n-1] in {1..K}^n
// require s[n]=s[n+1]=s[n+2]=0, n>=2
void suffixArray(int s[],int SA[],int n,int K)
{
    int n0=(n+2)/3,n1=(n+1)/3,n2=n/3,n02=n0+n2;
    int *s12 =new int[n02+3];s12[n02]=s12[n02+1]=s12[n02+2]=0;
    int *SA12=new int[n02+3];SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
    int *s0  =new int[n0];
    int *SA0 =new int[n0];
// generate positions of mod 1 and mod 2 suffixes
// the "+(n0-n1)" adds a dummy mod 1 suffix if n%3 == 1
    for(int i=0,j=0;i<n+(n0-n1);i++)if(i%3!=0)s12[j++]=i;
// lsb radix sort the mod 1 and mod 2 triples
    radixPass(s12,SA12,s+2,n02,K);
    radixPass(SA12,s12,s+1,n02,K);
    radixPass(s12,SA12,s,n02,K);
// find lexicographic names of triples
    int name=0,c0=-1,c1=-1,c2=-1;
    for(int i=0;i<n02;i++){
        if(s[SA12[i]]!=c0 || s[SA12[i]+1]!=c1 || s[SA12[i]+2]!=c2)
           {name++;c0=s[SA12[i]];c1=s[SA12[i]+1];c2=s[SA12[i]+2];}
        if(SA12[i]%3==1)s12[SA12[i]/3]=name; // left half
        else s12[SA12[i]/3+n0]=name;  // right half
    }
// recurse if names are not yet unique
    if(name<n02){
        suffixArray(s12,SA12,n02,name);
// store unique names in s12 using the suffix array
        for(int i=0;i<n02;i++)s12[SA12[i]]=i+1;
    }else // generate the suffix array of s12 directly
        for(int i=0;i<n02;i++)SA12[s12[i]-1]=i;
// stably sort the mod 0 suffixes from SA12 by their first character
    for(int i=0,j=0;i<n02;i++)if(SA12[i]<n0)s0[j++]=3*SA12[i];
    radixPass(s0,SA0,s,n0,K);
// merge sorted SA0 suffixes and sorted SA12 suffixes
    for(int p=0,t=n0-n1,k=0;k<n;k++){
#define GetI() (SA12[t] < n0 ? SA12[t]*3+1: (SA12[t] - n0)*3+2)
        int i=GetI(); // pos of current offset 12 suffix
        int j=SA0[p]; // pos of current offset 0 suffix
        if(SA12[t]<n0? // different compares for mod 1 and mod 2 suffixes
            leq(s[i],s12[SA12[t]+n0],s[j],s12[j/3]):
            leq(s[i],s[i+1],s12[SA12[t]-n0+1],s[j],s[j+1],s12[j/3+n0]))
        {// suffix from SA12 is smaller
            SA[k]=i;t++;
            if(t==n02) // done --- only SA0 suffixes left
            for(k++;p<n0;p++,k++)SA[k]=SA0[p];
        }else{// suffix from SA0 is smaller
            SA[k]=j;p++;
            if(p==n0) // done --- only SA12 suffixes left
            for(k++;t<n02;t++,k++)SA[k]=GetI();
        }
    }
    delete[] s12; delete[] SA12; delete[] SA0; delete[] s0;
}

int n,s[maxn],t[maxn],d[maxn],x[maxn],ml[17][maxn],mr[17][maxn],ub[65537];
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
void prermq(int z[],int ml[17][maxn],int mr[17][maxn],int n)
{
    int i,j,k,p;
    for(i=1,p=0;i<=n;i*=2,p++)
    {
        for(j=0;j<n;j+=i)
        {
            ml[p][j]=z[j];
            for(k=j+1;k<j+i;k++)
                ml[p][k]=(z[k]<?ml[p][k-1]);
            mr[p][j+i-1]=z[j+i-1];
            for(k=j+i-2;k>=j;k--)
                mr[p][k]=(z[k]<?mr[p][k+1]);
        }
        /*for(j=0;j<n;j++)
            printf("%d ",ml[p][j]);
        puts("");
        for(j=0;j<n;j++)
            printf("%d ",mr[p][j]);
        puts("");*/
    }
}
char tmp[maxn];
int lcp(int i,int j)
{
    if(i>=n || j>=n || i<0 || j<0)
    {
        printf("%d %d",i,j);
        scanf(" ");
        return 0;
    }
    i=x[i],j=x[j];
    if(i>j)i^=j^=i^=j;
    j--;
    int k=ub[i^j];
    return (mr[k][i])<?(ml[k][j]);
}
int find(int v,int l1,int l2)
{
    if(!lcp(v-l1,v))return v;
    int i,j,k=0,last=lcp(v-l1,v);
    for(i=0,j=(l2-1)<?(v-l1);i<=j;)
    {
        k=(i+j)/2;
        if(lcp(v-l1-k,v-k)!=last+k)j=k-1;
        else if(v-l1-k-1>=0 && lcp(v-l1-k-1,v-k-1)==last+k+1)i=k+1;
        else break;
    }
    if(lcp(v-l1-k,v-k)<l2)
        return v;
    return v-k;
}
main()
{
    int i,j,k,l,g,max,T,C=1;
    for(i=1,k=0;i<65536;i*=2,k++)
        for(j=i*2-1;j>=i;j--)ub[j]=k;
    while(scanf("%d",&n)==1)
    {
        scanf("%d%c",&g,tmp);
        gets(tmp);
        for(n=0;tmp[n];n++)
            s[n]=tmp[n]-'a'+1;
        s[n]=s[n+1]=s[n+2]=0;
        suffixArray(s,t,n,26);
        go(s,t,d,n);
        for(i=j=0;i<n;i++)
             j>?=d[i];
        printf("%d\n",j);
        /*for(i=0;i<n;i++)
            printf("%2d %s\n",d[i],tmp+t[i]);*/
        /*prermq(d,ml,mr,n-1);
        for(i=max=0;i<n;i++)
            max>?=d[i];
        for(i=1+g,k=0;max+g>=i && i<n;i++)
            for(j=i;j<n;j+=i-g)
            {
                j=find(j,i,i-g);
                l=lcp(j-i,j);
                if(l+g>=i)k+=l+g-i+1;
                if(l>0)j+=l-1;
            }
        printf("Case %d: %d\n",C++,k);*/
    }
}
