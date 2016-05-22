#include<cstdio>
main(int m,char **a)
{
    if(m!=3)return 0;
    FILE *f0=fopen(a[1],"r"),*f1=fopen(a[2],"r");
    int i,j,k;
    for(i=0;fscanf(f0,"%d",&j)>0 && fscanf(f1,"%d",&k)>0;i++)
        if(j<k)
            printf("%d: %d %d\n",j,k);
    fclose(f1);
    fclose(f0);
}
