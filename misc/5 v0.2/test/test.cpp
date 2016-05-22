#include<ctime>
#include<cstdio>
main()
{
    FILE *p=fopen("5_table.txt","r");
    int i,start=clock();
    while(fscanf(p,"%d",&i)==1);
    fclose(p);
    printf("%d\n",clock()-start);
    scanf("%d",&i);
}
