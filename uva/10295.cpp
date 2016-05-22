#include<string.h>
#include<stdio.h>
int main(){
    char line[1000],key[1000][20];
    int i,n,m,j;
    long hp[1000],gethp;
    scanf("%d %d",&m,&n);
    gets(line);
    for(i=0;i<m;i++){
        gets(line);
	   strcpy(key[i],strtok(line," "));
	   sscanf(strtok(NULL," "),"%ld",&hp[i]);
    }
    for(i=0;i<n;){
        gethp=0;
        gets(line);
        for(j=0;j<m;j++){
            if(strcmp(line,key[i])==0)
                gethp+=hp[i]; 
        }
        if(strcmp(line,".")==0){
            printf("%ld",gethp);
            i++;
        }
    }
    return 0;
}
