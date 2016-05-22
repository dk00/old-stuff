#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
main()
{
    string a;
    while(cin>>a && a!="#")
    {
        if(next_permutation(a.begin(),a.end()))
            cout<<a<<'\n';
        else
            cout<<"No Successor\n";
    }
}
