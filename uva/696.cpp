#include<stdio.h>
main(){
int c,r;
while(scanf("%d %d",&c,&r) && c && r){
    if(c>r){
        if(r==1)printf("%d",c);
        else if(r==2)printf("%d",c/4*4+((c%4)<?2)*2);
        else printf("%d",(c*r+1)/2);
    }
    else{
        if(c==1)printf("%d",r);
        else if(c==2)printf("%d",r/4*4+((r%4)<?2)*2);
        else printf("%d",(c*r+1)/2);
    }
    printf(" knights may be placed on a %d row %d column board.\n",c,r);
}
}
