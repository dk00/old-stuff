#include<stdio.h>
#include<stdlib.h>
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
main(){
int i,j,n,s1,s2,tt,step1,step2,t[9999],
go1a[9999],go1b[9999],go2a[9999],go2b[9999];
scanf("%d",&tt);
while(tt--){
    scanf("%d",&n);
    for(i=0;i<n;i++)scanf("%d",&t[i]);
    if(n==1){
        printf("%d\n%d%s",t[0],t[0],tt?"\n\n":"\n");
        continue;
    }
    qsort(t,n,sizeof(t[0]),numcmp);
	for(step1=s1=0,i=n;i-->1;s1++){
		go1a[s1]=t[0];
		go1b[s1]=t[i];
		step1+=t[i]+t[0]*(i>1);
	}
	for(step2=s2=0,i=n-1;i>2;i--,i--){
        go2a[s2]=t[0];
        go2b[s2++]=t[1];
		step2+=t[1]+t[0];
		go2b[s2]=t[i];
		go2a[s2++]=t[i-1];
		step2+=t[i]+t[1];
    }
	for(i++;i-->1;s2++){
		go2a[s2]=t[0];
		go2b[s2]=t[i];
		step2+=t[i]+t[0]*(i>1);
    }
    if(step1<=step2){
        printf("%d\n%d %d\n",step1,go1a[i],go1b[i]);
        for(i=1;i<s1;i++)
            printf("%d\n%d %d\n",t[0],go1a[i],go1b[i]);
    }
    else{
        printf("%d\n%d %d\n",step2,go2a[i],go2b[i]);
        for(i=1;i<s2;i++)
            printf("%d\n%d %d\n",t[(i+1)%2],go2a[i],go2b[i]);
    }
    if(tt)puts("");
}
}
