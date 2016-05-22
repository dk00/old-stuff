#include<cmath>
#include<cstdio>
#include<algorithm>
double gold=(1+sqrt(5))/2;
int r[]={10,10,10,10,10,10};
int fs(int n,int v)
{
    if(n>=v)
        return v+(int)sqrt(n-v);
    return v-(int)pow(v-n,gold);
}
struct data
{
    int sno,no,hp,at,de,sa,sd,sp,key;
    int u;
    char c1[10],c2[10],name[30];
    void calc()
    {
        key=hp*r[0]+
            at*r[1]+
            de*r[2]+
            sa*r[3]+
            sd*r[4]+
            fs(sp,88)*r[5];
    }
    char getdata(FILE *fp)
    {
        char tmp[1000];
        if(fscanf(fp,"%d %d%c",&sno,&no,tmp)!=3)return 0;
        fgets(name,29,fp);
        for(int i=0;name[i];i++)
            if(name[i]=='\n'){name[i]=0;break;}
        fscanf(fp,"%s %s%c",c1,c2,tmp);
        fgets(tmp,1000,fp);
        sscanf(tmp,"%d %d %d %d %d %d %d",&hp,&at,&de,&sa,&sd,&sp,&key);
        return 1;
    }
    bool operator<(data x)const
    {
        return(key<x.key || key==x.key && u<x.u);
    }
    bool operator>(data x)const
    {
        if(name[0]!='*' && x.name[0]=='*')return 1;
        if(name[0]=='*' && x.name[0]!='*')return 0;
        return(key>x.key || key==x.key && u>x.u);
    }
    void print()
    {
        printf("%3d %3d %-26s ",u,no,name);
        printf("%3d %3d %3d %3d %3d %3d %5d\n",hp,at,de,sa,sd,sp,key);
    }
}s[1000];
bool cmp(data a,data b)
{
    return a>b;
}
main()
{
    int i,n;
    char cmd[100];
    FILE *fp=fopen("pm.dat","r");
    for(n=0;s[n].getdata(fp);n++);
    fclose(fp);
    while(scanf("%s",cmd)==1 && cmd[0]!='q')
    {
        if(cmd[0]=='r')
        {
            for(i=0;i<6;i++)
                scanf("%d",r+i);
            for(i=0;i<n;i++)
                s[i].calc();
            std::sort(s,s+n,cmp);
            for(i=0;i<n;i++)
                s[i].u=i;
        }
        if(cmd[0]=='s')
            for(i=0;i<n;i++)
                s[i].print();
            
    }
}
