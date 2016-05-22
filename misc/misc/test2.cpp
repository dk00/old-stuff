#include<set>
#include<map>
#include<cstdio>
#include<string>
using namespace std;
char u[256],x[]="0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_$";
string res[]={"int","float","double","char","if","else","while","for","break","return"};
int reads(){
    int c=0,z=0,sum=0;
    while(z || !u[c=getchar()]){
        if(c=='\'')z=c;
        else if(c==z)z=0;
        if(c=='\n')sum++;
        if(c==EOF)return -1;
        
    }
    ungetc(c,stdin);
    return sum;
}
string readn(){
    int c;
    string tmp="";
    while(u[c=getchar()])tmp+=c;
    if(c!=EOF)ungetc(c,stdin);
    if('0'<=tmp[0] && tmp[0]<='9')return "int";
    return tmp;
}
main(){
    int i,l=1;
    for(i=0;x[i];i++)u[x[i]]=1;
    map<string,set<int> > $;
    while((i=reads())>=0){
        l+=i;
        $[readn()].insert(l);
    }
    for(i=0;i<10;i++)
        $[res[i]].clear();
    for(map<string,set<int> >::iterator p=$.begin();p!=$.end();p++){
        if(!p->second.size())
            continue;
        printf("%s:",p->first.c_str());
        for(set<int>::iterator q=p->second.begin();q!=p->second.end();q++)
            printf(" %d",*q);
        puts("");
    }
}
