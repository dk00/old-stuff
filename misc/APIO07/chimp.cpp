#include<cstdio>
#include<algorithm>
main()
{
    freopen("chimpin.txt","r",stdin);
    freopen("chimpout.txt","w",stdout);
    int x,y,n,m;
    scanf("%d %d",&x,&y);
    n=(abs(x)>?abs(y))*2;
    if(n/2==abs(y))
    {
        if(y>=0)m=n+abs(n/2-x);
        else m=3*n+abs(n/2+x);
    }
    else
    {
        if(x>=0)m=abs(n/2+y);
        else m=2*n+abs(n/2-y);
    }
    printf("%d\n",(n-1)*(n-1)+m-1);
}
