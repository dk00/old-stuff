#include <stdio.h>
int d[30][360];
main(){
    int l,s,i,j,k,cases=1;
    for(i=1;i<=26;i++)
        d[1][i]=1;
    for(;i<360;i++)
        d[1][i]=0;
    for(i=2;i<30;i++)
        for(j=1;j<360;j++){
            d[i][j]=0;
            if((j-1)/2==0)
                d[i][j]=1;
            else if(j<=((26-i+1)+26)*i/2)
                for(k=1;k<=(j-1)/2;k++)
                    d[i][j]+=d[i-1][k];
        }
    while(scanf("%d %d",&l,&s) && l+s){
        if(l>=30)  l=29;
        if(s>=360) s=359;
        printf("Case %d: %d\n",cases++,d[l][s]);
    }
}
