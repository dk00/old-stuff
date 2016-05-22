#include<stdio.h>
#include<stdlib.h>
main(){
char map[100][101];
int i,j,k,l,m,max,min;
while(scanf("%d",&m)!=EOF){
    gets(map[0]);
    for(max=i=0;i<m;i++)
        gets(map[i]);
    for(i=0;i<m;i++)
        for(j=0;j<m;j++){
            if(map[i][j]=='1'){
                for(min=3*m,k=0;k<m;k++)
                    for(l=0;l<m;l++)
                        if(map[k][l]=='3')
                            min<?=abs(i-k)+abs(j-l);
            }
            max>?=min;
        }
    printf("%d\n",max);
}
}
