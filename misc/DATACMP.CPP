#include<stdio.h>
#include<string.h>
main(){
char line[100];
long i,data[2020],n;
printf("Enter file name & path:");
gets(line);
freopen("311out.txt","r",stdin);
printf("loading");
for(i=0;scanf("%ld",&data[i])!=EOF;i++){
	if(i%10==0)printf(".");
}
printf("\nDone.\n");
fclose(stdin);
gets(line);
freopen("311.out","r",stdin);
for(i=0;scanf("%ld",&n)!=EOF;i++){
	if(n!=data[i])printf("#%ld ",i);
}
fclose(stdin);
scanf("    %d");
}
