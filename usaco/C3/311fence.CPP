#include<stdio.h>
const int MAX=1025;
int v[MAX],link[MAX][MAX],c[MAX],p=0,i;
void go(int s)
{
    while(v[s])
    {
        for(i=1;i<MAX && !link[i][s];i++);
        v[i]--,v[s]--;
        link[i][s]--;link[s][i]--;
        go(i);
    }
    c[p++]=s;
}
main(){
int s,f,l1,l2;
    for(s=0;s<MAX;s++)
    {
        v[s]=link[s][s]=0;
        for(f=0;f<s;f++)
            link[s][f]=link[f][s]=0;
    }
    scanf("%d",&f);
    while(f--)
    {
        scanf("%d %d",&l1,&l2);
        v[l1]++,v[l2]++;
        link[l1][l2]++,link[l2][l1]++;
    }
    for(s=1;s<MAX && v[s]%2!=1;s++);
    if(s>=MAX)for(s=1;v[s]==0;s++);
    go(s);
    while(p--)printf("%d\n",c[p]);
}
