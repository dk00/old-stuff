#include<cstdio>
#include<algorithm>
char s[1001],t[1001];
main()
{
    int i,j,k,n,m,x,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s %d",s,&x);
        for(n=0;s[n];n++)t[n]=s[n];
        t[n]=0;
        for(i=-n,m=0;i<n;i++)
            for(j=i>?0,k=0;j+k<n && i+j+k<n;k++)
            {
                if(s[j+k]!=t[i+j+k])x--;
                for(;j+k<n && i+j+k<n && x<0;j++,k--)
                    if(s[j]!=t[i+j])x++;
                if(x>=0)m>?=k+1;
            }
        printf("%d\n",m);
    }
}
