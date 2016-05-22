#include<cstdio>
template<class x>void _sw(x &a,x &b)
{
    x tmp;
    tmp=a,a=b,b=tmp;
}
template<class x>void ins_heap(x s[],int &n,x &a)
{
    int i;
    s[++n]=a;
    for(i=n;i>1;i/=2)
        if(s[i]<s[i/2])
            _sw(s[i],s[i/2]);
        else break;
}
template<class x>x ext_heap(x s[],int &n)
{
    int i,j;
    _sw(s[n],s[1]);
    for(i=1;i*2<n;i=j)
    {
        j=i*2;
        if(i*2+1<n && s[i*2+1]<s[i*2])
            j=i*2+1;
        if(s[j]<s[i])
            _sw(s[i],s[j]);
        else break;
    }
    return s[n--];
}
template<class x>void exchange(x s[],int &n,x &a)
{
    a=-a;
    _sw(a,s[1]);
    a=-a;
    int i,j;
    for(i=1;i*2<=n;i=j)
    {
        j=i*2;
        if(i*2+1<n && s[i*2+1]<s[i*2])
            j=i*2+1;
        if(s[j]<s[i])
            _sw(s[i],s[j]);
        else break;
    }
}
int add[30005],get[30005],s1[30005],s2[30005];
main()
{
    int i,j,x,n,m,n1,n2,T;
    scanf("%d",&T);
    while(T--)
    {
        n1=n2=0;
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            scanf("%d",add+i);
        for(i=0;i<m;i++)
            scanf("%d",get+i);
        for(i=j=0;i<n && j<m;i++)
        {
            x=add[i];
            if(n1 && s1[1]<-x)
                exchange(s1,n1,x);
            ins_heap(s2,n2,x);
            for(;j<m && i+1==get[j];j++)
            {
                printf("%d\n",s2[1]);
                x=-ext_heap(s2,n2);
                ins_heap(s1,n1,x);
            }
        }
        if(T)puts("");
    }
}
