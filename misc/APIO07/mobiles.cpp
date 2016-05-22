#include<cstdio>
int l[100005],r[100005],h[100005],x[100005];
int abs(int x){return x<0?-x:x;}
int go(int v)
{
    int sl=0,sr=0,hl=h[v],hr=h[v],xl=0,xr=0;
    if(l[v]>=0)
    {
        sl=go(l[v]);
        hl=h[l[v]],xl=x[l[v]];
    }
    if(r[v]>=0)
    {
        sr=go(r[v]);
        hr=h[r[v]],xr=x[r[v]];
    }
    h[v]=(hl>?hr);
    x[v]=(xl || xr || hl!=hr);
    if((xl && xr)|| sl<0 || sr<0 || abs(hl-hr)>1)return -1;
    if(!xl && !xr)
        return sl+sr+(hl-hr==-1);
    if(xl)
    {
        if(hr>hl)return -1;
        return sl+sr+(hl==hr);
    }
    if(xr)
    {
        if(xl>xr)return -1;
        return sl+sr+(hl<hr);
    }
    
}
main()
{
    //freopen("mobiles.in","r",stdin);
    //freopen("mobiles.out","w",stdout);
    int i,n;
    while(scanf("%d",&n)==1)
    {
        h[0]=0;
        for(i=1;i<=n;i++)
        {
            scanf("%d %d",l+i,r+i);
            if(l[i]>=0)h[l[i]]=h[i]+1;
            if(r[i]>=0)h[r[i]]=h[i]+1;
        }
        printf("%d\n",go(1));
    }
}
