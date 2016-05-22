/* @JUDGE_ID:  58589NF  101  c  "The Blocks Problem"*/
#include<stdio.h>
#include<string.h>
int main(){
int i,s[25][25],n,h[25],p[25],a,b,tp,temp[25];
char cmd1[6],cmd2[6];
while(scanf("%d",&n)!=EOF){
    for(i=0;i<n;i++){
        s[i][0]=i;
        h[i]=1;
        p[i]=i;
    }
    while(1){
        scanf("%s",cmd1);
        if(strcmp(cmd1,"quit")==0)
            break;
        else if(strcmp(cmd1,"move")*strcmp(cmd1,"pile")!=0)
        continue;
        scanf("%d %s %d",&a,cmd2,&b);
        if(a==b || p[a]==p[b] ||
        strcmp(cmd2,"over")*strcmp(cmd2,"onto")!=0)
            continue;
 	    if(strcmp(cmd2,"onto")==0){     //b上方的積木放回原位
            while(s[p[b]][h[p[b]]-1]!=b){
                tp=s[p[b]][--h[p[b]]];
                s[tp][h[tp]++]=tp;
                p[tp]=tp;
            }
        }
        if(strcmp(cmd1,"move")==0){     //a上的積木放回原來的位罝
            while(s[p[a]][h[p[a]]-1]!=a){
                tp=s[p[a]][--h[p[a]]];
                s[tp][h[tp]++]=tp;
                p[tp]=tp;
            }
            s[p[b]][h[p[b]]++]=s[p[a]][--h[p[a]]];
            p[a]=p[b];
        }
        else{     // 將a本身和其上的積木一起搬到到b所在的那堆積木之上
            i=0;
            while(s[p[a]][h[p[a]]]!=a)
                temp[i++]=s[p[a]][--h[p[a]]];
            for(i--;i>=0;i--){
                s[p[b]][h[p[b]]++]=temp[i];
                p[temp[i]]=p[b];
            }
        }
    }
    for(i=0;i<n;i++){
        printf("%d:",i);
        for(tp=0;tp<h[i];tp++)
            printf(" %d",s[i][tp]);
        printf("\n");
    }
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
/*
		  while(s[p[b]][h[p[b]]-1]!=b){
			 s[s[p[b]][h[p[b]]]][h[p[s[p[b]][h[p[b]]]]]]=s[p[b]][h[p[b]]];
			 h[s[p[b]][h[p[b]]]-1]+=1;
			 h[p[b]]-=1;
			 
            while(s[p[a]][h[p[a]]-1]!=a)
                s[p[a]][h[p[a]]++]=s[p[a]][--h[p[a]]];
            s[p[b]][h[p[b]]++]=s[p[a]][--h[p[a]]];
            
            tp=1;
            temp[tp++]=s[p[a]][--h[p[a]]];
            s[p[b]][h[p[b]]++]=temp[--tp];
*/
