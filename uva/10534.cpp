#include<stdio.h>
#define MAX(a,b) a>b?a:b
#define MIN(a,b) a<b?a:b
main(){
int s[10001],len1[10001],len2[10001],min1[10002],min2[10002];
int start,end,mid,i,j,n,max1,max2,best;
while(scanf("%d",&n)!=EOF){
    for(i=0;i<n;i++){
        scanf("%d",&s[i]);
        len1[i]=1;len2[i]=1;
    }
    min1[0]=0;min2[0]=0;
    min1[1]=s[0];min2[1]=s[n-1];
    max1=1;max2=1;best=0;
    for(i=1;i<n;i++){
        if(s[i]>min1[max1])
            min1[++max1]=s[i];
        for(start=1,end=max1;end-start>4;){
            mid=(start+end)/2;
            if(min1[max1]==s[i])break;
            if(min1[mid-1]<s[i] && s[i]<=min1[mid])break;
            if(min1[mid-1]>s[i])end=mid-2;
            else start=mid+1;
        }
        for(mid=start;mid<=end;mid++){
		  if(min1[mid-1]<s[i] &&s[i]<=min1[mid])break;
	   }
	   if(s[i]<min1[mid] && s[i]>min1[mid-1] && mid<=end)min1[mid]=s[i];
        if(s[n-i-1]>min2[max2])
            min2[++max2]=s[n-i-1];
        for(start=1,end=max2;end-start>4;){
            mid=(start+end)/2;
            if(min2[max2]==s[n-i-1])break;
            if(min2[mid-1]<s[i] && s[i]<=min2[mid])break;
            if(len2[mid-1]>s[i])end=mid-2;
            else start=mid+1;
        }
        for(mid=start;mid<=end;mid++){
		  if(min2[mid-1]<s[n-i-1] && s[n-i-1]<=min2[mid])break;
        }
	   if(s[n-i-1]<min2[mid] && s[n-i-1]>min2[mid-1] && mid<=end)min2[mid]=s[n-i-1];
        len1[i]=max1;len2[n-i-1]=max2;
    }
    for(i=0;i<n;i++)
	   best=MAX(MIN(len1[i],len2[i]),best);
    printf("%d\n",best*2-1);
}
}
