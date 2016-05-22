#include<cstdio>
main()
{
    while(scanf("%d",&m) && m)
    {
        scanf("%s",s);
        for(i=0;i<s;i++)
            if('A'<=s[i] && s[i]<='Z')
                s[i]+='a'-'A';
        for(j=0;j<26;j++)
        {
            if(s[0]=='a'+i)
            for(i=1;s[i];i++)
                if(s[i]=='a'+i)
                    sum[j][i]=1+sum[j][i-1];
                else
                    sum[j][i]=sum[j][i-1];
        }
    }
}
