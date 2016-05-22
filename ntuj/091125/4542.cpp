#include<cstdio>
const int N=10001;
int key[N],v[N];
char cmd[99999];
main()
{
    int i,m,a,b;
    for(i=0;i<N;i++)
        key[i]=v[i]=i;
    while(scanf("%d %s %d",&a,cmd,&b)>0){
        for(m=0;cmd[m];m++);
        b=v[b];
        while(m--){
            if(cmd[m]=='f'){
                if(b%2)b++;
                else b+=3;
            }
            else if(cmd[m]=='b')
                b-=2;
            else if(cmd[m]=='k')
                printf("%d\n",key[b]);
            else if(cmd[m]=='<')
                v[a]=b;
            else if(cmd[m]=='=')
                printf("%c\n",v[a]==b?'=':'#');
        }
    }
}
