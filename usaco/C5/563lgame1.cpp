/*
ID:s0000151
PROG:lgame
LANG:C++
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char fuck[40002][16],f_ind;
int score[26]={2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};
char s[8];
bool use[40002]={0};
char dic[40002][8];
char ans[130][8],a_ind;
int rec[130];
int d_ind=0;
int len;
int solve;
int max;

int used[8];
char now[8];
char wait[8];

int find(char *test)
{
	int left=0,right=d_ind-1,mid;
	while(left<=right)
	{
		mid=(left+right)/2;
		if(strcmp(test,dic[mid])>0)
			left=mid+1;
		else if(strcmp(test,dic[mid])<0)
			right=mid-1;
		else
			return mid;
	}
	return -1;
}


int inn(char *x)
{
	int i;
	for(i=0;i<a_ind;i++)
	{
		if(strcmp(ans[i],x)==0)
			return 1;
	}
	return 0;
}

int cmp2(const void *a,const void *b)
{
	if(*(char *)a > *(char *)b)
		return 1;
	else if(*(char *)a < *(char *)b)
		return -1;
	return 0;
}

void permute(int depth ,int end,int sc)
{
	char tmp2[8];
	int i,tmp;
	if(depth==end)
	{
        	wait[end]=0;
		tmp=find(wait);
                strcpy(tmp2,dic[tmp]);
                qsort((void *)tmp2,strlen(tmp2),sizeof(tmp2[0]),cmp2);
		if(tmp!=-1 && !use[tmp] && !inn(tmp2) )
		{
//			ans[a_ind]=tmp;

                        strcpy(ans[a_ind],tmp2);
			rec[a_ind]=sc;
			a_ind++;
                        use[tmp]=1;
			solve=1;
		}
	}
	else
	{
		for(i=0;i<end;i++)
		{
			if(!used[i])
			{
				wait[depth]=now[i];
				used[i]=1;
				permute(depth+1,end,sc);
				used[i]=0;
			}
			if(solve)
				break;
		}
	}
}

int u1[10]={0},u2[10]={0};
int sigma_g1[27],sigma_g2[27];
char g1[10],g2[10];
char w1[10],w2[10];

void generate_2(int depth ,int end,int mode)
{
	int i,tmp;
	if(depth==end)
	{
        	w2[end]=0;
		tmp=find(w2);
		if(tmp!=-1)
		{
			if(mode==0)
				strcpy(fuck[f_ind++],w2);
			else
			{
				if(strcmp(w1,w2)<0)
				{
					strcpy(fuck[f_ind],w1);
					strcat(fuck[f_ind]," ");
					strcat(fuck[f_ind],w2);
                                }
				else
				{
					strcpy(fuck[f_ind],w2);
					strcat(fuck[f_ind]," ");
					strcat(fuck[f_ind],w1);
				}
				f_ind++;
			}
		}
	}
	else
	{
		for(i=0;i<26;i++)
		{
			if(sigma_g2[i]>0)
			{
				sigma_g2[i]--;
				w2[depth]=i+'a';
				u2[i]=1;
				generate_2(depth+1,end,mode);
				sigma_g2[i]++;
				u2[i]=0;
			}
		}
	}
}

void generate(int depth ,int end)
{
	int i,tmp;
	if(depth==end)
	{
        	w1[end]=0;
		tmp=find(w1);
		if(tmp!=-1)
			generate_2(0,strlen(g2),1);
	}
	else
	{
		for(i=0;i<26;i++)
		{
			if(sigma_g1[i]>0)
			{
				sigma_g1[i]--;
				w1[depth]=i+'a';
				u1[i]=1;
				generate(depth+1,end);
				u1[i]=0;
				sigma_g1[i]++;
			}
		}
	}
}

void dfs(int depth,int have,int sc)
{
	int tmp,i;
	if(depth==len)
	{
		if(have>=3)
		{
                	now[have]=0;
			for(i=0;i<have;i++)
				used[i]=0;
			solve=0;
			permute(0,have,sc);


                }
	}
	else
	{
		now[have]=s[depth];
		dfs(depth+1,have+1,sc+score[s[depth]-'a']);
		now[have]=0;

		dfs(depth+1,have,sc);
	}
}

int cmp(const void *a,const void *b)
{
	return strcmp((char *)a,(char *)b);
}

int alpha[27]={0};
int can(char *a,char *b)
{
	int sigma_star[27]={0},i;
	int la=strlen(a),lb=strlen(b);
	if(la+lb>len)
		return 0;
        for(i=0;i<26;i++)
        	sigma_star[i]=0;
	for(i=0;i<la;i++)
		sigma_star[a[i]-'a']++;
	for(i=0;i<lb;i++)
		sigma_star[b[i]-'a']++;
	for(i=0;i<26;i++)
	{
		if(alpha[i]<sigma_star[i])
			return 0;
	}
	return 1;
}

void screw(char *g2,int sigma[27])
{
	int i,l=strlen(g2);
	for(i=0;i<27;i++)
		sigma[i]=0;
	for(i=0;i<l;i++)
		sigma[g2[i]-'a']++;
}

int main()
{
	int i,j;
	FILE *fptr=fopen("lgame.dict","r");
	while(fscanf(fptr,"%s",dic[d_ind])==1)
	{
		if(dic[d_ind][0]=='.')
			break;
		d_ind++;
	}
	fclose(fptr);
	freopen("lgame.in","r",stdin);
	freopen("lgame.out","w",stdout);
	scanf("%s",s);
	len=strlen(s);
        screw(s,alpha);
	a_ind=0;

	max=0;
	dfs(0,0,0);

	for(i=0;i<a_ind;i++)
	{
		if(rec[i]>max)
			max=rec[i];
		for(j=0;j<a_ind;j++)
		{
			if(rec[i]+rec[j]>max && can(ans[i],ans[j]))
				max=rec[i]+rec[j];
		}
	}

	printf("%d\n",max);

	f_ind=0;
	for(i=0;i<a_ind;i++)
	{
		if(rec[i]==max)
		{
			strcpy(g2,ans[i]);
			screw(g2,sigma_g2);
			generate_2(0,strlen(g2),0);
		}
		for(j=i;j<a_ind;j++)
		{
			if(rec[i]+rec[j]==max && can(ans[i],ans[j]))
			{
				strcpy(g1,ans[i]);
				strcpy(g2,ans[j]);
				screw(g1,sigma_g1);
				screw(g2,sigma_g2);
				generate(0,strlen(g1));
			}
		}
	}
	qsort((void *)fuck,f_ind,sizeof(fuck[0]),cmp);
	for(i=0;i<f_ind;i++)
		printf("%s\n",fuck[i]);

	return 0;
}
