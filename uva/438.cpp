#include<stdio.h>
int t,x1,y1,x2,y2,x3,y3,x4,y4;
int a1,b1,c1,a2,b2,c2;
double px,py;
main(){
scanf("%d",&t);
puts("INTERSECTING LINES OUTPUT");
while(t--){
    scanf("%d %d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
    b1=x1-x2;
    a1=y2-y1;
    b2=x3-x4;
    a2=y4-y3;
    if(a1*b2==a2*b1){
        if((x1-x2)*(y1-y3)==(x1-x3)*(y1-y2))puts("LINE");
        else puts("NONE");
        continue;
    }
    c1=a1*x1+b1*y1;
    c2=a2*x3+b2*y3;
    px=(c1*b2-c2*b1)/(double)(a1*b2-a2*b1);
    py=(a1*c2-a2*c1)/(double)(a1*b2-a2*b1);
    printf("POINT %.2lf %.2lf\n",px,py);
}
puts("END OF OUTPUT");
}
/*
| c1 b1
| c2 b2
*/
