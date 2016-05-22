#include<cstdio>
const int max=1594323;
char s0[]="_ox";
struct pattern
{
    int n,sc;;
    char p[9];
    int test(char *tmp)
    {
        int i,j;
        for(i=j=0;i<5;i++)
        {
            if(tmp[i]=='o' && p[i]=='o')j++;
            if(tmp[i]!=p[i])return 0;
        }
        return 5;
    }
}pat[100];
short sc[max];
int num(char *tmp)
{
    int i,j;
    for(i=12,j=0;i>=0;i--)
    {
        j*=3;
        if(tmp[i]=='o')j++;
        else if(tmp[i]=='x')j+=2;
    }
    return j;
}
char *grp(int k,char *tmp)
{
    for(int i=0;i<13;i++,k/=3)
        tmp[i]=s0[k%3];
    return tmp;
}
main()
{
    int i,j,k,l,p,q,pn;
    char tmp[20];
    FILE *fp=fopen("data2.txt","r");
    for(pn=0;fscanf(fp,"%s",pat[pn].p)==1;pn++)
        fscanf(fp,"%d",&pat[pn].sc);
    fclose(fp);
    tmp[13]=0;
    for(i=0;i<max;i++)
    {
        if(i%100000==0)
            printf("%d ",i);
        grp(i,tmp);
        for(j=sc[i]=0;j<pn;j++)
            for(k=2;k<7;k++)
            {
                p=pat[j].test(tmp+k);
                if(p==5)
                    sc[i]+=pat[j].sc;
            }
    }
    puts("");
    fp=fopen("5_score.txt","w");
    for(i=0;i<max;i++)
    {
        if(i%100000==0)
            printf("%d ",i);
        fprintf(fp,"%d ",sc[i]);
    }
    fclose(fp);
}
