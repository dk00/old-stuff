#include<stdio.h>
int s[100];
int cut(int i,int j){
    if(i==j)return 0;
    int min=cut(i,i)+cut(i+1,j);
    for(int k=i+1;k<j;k++)      
        min<?=(cut(i,k)+cut(k+1,j));
    min+=s[j]-s[i-1];       
    return min;
}
main(){
int i,j,k,l,n;
s[0]=0;
while(scanf("%d",&l) && l){
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&s[i]);
    s[++n]=l;
    printf("The minimum cutting is %d.\n",cut(1,n));
}
}
