#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
int take(int d,int n,int s[]);
int start(int s[],int n);
int max;
main(){
int i,j,k,t,n,p1,p2,p3,p4,q1,q2,q3,q4,q5,q6,num,w1[40],w2[40],
    w3[40],w4[40],a1[40],a2[40],a3[40],a4[40],a5[40],a6[40];
char name[1000];
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    p1=p2=p3=p4=q1=q2=q3=q4=q5=q6=0;
    while(n--){
        scanf("%s %d",name,&num);
        if(!strcmp(name,"RedWater") && num!=100)w1[p1++]=num;
        if(!strcmp(name,"OrangeWater") && num!=100)w2[p2++]=num;
        if(!strcmp(name,"BlueWater") && num!=100)w3[p3++]=num;
        if(!strcmp(name,"WhiteWater") && num!=100)w4[p4++]=num;
        if(!strcmp(name,"Arrow") && num!=1000)a1[q1++]=num;
        if(!strcmp(name,"Bolt") && num!=1000)a2[q2++]=num;
        if(!strcmp(name,"BrozenArrow") && num!=1000)a3[q3++]=num;
        if(!strcmp(name,"BrozenBolt") && num!=1000)a4[q4++]=num;
        if(!strcmp(name,"IronArrow") && num!=1000)a5[q5++]=num;
        if(!strcmp(name,"IronBolt") && num!=1000)a6[q6++]=num;
    }
    int step=0;
    max=100;
    step+=start(w1,p1);
    step+=start(w2,p2);
    step+=start(w3,p3);
    step+=start(w4,p4);
    max=1000;
    step+=start(a1,q1);
    step+=start(a2,q2);
    step+=start(a3,q3);
    step+=start(a4,q4);
    step+=start(a5,q5);
    step+=start(a6,q6);
    printf("%d\n",step);
}
}
/*
best:   a+b==max (0)(-2)
normal: a+b<max (1)(-1)
bad:    a+b>max (1)(-1)
*/
int take(int d,int i,int num,int n,int s1[]){
    while(!s1[i] && i<n)i++;
    if(i>=n){
        for(i=0;i<n && !s1[i];i++);
        if(i>=n)return 1;
        num=0;
    }
    if(d<1)return 0;
    if(!num){
        int k=s1[i];
        s1[i]=0;
        int j=take(d,i+1,k,n,s1);
        s1[i]=k;
        return j;
    }
    if(num>max)num-=max;
    int j,k;
    for(j=i;j<n && num+s1[j]<=max;j++)
        if(num+s1[j]==max){
            k=s1[j],s1[j]=0;
            if(take(d-1,0,0,n,s1))return 1;
            s1[j]=k;
            return 0;
        }
    for(;i<n;i++){
        if(!s1[i])continue;
        k=s1[i],s1[i]=0;
        if(take(d-1,i+1,num+k,n,s1))return 1;
        s1[i]=k;
    }
    return 0;
}
int start(int s[],int n){
    if(n<=1)return 0;
int i,k;
    qsort(s,n,sizeof(s[0]),numcmp);
    for(i=(n/2-1)>?1;;i++){
        k=take(i,0,0,n,s);
        if(k)return i;
    }
}
