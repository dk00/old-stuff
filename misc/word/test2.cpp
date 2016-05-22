#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int score[128],ex[128];
struct spell{
    char *word;
    int sc,ext;
    spell(){}
    spell(char a[])
    {
        word=a;
        sc=ext=0;
        for(int i=0;a[i];i++)
            sc+=score[a[i]],
            ext+=ex[a[i]];
    }
    bool operator<(spell a)const
    {
        if(strlen(word)!=strlen(a.word))
            return strlen(word)<strlen(a.word);
        if(ext!=a.ext)
            return ext>a.ext;
        return sc>a.sc;
    }
    
}t[399999];
char s[399999][20],res[399999][20];
char u[128];
char cmp(char a[],char b[])
{
    int i;
    for(i=0;a[i];i++)u[a[i]]=0;
    for(i=0;b[i];i++)u[b[i]]=0;
    for(i=0;a[i];i++)u[a[i]]++;
    for(i=0;b[i];i++)
        if(!u[b[i]]--)return 0;
    return 1;
}
main()
{
    int i,j,n=0,m;
    char tmp[999];
    for(i='a';i<='z';i++)
        score[i]=2;
    score['z']=score['y']=score['x']=score['j']=4;
    score['m']=score['p']=score['c']=score['f']=3;
    for(j=0;j<9;j++)
    {
        sprintf(tmp,"%d",j);
        FILE *fp=fopen(tmp,"r");
        while(fscanf(fp,"%s",tmp)==1)
        {
            for(i=0;('A'<=tmp[i] && tmp[i]<='Z')||('a'<=tmp[i] && tmp[i]<='z');i++);
            if(tmp[i] || i>15 || i<3)continue;
            strcpy(s[n++],tmp);
        }
    }
    printf("%d\n",n);
    while(scanf("%s",tmp)==1){
        for(i='a';i<='z';i++)ex[i]=0;
        for(i=0;tmp[i];i++)
            ex[tmp[i]]=1;
        scanf("%s",tmp);
        for(i=m=0;i<n;i++)
            if(cmp(tmp,s[i]))
            {
                strcpy(res[m],s[i]);
                t[m++]=res[m];
            }
        sort(t,t+m);
        int p=150,q=1;
        for(i=0;i<p;i++)
            printf("%s %d\n",t[i].word,t[i].sc);
    }
}
