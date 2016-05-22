#include<stdio.h>
#include<stdlib.h>
int ab[1000000],a[1000000],b[1000000],p,oi,oj;
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
int search_2nd(int z,int key){
    int r;
    for(r=z;r<p && ab[r]==key;r++)
        if(a[r]!=oi && b[r]!=oi && a[r]!=oj && b[r]!=oj)
            return 1;
    for(r=z;r>=0 && ab[r]==key;r--)
        if(a[r]!=oi && b[r]!=oi && a[r]!=oj && b[r]!=oj)
            return 1;
    return 0;
}
int bin_search(int stt,int end,int key){
    if(stt>end)return 0;
    int mid=(stt+end)/2;
    if(key==ab[mid])return search_2nd(mid,key);
    else if(key<ab[mid])return bin_search(stt,mid-1,key);
    return bin_search(mid+1,end,key);
}
main(){//4993200 268095 352805 4372300
int i,j,n,key,max,find,s[1000];
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)scanf("%d",&s[i]);
    qsort(s,n,sizeof(s[0]),numcmp);
    max=-2147483647;
    for(find=p=i=0;i<n-1;i++)
        for(j=i+1;j<n;j++){
            a[p]=i,b[p]=j;
            ab[p++]=s[i]+s[j];
        }
    qsort(ab,p,sizeof(ab[0]),numcmp);
    for(oi=0;oi<n;oi++)
        for(oj=0;oj<n;oj++){
            if(oi==oj)continue;
            key=s[oi]-s[oj];
            if(bin_search(0,p-1,key)){
                max>?=s[oi];
                find=1;
            }
        }
    if(find)printf("%d\n",max);
    else puts("no solution");
}
}
