#include<stdio.h>
main(){
int cake[101],i,sum,done,n,max,side[101];
char c;
for(i=-1;scanf("%d%c",&cake[++i],&c)!=EOF;i=-1){
    printf("%d%c",cake[i],c);
    if(c=='\n'){
        printf("0\n");
        continue;
    }
    while(1){
        scanf("%d%c",&cake[++i],&c);
        printf("%d%c",cake[i],c);
        if(c=='\n')break;
    }n=i;sum=n;
    done=0;
    while(!done){
        for(i=1,done=1;i<=sum && done;i++)
            done=(cake[i-1]<=cake[i]);
        if(done)break;
        for(i=n,max=n;i>=0;i--){
            if(cake[i]>cake[max])
                max=i;
        }
        if(max>0){
            printf("%d ",sum-max+1);
            for(i=-1;max>=0;)
                side[++i]=cake[max--];
            while(i>=0)
                cake[i]=side[i--];
        }
        printf("%d ",sum-(max=n--)+1);
        for(i=-1;max>=0;)
            side[++i]=cake[max--];
        while(i>=0)
            cake[i]=side[i--];
    }
    printf("0\n");
}
}
