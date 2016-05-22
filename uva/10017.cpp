#include<stdio.h>
int step,h[3],s[3][250];
void show(){
    int i;
    if(step--<0)return;
    printf("\nA=>  ");
    for(i=0;i<h[0];i++)
        printf(" %d",s[0][i]);
    printf("\nB=>  ");
    for(i=0;i<h[1];i++)
        printf(" %d",s[1][i]);
    printf("\nC=>  ");
    for(i=0;i<h[2];i++)
        printf(" %d",s[2][i]);
    puts("");
}
void move(int n,int a,int b,int c){
    if(step<0)return;
    if(n==1){
        s[c][h[c]++]=s[a][--h[a]];
        show();
    }
    else{
        move(n-1,a,c,b);
        s[c][h[c]++]=s[a][--h[a]];
        show();
        move(n-1,b,a,c);
    }
}
main(){
int n,m,C=0;
while(scanf("%d %d",&n,&m) && n+m){
    if(C++)puts("");
    printf("Problem #%d\n\n",C);
    for(h[0]=h[1]=h[2]=0,step=m;h[0]<n;h[0]++)s[0][h[0]]=n-h[0];
    show();
    move(n,0,1,2);
}
}
