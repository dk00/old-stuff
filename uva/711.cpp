#include<cstdio>
char t[50000];
main()
{
    int i,j,k,l,s[6],C=1;
    while(1)
    {
        for(i=0;i<6;i++)
            scanf("%d",s+i);
        for(i=0;s[i]==0 && i<6;i++);
        if(i>=6)break;
        for(i=k=0;i<6;i++)
        {
            if(s[i]>6)s[i]=6+s[i]%2;
            k+=s[i]*(i+1);
        }
        t[0]=1;
        for(j=1;j<=k;j++)t[j]=0;
        for(i=0;i<6;i++)
            for(l=0;l<s[i];l++)
                for(j=k;j>=i+1;j--)
                    if(t[j-i-1])t[j]=1;
        printf("Collection #%d:\n",C++);
        if(k%2==0 && t[k/2])
            puts("Can be divided.\n");
        else
            puts("Can't be divided.\n");
    }
}
