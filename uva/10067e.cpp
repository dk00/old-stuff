#include<stdio.h>
int on[10000],q1[10001],l[4][10000],r[4][10000];
main(){
int t,n,i,j,k,start,target;
for(i=0;i<10000;i++){
    l[0][i]=i-1;
    l[1][i]=i-10;
    l[2][i]=i-100;
    l[3][i]=i-1000;
    r[0][i]=i+1;
    r[1][i]=i+10;
    r[2][i]=i+100;
    r[3][i]=i+1000;
    if(i%10==9)r[0][i]=i-9;
    if(i%10==0)l[0][i]=i+9;
    if(i%100/10==9)r[1][i]=i-90;
    if(i%100/10==0)l[1][i]=i+90;
    if(i%1000/100==9)r[2][i]=i-900;
    if(i%1000/100==0)l[2][i]=i+900;
    if(i/1000==9)r[3][i]=i-9000;
    if(i/1000==0)l[3][i]=i+9000;
}
scanf("%d",&t);
while(t--){
    for(i=0;i<10000;i++)on[i]=-1;
    for(start=i=0;i<4;i++){
        scanf("%d",&j);
        start=start*10+j;
    }
    for(target=i=0;i<4;i++){
        scanf("%d",&j);
        target=target*10+j;
    }
    scanf("%d",&n);
    while(n--){
        for(i=k=0;i<4;i++){
            scanf("%d",&j);
            k=k*10+j;
        }
        on[k]=-2;
    }
    on[q1[0]=start]=0;
    for(i=0,j=1;on[target]<=0 && i<j;i++){
        for(k=0;k<4;k++){
            if(on[l[k][q1[i]]]==-1){
                q1[j++]=l[k][q1[i]];
                on[l[k][q1[i]]]=on[q1[i]]+1;
            }
            if(on[r[k][q1[i]]]==-1){
                q1[j++]=r[k][q1[i]];
                on[r[k][q1[i]]]=on[q1[i]]+1;
            }
        }
    }
    printf("%d\n",on[target]>?-1);
}
}
