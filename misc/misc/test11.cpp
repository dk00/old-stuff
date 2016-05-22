#include<cstdio>
int s[1001],t[1001];
main()
{
    int i,j,k,l,p,n,m;
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
        scanf("%d",&s[i]);
    try{for(i=l=0;i<n;i++)
    {
        if(s[i]<=l)continue;
        for(j=i,k=0;j<n;j++)
            if(s[j]<=s[i])
                t[k++]=j;
        for(i=0;i<k;i++)
        {
            for(j=p=0;j<i;j++)
                if(s[t[j]]<s[t[i]])
                    p++;
            if(p>m)throw 0;
        }
        for(i=t[0],j=0;i<=t[k-1];i++)
            if(s[i]<=l)j++;
        if(j>m)throw 0;
        l=s[i];
        throw 1;
    }}
    catch(int a){puts(a?"yes":"no");}
}
