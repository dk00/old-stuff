#include<cstdio>
main()
{
    int i,j,k,t,sum,s[26],d[26],u[26],c[26][26];
    char tmp1[1000],tmp2[1000];
    scanf("%d%c",&t,tmp1);
    gets(tmp1);
    while(t--)
    {
        for(i=0;i<26;i++)
        {
            s[i]=d[i]=0;
            for(j=0;j<26;j++)
                c[i][j]=0;
        }
        while(gets(tmp1) && tmp1[0])
        {
            i=tmp1[0]-'A';
            if(sscanf(tmp1+1,"%d %s",&s[i],tmp2)==2)
                for(j=0;tmp2[j];j++)
                    c[i][tmp2[j]-'A']=1;
        }
        for(i=sum=0;i<26;i++)
            for(j=0;j<26;j++)
                if(c[i][j])
                    d[i]+=s[j];
        while(1)
        {
            for(i=0;(!s[i] || d[i]) && i<26;i++);
            if(i>=26)break;
            for(j=i+1,i=s[i];j<26;j++)
                if(s[j] && !d[j] && s[j]<i)i=s[j];
            sum+=i;
            for(j=0;j<26;j++)
                u[j]=(s[j] && !d[j]);
            for(j=0;j<26;j++)
                if(u[j])
                {
                    s[j]-=i;
                    for(k=0;k<26;k++)
                        if(c[k][j])
                            d[k]-=i;
                }
        }
        printf("%d\n",sum);
        if(t)puts("");
    }
}
