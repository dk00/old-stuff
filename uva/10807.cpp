#include<stdio.h>
main(){
while(scanf("%d",&n) && n){
    scanf("%d",&m);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c1[i][j]=0;
    while(m--){
        scanf("%d %d %d",&i,&j,&k);
        i--,j--;
        if(c1[i][j])
            if(c2[i][j])
                if(k<c1[i][j]){
                    c2[i][j]=c1[i][j];
                    c1[i][j]=k;
                }
                else if(k<c2[i][j])c2[i][j]=k;
            else c2[i][j]=k;
        else c1[i][j]=k;
    }
    
}
}
