#include<stdio.h>
#include<string.h>
main(){
int i,j,t;
char c,s1[101],s2[101],s3[101],s4[101],s5[101],l2[101];
scanf("%d%c",&t,&c);
while(t--){
    i=0;
    while((c=getchar())!='<')s1[i++]=c;
    s1[i]=0;i=0;
    while((c=getchar())!='>')s2[i++]=c;
    s2[i]=0;i=0;
    while((c=getchar())!='<')s3[i++]=c;
    s3[i]=0;i=0;
    while((c=getchar())!='>')s4[i++]=c;
    s4[i]=0;i=0;
    while((c=getchar())!='\n')s5[i++]=c;
    s5[i]=0;
    gets(l2);
    for(i=strlen(l2)-1;l2[i]=='.';i--)l2[i]=0;
    printf("%s%s%s%s%s\n%s%s%s%s%s\n",s1,s2,s3,s4,s5,l2,s4,s3,s2,s5);
}
}
