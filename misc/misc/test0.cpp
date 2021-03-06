#include<map>
#include<cstdio>
#include<string>
using namespace std;
char id[35][3]={
    "1t","2t","3t","4t","5t","6t","7t","8t","9t",
    "1s","2s","3s","4s","5s","6s","7s","8s","9s",
    "1c","2c","3c","4c","5c","6c","7c","8c","9c",
    "e","w","s","n","r","g","b"},
    name[35][5]={
    "一萬","二萬","三萬","四萬","五萬","六萬","七萬","八萬","九萬",
    "一索","二索","三索","四索","五索","六索","七索","八索","九索",
    "一筒","二筒","三筒","四筒","五筒","六筒","七筒","八筒","九筒",
    "東風","西風","南風","北風","紅中","青發","白版"
    };
int inf=999999999;
int p[5][5]={
    {0,   1,   2,   3,  inf},
    {0,   0,   1,   2,    3},
    {0,   0,   0,   1,    2},
    {0,   0,   0,   0,    1},
    {0,   0,   0,   0,    0}
},c[5][5]={
    {0,   1,   2,   3,  inf},
    {0,   0,   1,   2,    3},
    {0,   0,   0,   1,    2},
    {0,   0,   0,   0,    1},
    {0,   0,   0,   0,    0}
},t[5][5]={
    {0,   1,   2,   3,  inf},
    {0,   0,   1,   2,    3},
    {0,   0,   0,   1,    2},
    {0,   0,   0,   0,    1},
    {0,   0,   0,   0,    0}
};
map<string,int> num;
int sum,m,u[34],o[34],r[34],comb[9999][3];
void print(int[]);
void init()
{
    int i;
    for(i=0;i<34;i++)
    {
        num[id[i]]=i;
        comb[i][0]=comb[i][1]=comb[i][2]=i;
    }
    m=i;
    for(i=0;i<7;i++)
    {
        comb[m][0]=i;
        comb[m][1]=i+1;
        comb[m++][2]=i+2;
        comb[m][0]=i+9;
        comb[m][1]=i+10;
        comb[m++][2]=i+11;
        comb[m][0]=i+18;
        comb[m][1]=i+19;
        comb[m++][2]=i+20;
    }
}
char add(int x)
{
    int i;
    for(i=0;i<3;i++)
        if(++u[comb[x][i]]+r[comb[x][i]]>4)break;
    if(i>=3)return 1;
    while(i>=0)
        u[comb[x][i--]]--;
    return 0;
}
void rm(int x)
{
    for(int i=0;i<3;i++)
        u[comb[x][i]]--;
}
int go0(int d,int i)
{
    if(d==14)return sum++;
    if(!d)
    {
        for(i=0;i<34;i++)
            u[i]+=2,go0(2,0),u[i]-=2;
        return 0;
    }
    for(;i<m;i++)
        if(add(i))
            go0(d+3,i),rm(i);
}
int diff()
{
    int i,sum=0;
    for(i=0;i<34;i++)
        if(u[i]>o[i])sum+=u[i]-o[i];
    return sum;
}
int fix,last,ub,ext,cnt;
int cost(int l,int x)
{
    int i=comb[x][0],j=comb[x][1],k=comb[x][2];
    if(x<34)
        return l+t[o[i]][u[i]];
    return l+t[o[i]][u[i]]+t[o[j]][u[j]]+t[o[k]][u[k]];
}
int go(int d,int i,int l)
{
    if(cnt>=10)return 0;
    if(d+fix==17)
    {
        if(l>last)
        {
            cnt++;
            print(u);
        }
        return 0;
    }
    int nl=ext;
    if(!d)
    {
        for(i=0;i<34;i++)
            if((nl=l+p[o[i]][u[i]+2])<=ub)
                u[i]+=2,go(2,0,nl),u[i]-=2;
            else ext=min(ext,nl);
        return 0;
    }
    for(;i<m;i++)
        if(add(i))
        {
            if((nl=cost(l,i))<=ub)go(d+3,i,nl);
            else ext=min(ext,nl);
            rm(i);
        }
    return 0;
}
void print(int s[])
{
    int i,j;
    for(i=0;i<34;i++)
        for(j=0;j<s[i];j++)
            printf("%c%c",name[i][0],name[i][1]);
    puts("");
    for(i=0;i<34;i++)
        for(j=0;j<s[i];j++)
            printf("%s",name[i]+2);
    puts("");
}
main()
{
    init();
    int i,j,fix;
    go0(0,0);
    printf("%d\n",sum);
    while(1)
    {
        char tmp[99];
        for(i=0;i<34;i++)o[i]=u[i]=r[i]=0;
        for(i=fix=0;i<17;i++)
        {
            scanf("%s",tmp);
            if(tmp[0]=='-')u[num[tmp+1]]++,fix++;
            else o[num[tmp]]++;
        }
        while(scanf("%s",tmp) && num.count(tmp))
            r[num[tmp]]++;
        print(o);
        for(ub=cnt=0,ext=inf-1,last=-1;cnt<10;)
        {
            printf("%d\n",ub);
            go(0,0,0);
            if(ext>=inf)break;
            last=ub,ub=ext,ext=inf;
        }
    }
}
