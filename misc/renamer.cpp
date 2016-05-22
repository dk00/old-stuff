#include<stdio.h>
#include<string.h>
main(){
char s1[1000],s2[1000],keyword[100];
int n,t=1;
FILE *f;
scanf("%s",keyword);
for(n=0;;n++){
    sprintf(s1,"%s%d.in",keyword,n);
    f=fopen(s1,"r");
    if(f==NULL)return 0;
    fclose(f);
    sprintf(s1,"%s.%d",keyword,t++);
    rename(s1,s2);
    sprintf(s1,"%s%docen.in",keyword,n);
    f=fopen(s1,"r");
    if(f==NULL)continue;
    fclose(f);
    sprintf(s1,"%s.%d",keyword,t++);
    rename(s1,s2);
    sprintf(s1,"%s%da.in",keyword,n);
    f=fopen(s1,"r");
    if(f==NULL)continue;
    fclose(f);
    sprintf(s1,"%s.%d",keyword,t++);
    rename(s1,s2);
    sprintf(s1,"%s%db.in",keyword,n);
    f=fopen(s1,"r");
    if(f==NULL)continue;
    fclose(f);
    sprintf(s1,"%s.%d",keyword,t++);
    rename(s1,s2);
}
}

