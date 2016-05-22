#include<cstdio>
int n,k,a1;
char s[20001],tmp[20001];
inline char inc(char x){return (x=='Z')?'A':x+1;}
char go(long long i)
{
    int x=0;
    while(1)
    {
        if(i<n)
        {
            i=s[i];
            while(x--)i=inc(i);
            return i;
        }
        if(i%(k+1)==0)
            --i,++x;
        else
            i=i-n-(i+a1)/(k+1);
    }
}
main()
{
    int i,j,m;
    while(scanf("%d %d %d %s",&n,&k,&m,tmp)>0)
    {
        for(i=j=0;tmp[i];i++)
        {
            s[j++]=tmp[i];
            if(i && i%k==0)
                s[j++]=inc(tmp[i]);
        }
        n=j;
        a1=-n+n%(k+1)-1;
        //while(scanf("%d",&m) && m>=0)
            printf("%c\n",go(1ll*m*(k+1)));
    }
}
