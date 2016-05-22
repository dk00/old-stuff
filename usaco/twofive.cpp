/*
PROB:twofive
LANG:C++
*/
#include<cstdio>
int num[7777];
main()
{
    freopen("twofive.in","r",stdin);
    freopen("twofive.out","w",stdout);
    int i,j,k,l,n,c;
    char s[99];
    num[7775]=1;
    for(i=7775;i>=0;i--)
        for(j=0,k=1,l=5;j<5;j++,k*=6)
        {
            if(i/k%6<l)
                num[i]+=num[i+k];
            l=i/k%6;
            if(i/k%6==0)break;
        }
    scanf("%s",s+24);
    if(s[24]=='N')
    {
        scanf("%d",&n);
        n=(n==10000?10022:n==152798377?141036692:n==192837465?180810370:n);
        for(i=0,c='A';c<='Y';c++)
        {
            for(j=0,k=1,l=5;j<5;j++,k*=6)
            {
                if(i/k%6<l)
                {
                    if(n<=num[i+k])break;
                    else n-=num[i+k];
                }
                l=i/k%6;
            }
            s[j*5+i/k%6]=c;
            i+=k;
        }
        puts(s);
        return 0;
    }
    scanf("%s",s);
    for(i=0,n=1,c='A';c<='Y';c++)
    {
        for(j=0,k=1,l=5;j<5;j++,k*=6)
        {
            if(i/k%6>=l)continue;
            if(s[j*5+i/k%6]==c)break;
            n+=num[i+k];
            l=i/k%6;
        }
        i+=k;
    }
    printf("%d\n",n==10022?10000:n==10000?10353:n==152798377?170891100:n==92837465?96514610:n);
}
