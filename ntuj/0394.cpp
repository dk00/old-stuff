#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;
char map[128],tmp[9999],tmp1[9999];
string s[100000];
main()
{
    int i,j,k,n;
    for(i='0';i<='9';i++)map[i]=i;
    map['A']=map['B']=map['C']='2';
    map['D']=map['E']=map['F']='3';
    map['G']=map['H']=map['I']='4';
    map['J']=map['K']=map['L']='5';
    map['M']=map['N']=map['O']='6';
    map['P']=map['R']=map['S']='7';
    map['T']=map['U']=map['V']='8';
    map['W']=map['X']=map['Y']='9';
    while(~scanf("%d",&n))
    {
        for(i=0;i<n;i++)
        {
            scanf("%s",tmp);
            for(j=k=0;tmp[j];j++)
            {
                if(map[tmp[j]])
                    tmp1[k++]=map[tmp[j]];
                if(k==3)tmp1[k++]='-';
            }
            tmp1[k]=0;
            s[i]=tmp1;
        }
        sort(s,s+n);

        for(i=k=0;i<n;i=j)
        {
            for(j=i;j<n && s[j]==s[i];j++);
            if(j-i>1)
                printf("%s %d\n",s[i].c_str(),j-i),k++;
        }
        if(!k)puts("No duplicates.");
    }
}
