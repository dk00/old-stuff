#include<cstdio>
int min(int a,int b){if(a<b)return a;return b;} //Boxes
main()
{
    int i,j,n,w[1005],mw[1005],now,s[1005];
    while(scanf("%d",&n) && n)
    {
        for(i=0,j=1;i<n;i++)
            scanf("%d %d",&w[i],&mw[i]);
        s[0]=w[--n];
        while(n--)
        {
            for(i=j-1;i>=0;i--)
            {
                if(mw[n]>=s[i])
                {
                    if(i==j-1)
                        s[j++]=s[i]+w[n];
                    else if(s[i]+w[n]<s[i+1])
                        s[i+1]=s[i]+w[n];
                }
            }
            if(w[n]<s[0])
                s[0]=w[n];
        }
        printf("%d\n",j);
    }
}
