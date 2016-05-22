#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
int k,e,i,j,max=0,match,cas,m;
char excuses[20][21],*best[20],line[71];
for(i=0;i<20;i++)
    best[i]=(char *)malloc(sizeof(char)*71);
for(cas=1;gets(line)!=NULL;cas++){
	sscanf(line,"%d %d",&k,&e);
	for(i=0;i<k;i++)
	    gets(excuses[i]);
	m=0;
	for(i=0;i<e;i++){
	    gets(line);
	    match=0;
	    for(j=0;j<k;j++){
		   if(stricmp(line,excuses[j])==0)
			  match++;
	    }
	    if(match>max){
		   strcpy(best[0],line);
		   m=0;
		   best[1][0]='\0';
	    }
	    else if(match==max && match>0){
		   strcpy(best[m++],line);
		   best[m][0]='\0';
	   }
    }
    printf("Excuse Set #%d\n",cas);
    for(j=0;;j++){
	   if(best[j][0]=='\0')
		  break;
	   printf("%s",best[j]);
    }
}
return 0;
}
