#include<cstdio>
const int max=1594323;
char s0[]="_ox";
struct pattern
{
    int n,len,bl[15],sc[6];;
    char p[9];
    int test(char *tmp)
    {
        int i,j;
        for(i=j=0;i<len;i++)
        {
            if(tmp[i]=='o' && p[i]=='o')j++;
            if(tmp[i]=='_' && p[i]=='o')continue;
            if(tmp[i]!=p[i])return 0;
        }
        return j;
    }
}pat[100];
short sc[max];
struct pair{int a,b;} th[max][10],bl[max][10];
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
    FILE *fp=fopen("data.txt","r");
    for(pn=0;fscanf(fp,"%d",&pat[pn].len)==1;pn++)
    {
        fscanf(fp,"%s %d",pat[pn].p,&pat[pn].n);
        for(j=0;j<pat[pn].n;j++)
            fscanf(fp,"%d",&pat[pn].sc[j]);
        fscanf(fp,"%d",&k);
        for(j=0;j<k;j++)
            fscanf(fp,"%d",&pat[pn].bl[j]);
        pat[pn].bl[j]=-1;
    }
    fclose(fp);
    tmp[13]=0;
    for(i=0;i<max;i++)
        th[i][0].a=bl[i][0].a=-1;
    for(i=0;i<max;i++)
    {
        if(i%100000==0)
            printf("%d ",i);
        grp(i,tmp);
        for(j=sc[i]=0;j<pn;j++)
            for(k=7-pat[j].len;k<7;k++)
            {
                p=pat[j].test(tmp+k);
                if(p>0)
                    sc[i]+=pat[j].sc[p-1];
                if(p==pat[j].n)
                {
                    
                    for(p=k;p<k+pat[j].len;p++)
                    {
                        if(tmp[p]=='o')
                        {
                            tmp[p]='_';
                            q=num(tmp);
                            tmp[p]='o';
                        }
                        else continue;
                        for(l=0;th[q][l].a!=-1;l++);
                        th[q][l]=(pair){p,pat[j].n};
                        th[q][l+1]=(pair){-1,-1};
                    }
                    for(p=0;bl[i][p].a>=0;p++);
                    for(l=0;pat[j].bl[l]>=0;p++,l++)
                        bl[i][p]=(pair){pat[j].bl[l]+k,pat[j].n+1};
                    bl[i][p]=(pair){-1,-1};
                }
            }
    }
    puts("");
    fp=fopen("5_score.txt","w");
    for(i=0;i<max;i++)
        fprintf(fp,"%d ",sc[i]);
    fclose(fp);
    fp=fopen("5_table.txt","w");
    for(i=0;i<max;i++)
    {
        if(i%100000==0)
            printf("%d ",i);
        if(th[i][0].a>=0 || bl[i][0].a>=0)
            fprintf(fp,"%d ",i);
        else continue;
        for(j=0;th[i][j].a>=0;j++)
            fprintf(fp,"%d %d ",th[i][j].a,th[i][j].b);
        fprintf(fp,"-1 -1\n");
        for(j=0;bl[i][j].a>=0;j++)
            fprintf(fp,"%d %d ",bl[i][j].a,bl[i][j].b);
        fprintf(fp,"-1 -1\n");
    }
    fclose(fp);
    puts("");
    while(scanf("%s",tmp)==1)
    {
        if('0'<=tmp[0] && tmp[0]<='9')
        {
            sscanf(tmp,"%d",&i);
            puts(grp(i,tmp));
        }
        i=num(tmp);
        printf("%d %d\n",i,sc[i]);
        for(j=0;th[i][j].a>=0;j++)
            printf("(%d,%s)\n",th[i][j].a,pat[th[i][j].b].p);
        puts("");
        for(j=0;bl[i][j].a>=0;j++)
            printf("(%d,%s)\n",bl[i][j].a,pat[bl[i][j].b].p);
        puts("");
    }
}
