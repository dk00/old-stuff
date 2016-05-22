/* @JUDGE_ID:  58589NF  264  C++  "Count on Cantor"*/
#include<stdio.h>
main(){
long cantor,i,s[4500],start,end,mid;
s[0]=0;
for(i=1;i<4500;i++)s[i]=s[i-1]+i;
while(scanf("%ld",&cantor)!=EOF){
    printf("TERM %ld IS ",cantor);
    for(start=0,end=4499;start+1<end;){
        if(s[mid=(start+end)/2]>cantor) end=mid;
        else if(s[mid]<cantor) start=mid;
        else{
            start=mid-1;
            end=start+1;
        }
    }
    cantor-=s[start];
    if(end%2==1)        //奇數排
        printf("%ld/%ld\n",end-cantor+1,cantor);
    else                //偶數排
        printf("%ld/%ld\n",cantor,end-cantor+1);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
