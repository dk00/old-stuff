#include<map>			
#include<cstdio>
#include<string>
using namespace std;
struct puzzle
{
    char s[24];
    int u;
    void go(int type)
    {
        char i,tmp,*a,b[12],*c,x;
        a=s+type%2*12;
        c=s+(1-type%2)*12;
        if(type/2==type%2)x=2;
        else x=10;
        for(i=0;i<12;i++)b[(i+x)%12]=a[i];
        for(i=0;i<12;i++)a[i]=b[i];
        for(i=9;i<12;i++)c[i]=a[i];
    }
    bool operator<(puzzle a)const
    {
        for(int i=0;i<24;i++)
            if(s[i]!=a.s[i])return s[i]<a.s[i];
        return 0;
    }
    bool operator!=(puzzle a)const{return(a<*this || *this<a);}
    bool operator==(puzzle a)const{return!(a!=*this);}
}q1[120000],q2[1500],start=(puzzle)
    {{0,3,4,3,0,5,6,5,0,1,2,1,0,7,8,7,0,9,10,9,0,1,2,1},0};
char s1[120000],s2[1500],m1[120000],m2[1500];
int l1[120000],l2[1500];
int go(char max,puzzle q[],char step[],char move[],int last[],map<puzzle,int>& h)
{
    int i,j,k;
    q[0]=start,move[0]=-1;
	h[start]=0;
    for(i=0,j=1;i<j;i++)
        for(k=0,q[i].u=i;step[i]<max && k<4;k++)
        {
            if((k+2)%4==move[i])continue;
            q[i].go(k);
            last[j]=i,step[j]=step[i]+1,move[j]=k;
			if(h.count(q[i])<1)
	            q[h[q[i]]=j++]=q[i];
            q[i].go((k+2)%4);
        }
    return j;
}
void printA(int i)
{
    if(i)printA(l2[i]),printf("%d",m2[i]+1);
}
void printB(int i)
{
    if(i)printf("%d",(m1[i]+2)%4+1),printB(l1[i]);
    else puts("");
}
main()
{
    int i,j,k,T;
	map<puzzle,int> h;
    j=go(10,q1,s1,m1,l1,h);
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<24;i++)scanf("%d",start.s+i);
		map<puzzle,int> tmp;
        j=go(6,q2,s2,m2,l2,tmp);
        for(i=0;h.count(q2[i])<1 && i<j;i++);
        if(i>=j)puts("NO SOLUTION WAS FOUND IN 16 STEPS");
        else if(i==0 && !h[q2[i]])puts("PUZZLE ALREADY SOLVED");
        else printA(i),printB(h[q2[i]]);
    }
}
