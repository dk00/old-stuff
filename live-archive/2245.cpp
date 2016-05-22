#include<cstdio>
#include<cstring>
void add(char *a,char *b)
{
    int i,j,n;
    for(n=0;b[n];n++);
    for(i=n-1;i>=0;i--)
    {
        a[i]+=b[i]-'0';
        if(a[i]>'9')
            a[i]-=10,a[i-1]++;
    }
}
void div8(char *a)
{
    int i,n;
    for(n=0;a[n];n++);
    for(i=0;a[i]=='0';i++);
    for(;i<n;i++)
    {
        if((a[i]-'0')%8)
        {
            if(a[i+1]==0)
                n++,a[i+1]='0',a[i+2]=0;
            a[i+1]+=((a[i]-'0')%8)*10;
        }
        a[i]=(a[i]-'0')/8+'0';
    }
}
main()
{
    int i,j;
    char s[10000],five[10000],ans[10001];
    strcpy(five,"125");
    while(scanf("%d.%s",&i,s)==2)
    {
        printf("%d.%s [8] = %d.",i,s,i);
        strcpy(five,"125");
        for(i=0;s[i];i++)
        {
            ans[3*i]=ans[3*i+1]=ans[3*i+2]='0';
            ans[3*i+3]=0;
            for(j='0';j<s[i];j++)
                add(ans,five);
            div8(five);
        }
        printf("%s [10]\n",ans);
    }
}
