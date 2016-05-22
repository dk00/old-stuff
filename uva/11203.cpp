#include<cstdio>
main()
{
    int i,a,b,c,T;
    char tmp[100];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",tmp);
        for(i=0;tmp[i];i++)
            if(tmp[i]!='?' && tmp[i]!='M' && tmp[i]!='E')
                goto no;
        a=b=c=0;
        for(i=0;tmp[i];i++)
            if(tmp[i]=='M')a++;
            else if(tmp[i]=='E')b++;
        if(a!=1 || b!=1)goto no;
        for(i=a=0;tmp[i]!='M';i++,a++);
        for(b=0;tmp[i]!='E';i++,b++);
        for(c=0;tmp[i];i++,c++);
        if(c>1 && b && a && c==a+b)
            puts("theorem");
        else no:puts("no-theorem");
    }
}
