#include<stdio.h>
main(){
long tow=1,n1,n2,r1[100],r2[100],w[2][100],i,j,k,max;
long *s1=w[0],*s2=w[1],*tmp;
while(scanf("%ld %ld",&n1,&n2) && n1 || n2){
    for(i=0;i<n1;i++)scanf("%ld",&r1[i]);
    for(i=0;i<n2;i++)scanf("%ld",&r2[i]);
    s1[0]=(r1[0]==r2[0]);
    for(i=1;i<n2;i++)s1[i]=(r1[0]==r2[i] || s1[i-1]);
    for(i=1;i<n1;i++){
        s2[0]=(r1[i]==r2[0] || s1[0]);
        for(j=1;j<n2;j++){
            if(r1[i]==r2[j])
                s2[j]=1+s1[j-1];
            else
                s2[j]=s1[j]>?s2[j-1];
        }
        tmp=s1;s1=s2;s2=tmp;
    }
    printf("Twin Towers #%ld\n",tow++);
    printf("Number of Tiles : %ld\n\n",s1[n2-1]);
}
}
