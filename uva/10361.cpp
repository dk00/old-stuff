#include<stdio.h>
#include<string.h>
void main(){
char l1[101],l2[101],c1[101],c2[101],s2[101]="0",s3[101],s4[101]="1",s5[101];
char *p;
int i,n;
scanf("%d",&n);
gets(NULL);
for(i=0;i<n;i++){
	gets(l1);
	if(strchr(l1,'>')-strchr(l1,'<')<=1){
		s2[0]='\0';
		*strchr(l1,'>')='<';
	}
	if(strrchr(l1,'>')-strrchr(l1,'<')<=1){
		s4[0]='\0';
		*strrchr(l1,'<')='<';
	}
	p=strtok(l1,"<");
	strcpy(c1,p);
	if(s2[0]!='\0'){
		p=strtok(NULL,">");
		strcpy(s2,p);
	}
	p=strtok(NULL,"<");
	strcpy(s3,p);
	if(s4[0]!='\0'){
		p=strtok(NULL,">");
		strcpy(s4,p);
	}
	p=strtok(NULL,">");
	strcpy(s5,p);
	strcat(c1,s2);
	strcat(c1,s3);
	strcat(c1,s4);
	strcat(c1,s5);
	gets(l2);
	strcpy(c2,strtok(l2,"."));
	strcat(c2,s4);
	strcat(c2,s3);
	strcat(c2,s2);
	strcat(c2,s5);
	printf("%s\n%s\n",c1,c2);
}
}