/* @JUDGE_ID:  58589NF  111  c  ""*/
#include<stdio.h>
int main(){
int c[20],r[20],n,i,j,len[20],max,l[20];
scanf("%d",&n);
for(i=0;i<n;i++){
    scanf("%d",&c[i]);
}
for(i=0;i<n;i++)
    r[c[i]-1]=i;
for(i=0;i<n;i++)
    c[r[i]]=i;
while(scanf("%d",&l[0])!=EOF){
    len[0]=1;
    max=0;
    for(i=1;i<n;i++){
        scanf("%d",&l[i]);
        len[i]=1;
    }
    for(i=0;i<n;i++)
        r[l[i]-1]=c[i];
    for(i=1;i<n;i++){
        for(j=0;j<i;j++){
            if(r[i]>r[j] && len[i]<len[j]+1)
                len[i]=len[j]+1;
        }
        if(max<len[i])
            max=len[i];
    }
    printf("%d\n",max);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
