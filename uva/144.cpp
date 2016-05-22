#include<stdio.h>
const int qsize=30;
int q[50],get[50];
main(){
int i,j,k,n,g,rem;
while(scanf("%d %d",&n,&k) && n+k){
    k=k;
    for(i=0;i<n;i++){
        q[i]=i+1;
        get[i+1]=40;
    }
    for(g=rem=i=0,j=n;i<j;i++){
        if(!rem)
            rem=(++g)%k;
        if(!rem)rem=k;
        if(get[q[i%qsize]]>rem){
            printf("%5d%8d%8d\n",q[i%qsize],40+rem-get[q[i%qsize]],rem);
            get[q[i%qsize]]-=rem;
            rem=0;
            q[j++%qsize]=q[i%qsize];
        }
        else if(get[q[i%qsize]]==rem){
            printf("%5d%8d%8d\n",q[i%qsize],40+rem-get[q[i%qsize]],rem);
            get[q[i%qsize]]=0;
            rem=0;
            //printf("%3d",q[i%qsize]);
        }
        else if(get[q[i%qsize]]<rem){
            printf("%5d%8d%8d\n",q[i%qsize],40,rem);
            rem-=get[q[i%qsize]];
            get[q[i%qsize]]=0;
            //printf("%3d",q[i%qsize]);
        }
    }
    puts("");
}
}
