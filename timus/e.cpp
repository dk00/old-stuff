#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
char tmp[100000],tmp1[100000],tmp2[100000];
short numcmp(char a[],char b[])
{
    int i,j,k,l;
    for(i=0;a[i]=='0';i++);
    for(j=0;b[j]=='0';j++);
    for(k=0;a[i+k];k++);
    for(l=0;b[j+l];l++);
    if(k!=l)return k-l;
    while(k>=0 && a[i+k]==b[j+l])k--,l--;
    if(k>=0)return 0l+a[i+k]-b[j+l];
    if((i!=0)!=(j!=0))return (j!=0)-(i!=0);
    return j-i;
}
struct word
{
    string s1;
    bool operator<(word x)const
    {
        int i,j,k,l,r;
        const char *a=s1.c_str(),*b=x.s1.c_str();
        if(('0'<=a[0] && a[0]<='9')^('0'<=b[0] && b[0]<='9'))
            return a[0]<b[0];
        for(i=j=0;a[i] && b[j];i+=k,j+=l)
        {
            if('0'<=a[i] && a[i]<='9')
            {
                for(k=0;'0'<=a[i+k] && a[i+k]<='9';)
                    tmp1[k]=a[i+k++];
                for(l=0;'0'<=b[j+l] && b[j+l]<='9';)
                    tmp2[l]=b[j+l++];
                tmp1[k]=tmp2[l]=0;
                r=numcmp(tmp1,tmp2);
                if(r)return r<0;
            }
            else
            {
                for(k=0;'0'>a[i+k] || a[i+k]>'9';)
                    tmp1[k]=a[i+k++];
                for(l=0;'0'>b[j+l] || b[j+l]>'9';)
                    tmp2[l]=b[j+l++];
                tmp1[k]=tmp2[l]=0;
                r=strcmp(tmp1,tmp2);
                if(r)return r<0;
            }
        }
        if(b[j])return 1;
        return 0;
    }
}s[100000];
main()
{
    int max=0,i,n;
    for(n=0;scanf("%s",tmp)==1;n++)
        s[n].s1=tmp;
    sort(s,s+n);
    for(i=0;i<n;i++)
        puts(s[i].s1.c_str());
}
