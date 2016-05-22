#include<stdio.h>
#include<string.h>
int n,use[10],path[2000];
void dfs(int d){
    if(d>=n)return;
    for(int i=0;i<10;i++)
        if(use[i]){
            use[i]--;
            use[2]-=(i==5);
            use[5]-=(i==2);
            use[6]-=(i==9);
            use[9]-=(i==6);
            path[d]=i;
            dfs(d+1);
            use[2]+=(i==5);
            use[5]+=(i==2);
            use[6]+=(i==9);
            use[9]+=(i==6);
            use[i]++;
            return;
        }
}
int set(int d){
    if(d>=n)return 0;
    int i;
    for(i=0;i<path[d];i++);
    use[i]--;
    use[2]-=(i==5);
    use[5]-=(i==2);
    use[6]-=(i==9);
    use[9]-=(i==6);
    if(set(d+1))return 1;
    use[i]++;
    use[2]+=(i==5);
    use[5]+=(i==2);
    use[6]+=(i==9);
    use[9]+=(i==6);
    for(i++;i<10;i++)
        if(use[i]){
            use[i]--;
            use[2]-=(i==5);
            use[5]-=(i==2);
            use[6]-=(i==9);
            use[9]-=(i==6);
            path[d]=i;
            dfs(d+1);
            use[2]+=(i==5);
            use[5]+=(i==2);
            use[6]+=(i==9);
            use[9]+=(i==6);
            use[i]++;
            return 1;
        }
    return 0;
}
main(){
int i,point;
char s[2000];
while(scanf("%s",s) && strcmp(s,".")){
    for(i=0;i<10;i++)use[i]=0;
    for(point=-1,i=0;s[i];i++){
        if(s[i]=='.'){
            point=i;
            continue;
        }
        use[s[i]-'0']++;
        path[i-(point>=0)]=s[i]-'0';
    }
    n=i-1;
    use[2]+=use[5];
    use[5]=use[2];
    use[6]+=use[9];
    use[9]=use[6];
    if(set(0)){
        for(i=0;i<n;i++){
            if(point==i)putchar('.');
            printf("%d",path[i]);
        }
        puts("");
    }
    else puts("The price cannot be raised.");
    
}
}
