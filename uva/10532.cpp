#include<iostream>
#include<algorithm>
using namespace std;
int p[50];
unsigned long long s[51];
main()
{
    s[0]=1llu;
    int i,j,k,l,n,m,C=1;
    while(cin>>n>>m && n+m)
    {
        for(i=0;i<n;i++)
            s[i+1]=0,cin>>p[i];
        sort(p,p+n);
        for(i=l=0;i<n;)
        {
            for(k=n;k>=0;k--)
                for(j=i;k+j-i+1<=n && p[i]==p[j];j++)
                    s[k+j-i+1]+=s[k];
            while(p[i]==p[l])i++;
            l=i;
        }
        cout<<"Case "<<C++<<":\n";
        while(m--)
        {
            cin>>i;
            cout<<s[i]<<endl;
        }
    }
}
