#include<cstdio>
#include<algorithm>
bool cmp(const int& a,const int& b){return a>b;}
main()
{
    register short i,j,k,l,n;
    int p,s[1000];
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        std::sort(s,s+n,cmp);
        /*for(l=0;l<n;l++)
            for(i=0;s[i]*3>=s[l] && i+2<n;i++)
            {
                if(i==l)continue;
                for(j=i+1,k=n-1;j<k;j++)
                {
                    p=s[l]-s[i]-s[j];
                    while(j<k && s[k]<p)k--;
                    while(s[k]==p)
                    if(j!=l && k--!=l)goto find;
                }
            }*/
        puts("no solution");
        continue;
        find:printf("%d\n",s[l]);
    }

}
