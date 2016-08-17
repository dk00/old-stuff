#include<cstdio>
#include<algorithm>
struct frac
{
    long long a,b;
    void operator=(int s){a=s,b=1;}
    void operator+=(frac s)
    {
        if(b<s.b)
            a*=s.b/b,b*=s.b/b;
        if(s.b<b)
            s.a*=b/s.b,s.b*=b/s.b;
        a+=s.a;
    }
    frac operator*(frac s){return (frac){a*s.a,b*s.b};}
    long long operator*(long long s){return s*a/b;}
};
struct poly
{
    int d;
    frac s[100];
    void init(int n)
    {
        d=n,s[0]=(frac){1,1};
        for(int i=1;i<n;i++)
            s[i]=(frac){1,s[i-1].b*i};
    }
    frac& operator[](int n){return s[n];};
    poly& operator*=(poly& a)
    {
        int i,j;
        poly tmp;
        tmp=*this;
        for(i=0;i<d+a.d-1;i++)
            s[i]=0;
        for(i=0;i<d;i++)
            for(j=0;j<a.d;j++)
                s[i+j]+=a.s[j]*tmp.s[i];
        d+=a.d-1;
        return *this;
    }
};


using namespace std;
long long f[21];
int getseq(int s[])
{
    int n;
    char *p,tmp[1000];
    scanf("%s",tmp);
    p=strtok(tmp+1,",");
    for(n=0;p && sscanf(p,"%d",&s[n])==1;n++)
        p=strtok(NULL,",");
    return n;
}
int makeset(int s[],int u[],int s2[],int n2)
{
    int i,n,s0[25];
    if(!n2)return 0;
    copy(s2,s2+n2,s0);
    sort(s0,s0+n2);
    s[0]=s0[0],u[0]=1;
    for(i=n=1;i<n2;i++)
        if(s0[i]!=s0[i-1])
            s[n]=s0[i],u[n++]=1;
        else u[n-1]++;
    return n;
}
int getset(int s[],int u[])
{
    int n0,s0[1000];
    n0=getseq(s0);
    return makeset(s,u,s0,n0);
}
long long calc(int u[],int n,int k)
{
    int i,j,l;
    long long t[25]={0};
    t[0]=f[k];
    for(l=0;l<n;l++)
    for(i=k;i>0;i--)
        for(j=1;i-j>=0 && j<=u[l];j++)
            t[i]+=t[i-j]/f[j];
    return t[k];
}
long long find(int s1[],int u1[],int n1,int s2[],int n2)
{
    int i,j;long long num=0;
    for(i=0;i<n2;i++,u1[j]--)
        for(j=0;s1[j]<s2[i];j++)
        {
            if(!u1[j])continue;
            u1[j]--;
            num+=calc(u1,n1,n2-i-1);
            u1[j]++;
        }
    return num;
}
void makeseq(int s1[],int u1[],int n1,int s2[],int n2,long long k)
{
    int i,j;long long l;
    for(i=0;i<n2;s2[i++]=s1[j],u1[j]--)
        for(j=0;j<n1;j++)
        {
            if(!u1[j])continue;
            u1[j]--;
            l=calc(u1,n1,n2-i-1);
            u1[j]++;
            if(k>=l)k-=l;
            else break;
        }
}
void printset(int s[],int u[],int n)
{
    if(!n){puts("()");return;}
    u[0]--,printf("(%d",s[0]);
    for(int i=0;i<n;i++)
        while(u[i]--)printf(",%d",s[i]);
    puts(")");
}
void printseq(int s[],int n)
{
    if(!n){puts("{}");return;}
    printf("{%d",s[0]);
    for(int i=1;i<n;i++)
        printf(",%d",s[i]);
    puts("}");
}
main()
{   char cmd[1000];
    long long k;
    int n1,n2,s1[25],s2[25],u1[25];
    for(k=f[0]=1;k<21;k++)
        f[k]=f[k-1]*k;
    while(scanf("%s",cmd) && strcmp(cmd,"end"))
    {
        if(!strcmp(cmd,"degrade"))
        {
            n1=getset(s1,u1);
            printset(s1,u1,n1);
        }
        if(!strcmp(cmd,"promote"))
        {
            n1=getset(s1,u1);
            for(k=n2=0;k<n1;k++)
                n2+=u1[k];
            scanf("%lld",&k);
            makeseq(s1,u1,n1,s2,n2,k);
            printseq(s2,n2);
        }
        if(!strcmp(cmd,"rank"))
        {
            n2=getseq(s2);
            n1=makeset(s1,u1,s2,n2);
            printf("%lld\n",find(s1,u1,n1,s2,n2));
        }
        if(!strcmp(cmd,"derive"))
        {
            n1=getset(s1,u1);
            scanf("%d %d",&n2,&k);
            makeseq(s1,u1,n1,s2,n2,k);
            printseq(s2,n2);
        }
        if(!strcmp(cmd,"find"))
        {
            n2=getseq(s2);
            n1=getset(s1,u1);
            printf("%lld\n",find(s1,u1,n1,s2,n2));
        }
        if(!strcmp(cmd,"calc"))
        {
            scanf("%d %d",&n1,&n2);
            for(k=0;k<n1;k++)
                scanf("%d",&u1[k]);
            printf("%lld\n",calc(u1,n1,n2));
        }
    }
}
