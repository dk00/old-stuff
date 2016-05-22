#include<cstdio>
main()  //Sum
{
    int i,j,sum;
    char last,s[100];
    while(gets(s))
    {
        for(i=sum=0;s[i];i++)
        {
            if(s[i]>='0' && s[i]<='9')
            {
                if(i>0)
                    last=s[i-1];
                else last='+';
                for(j=0;s[i] && s[i]>='0' && s[i]<='9';i++)
                    j=j*10+s[i]-'0';
                i--;
                if(last=='-')
                    j=-j;
                sum+=j;
            }
        }
        printf("%d\n",sum);
    }
}
