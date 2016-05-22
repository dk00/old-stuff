#include<cmath>
#include<cstdio>
#include<cstring>
main()
{
    int i,j,k,n,m,pos,next[201];
    char num[202],now[100];
    while(gets(num)!=NULL)
    {
        n=strlen(num);
        next[1]=0;
        for(i=1,j=0;i<n;i++)
        {
            while(j>0 && num[i]!=num[j])
                j=next[j];
            if(num[i]==num[j])
                j++;
            next[i+1]=j;
        }
        for(i=pos=1,k=0;k<n && i<10000000;i++)
        {
            sprintf(now,"%d",i);
            m=floor(log10(i))+1;
            for(j=0;j<m && k<n;j++,pos++)
            {
                while(k>0 && num[k]!=now[j])
                    k=next[k];
                if(num[k]==now[j])
                    k++;
            }
        }
        if(i>=10000000)
            puts("-1");
        else
            printf("%d\n",pos-n);
    }
}
