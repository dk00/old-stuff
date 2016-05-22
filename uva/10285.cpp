#include<stdio.h>
main(){
int i,j,k,r,c,t,max,h[100][100],len[100][100];
char s[10000];
scanf("%d",&t);
while(t--){
    scanf("%s %d %d",s,&r,&c);
    printf("%s:",s);
    for(max=k=i=0;i<r;i++)
        for(j=0;j<c;j++){
            scanf("%d",&h[i][j]);
            len[i][j]=1;
            k>?=h[i][j];
        }
    while(k--)
        for(i=0;i<r;i++)
            for(j=0;j<c;j++)
                if(h[i][j]==k){
                    if(j>0 && h[i][j-1]>h[i][j])
                        len[i][j]>?=(len[i][j-1]+1);
                    if(j+1<c && h[i][j+1]>h[i][j])
                        len[i][j]>?=(len[i][j+1]+1);
                    if(i>0 && h[i-1][j]>h[i][j])
                        len[i][j]>?=(len[i-1][j]+1);
                    if(i+1<r && h[i+1][j]>h[i][j])
                        len[i][j]>?=(len[i+1][j]+1);
                    max>?=len[i][j];
                }
    printf(" %d\n",max);
}
}
