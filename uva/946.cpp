#include<cstdio>
struct box
{
    int l,h;
}s[200];
main()
{
    int i,j,k,l,n;
    while(scanf("%d",&n)==1)
    {
        for(i=1;i<=n;i++)
        {
            scanf("%d",&l);
            for(j=i-1;j>=0;j--)
                if(l>s[j].l)break;
            while(j<i-1 && l+s[j].l+s[j].h>s[j+1].l+s[j+1].h)j++;
            for(j++,k=i;k>j;k--)s[k]=s[k-1];
            s[j]=(box){l,s[j-1].l+s[j-1].h};
        }
        printf("%d\n",s[n].l+s[n].h);
    }
}
