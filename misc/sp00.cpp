#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
bool test(char *a[])
{
    return 1;
}
bool cmp(char a[],char b[])
{
    return strcmp(a,b)<0;
}
bool w[256];
main(int m,char *a[])
{
    if(m<2)
    {
        printf("Usage: %s filename\n",a[0]);
        return 0;
    }
    int i,last;
    for(i='a';i<='z';i++)w[i]=1;
    for(i='A';i<='Z';i++)w[i]=1;
    w['-']=1;
    vector<string> s;
    string tmp;
    freopen(a[1],"r",stdin);
    last=' ';
    while((i=getchar())!=EOF)
    {
        if(tmp.length()==0)
        {
            if(!w[last] && i=='A')
                tmp.push_back(i);
        }
        else if(w[i])tmp.push_back(i);
        else 
        {
            s.push_back(tmp);
            tmp.clear();
        }
        last=i;
    }
    sort(s.begin(),s.end());
    for(i=0;i<s.size();i++)
        if(!i || s[i]!=s[i-1])
            puts(s[i].c_str());
}
