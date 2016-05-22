#include<stdio.h>
#include<string.h>
FILE *f1,*f2;
const char sort[5][20]=
{
    "Title","Artist","Album","Year","Comment"
};
const int dn=5,byte[5]={30,30,30,4,30};
char tag[4],data[5][50];
void printinfo(char *s,int len)
{
    printf("%s %d byte(s)",s,len)
    printf("TAG: %s",tag);
    if(strcmp(tag,"TAG")!=0)
    {
        puts("Format unknown");
        return;
    }
    int i;
    for(i=0;i<dn;i++)
        printf("%s: %s\n",sort[i],data[i]);
    puts("------------------------------");
}
void work()
{   char name[50]
    
    int i,len;
    while(1)
    {
        if(fscanf(f1,"%s",name)==EOF)
            return;
        f2=fopen(name,"r+");
        if(f2==NULL)
            continue;
        len=ftell(f2);
        fseek(f2,-128,SEEK_END);
        for(i=0;i<cn;i++)
            fgets(f2,data[i],byte[i]+1);
        printinfo(name,len);
    }
}
main()
{
    
    f1=f2=NULL;
    while(1)
    {
        scanf("%s",cmd);
        if(strcmp(cmd,"exit")==0)
            break;
        if(strcmp(cmd,"list")==0)
        {
            if(f1!=NULL)
                fclose(f1);
            scanf("%s",name);
            f1=fopen(name,"r");
            if(f1==NULL)
                puts("error");
        }
        if(strcmp(cmd,"go")==0)
        {
            if(f1==NULL)
            {
                puts("list is not loaded");
                continue;
            }
            work();
        }
    }
    if(f1!=NULL)
        fclose(f1);
    if(f2!=NULL)
        fclose(f2);
}
