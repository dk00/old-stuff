#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
char tmp[9999];
void print(string& s,int j)
{
	string tmp=s;
	tmp.insert(j,1,'^');
	puts(tmp.c_str());
}
main()
{
	int i,j,k,T;
	gets(tmp);
	sscanf(tmp,"%d",&T);
	while(T-- && gets(tmp))
	{
		string s="";
		for(i=j=0;tmp[i];i++)
		{
			if(tmp[i]=='x')
			{
				if(j>0 && s.length())
					s.erase(--j,1);
			}
			else if(tmp[i]=='K')
			{
				while(j>0 && s.length() && s[j-1]!=' ')
					s.erase(--j,1);
			}
			else if(tmp[i]=='c')
			{
				if(j>0)
					s.insert(j++,1,s.at(j-1));
			}
			else if(tmp[i]=='D')
			{
				string sub="";
				for(k=j-1;k>=0 && s[k]!=' ';k--)
					sub.insert(0,1,s[k]);
				if(sub.length())
					s.insert(j,sub);
				j+=sub.length();
			}
			else if(tmp[i]=='R')
			{
				string sub="";
				for(k=j-1;k>=0 && s[k]!=' ';k--)
					sub.insert(0,1,s[k]);
				reverse(sub.begin(),sub.end());
				if(sub.length())
					s.replace(k+1,sub.length(),sub);
			}
			else if(tmp[i]=='p')
			{
				while(j>0)
					s.erase(--j,1);
			}
			else if(tmp[i]=='W')
			{
				s.erase(j);
			}
			else if(tmp[i]=='h')
			{
				if(j)j--;
			}
			else if(tmp[i]=='L')
			{
				if(j<s.length())j++;
			}
			else if(tmp[i]=='f')
			{
				j=0;
			}
			else if(tmp[i]=='G')
			{
				j=s.length();
			}
			else
				s.insert(j++,1,tmp[i]);
		}
		print(s,j);
	}
}
