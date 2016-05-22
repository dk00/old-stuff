#include<cstdio>
#include<cstring>
const int Max=1048573;
struct hash
{
    long long k;
    int num;
    hash *next;
}*h[Max];
int max;
long long ans;
inline void clear()
{
    for(int i=0;i<Max;i++)
        for(hash *ptr;h[i];h[i]=ptr)
        {
            ptr=h[i]->next;
            delete h[i];
        }
}
inline void add(long long x)
{
    int v=x%Max;
    hash *ptr;
    for(ptr=h[v];ptr && x!=ptr->k;ptr=ptr->next);
    if(!ptr)
    {
        ptr=new hash;
        ptr->k=x,ptr->num=0,ptr->next=h[v],h[v]=ptr;
    }
    ptr->num++;
    if(ptr->num>max ||(ptr->num==max && ptr->k<ans))
        max=ptr->num,ans=ptr->k;
}
inline void print(int n,long long x)
{
    if(n<=0)return;
    print(n-1,x/26);
    putchar('a'+x%26);
}
char s[1000000];
main()
{
    int i,n;
    long long k,r;
    while(scanf("%d %s",&n,s)==2)
    {
        clear();
        for(i=k=max=0,r=1;i<n;i++,r*=26)
            k=k*26+s[i]-'a';
        add(k);
        for(;s[i];i++)
        {
            k=(k*26+s[i]-'a')%r;
            add(k);
        }
        print(n,ans);
        puts("");
    }
}
