#include<stdio.h>
int n,use[10],path[2000];
void dfs(int d){
    if(d>=n)return;
    for(int i=0;i<10;i++)
        if(use[i]){
            use[i]--;
            path[d]=i;
            dfs(d+1);
            use[i]++;
            return;
        }
}
int set(int d){
    if(d>=n)return 0;
    int i;
    for(i=0;i<path[d];i++);
    use[i]--;
    if(set(d+1))return 1;
    use[i]++;
    for(i++;i<10;i++)
        if(use[i]){
            use[i]--;
            path[d]=i;
            dfs(d+1);
            use[i]++;
            return 1;
        }
    return 0;
}
main(){
int i;
char s[2000];
while(scanf("%s",s)!=EOF){
    for(i=0;i<10;i++)use[i]=0;
    for(i=0;s[i];i++){
        use[s[i]-'0']++;
        path[i]=s[i]-'0';
    }
    n=i;
    set(0);
    for(i=0;i<n;i++)printf("%d",path[i]);
    puts("");
}
}
