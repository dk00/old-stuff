#include<stdio.h>
int s[100000];
main(){
freopen("cowxor.in","r",stdin);
freopen("cowxor.out","w",stdout);
int i,n,min1,max1,min2,max2,best=-1;
scanf("%d %d",&n,s);
for(i=1;i<n;i++)scanf("%d",&s[i]);
best=min1=max1=*s;
for(i=1;i<n;i++){
    min2=(s[i]<?(min1^s[i])<?(max1^s[i]));
    max2=(s[i]>?(min1^s[i])>?(max1^s[i]));
    best>?=max2;
    min1=min2;
    max1=max2;
}
printf("%d\n",best);
}
