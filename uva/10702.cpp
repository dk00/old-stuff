#include<stdio.h>
int tr0[100][100],base[2][100],*tr1=base[0],*tr2=base[1],*tmp;
main(){
int i,j,k,l,c,s,e,t,max,ed[100];
while(scanf("%d %d %d %d",&c,&s,&e,&t) && c+s+e+t){
    for(s--,max=i=0;i<c;i++){
        ed[i]=0;
        for(j=0;j<c;j++)
            scanf("%d",&tr0[i][j]);
    }
    while(e--){
        scanf("%d",&i);
        ed[i-1]=1;
    }
    for(i=0;i<c;i++)tr1[i]=tr0[s][i];
    while(t-->1){
        for(i=0;i<c;i++){
            tr2[i]=0;
            for(j=0;j<c;j++)
                tr2[i]>?=(tr1[j]+tr0[j][i]);
        }
        tmp=tr1;tr1=tr2;tr2=tmp;
    }
    for(i=0;i<c;i++)if(ed[i])max>?=tr1[i];
    printf("%d\n",max);
}
}
