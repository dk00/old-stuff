#include<cstdio>
main()
{
    int n,ac,sum=0,h1,d1,w1,h2,d2,w2;
    char s[1000];
    while(gets(s))
    {
        ac=1;
        sscanf(s,"%d %d %d",&h1,&d1,&w1);
        for(n=1;;n++)
        {
            gets(s);
            if(sscanf(s,"%d %d %d",&h2,&d2,&w2)<3)
                break;
            if(h1-w1*2<h2 || d1-w1*2<d2)
                ac=0;
            h1=h2,d1=d2,w1=w2;
        }
        gets(s);
        sscanf(s,"%d %d %d",&h1,&d1,&w1);
        while(--n)
        {
            gets(s);
            if(sscanf(s,"%d %d %d",&h2,&d2,&w2)<3)
                break;
            if(h1-w1*2<h2 || d1-w1*2<d2)
                ac=0;
            h1=h2,d1=d2,w1=w2;
        }
        sum+=ac;
        gets(s);
    }
    printf("Get %d point\n",sum);
    printf("%d\n",sum);
    scanf(" ");
}
