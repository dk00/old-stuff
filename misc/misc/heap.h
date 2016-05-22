#ifndef keytype
#define keytype int
#endif
class HEAP{
    keytype t,s[10000];
    void adj(int i);
public:
    int n;
    void min(keytype& p);
    void insert(keytype p);
};
void HEAP::adj(int i){
int l=i*2+1,r=i*2+2,min;
    if(l<n && s[l]<s[i])min=l;
    else min=i;
    if(r<n && s[r]<s[min])min=r;
    if(min!=i){
        t=s[i],s[i]=s[min],s[min]=t;
        adj(min);
    }
}
void HEAP::insert(keytype p){
    s[n]=p;
    int i=n++;
    while(i>0 && s[i]<s[(i-1)/2]){
        t=s[i],s[i]=s[(i-1)/2],s[(i-1)/2]=t;
        n=(i-1)/2;
    }
}
void HEAP::min(keytype& p){
    p=s[0];
    s[0]=s[--n];
    adj(0);
}

