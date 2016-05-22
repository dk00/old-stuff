#include<stdio.h>
#include<string.h>
#define top(a)  pile[(a)][h[(a)]-1]
#define push(b) pile[(b)][h[(b)]++]
#define pop(c)  pile[(c)][--h[(c)]]
char pile[52][52][3];
main(){
int i,j,k,move,h[52],n;
while(scanf("%s",pile[0][0]) && strcmp(pile[0][0],"#")){
    h[0]=1;
    for(i=1;i<52;i++){
        scanf("%s",pile[i][0]);
        h[i]=1;
    }
    n=52;
    while(n>1){
        for(move=0,i=1;i<n;i++){
            if(i>=3&&(top(i-3)[0]==top(i)[0]||top(i-3)[1]==top(i)[1])){
                move=3;
                break;
            }
            else if(top(i-1)[0]==top(i)[0] || top(i-1)[1]==top(i)[1]){
                move=1;
                break;
            }
        }
        if(!move)break;
        if(move==3)
            strcpy(push(i-3),pop(i));
        if(move==1)
            strcpy(push(i-1),pop(i));
        if(!h[i])
            for(n--,j=i+1;j<=n;j++){
                for(k=0;k<h[j];k++)
                    strcpy(pile[j-1][k],pile[j][k]);
                h[j-1]=h[j];
            }
    }
    printf("%d pile%sremaining:",n,(n-1)?"s ":" ");
    for(i=0;i<n;i++)printf(" %d",h[i]);
    puts("");
}
}
