#include<cstdio>
int n,s[99];
char x[99];
char less(int a1,int l1,int a2,int l2)
{
    while(l1 && a1<n && x[a1]=='0')a1++,l1--;
    while(l2 && a2<n && x[a2]=='0')a2++,l2--;
    if(l1!=l2)return l1<l2;
    for(int i=0;i<l1;i++)
        if(x[a1+i]!=x[a2+i])
            return x[a1+i]<x[a2+i];
    return 0;
}
int go(int l)
{
    int i,j;
    for(i=0;i<=n;i++)
        s[i]=0;
    s[0]=1;
    for(i=0;i<n-l;i++)
    {
        if(x[i]=='0')
        {
            if(i || i+1==n-l)
                s[i+1]+=s[i];
            continue;
        }
        for(j=1;i+j<=n-l;j++)
            if(less(i,j,n-l,l))
                s[i+j]+=s[i];
    }
    return s[n-l];
}
main()
{
    int i,sum;
    while(scanf("%s",x) && x[0]!='#')
    {
        for(n=0;x[n];n++);
        for(i=1,sum=0;i<n;i++)
            if(x[n-i]!='0' && (i>1 || x[n-1]>'1'))sum+=go(i);
        if(sum)
            printf("The code %s can represent %d numbers.\n",x,sum);
        else
            printf("The code %s is invalid.\n",x);
    }
}
