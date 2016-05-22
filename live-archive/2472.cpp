#include<cstdio>
#include<algorithm>
using namespace std;
int n,s[10000],tmp[200][10000];
struct step{int i,j,k;}p[200];
int h()
{
    int i,j,k;
    for(i=k=0;i<n;i=j,k++)
        for(j=i+1;j<n && s[j]-1==s[j-1];j++);
    return k-1;
}
void cp(int a,int b,int c,int d)
{
    copy(s,s+n,tmp[d]);
    copy(tmp[d]+b+1,tmp[d]+n,s+a);
    copy_backward(s+c,s+n-b+a-1,s+n);
    copy(tmp[d]+a,tmp[d]+b+1,s+c);
}
int now,next;
char go(int d)
{
    int H=h();
    if((d*2+H)/3>now/3)
    {
        next<?=d*3+h();
        return 0;
    }
    int i,j,k;
    if(!H)
    {
        for(i=0;i<d;i++)
        {
            for(j=0;j<n;j++)
                printf("%d ",tmp[i][j]);
            puts("");
        }
        for(j=0;j<n;j++)
            printf("%d ",s[j]);
        puts("");
        return 1;
    }
    
    for(i=0;i<n;i++)
        for(j=i;j<n;j++)
            for(k=n-j+i-1;k>=0;k--)
            {
                cp(i,j,k,d);
                p[d]=(step){i,j,k};
                if(go(d+1))return 1;
                copy(tmp[d],tmp[d]+n,s);
            }
    return 0;
}
main()
{
    int i,j,k,T;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        now=h();
        while(1)
        {
            next=10000;
            if(i=go(0))break;
            //printf("%d\n",next/2);
            now=next;
        }
        printf("%d\n",now);
    }
}
