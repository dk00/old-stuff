#include<cstdio>
#include<cstdlib>
main()
{
    while(1)
    {
        system("0420g > in");
        system("0420a < in >out1");
        system("0420b < in >out2");
        FILE *f0=fopen("out1","r"),*f1=fopen("out2","r");
        int i,j,k;
        for(i=0;fscanf(f0,"%d",&j)>0 && fscanf(f1,"%d",&k)>0;i++)
            if(j<k)
            {
                printf("%d: %d %d\n",i,j,k);
                return 0;
            }
        fclose(f1);
        fclose(f0);
    }
}
