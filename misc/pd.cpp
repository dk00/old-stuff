#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char list1[][20]={"RedWater","OrangeWater","BlueWater","WhiteWater"},
list2[][20]={"Arrow","Bolt","BrozenArrow","BrozenBolt","IronArrow",
"IronBolt"};
int nn,max,p[40],u[40];
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
int start(int n,int s[]);
bool take(int d,int i,int num);
main(){
int i,j,n,t,num,step,p[4],w[4][40],q[6],a[6][40];
char name[1000];
scanf("%d",&t);
while(t--){
    for(i=0;i<4;i++)p[i]=0;
    for(i=0;i<6;i++)q[i]=0;
    scanf("%d",&n);
    while(n--){
        scanf("%s %d",name,&num);
        if(num!=100)for(i=0;i<4;i++)
            if(!strcmp(name,list1[i]))
                w[i][p[i]++]=num;
        if(num!=1000)for(i=0;i<6;i++)
            if(!strcmp(name,list2[i]))
                a[i][q[i]++]=num;
    }
    for(i=step=0,max=100;i<4;i++)
        step+=start(p[i],w[i]);
    for(i=0,max=1000;i<6;i++)
        step+=start(q[i],a[i]);
    printf("%d\n",step);
}
}
bool take(int d,int i,int num){
    while(!u[i] && i<nn)i++;
    if(i>=nn || !num){
        for(i=0;i<nn && !u[i];i++);
        if(i>=nn)return true;
        if(num)return false;
        u[i]=0;
        if(take(d,i+1,p[i]))return true;
        u[i]=1;
        return false;
    }
    if(d<1)return false;
    if(num>max)num-=max;
    int j;
    for(j=i;p[j]+num<=max && j<nn;j++)
        if(u[j] && p[j]+num==max){
            u[j]=0;
            if(take(d-1,0,0))return true;
            u[j]=1;
            return false;
        }
    for(;i<nn;i++){
        if(!u[i])continue;
        u[i]=0;
        if(take(d-1,i+1,num+p[i]))
            return true;
        u[i]=1;
    }
    return false;
}
int start(int n,int s[]){
    if((nn=n)<=1)return 0;
    qsort(s,n,sizeof(s[0]),numcmp);
    int i;
    for(i=0;i<n;i++)u[i]=1,p[i]=s[i];
    for(i=n/2+(n&1);;i++)
        if(take(i,0,0))return i;
}
