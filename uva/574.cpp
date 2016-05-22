#include<stdio.h>
int t,n,s[12],num[12],nsum,m,path[12],j;
void sum(int d,int k,int i){
    if(d>=n)return;
    for(;i<m;i++){
        if(k+s[i]==t  && num[i]>0){
            path[d]=i;
		  printf("%d",s[path[0]]);
            for(j=1;j<=d;j++)
                printf("+%d",s[path[j]]);
            printf("\n");
            nsum|=1;
            continue;
        }
        else if(k+s[i]<t && num[i]>0){
            num[i]--;path[d]=i;
		  sum(d+1,k+s[i],i);
		  num[i]++;
        }
    }
}
main(){
int i;
while(1){
    scanf("%d %d",&t,&n);
    if(!t && !n) break;
    for(i=0;i<n;i++) num[i]=0;
    nsum=0;
    for(i=0,m=0;i<n;i++){
        scanf("%d",&s[m++]);
	   if(i>0 && s[m-2]==s[m-1])m--;
        num[m-1]++;
    }
    printf("Sums of %d:\n",t);
    sum(0,0,0);
    if(nsum==0) printf("NONE\n");
}
}
