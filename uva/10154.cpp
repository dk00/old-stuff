#include<cstdio>
#include<algorithm>
struct tu
{
    int a,b;
    bool operator<(tu x)const{return(b<x.b ||(b==x.b && a<x.a));}
}s[5607];
int t[5608];
main()
{
    int i,j,k,n;
    for(n=0;scanf("%d %d",&s[n].a,&s[n].b)==2;n++);
    std::sort(s,s+n);
    for(i=k=0;i<n;i++)
    {
        if(t[k]+s[i].a<=s[i].b)
            t[k+1]=t[k]+s[i].a,k++;
        for(j=k-1;j>=0;j--)
            if(t[j]+s[i].a<=s[i].b)
                t[j+1]<?=(t[j]+s[i].a);
    }
    printf("%d\n",k);
}
