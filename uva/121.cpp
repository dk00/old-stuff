#include<stdio.h>
#include<math.h>
main(){
long grid,skew1,skew2,row,col;
double a,b,sq3=sqrt(3.0)/2;
while(scanf("%lf %lf",&a,&b)!=EOF){
    grid=(floor(a)*floor(b));
    row=1+floor((a-1)/sq3);
    col=floor(b);
    skew1=(row/2)*col+(row%2)*col;
    if(b-floor(b)<0.5)col--;
    skew1+=(row/2)*col;
    row=1+(long)((b-1)/sq3);
    col=floor(a);
    skew2=(row/2)*col+(row%2)*col;
    if(a-floor(a)<0.5)col--;
    skew2+=(row/2)*col;
    if(grid>=(skew1>?skew2))printf("%ld grid\n",grid);
    else printf("%ld skew\n",skew1>?skew2);
}
}
