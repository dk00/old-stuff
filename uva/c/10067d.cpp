#include<stdio.h>
int l[]={5,5,5,5},r[]={5,5,5,5},on[10][10][10][10],ww[4],
p,t1,t2,t3,t4,min;
void play(int s,int *w){
    if(w[0]==t1 && w[1]==t2 && w[2]==t3 && w[3]==t4){
        min<?=s;
        on[t1][t2][t3][t4]=1;
        return;
    }
    if(s>=min || on[w[0]][w[1]][w[2]][w[3]])return;
    on[w[0]][w[1]][w[2]][w[3]]=1;
    for(int i=0;i<4;i++){
        if(l[i] && r[i]==5){
            w[i]=(w[i]+9)%10;
            l[i]--;
            play(s+1,w);
            l[i]++;
            w[i]=(w[i]+1)%10;
        }
        if(r[i] && l[i]==5){
            w[i]=(w[i]+1)%10;
            r[i]--;
            play(s+1,w);
            r[i]++;
            w[i]=(w[i]+9)%10;
        }
    }
}
main(){
int t,n,x1,x2,x3,x4;
scanf("%d",&t);
while(t--){
    for(x1=0;x1<10;x1++)for(x2=0;x2<10;x2++)for(x3=0;x3
    <10;x3++)for(x4=0;x4<10;x4++)on[x1][x2][x3][x4]=0;
    scanf("%d %d %d %d",&ww[0],&ww[1],&ww[2],&ww[3]);
    scanf("%d %d %d %d %d",&t1,&t2,&t3,&t4,&n);
    while(n--){
        scanf("%d %d %d %d",&x1,&x2,&x3,&x4);
        on[x1][x2][x3][x4]=1;
    }min=10000;
    play(0,ww);
    if(on[t1][t2][t3][t4])printf("%d\n",min);
    else puts("-1");
}
}
