#include<set>
#include<cstdio>
#include<string>
using namespace std;
char tol[256],u[256];
void getword(char *s)
{
    char c=getchar();
    while(u[c])
        *(s++)=tol[c],c=getchar();
    *s=0;
    ungetc(c,stdin);
}
char tmp[5000];
main()
{
    int i,j,k,c,max;
    string ans;
    multiset<string> s;
    for(i='A';i<='Z';i++)u[i]=1,tol[i]=i+32;
    for(i='a';i<='z';i++)u[i]=1,tol[i]=i;
    while(1)
    {
        c=max=0,s.clear();
        while(c!='#')
        {
            c=getchar();
            if(u[c])
            {
                ungetc(c,stdin);
                getword(tmp);
                s.insert((string)tmp);
                k=s.count((string)tmp);
                if(k>max)max=k,ans=tmp;
            }
        }
        if(!s.size())break;
        printf("%4d %s\n",max,ans.c_str());
    }
}
