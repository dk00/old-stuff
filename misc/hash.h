const int hashsize=1023;
struct list{
    int s;
    list *next;
};
struct Hash{
    list *head[hashsize],*top[hashsize];
    int calc(int s){return s%hashsize;}
public:
    void clear(){
        for(int i=0;i<hashsize;i++){
            head[i]=new list;
            top[i]=head[i];
            top[i]->next=NULL;
        }
    }
    void insert(int s);
    bool find(int s);
}hash;
void Hash::insert(int s){
int i=calc(s);
    *top[i]=(list){s,new list};
    top[i]=top[i]->next;
    top[i]->next=NULL;
}
bool Hash::find(int s){
int i=calc(s);
list *ptr;
    for(ptr=head[i];ptr-top[i] && ptr;ptr=ptr->next)
        if(ptr->s==s)return true;
    return false;
}
