#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define MAX 1100
#define P 71387

class node
{
public:
	node *next;
        int num;
	char s[MAX];
};

class list
{
public:
	node* first;
	void add(char *s,int num)
	{
		node *c=(node *)malloc(sizeof(node));
		strcpy(c->s,s);
                c->num=num;
		c->next=first;
		first=c;
	}
	node *search(char *s)
	{
		node *ptr=first;
		while(ptr!=NULL)
		{
			if(strcmp(ptr->s,s)==0)
				break;
			ptr=ptr->next;
		}
		return ptr;
	}
	void del_all()
	{
		node *ptr,*tmp;
		ptr=first;
		while(ptr!=NULL)
		{
			tmp=ptr;
			ptr=ptr->next;
			free(tmp);
		}
	}
};


class table
{
public:
	list t[P];
	void initialize()
	{
		int i;
		for(i=0;i<P;i++)
			t[i].first=NULL;
	}
	int func(char *s)
	{
		int total=0,i,l=strlen(s);
		for(i=0;i<l;i++)
		{
			if(s[i]>='a' && s[i]<='z')
				total=(total*52+s[i]-'a')%P;
			else
				total=(total*52+s[i]-'A'+26)%P;
		}
		return total;
	}
	int add(char *s,int num)
	{
		int h=func(s);
		node *ptr=t[h].search(s);
		if(ptr==NULL)
		{
			t[h].add(s,num);
			return -1;
		}
		else
			return ptr->num;
	}
	void del()
	{
		int i;
		for(i=0;i<P;i++)
		{
			t[i].del_all();
			t[i].first=NULL;
		}
	}
};


//table hash;
//char q[1024][MAX];

char dic[102][2][12];
int dicl[102][2],count,ind;

map<char*,int> table;

void dfs(char *now)
{
	int i;
	map<char *,int>::iterator ptr;
	char later[MAX];
	char *mid,*tmp,*tmp2;
        if(count>1000)
        	return;
        for(i=0;i<ind;i++)
        {
		tmp=now;
		mid=tmp;
		while(1)
		{
			mid=strstr(tmp+(mid-tmp),dic[i][0]);
			if(mid!=NULL)
			{
				strcpy(later,now);
				tmp2=strstr(later+(mid-tmp),dic[i][0]);
				strcpy(tmp2,dic[i][1]);
				strcpy(tmp2+dicl[i][1],mid+dicl[i][0]);
			}
			else
				break;
			ptr=table.find(later);
			if(ptr->second==2)
				count=1001;
			else if(ptr==table.end())
			{
				table.insert(make_pair(later,2));
				count++;
				dfs(later);
				table[later]=1;
			}

			if(count>1000)
				break;

			mid=mid+dicl[i][0];
                }
                if(count>1000)
                	break;
	}
}

int main()
{
	int c;
	char *tmp;
	char now[MAX],later[MAX];
	char s[MAX];
	int cas,asd,a,b,i;
//	freopen("10027.txt","r",stdin);
	gets(s);
	cas=atol(s);
	gets(s);
	for(asd=0;asd<cas;asd++)
	{
        	if(asd!=0)
                	printf("\n");
                table.clear();
		ind=0;
		gets(now);
		tmp=now+1;
		tmp[strlen(tmp)-1]=0;
                strcpy(later,tmp);
		strcpy(now,later);
		while(gets(s)!=NULL)
		{
			if(s[0]==0)
				break;
			tmp=s+1;
			a=0;
			while(tmp[a]!='\"')
				a++;
			strncpy(dic[ind][0],tmp,a);
			dic[ind][0][a]=0;

                        b=a+1;
			while(tmp[b]!='\"')
				b++;
			tmp=tmp+b+1;

			strcpy(dic[ind][1],tmp);
			dic[ind][1][strlen(dic[ind][1])-1]=0;

			dicl[ind][0]=strlen(dic[ind][0]);
			dicl[ind][1]=strlen(dic[ind][1]);

			ind++;
		}
		table.insert(make_pair(now,2));
                count=1;
		dfs(now);

		if(count>1000)
			printf("Too many.\n");
		else
			printf("%d\n",count);
	}
	return 0;
}
