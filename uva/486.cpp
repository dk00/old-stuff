#include<cstdio>
#include<cstring>
char num0[][15]={"zero","one","two","three","four",
    "five","six","seven","eight","nine"},
    teen[][15]={"ten","eleven","twelve","thirteen","fourteen",
    "fifteen","sixteen","seventeen","eighteen","nineteen"},
    ty[][15]={"","ten","twenty","thirty","forty",
    "fifty","sixty","seventy","eighty","ninety"},
    q[][15]={"zero","ten","hundred","thousand","","","million"};
int tonum(char *s1)
{
    int i,j;
    for(i=0;i<10;i++)
        if(!strcmp(s1,num0[i]))
            return i;
    for(i=0;i<10;i++)
        if(!strcmp(s1,teen[i]))
            return i+10;
    for(i=0;i<10;i++)
        if(!strcmp(s1,ty[i]))
            return i*10;
    for(i=0,j=1;i<7;i++,j*=10)
        if(!strcmp(s1,q[i]))
            return j;
    j/=(j/j-1);
}
main()
{
    int i,j,k,num,tmp2,tmp3;
    char *p,s[1000],tmp1[100];
    while(gets(s))
    {
        p=strtok(s," ");
        sscanf(p,"%s",tmp1);
        p=strtok(NULL," ");
        num=0;
        if(!strcmp(tmp1,"negative"))
        {
            putchar('-');
            j=sscanf(p,"%s",tmp1);
            p=strtok(NULL," ");
        }
        do{
            tmp2=tonum(tmp1);
            j=sscanf(p,"%s",tmp1);
            p=strtok(NULL," ");
            if(tmp2>=20)
            {
                if(j)
                {
                    tmp3=tonum(tmp1);
                    j=sscanf(p,"%s",tmp1);
                    p=strtok(NULL," ");
                    if(tmp3>=100)
                    {
                        tmp2*=tmp3;
                        continue;
                    }
                    else tmp2+=tmp3;
                    if(j)
                    {
                        tmp3=tonum(tmp1);
                        if(tmp3>=100)
                        {
                            tmp2*=tmp3;
                            j=sscanf(p,"%s",tmp1);
                            p=strtok(NULL," ");
                        }
                    }
                }
            }
            else if(j)
            {
                tmp3=tonum(tmp1);
                if(tmp3>=100)
                {
                    tmp2*=tmp3;
                    j=sscanf(p,"%s",tmp1);
                    p=strtok(NULL," ");
                }
            }
            num+=tmp2;
        }while(p);
        printf("%d\n",num);
    }
}
