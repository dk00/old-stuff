#include<stdio.h>
#include<malloc.h>
#include<math.h>
main(){
int sum,min,*s1=(int *)malloc(sizeof(int)*50001),i,m,
*tmp,k[100],*s2=(int *)malloc(sizeof(int)*50001),j,n;
scanf("%d",&n);
for(;n>0;n--){
    scanf("%d",&m);
    for(sum=(i=0);i<m;i++){
        scanf("%d",&k[i]);
        sum+=k[i];
        s1[i]=(s2[i]=0);
    }
    for(min=sum;i<=sum;i++)
        s1[i]=(s2[i]=0);
    for(i=0,s1[0]=1;i<m;i++){
        for(j=0;j+k[i]<=sum;j++){
            s2[j]=(s1[j] || s2[j]);
            s2[j+k[i]]=s1[j];
        }
        for(;j<=sum;j++)
            s2[j]=(s1[j] || s2[j]);
        tmp=s1;s1=s2;s2=tmp;
    }
    for(i=0;i<=sum;i++){
        if(s1[i] && abs(sum-i*2)<min)min=abs(sum-i*2);
    }
    printf("%d\n",min);
}
}
