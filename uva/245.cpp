/* @JUDGE_ID:  58589NF  245  C++  "Uncompress"*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct lnklst{
    char s[51];
    lnklst *next;
};
int main(){
char line[1000],word[51];
lnklst *head=(lnklst *)malloc(sizeof(lnklst)),*last,*ptr;
int i,j;
last=head;
last->next=NULL;
while(1){
    gets(line);
    if(line[0]='0')
        break;
    for(i=0,j=0;line[i]!='\0';i++){
        if(line[i]>='A' && line[i]<='Z')
            word[j++]=line[i];
        else if(line[i]>='a' && line[i]<='z')
            word[j++]=line[i];
        else if(line[i]>='1' && line[i]<='9'){
            for(j=line[i]-'0',ptr=head;j>0;j--,ptr=ptr->next);
            printf("%s",ptr->s);
        }
        else{
            word[j]='\0';
            last->next=(lnklst *)malloc(sizeof(lnklst));
            strcpy(last->s,word);
            last=last->next;
            last->next=NULL;
        }
    }
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
