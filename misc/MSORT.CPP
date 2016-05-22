#include<stdio.h>
main(){
int s[2][10000];
int i,j,r,f,n,p1,p2;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)scanf("%d",&s[0][i]);
    for(f=0,r=1;r<=n;r*=2,f=!f)
        for(i=r;i-r<n;i+=2*r)
            for(j=i-r,p1=i-r,p2=i;j<i+r && j<n;){
                if(p1>=i)s[!f][j++]=s[f][p2++];
                else if(p2>=i+r || p2>=n)s[!f][j++]=s[f][p1++];
                else if(s[f][p1]<s[f][p2])s[!f][j++]=s[f][p1++];
                else s[!f][j++]=s[f][p2++];
            }
    for(i=0,f=!f;i<n;i++)
        printf("%d ",s[f][i]);
    puts("");
}
}
