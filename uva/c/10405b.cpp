#include<stdio.h>
main(){
long len[2][1000],l1,l2,i,j;
char c1[1002],c2[1002];
while(gets(c1)!=NULL){
    gets(c2);
    l1=strlen(c1);
    l2=strlen(c2);
    len[0][0]=(c1[0]==c2[0]);
    for(j=1;j<l2;j++)len[0][j]=(len[0][j-1] || c1[0]==c2[j]);
    for(i=1;i<l1;i++){
        len[i%2][0]=(len[(i+1)%2][0] || c1[i]==c2[0]);
        for(j=1;j<l2;j++){
            if(c1[i]==c2[j])
                len[i%2][j]=len[(i+1)%2][j-1]+1;
            else
                len[i%2][j]=len[(i+1)%2][j]>?len[i%2][j-1];
        }
    }
    printf("%ld\n",len[(l1-1)%2][l2-1]);
}
}
