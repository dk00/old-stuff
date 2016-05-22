#include<stdio.h>
long inp[1000000];
char p[1000000];
main(){
long i,j,n,Case;
char c,c1,c2;
for(Case=1;scanf("%c",&c1)!=EOF;Case++){
    for(c2=j=i=0;c2!='\n';i++,j++){    
        scanf("%c",&c2);
        p[i]=c1;
        for(;c2==c1 && c2!='\n';j++){
            inp[j]=i;
            p[i]=c1;
            scanf("%c",&c2); 
        }
        inp[j]=i;
        c1=c2;
    }
    scanf("%ld",&n);
    printf("Case %ld:\n",Case);
    while(n--){
        scanf("%ld %ld",&i,&j);
        if(inp[i]==inp[j] || i==j)printf("Yes\n");
        else printf("No\n");
    }
    scanf("%c",&c);
    while(c!='\n')scanf("%c",&c);
}
}
