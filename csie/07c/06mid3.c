ans(i){puts(i?"yes":"no");}
main()
{
    int i,n,sum;
    char s[9999];
    while(scanf("%s",s+2)==1)
    {
        s[0]=s[1]='0';
        for(n=sum=0;s[n];n++)
            sum+=s[n]-='0';
        ans(s[n-1]%2==0);
        ans(sum%3==0);
        ans((s[n-1]+s[n-2]*10)%4==0);
        ans(s[n-1]%5==0);
        ans(sum%3==0 && s[n-1]%2==0);
        ans((s[n-1]+s[n-2]*10+s[n-3]*100)%8==0);
        ans(sum%9==0);
        ans(s[n-1]==0);
    }
}
