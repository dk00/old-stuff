#include<cstdio>
#include<string>
using namespace std;
char A[]="qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_",
	 N[]="0123456789",
	 S[]="+-():=;,";
char c0[256],c1[256],c2[256],error;
int num,al;
void seterr()
{
	if(!error)
	{
		puts("TOKEN ERROR");
		error=1;
	}
}
void print(string &s)
{
	if(s=="")return;
	if(!al && num>8)
		seterr();
	if(num+al>32)
		seterr();
	if(error)return;
	printf("%s\n",s.c_str());
	num=al=0;
	s="";
}
void init()
{
	int i;
	for(i=0;A[i];i++)
		c0[A[i]]=c2[A[i]]=1;
	for(i=0;N[i];i++)
		c1[N[i]]=c2[N[i]]=1;
	for(i=0;S[i];i++)
		c2[S[i]]=1;
}
main()
{
	int n,c,stt;
	init();
	while(1)
	{
		stt=1;
		error=0;
		while(1)
		{
			num=0,al=0;
			string to="";
			for(n=0;;n++)
			{
				c=getchar();
//				printf("[%c]",c);
				if(c==EOF)
				{
					if(!stt)puts("");
					return 0;
				}
				stt=0;
				if(!(num+al) && c0[c]+c1[c])
					print(to);
				if(c1[c])num++;
				else if(c0[c])al++;
				else 
				{
					if(c=='-' && to=="-")
					{
						while(1)
						{
							c=getchar();
							if(c=='\n' || c==EOF)break;
						}
						break;
					}
					if(num+al && !(c0[c]+c1[c]))
						print(to);
					if(to==":" && c!='=')
						seterr();
					if(to!="" && (to!=":" || c!='='))
						print(to);
					if(to!=":" && c=='=')
						seterr();
				}
				if(c!='\n' && c!=' ' && c!='\t' && !c2[c])
				{
					if(!error)
					{
						/*printf("%c|",c);
						puts(to.c_str());*/
						seterr();
					}
				}
				if(c!='\n' && c!=' ' && c!='\t')to.push_back(c);
				if(c=='\n')break;
			}
			if(!n)break;
		}
		puts("");
	}
}
