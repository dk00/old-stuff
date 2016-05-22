#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
short numcmp(char a[],char b[])
{
    int i,j,k,l;
    for(k=0;a[k]=='0';k++);
    for(l=0;b[l]=='0';l++);
    if(a[k]+b[l]==0)return 0;
    for(i=0;a[i+k] && b[i+l];i++);
    if(a[i+k] || b[i+l])return a[i+k]-(short)b[i+l];
    for(i=0;a[i+k] && a[i+k]==b[i+l];i++);
    return a[i+k]-(short)b[i+l];
}
char tmp[102400],tmp1[100000],tmp2[100000];
struct a
{
    char *s1;
    bool operator<(a c)const
    {
        int i,j,k,l,res;
        const char *x=s1,*y=c.s1;
        if(('0'<=x[0] && x[0]<='9')^('0'<=y[0] && y[0]<='9'))
            return ('0'<=x[0] && x[0]<='9');
        for(i=j=0;x[i] && y[j];i+=k,j+=l)
        {
            if('0'<=x[i] && x[i]<='9' && '0'<=y[j] && y[j]<='9')
            {
                for(k=0;'0'<=x[i+k] && x[i+k]<='9';k++)
                    tmp1[k]=x[i+k];
                for(l=0;'0'<=y[j+l] && y[j+l]<='9';l++)
                    tmp2[l]=y[j+l];
                tmp1[k]=tmp2[l]=0;
                res=numcmp(tmp1,tmp2);
                if(res)return res<0;
            }
            else
            {
                k=l=1;
                if(x[i]!=y[j])return x[i]<y[j];
            }
        }
        if(y[j])return 1;
        if(!x[i])
            for(i=j=0;x[i] || y[i];i++,j++)
                if((x[i]=='0')^(y[i]=='0'))
                    return(x[i]=='0');
        return 0;
    }
}s[100000];
main()
{
    int i,n,c;
    s[0].s1=tmp;
    for(i=n=0;(c=getchar())!=EOF;)
        if(c=='\n')
        {
            tmp[i++]=0;
            s[++n].s1=tmp+i;
        }
        else tmp[i++]=c;
    sort(s,s+n);
    for(i=0;i<n;i++)
        puts(s[i].s1);
}
