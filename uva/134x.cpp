#include<ctype.h>
#include<stdio.h>
#include<string.h>
enum {A=1,MOD,BA,DA,LA,NAM,PREDA,predstring,predname,preds,verbpred,
predclaim,statement,sentence};
int vw[256];
int inline type(char *s){
  if(!s[1] && vw[*s])return A;
  if(!s[2] && vw[s[1]]){
      if(*s=='g')return MOD;
      if(*s=='b')return BA;
      if(*s=='d')return DA;
      if(*s=='l')return LA;
  }
  if(!vw[s[strlen(s)-1]])return NAM;
  if(strlen(s)==5 && !vw[*s] && !vw[s[3]] && vw[s[1]]!=vw[s[2]])
      return PREDA;
  return -1;
}
main(){
int i,n,pos,error,g[1000],stack[1000],use[100];
char c,s[1000];
vw['a']=vw['e']=vw['i']=vw['o']=vw['u']=1;
while((c=getchar())!='#'){
  n=error=0;
  for(i=0;i<100;i++)use[i]=0;
  while(1){
      while(!isalpha(c) && c-'.' && c-'#')c=getchar();
      if(c=='#')return 0;
      if(c=='.')break;
      for(i=0;isalpha(c);i++){
          s[i]=c;
          c=getchar();
      }
      s[i]=0;
      g[n]=type(s);
      if(g[n++]==-1)error=1;
  }
  if(error){
      puts("Bad!");
      continue;
  }
  g[n]=-2;
  for(pos=i=0;i<n;i++){
      if(g[i]==A){
          use[predstring]=1;
          if(!pos||(stack[pos-1]!=predstring&&stack[pos-1]!=preds)){
              error=1;
              break;
          }
          else stack[pos-1]=preds;
          stack[pos++]=A;
      }
      if(g[i]==MOD || g[i]==LA){
          use[g[i]]=1;
          stack[pos++]=g[i];
      }
      if(g[i]==BA){
          if(!pos || stack[pos-1]!=predname){
              error=1;
              break;
          }
          stack[pos++]=g[i];
      }
      if(g[i]==DA)
          stack[pos++]=g[i];
      if(g[i]==NAM)
          stack[pos++]=predname;
      if(g[i]==PREDA){
          if(!pos || stack[pos-1]!=predstring)
              stack[pos++]=predstring;
          if(pos>2 && stack[pos-3]==preds && stack[pos-2]==A &&
             g[i+1]!=PREDA)pos-=2;
          if(i==n-1 || (g[i+1]!=PREDA && g[i+1]!=A)){
              if(pos-3>=0&&stack[pos-3]==preds&&stack[pos-2]==A)
                  pos-=2;
              else if(pos>=2){
                  if(stack[pos-2]==LA)
                      stack[--pos-1]=predname;
                  else if(stack[pos-2]==MOD)
                      stack[--pos-1]=verbpred;
                  else if(stack[pos-2]==DA)
                      stack[--pos-1]=predclaim;
              }
              if(pos>=3&&stack[pos-3]==predname&&stack[pos-2]==BA
              &&(stack[pos-1]==predstring || stack[pos-1]==preds))
                  stack[(pos-=2)-1]=predclaim;
          }
      }
      if(pos){
          if(stack[pos-1]==verbpred && g[i+1]!=LA && g[i+1]!=NAM)
              stack[--pos-1]=statement;
          if(pos>=3 && stack[pos-3]==predname && stack[pos-2]==
             verbpred && stack[pos-1]==predname)
              stack[(pos-=2)-1]=statement;
      }
  }
  if(*stack==predclaim || *stack==statement)*stack=sentence;
  puts((!error && *stack==sentence && pos==1)?"Good":"Bad!");
  if(c=='#')return 0;
}
}
