#include<math.h>
#include<stdio.h>
main()
{
    int i;
    double j,min,s[9];
    scanf("%lf %lf %lf",s,s+1,s+2);
    {
        j=s[0]+s[1]+s[2];
        min=j*j;
        for(i=0;i<3;i++)
            if((j-s[i])*(j-s[i])+s[i]*s[i]<min)
                min=(j-s[i])*(j-s[i])+s[i]*s[i];
        printf("%lf\n",sqrt(min));
    }
}
