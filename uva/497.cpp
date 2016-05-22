#include<stdio.h>
main(){
long t,i,j,k,len[10000],head[10000],s[10000],max,n,m;
char line[1000];
scanf("%ld%c",&t,&line[0]);
gets(line);
while(t--){
    for(max=n=0;gets(line)!=NULL && sscanf(line,"%ld",&s[n])==1;n++)
        head[n]=-1;
    len[max=(1<?n)]=n-1;
    for(i=n-2;i>=0;i--){
        if(s[i]<=s[len[max]]){
            head[i]=len[max++];
            len[max]=i;
        }
        else{
            for(j=2,k=max,m=max/2+1;k-j>3;m=(j+k)/2){
                if(s[len[m]]<=s[i] && s[len[m-1]]>=s[i])break;
                else if(s[len[m]]>=s[i])j=m+1;
                else k=m-1;
            }
            for(m=max;m>1;m--)
                if(s[len[m]]<=s[i] && s[len[m-1]]>=s[i])break;
            if(m>1){
                len[m]=i;
                head[i]=len[m-1];
            }
            else if(s[i]>s[len[1]])len[1]=i;
        }
    }
    printf("Max hits: %ld\n",max);
    for(k=len[max];k>=0 && n;k=head[k])printf("%ld\n",s[k]);
    if(t)puts("");
}
}
