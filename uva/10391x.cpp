#include<stdio.h>
#include<string.h>
const int hashsize=262139;
struct list{
    char *s;
    list *next;
};
struct Hash{
    list *head[hashsize],*top[hashsize];
    int calc(char *s){
        int i=0;
        if(*s)i=(i<<1)|*(s++);
        if(*s)i=(i<<1)|*(s++);
        if(*s)i=(i<<1)|*(s++);
        if(*s)i=(i<<1)|*(s++);
        if(*s)i=i^*(s++);
        if(*s)i=i^(*(s++)<<8);
        if(*s)i=i^(*(s++)<<16);
        if(*s)i=i^(*(s++)<<24);
        return i%hashsize;
    }
public:
    void clear(){
        for(int i=0;i<hashsize;i++){
            head[i]=new list;
            top[i]=head[i];
            top[i]->next=NULL;
        }
    }
    void insert(char *s);
    bool find(char *s);
}hash;
void Hash::insert(char *s){
int i=calc(s);
    *top[i]=(list){new char[100],new list};
    strcpy(top[i]->s,s);
    top[i]=top[i]->next;
    top[i]->next=NULL;
}
bool Hash::find(char *s){
int i=calc(s);
list *ptr;
    for(ptr=head[i];ptr-top[i] && ptr;ptr=ptr->next)
        if(!strcmp(ptr->s,s))return true;
    return false;
}
char word[120000][100];
main(){
int i,j,n;
char c;
hash.clear();
for(n=0;gets(word[n]);n++)hash.insert(word[n]);
for(i=0;i<n;i++)
    for(j=1;word[i][j];j++){
        c=word[i][j];
        word[i][j]=0;
        if(!hash.find(word[i])){
            word[i][j]=c;
            continue;
        }
        word[i][j]=c;
        if(hash.find(word[i]+j)){
            puts(word[i]);
            break;
        }
    }
}
