#include<cstdio>
char tmp[10011];
long long s[10011];
main()
{
    int i;
    freopen("pf.in","r",stdin);
    while(scanf("%s",tmp)==1 && tmp[0]!='0')
    {
        s[0]=1;
        for(i=0;tmp[i];i++)
            s[i+1]=0;
        for(i=0;tmp[i];i++)
        {
            if(tmp[i]>='1')
                s[i+1]+=s[i];
            if(tmp[i]>='1' && tmp[i]<='2' && tmp[i+1]>='0')
                s[i+2]+=s[i];
        }
        printf("%I64d\n",s[i]);
    }
}
