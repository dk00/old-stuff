#include<cstdio>
#include<cstring>
void rev(char s[],int n)
{
    for(int i=0;i<n-i;i++)
    {
        char t=s[i];
        s[i]=s[n-i-1];
        s[n-i-1]=t;
    }
}
main()
{
    int i,j,k,l,n,C=0;
    char s1[99],s2[99],s[99],tmp[99];
    while(gets(s) && strcmp(s,"STOP"))
    {
        if(C++)puts("");
        printf("Dataset #%d:  The initial order is %s.\n",C,s);
        scanf("%d",&n);
        for(l=0;l<n;l++)
        {
            scanf("%s",tmp);
            for(i=0;s[i]!=tmp[0];i++)s1[i]=s[i];
            for(j=0;s[i+j+1];j++)s2[j]=s[i+j+1];
            s1[i]=s2[j]=0;
            if(i<=j)rev(s1,i);
            else rev(s2,j);
            for(k=0;k<i;k++)
                s[k]=s1[k];
            for(k=0;k<j;k++)
                s[i+k]=s2[k];
            s[i+k]=0;
            printf("After %s leaves, the order is %s.\n",tmp,s);
            scanf("%c",tmp);
        }
    }
}
