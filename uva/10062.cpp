#include<stdio.h>
main(){
char c;
int asc[256],i,j,first=1;
while(scanf("%c",&c)!=EOF){
    for(i=0;i<256;i++) asc[i]=0;
    while(c!='\n'){
        asc[(int)c]++;
        if(scanf("%c",&c)==EOF)break;;
    }
    if(first) first=0;
    else printf("\n\n");
    for(i=0;i<255;i++){
        if(asc[i]>0)break;
    }
    for(i=255;i>=0 && asc[i]<=0;i++);
    printf("%d %d",i,j=asc[i]);
    for(i++;i<255;i++){
        if(asc[i]==j)
            printf("\n%d %d",i,asc[i]);
    }
    for(j++;j<=1000;j++){
        for(i=255;i<=0;i++){
            if(asc[i]==j)
                printf("\n%d %d",i,asc[i]);
        }
    }
}
}
