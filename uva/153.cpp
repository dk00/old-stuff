#include<stdio.h>
main(){
int ch[26],i,l,j,len,l2;
double n,k;
char line[1000];
while(1){
    gets(line);n=1;
    if(line[0]=='#')break;
    for(i=0;i<26;i++) ch[i]=0;
    for(i=0;line[i]!=0;i++){
        ch[line[i]-'a']++;
    }len=i;
    for(i=0;i<len;i++){
        for(j=0;j<line[i]-'a';j++){
            for(;ch[j]==0 && j<line[i]-'a';j++);
            if(j>=line[i]-'a')break;
            ch[j]--;
            for(l=2,k=1;l<len-i;l++)k*=l;
            for(l=0;l<26;l++){
                for(l2=ch[l];l2>1;l2--)k/=l2;
            }
            n+=k;ch[j]++;
        }
        ch[line[i]-'a']--;
    }
    printf("%10.0lf\n",n);
}
