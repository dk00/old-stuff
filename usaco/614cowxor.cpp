/*
ID: s0000151
PROG: cowxor
LANG: C++
*/
#include<stdio.h>
int n,ms,me,max=-1,init,bit[21],s[100000],dp[100000],use[21][100000];
void atry(int d,int s1,int e1,int s2,int e2){
int i,j,k=0,l;
    if(!d){
        for(i=s1;i<=e1;i++)
            for(j=s2;j<=e2;j++){
                k=(i?dp[j]^dp[i-1]:dp[j]);
                if(k>max || (k==max && j<me)){
                    max=k;
                    ms=i,me=j;
                }
            }
        return;
    }
    if(init){
        for(i=s1;i<=s2;i++)
            if(s[i]&bit[d])use[d][k++]=i;
        for(l=k,i=s2;i<=e2;i++)
            if(s[i]&bit[d])use[d][l++]=i;
        if(!k || !l){
            atry(d-1,s1,e1,s2,e2);
            return;
        }
        for(i=0;i<k;i++)
            for(j=k+k%2;j<l;j++,j++)
                atry(d-1,i?use[d][i-1]+1:s1,use[d][i],use[d][j],
                j+1<l?use[d][j+1]-1:e2);
    }
    else{
        init=1;
        for(i=0;i<n;i++)
            if(s[i]&bit[d])use[d][k++]=i;
        for(i=0;i<k;i++)
            for(j=i;j<k;j++,j++)
                atry(0,i?use[d][i-1]+1:0,use[d][i],use[d][j],
                j+1<k?use[d][j+1]-1:n-1);
    }
}
main(){
int i,j;
for(i=bit[1]=1;i<20;i++)bit[i+1]=bit[i]<<1;
freopen("cowxor.in","r",stdin);
freopen("cowxor.out","w",stdout);
scanf("%d",&n);
for(i=0;i<n;i++){
    scanf("%d",&s[i]);
    max>?=s[i];
}
dp[0]=s[0];
for(i=1;i<n;i++)dp[i]=s[i]^dp[i-1];
for(i=20;i>0;i--)if(max&bit[i])break;
max=-1;

atry(i,0,n-1,0,n-1);
printf("%d %d %d\n",max,ms+1,me+1);
}
