#include<stdio.h>
int la[1001][1001],lb[1001][1001],done[1001][1001],ca,cb,n,path[100000];
class jug{
public:
    int a;
    int b;
    void operator=(jug k);
    int filla();
    int fillb();
    int emptya();
    int emptyb();
    int atob();
    int btoa();
};
void jug::operator=(jug k){
    a=k.a;
    b=k.b;
}
int jug::filla(){
    if(done[ca][b])return 0;
    la[ca][b]=a;
    lb[ca][b]=b;
    a=ca;
    return done[a][b]=1;
}
int jug::fillb(){
    if(done[a][cb])return 0;
    la[a][cb]=a;
    lb[a][cb]=b;
    b=cb;
    return done[a][b]=2;
}
int jug::emptya(){
    if(done[0][b])return 0;
    la[0][b]=a;
    lb[0][b]=b;
    a=0;
    return done[a][b]=3;
}
int jug::emptyb(){
    if(done[a][0])return 0;
    la[a][0]=a;
    lb[a][0]=b;
    b=0;
    return done[a][b]=4;
}
int jug::atob(){
    if(done[0>?a-cb+b][cb<?a+b])return 0;
    la[0>?a-cb+b][cb<?a+b]=a;
    lb[0>?a-cb+b][cb<?a+b]=b;
    b=a+b;a=0;
    if(b>cb){a=b-cb;b=cb;}
    return done[a][b]=5;
}
int jug::btoa(){
    if(done[ca<?a+b][0>?b-ca+a])return 0;
    la[ca<?a+b][0>?b-ca+a]=a;
    lb[ca<?a+b][0>?b-ca+a]=b;
    a=a+b;b=0;
    if(a>ca){b=a-ca;a=ca;}
    return done[a][b]=6;
}
jug q[2][10000],*s1=q[0],*s2=q[1],*tmp;
main(){
int j1,j2;
char key[7][9]={
"","fill A","fill B","empty A","empty B","pour A B","pour B A"
};
while(scanf("%d %d %d",&ca,&cb,&n)!=EOF){
    s1[0].a=s1[0].b=0;
    for(j1=0;j1<=ca;j1++){
        for(j2=0;j2<=cb;j2++)done[j1][j2]=0;
    }
    done[0][0]=7;
    j1=1;j2=0;
    while(1){
        while(j1--){
            if(s1[j1].a==n || s1[j1].b==n){
                ca=s1[j1].a;
                cb=s1[j1].b;
                break;
            }
            s2[j2]=s1[j1];
            if(s2[j2].a<ca && s2[j2].filla())j2++;
            s2[j2]=s1[j1];
            if(s2[j2].b<cb && s2[j2].fillb())j2++;
            s2[j2]=s1[j1];
            if(s2[j2].a>0 && s2[j2].emptya())j2++;
            s2[j2]=s1[j1];
            if(s2[j2].b>0 && s2[j2].emptyb())j2++;
            s2[j2]=s1[j1];
            if(s2[j2].a>0 && s2[j2].b<cb && s2[j2].atob())j2++;
            s2[j2]=s1[j1];
            if(s2[j2].b>0 && s2[j2].a<ca && s2[j2].btoa())j2++;
        }
        puts("");
        if(j1>-1)break;
        j1=j2,j2=0;
        tmp=s1;s1=s2;s2=tmp;
    }
    if(ca==n){
        if(cb>0){
            la[ca][0]=ca;
            lb[ca][0]=cb;
            done[ca][0]=4;
            cb=0;
        }
        la[0][ca]=ca;
        lb[0][ca]=cb;
        done[0][ca]=5;
        cb=ca;
        ca=0;
    }
    for(n=0;ca || cb;n++){
        path[n]=done[ca][cb];
        j1=la[ca][cb];j2=lb[ca][cb];
        ca=j1;cb=j2;
    }
    while(n--)puts(key[path[n]]);
    puts("success");
}
}
