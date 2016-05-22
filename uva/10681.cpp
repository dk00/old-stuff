#include<stdio.h>
int link[100][100],ari[201][100];
main(){
int i,j,k,c,l,s,e,d;
while(scanf("%d %d",&c,&l) && c+l){
    for(i=0;i<c;i++)
        for(j=0;j<c;j++)link[i][j]=0;
    while(l--){
        scanf("%d %d",&i,&j);
        i--,j--;
        link[i][j]=link[j][i]=1;
    }
    scanf("%d %d %d",&s,&e,&d);
    s--,e--;
    for(i=0;i<c;i++)
        for(k=0;k<=d;k++)ari[k][i]=0;
    ari[0][s]=1;
    for(k=0;k<d;k++)
        for(i=0;i<c;i++)
            if(ari[k][i])
                for(j=0;j<c;j++)
                    if(link[i][j])
                        ari[k+1][j]=1;
    if(ari[d][e])puts("Yes, Teobaldo can travel.");
    else puts("No, Teobaldo can not travel.");
}
}
