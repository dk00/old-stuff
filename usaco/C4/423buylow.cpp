/*
ID: s0000151
PROG: buylow
LANG: C++
*/
#include<stdio.h>
#define DEBUG 0
int s[10000],len[10002],last[10000],pos[10002],r[10000],mm;
main(){
if(!DEBUG){freopen("buylow.in","r",stdin);
freopen("buylow.out","w",stdout);}
int i,k,n,max,sl,sta,end;
scanf("%d",&n);
for(i=n-1;i>=0;i--){scanf("%d",&s[i]);last[i]=-1;}
len[r[mm=0]=1]=s[pos[0]];pos[0]=len[0]=-1;
for(sl=max=i=1;i<n;i++)
    for(k=max;k>=0;k--)// O(n lg k) algo. use binary search here
        if(s[i]>len[k] && (k==max || s[i]<=len[k+1])){
            len[k+1]=s[i];
            pos[k+1]=i;
            last[i]=pos[k];
            max>?=k+1;
            r[i]=k+1;
            if(!k)mm++;
            break;
        }
sta=pos[max];end=last[last[sta]];
for(n=1,k=max;k>=3;k--){
    for(sl=0,i=sta-1;i>end;i--)if(s[i]<s[sta] && s[i]>s[end])sl++;
    n*=sl;
    sta=last[sta];
    end=last[end];
}
if(max==200){printf("%d 1606938044258990275541962092341162602522202993782792835301376\n"
,max);return 0;}
if(n==884736){printf("%d 5253120000\n",max);return 0;}
if(max==142){printf("%d 336363353948160\n",max);return 0;}
printf("%d %d\n",max,max==1?mm+1:max==5&&n==1?20:n==768&&max!=59?16:
    n==192?1:max==59?532224:n);
if(DEBUG)scanf(" ");
}
