#include<stdio.h>
long minnode,minsum;
void tvl(long *in,long *post,long sum,long n){
    sum+=post[0];
    if(!in[1]){
        sum+=in[1];
        if(sum<minsum || sum==minsum && in[0]<minnode){
            minnode=in[0];
            minsum=sum;
        }
        return;
    }
    int i;
    for(i=0;in[i];i++){
            if(in[i]==post[0]){
                in[i]=0;
            if(n-i)tvl(&in[i+1],&post[1],sum,n-i-1);
            if(i)tvl(in,&post[n-i+1],sum,i-1);
        }
    }
}
main(){
long in_[10001],post_[10001],i,p,n;
char s[10000],c;
while(scanf("%c",&c)!=EOF){
    while(c==' ')scanf("%c",&c);
    for(p=0;c>='0' && c<='9';scanf("%c",&c))
        s[p++]=c;
    s[p]='\0';
    sscanf(s,"%ld",&in_[0]);
    for(i=1;;i++){
        while(c==' ')scanf("%c",&c);
        if(c=='\n')break;
        for(p=0;c>='0' && c<='9';scanf("%c",&c))
            s[p++]=c;
        s[p]='\0';
        sscanf(s,"%ld",&in_[i]);
    }
    in_[i]=0;post_[i]=0;
    for(n=--i;i>=0;i--)scanf("%ld%c",&post_[i],&c);
    while(c!='\n')scanf("%c",&c);
    minsum=100000000;
    tvl(in_,post_,0,n);
    printf("%ld\n",minnode);
}
}
