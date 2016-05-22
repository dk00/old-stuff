#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
main()
{
    int n;
    string str;
    cin>>n;
    while(n)
    {
        cin>>str;
        sort(str.begin(),str.end());
        cout<<str<<endl;
        while(next_permutation(str.begin(),str.end()))
        {
            cout<<str<<endl;
        }
        n--;if(n>0)cout<<endl;
    }
}
