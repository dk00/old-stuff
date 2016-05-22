#include<stdio.h>
#include<string.h>
char word[201][11],c[200][200];
int n,p,q,len[201],s[201];
int comp(char a[],char b[]){
    for(p=q=0;a[p] && q<2;p++)
        q+=(a[p]!=b[p]);
    return(q==1);
}
main(){
int i,j,k,t,q[1000];
char s1[11],s2[11],line[10000];
scanf("%d",&t);
gets(line);
while(t--){
    for(n=0;gets(word[n]) && *word[n]!='*';n++)
        len[n]=strlen(word[n]),s[n]=-1;
    for(i=0;i<n;i++)
        for(c[i][i]=0,j=i+1;j<n;j++)
            if(len[i]==len[j])
                c[i][j]=c[j][i]=comp(word[i],word[j]);
    while(gets(line) && sscanf(line,"%s %s",s1,s2)==2){
        printf("%s %s ",s1,s2);
        for(i=0;strcmp(s1,word[i]);i++);
        for(j=0;strcmp(s2,word[j]);j++);
        s[i]=0,q[0]=i,p=j;
        for(i=0,j=1;i<j;i++){
            if(s[p]>=0)break;
            for(k=0;k<n;k++)
                if(c[q[i]][k] && s[k]==-1)
                    s[k]=s[q[i]]+1,q[j++]=k;
        }
        printf("%d\n",s[p]);
    }
}
}
