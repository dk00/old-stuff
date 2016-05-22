#include<stdio.h>
main(){
int set[26],i,j,n,l1,l2,sum,t;
char line[1000];
scanf("%d%c",&t,&line[0]);
gets(line);
for(;t>0;t--){
    gets(line);
    for(i=0,n=line[0]-'A';i<=n;i++)set[i]=i;
    while(1){
        if((gets(line)==NULL))break;
        if(line[0]=='\0')break;
        for(i=0;line[i]!='\0' && line[i]==' ';i++);
        l1=line[i]-'A';
        for(i++;line[i]!='\0' && line[i]==' ';i++);
        l2=line[i]-'A';
        for(i=l1;set[i]!=i;i=set[i]);
        for(j=l2;set[j]!=j;j=set[j]);
        if(i==j)continue;
        if(i<j)set[j]=i;
        else set[i]=j;
    }
    for(i=0,sum=0;i<=n;i++){
        if(set[i]==i)sum++;
    }
    printf("%d\n",sum);
    if(t>1)printf("\n");
}
}
