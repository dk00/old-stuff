#include<cstdio>
int lis(const int &n,const int s[])
{
    int p[n],t[n];
    t[0]=0;
    for(i=l=1;i<n;i++)
    {
        for(j=0,k=l;j<=k;)
        {
            x=(j+k)/2;
            if(s[i]>s[t[x]])
                j=x+1;
            else if(x && s[i]<s[t[x-1]])
                k=x-1;
            else break;
        }
        t[x]=i;
        if(x)p[i]=t[x-1];
        if(x>=l)l++;
    }

    return l;
}
main()
{

}
