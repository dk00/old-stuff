#include<stdio.h>
main()
{
int a,b,i,s[1000],n;
float c,d,e;
    scanf("%d",&a);
    for(;a>0;a--)
    {
        c=e=0;
        scanf("%d",&n);
        for(b=0;b<n;b++)
        {
            scanf("%d",&s[b]);
            //c=s[b]+c;
            c+=s[b];
        }
        d=c/n;
        for(b=0;b<n;b++)
        {
            if(s[b]>d){
                e++;
            }
        }
        printf("%.3lf%%\n",100*e/n);
    }
    scanf(" ");
    return 0;
}
