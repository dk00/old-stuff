#include<stdio.h>
main(){
int a,b,c,d;
for(a=6;a<=200;a++)
    for(b=2;b*b*b*3<=a*a*a;b++)
        for(c=b;b*b*b+c*c*c*2<=a*a*a;c++)
            for(d=c;b*b*b+c*c*c+d*d*d<=a*a*a;d++)
                if(a*a*a==b*b*b+c*c*c+d*d*d)
                    printf("Cube = %d, Triple = (%d,%d,%d)\n",
                    a,b,c,d);
}
