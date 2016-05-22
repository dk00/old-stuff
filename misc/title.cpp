#include<iostream>
#include<string>
using namespace std;
string title[1000];
main(){
int i,n;
for(n=0;cin>>title[n] && title[n]!="!";n++)
    for(i=0;i<n;i++)
        if(title[i]==title[n]){
            n--;
            break;
        }
for(i=0;i<n;i++)cout<<title[i]<<'\n';
system("pause");
}
