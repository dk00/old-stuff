/*
PROB:hidden
LANG:C++
*/
#include<cstdio>
char s[200002];
main()
{
    int i,j,k,n,T;
    freopen("hidden.in","r",stdin);
    freopen("hidden.out","w",stdout);
    scanf("%d",&n);
    for(i=0;scanf("%s",s+i)>0;i+=72);
    {
        for(n=0;s[n];n++);
        s[n*2]=0;
        for(i=n-1;i>=0;i--)s[i+n]=s[i];
        for(i=k=0,j=1;i+j+k<2*n;)
        {
            if(s[i+j+k]<s[i+k])i+=j,k=0,j=1;
            else if(s[i+k]<s[i+j+k])j+=k+1,k=0;
            else k++;
        }
        printf("%d\n",(i%n));
    }
}
