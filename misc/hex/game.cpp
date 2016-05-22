#include"game.h"
const char *_num[13]={__num[0]+2,__num[1]+2,__num[2]+2,__num[3]+2,__num[4]+2,
__num[5]+2,__num[6]+2,__num[7]+2,__num[8]+2,__num[9]+2,__num[10]+2,__num[11]+2,
__num[12]+2};
const char **num=_num+2;
#include<cstring>
#define Ext
void hex::flip(char p,char rec)
{
    char i;
    char const *a=adj1[p],*b=adj2[p];
    for(i=0;a[i]>=0;i++)
        copy[pl][a[i]]++,sn[pl]++,
        copy[s[p]][a[i]]--,sn[s[p]]--;
#ifdef Ext
    for(i=0;b[i]>=0;i++)
        jmp[pl][b[i]]++,
        jmp[s[p]][b[i]]--;
#endif
    if(rec)act[frm]=2,pi[frm++]=p;
    s[p]=3-s[p];
}
char hex::add(char p,char c,char rec)
{
    spc--;
    char i,sum=0;
    char const *a=adj1[p],*b=adj2[p];
    sn[s[p]=c]++;
    for(i=0;a[i]>=0;i++)
    {
        copy[s[p]][a[i]]++;
        if(rec && s[a[i]]==3-pl)
            flip(a[i]),sum++;
    }
#ifdef Ext
    for(i=0;b[i]>=0;i++)
        jmp[s[p]][b[i]]++;
#endif
    if(rec)act[frm]=1,pi[frm++]=p;
    return sum;
}
void hex::del(char p,char rec)
{
    spc++;
    sn[s[p]]--;
    char i;
    char const *a=adj1[p],*b=adj2[p];
    for(i=0;a[i]>=0;i++)
        copy[pl][a[i]]--;
#ifdef Ext
    for(i=0;b[i]>=0;i++)
        jmp[pl][b[i]]--;
#endif
    s[p]=0;
    if(rec)act[frm]=0,pi[frm++]=p;
}
char hex::taste(char p)
{
    if(p<0 || s[p])return -1;
    return copy[!pl][p];
}
char hex::move(char p,char q,char ch)
{
    if(ch)
        if(q<0 || s[q])return -1;
    char tmp=add(q,pl);
    if(p!=q)del(p);
    fn[++step]=frm;
    pl=3-pl;
    return tmp;
}
char hex::undo()
{
    if(!step)return 0;
    step--,pl=3-pl;
    while(frm>fn[step])
        if(act[--frm]>1)
            flip(pi[frm],0);
        else if(act[frm])
            del(pi[frm],0);
        else
            add(pi[frm],pl,0);
}
char hex::end()
{
    int i,j;
    for(i=0;i<61;i++)
        if(!s[i] && copy[1][i]+jmp[1][i])
            break;
    j=i;
    for(i=0;i<61;i++)
        if(!s[i] && copy[2][i]+jmp[2][i])
            break;
    if(i<61 && j<61)return 0;
    if(i<61)return 1+(sn[0]<sn[1]+spc);
    return 1+(sn[0]+spc<sn[1]);
}
void hex::reset()
{
    memset(s,3,sizeof(s));
    memset(copy,0,sizeof(copy));
    memset(jmp,0,sizeof(jmp));
    hex &a=*this;
    for(int i=0;i<Npos;i++)a[i]=0;
    pl=1;
    add(0,1),add(34,1),add(56,1);
    add(4,2),add(26,2),add(60,2);
    step=frm=cn[1]=cn[2]=jn[1]=jn[2]=sn[1]=sn[2]=0;
}
