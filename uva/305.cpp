/* @JUDGE_ID:  58589NF  305  C++  "Joseph"*/
#include<stdio.h>
main(){
long m,k,p,i,b,s[15]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
,-1,-1,-1,-1};
while(1){
    scanf("%ld",&k);
    if(k==0) break;
    for(m=k+1;s[k]==-1;m+=m%(2*k)==0?k:1){
	   i=m%(k+k);
	   if(i==0) i=2*k;
	   for(b=k,p=0;b>0;){
		  if(i<=k) break;
		  p=b+k-i;
		  b--;
            i=m%(b+k);
            if(i==0) i=b+k;
            i-=p;
            if(i<=0) i+=b+k;
        }
        if(b<=0) s[k]=m;
    }
    printf("%ld\n",s[k]);
}
}
/*@END_OF_SOURCE_CODE*/
