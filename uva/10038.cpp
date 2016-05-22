#include<stdio.h>
#include<stdlib.h>
main(){
long n,i,last,jolly,now,j[3000];
while(scanf("%ld",&n)!=EOF){
    jolly=1;
    for(i=0;i<n;i++)j[i]=0;
    scanf("%ld",&last);
    for(i=1;i<n;i++){
        scanf("%ld",&now);
        if(abs(last-now)>=n || abs(last-now)==0)jolly=0;
        if(j[abs(last-now)])jolly=0;
        j[abs(last-now)]=1;
        last=now;
    }
    if(jolly)printf("Jolly\n");
    else printf("Not jolly\n");
}
}
