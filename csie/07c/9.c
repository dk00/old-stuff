#include<string.h>
char *tmp,*s[512],c1[]="<A HREF=\"",c2[]="<a href=\"";
num[512];
main()
{
    int i,j,c,n;
    tmp=malloc(8193);
    for(i=n=0;(c=getchar())>=0;)
    {
        if(c==c1[i] || c==c2[i])i++;
        else i=0;
        if(c1[i])continue;
        for(i=j=0;(c=getchar())!='\"';j++)
            tmp[j]=c;
        tmp[j]=0;
        for(j=0;j<n;j++)
            if(!strcmp(tmp,s[j]))break;
        if(j<n)num[j]++;
        else{
            num[n]=1;
            s[n++]=tmp;
            tmp=malloc(8193);
        }
    }
    for(i=0;i<n;i++)
        for(j=1;j<n;j++)
            if(strcmp(s[j-1],s[j])>0)
            {
                tmp=s[j-1],s[j-1]=s[j],s[j]=tmp;
                c=num[j-1],num[j-1]=num[j],num[j]=c;
            }
    for(i=0;i<n;i++)
        printf("%d %s\n",num[i],s[i]);
}
