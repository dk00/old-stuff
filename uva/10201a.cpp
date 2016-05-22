#include<cstdio>
int d[200],s[200],ne[200];
int next(int k)
{
    if(ne[k]>=0)
        return ne[k];
    ne[k]=k+1;
    while(s[k]<s[ne[k]])
        ne[k]=next(ne[k]);
    return ne[k];
}
main()
{
    char tmp[1000];
    int i,j,n,m,a,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%c",&m,tmp);
        for(n=0;gets(tmp) && sscanf(tmp,"%d %d",&d[n],&s[n])==2;n++)
            ne[n]=-1;
        d[n]=m+100,s[n]=0;
        for(i=0,m=100-d[0],a=0;i<n;m-=d[j]-d[i],i=j)
        {
            if(m<0 || d[i+1]-d[i]>200)
                break;
            j=next(i);
            if(d[j]-d[i]>200)j=i+1;
            if(s[i]<s[j])
                a+=(200-m)*s[i],m=200;
            else if(m<d[j]-d[i])
                a+=(d[j]-d[i]-m)*s[i],m=d[j]-d[i];
        }
        if(i<n)puts("Impossible");
        else printf("%d\n",a);
        if(t)puts("");
    }
}
