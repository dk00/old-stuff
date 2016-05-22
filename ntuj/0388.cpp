#include<map>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
char x[1001],t0[1001],t1[1001];
string p[1001];
int len[1001];
void ins(char a[],int n)
{
    for(int i=n;i>0;i--)
        if(a[i]<a[i-1])swap(a[i],a[i-1]);
}
void print(int i)
{
    int j=i-p[i].length();
    if(j>=0)
    {
        print(j);
        putchar(' ');
    }
    printf("%s",p[i].c_str());
}
main()
{
    int i,j,k,n,T;
    map<string,string> h;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s %d",x,&n);
        for(i=0;x[i];i++)
            len[i]=0,p[i]="";
        for(i=0;i<n;i++)
        {
            scanf("%s",t0);
            for(j=0;t1[j]=t0[j];j++);
            sort(t1,t1+j);
            if(h[t1]=="")h[t1]=t0;
            else h[t1]="-";
            len[j]++;
        }
        for(i=t0[0]=0;x[i];i++)
        {
            if(i && p[i-1]=="")continue;
            for(j=0;j<100 && x[i+j];j++)
            {
                t0[j]=x[i+j],t0[j+1]=0;
                for(k=j;k>0 && t0[k]<t0[k-1];k--)
                    swap(t0[k],t0[k-1]);
                if(!len[j+1])continue;
                string &word=h[t0],&p0=p[i+j];
                if(word!="")
                {
                    if(p[i-1]=="-" || word=="-" || p0!="")p0="-";
                    else p0=word;
                }
            }
        }
        if(p[i-1]=="")puts("impossible");
        else if(p[i-1]=="-")puts("ambiguous");
        else print(i-1),puts("");
    }
}
