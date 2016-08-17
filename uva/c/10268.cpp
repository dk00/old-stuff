#include<cstdio>
int s[1000000];
main()
{
    int c,i,j,n,x;
    while(scanf("%d",&x)==1)
    {
        for(n=c=0;c!='\n';n++)
        {
            scanf("%d",&s[n]);
            while(1)
            {
                c=getchar();
                if(c=='\n' ||(c>='0' && c<='9'))break;
            }
            if(c!='\n')ungetc(c,stdin);
        }
        s[n-1]=0;
        for(i=n-2,j=1;i>=0;i--,j*=x)
            s[i]=s[i+1]+s[i]*j*(n-1-i);
        printf("%d\n",s[0]);
    }
}
