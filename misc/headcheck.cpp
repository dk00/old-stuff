#include<map>
#include<string>
#include<cstdio>
#include<cstring>
using namespace std;
char s[300],t[300];
main()
{
    map<string,int> h;
    h["stdio.h"]=2;
    h["stdlib.h"]=2;
    h["string.h"]=2;
    h["time.h"]=2;
    h["math.h"]=2;
    h["cstdio"]=2;
    h["cstdlib"]=2;
    h["cstring"]=2;
    h["ctime"]=2;
    h["cmath"]=2;
    h["iostream"]=2;
    h["string"]=2;
    h["algorithm"]=2;
    h["vector"]=2;
    h["queue"]=2;
    h["set"]=2;
    h["list"]=2;
    h["stack"]=2;
    h["map"]=2;
    h["bitset"]=2;
    int i,j;
    while(fgets(s,50,stdin))
    {
        if(strncmp(s,"#include",8))
            continue;
        for(i=0;s[i] && s[i]!='<';i++);
        for(j=0;s[j] && s[j]!='>';j++);
        s[j]=0;
        sscanf(s+i+1,"%s",t);
        if(h[t]!=2)
            return 0;
    }
    puts("OK");
}
