#include<stdio.h>
int yn,min,max,len,stick[51];
inline void calc(int n);
inline void cut(int n,int l,int i);
main(){
int i,k,n,sum;
while(scanf("%d",&n) && n){
    min=50;
    for(i=0;i<=50;i++)stick[i]=0;
    for(yn=max=sum=i=0;i<n;i++){
        scanf("%d",&k);
        min<?=k,max>?=k;
        sum+=k;
        stick[k]++;
    }
    for(len=max;len<=sum;len++){
        if(sum%len)continue;
        calc(sum/len);
        if(yn)break;
    }
    printf("%d\n",len);
}
}
inline void calc(int n){
    if(n==1){
        yn=1;
        return;
    }
    int i;
    for(i=max;!stick[i];i--);
    stick[i]--;
    if(len-i)cut(n,len-i,i<?(len-i));
    else calc(n-1);
    stick[i]++;
}
inline void cut(int n,int l,int i){
    //if(yn)return;
    if(l==i && stick[i]){
        stick[i]--;
        calc(n-1);
        stick[i]++;
        return;
    }
    for(;i>=min && !yn;i--)
        if(stick[i]){
            stick[i]--;
            cut(n,l-i,i<?(l-i));
            stick[i]++;
        }
}
