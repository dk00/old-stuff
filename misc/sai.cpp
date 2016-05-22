#include<cstdio>
main()
{
    int i,j,k;
    char c,s[1000];
    while((c=getchar())!=EOF)
    {
        i=j=0;
        ungetc(c,stdin);
        while((c=getchar())!='\n')
        {
            s[j++]=c;
            if(c=='A')i--;
            if(c=='A' || c=='S')k=1;
            if(c=='i'|| c=='a' || c=='s')i++;
            if(i==1)
                i=k=0,s[j++]='-';
        }
        s[j]=0;
        if(j>0 && s[j-1]=='-')
            s[--j]=0;
        if(i==0 && k==0)
            puts(s);
        else puts("0");
    }
}
