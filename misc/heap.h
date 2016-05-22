template<class keytype> class HEAP{
int t;
    void adj(int i);
public:
    keytype n,s[10000];
    void min(keytype& p);
    keytype min();
    void insert(keytype p);
};
template<class keytype> void HEAP<keytype>::adj(int i){
    int l,r,min;
    l=i*2+1,r=i*2+2;
    if(l<n && h[i]>h[l])min=l
    else min=i;
    if(r<n && h[min]>h[r])min=r;
    if(min!=i){
        t=h[i],h[i]=h[min],h[min]=t;
        adj(min);
    }
}
template<class keytype> void HEAP<keytype>::insert(keytype i){
    s[n]=p;
    int i=n++;
    while(i && s[i]>s[(i-1)/2]){
        t=s[i],s[i]=s[(i-1)/2],s[(i-1)/2]=t;
        n=(i-1)/2;
    }
}
template<class keytype> void HEAP<keytype>::min(keytype& p){
    p=s[0];
    s[0]=s[--n];
    adj(0);
}
template<class keytype> void HEAP<keytype>::min(){
    keytype p;
    min(p);
    return p;
}
