#include<stdio.h>
#include<stdlib.h>
inline int abs(int n){return n<0?-n:n;}
inline int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
int s[1000];
main(){
int i,j,k,n,m,p,q,r,sum,C=1;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)
        scanf("%d",&s[i]);
    scanf("%d",&m);
    printf("Case %d:\n",C++);
    qsort(s,n,sizeof(s[0]),numcmp);
    while(m--){
        scanf("%d",&j);
        sum=s[0]+s[1];
        for(i=0;i<n;i++){
            k=j-s[i];
            if(i)s[i]=s[i-1];
            else s[i]=s[i+1];
            for(p=i,q=n-2;p<=q;){
                r=(p+q)/2;
                if(s[r]<=k && k<=s[r+1])break;
                else if(k>s[r+1])p=r+1;
                else q=r-1;
            }
            p=j-k+s[r+(k-s[r]>s[r+1]-k)];
            if(abs(j-sum)>abs(j-p))sum=p;
            s[i]=j-k;
        }
        printf("Closest sum to %d is %d.\n",j,sum);
    }
}
}
