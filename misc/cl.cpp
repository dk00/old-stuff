#include<map>
#include<string>
#include<cstdio>
using namespace std;
char str[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
char u[256];
main()
{
    map<string,char> h;
    FILE *fp=fopen("darklist","r");
    if(!fp)return 0;
    while(fscanf(fp,"%s",u)==1)
        h[u]=2;
    fclose(fp);
    int i,x;
    for(i=0;str[i];i++)
        u[str[i]]=1;
    string tmp;
    while((x=getchar())!=EOF)
    {
        tmp="";
        while(x!=EOF && u[x])
        {
            tmp.push_back(x);
            x=getchar();
        }
        if(h[tmp]==2)
        {
            printf("!%s!",tmp.c_str());
            return 0;
        }
    }
    puts("OK");
}
