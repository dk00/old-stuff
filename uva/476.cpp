/* @JUDGE_ID:  58589NF  476  C++  "Points in Figures: Rectangles"*/
#include<stdio.h>
#define ER 0.0001
int main(){
double lx[10],ly[10],rx[10],ry[10],sx,sy;
char c;
int i,n,p;
for(i=0;i<10;i++){
    scanf("%c",&c);
    if(c=='*') break;
    scanf(" %lf %lf %lf %lf%c",&lx[i],&ry[i],&rx[i],&ly[i]);
}
n=i;
for(p=1;scanf("%lf %lf",&sx,&sy)!=EOF;p++){
    if(sx==9999.9 && sy==9999.9) break;
    for(c=0,i=0;i<n;i++){
        if(sx-ER>lx[i] && sy-ER>ly[i] && sx+ER<rx[i] && sy+ER<ry[i]){
            printf("Point %d is contained in figure %d\n",p,i+1);
            c=1;
        }
    }
    if(c==0) printf("Point %d is not contained in any figure\n",p);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
