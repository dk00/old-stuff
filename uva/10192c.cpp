#include<stdio.h>
#define max(a,b) a>b?a:b
main(){
char line1[101],line2[101],c;
int lcslen[101][101],l1,l2,i,j,Case=1;
for(;1;Case++){
    lcslen[0][0]=0;
    for(l1=0;1;){
        scanf("%c",&c);
        if(c=='\n' || c=='#') break;
        line1[++l1]=c;
        lcslen[l1][0]=0;
    }
    if(c=='#') break;
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
    printf("Case #%d: you can visit at most %d cities.\n",
    Case,lcslen[l1][l2]);
}
}
