#include<cstdio>
main()
{
    int i,j,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d:%d",&i,&j);
        while(1)
        {
            j++;
            if(j>=60)i++;
            j%=60;
            i%=24;
            if(i==0 &&(j<10 || j/10==j%10))break;
            if(i && i<10 && i==j%10)break;
            if(i>=10 && i/10+i%10*10==j)break;
        }
        printf("%02d:%02d\n",i,j);
    }
}
