#include<time.h>
#include<stdio.h>
#include<stdlib.h>
main()
{
    int i,j,sum,max,s[1000];
    for(i=0;i<5;i++)
    {
        for(j=sum=max=0;j<50;j++)
        {
            s[j]=1+rand()%5000;
            sum+=s[j];
            if(sum>max)
                max=sum;
        }
        printf("50 %d\n",max+sum/(5+rand()%4500));
        for(j=0;j<50;j++)
            printf("%d ",s[j]);
        puts("");
    }
    getchar();
}
