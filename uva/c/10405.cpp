#include<stdio.h>
#define max(a,b) a>b?a:b
main(){
char line1[1001],line2[1001],c;
int lcslen[1001][1001],l1,l2,i,j;
while(scanf("%c",&c)!=EOF){
    line1[l1=1]=c;
    lcslen[0][0]=0;
    lcslen[1][0]=0;
    while(1){
        scanf("%c",&c);
        if(c=='\n') break;
        line1[++l1]=c;
        lcslen[l1][0]=0;
    }
    for(l2=0;1;){
        scanf("%c",&c);
        if(c=='\n') break;
        line2[++l2]=c;
        lcslen[0][l2]=0;
    }
    for(i=1;i<=l1;i++){
        for(j=1;j<=l2;j++){
            if(line1[i]==line2[j])
                lcslen[i][j]=lcslen[i-1][j-1]+1;
            else
                lcslen[i][j]=max(lcslen[i-1][j],lcslen[i][j-1]);
        }
    }
    printf("%d\n",lcslen[l1][l2]);
}
}
