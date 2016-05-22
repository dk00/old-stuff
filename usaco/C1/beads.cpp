/*
LANG:C++
TASK:beads
*/
#include<cstdio>
main()
{
    freopen("beads.in","r",stdin);
    freopen("beads.out","w",stdout);
    int i,j,k,l,w,lw,llw,n,max;
    char s[1000];
    scanf("%d %s",&n,s);
    for(i=0;i<n;i++)s[i+n]=s[i];
    for(i=k=l=max=lw=w=0;i<n*2;i=j)
    {
        llw=lw,lw=w,w=0;
        for(j=i;j<2*n && j-i<=n &&(s[j]=='w' ||  s[j]==s[i]);j++)
            if(s[j]=='w')w++;
            else w=0;
        k=l+llw,l=j-i;
        max>?=k+l;

    }
    printf("%d\n",max<?n);
    scanf(" ");
}
