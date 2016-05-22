#include<stdio.h>
main(){
	char line[1000],fname[1000];
	long sum=0,p;
	FILE *list=fopen("filelist.txt","r"),*log=fopen("codelog.txt","w");
	while(fscanf(list,"%s",fname)!=EOF && freopen(fname,"r",stdin)){
		p=0;
		while(gets(line)!=NULL)p++;
		fprintf(log,"%s %ld\n",fname,p);
		sum+=p;
		fclose(stdin);
	}
    printf("%ld\n",sum);
    scanf(" ");
}
