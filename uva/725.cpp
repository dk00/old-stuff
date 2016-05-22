#include<stdio.h>
int p,q,use[10],num[30240];
void perm(int d,int s){
    if(d>=5){
        num[p++]=s;
        return;
    }
    for(int i=0;i<10;i++)
        if(use[i]){
            use[i]=0;
            perm(d+1,s*10+i);
            use[i]=1;
        }
}
int test(int a,int b){
    for(q=5;q--;){
        if(!use[a%10]){
            for(b=0;b<10;b++)use[b]=1;
            return 0;
        }
        use[a%10]=0;
        a/=10;
    }
    for(q=5;q--;){
        if(!use[b%10]){
            for(b=0;b<10;b++)use[b]=1;
            return 0;
        }
        use[b%10]=0;
        b/=10;
    }
    for(b=0;b<10;b++)use[b]=1;
    return 1;
}
main(){
int i,a=0,n,find;
for(i=0;i<10;i++)use[i]=1;
perm(0,0);
while(scanf("%d",&n) && n){
    if(a)puts("");
    else a=1;
    for(i=find=0;num[i]*n<100000 && i<p;i++)
        if(test(num[i],num[i]*n)){
            find=1;
            printf("%05d / %05d = %d\n",num[i]*n,num[i],n);
        }
    if(!find)printf("There are no solutions for %d.\n",n);
}
}
