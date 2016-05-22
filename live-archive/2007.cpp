#include<cstdio>
int c[7][256];
char s[100],mes[100],stack[10000];
main()
{
    int i,j,k,u,n;
    c[0]['<']=c[1]['<']=c[2]['<']=c[3]['<']=c[4]['<']=1;
    for(i='A';i<='Z';i++)c[1][i]=3,c[2][i]=4;
    c[1]['/']=2;
    c[3]['>']=5,c[4]['>']=6;
    u=1;
    while(u)
    {
        mes[0]=k=u=n=0;
        while(gets(s))
        {
            for(i=0;s[i];i++,u++)
            {
                if(s[i]=='#')break;
                k=c[k][s[i]];
                if(k==3 || k==4)j=s[i];
                if(k==5)stack[n++]=j,k=0;
                if(k==6)
                {
                    k=0;
                    if(n && stack[n-1]==j)n--;
                    else if(n && !mes[0])
                        sprintf(mes,"Expected </%c> found </%c>",
                        stack[n-1],j);
                    else if(!n && !mes[0])
                        sprintf(mes,"Expected # found </%c>",j);
                }
            }
            if(s[i]=='#')break;
        }
        if(!u)break;
        if(n>0 && !mes[0])
            sprintf(mes,"Expected </%c> found #",stack[n-1]);
        if(mes[0])puts(mes);
        else puts("Correctly tagged paragraph");
    }
}
