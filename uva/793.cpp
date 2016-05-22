#include<stdio.h>
main(){
long set[1001],i,j,n,t,a,b,con=0;//,deep[1001];
char c,line[1000];
scanf("%ld%c",&t,&c);
gets(line);
while(t--){
    scanf("%ld%c",&n,&c);
    while(n--)set[n+1]=n+1;//deep[n+1]=0;    n+1;
    for(a=b=0;gets(line);){
        if(sscanf(line,"%c %ld %ld",&c,&i,&j)<3)break;
        if(c=='c'){
            while(set[i=set[i]]!=i);
            while(set[j=set[j]]!=j);
            set[i>?j]=i<?j;
        }
        else{
            while(set[i=set[i]]!=i);
            while(set[j=set[j]]!=j);
            if(i==j)a++;
            else b++;
        }
    }
    printf("%ld,%ld\n",a,b);
    if(t)puts("");
}
}
