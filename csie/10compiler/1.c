#include<stdio.h>
typedef struct {
  const char str[9];
  unsigned code;
} Token;
const int kNumTokens = 40;
const char *kToken[] = {"*","+","-","/","%","&&","||","!","<",">","<=",">=","==","!=","&","|","^","(",")","[","]","{","}",",",";","=","char","int","void","if","else","while","for","continue","break","return"," ","\t","\n","\r"};
const unsigned kCode[] = {42,43,45,47,37,265,266,33,60,62,261,262,263,264,38,124,94,40,41,91,93,123,125,44,59,61,268,269,270,271,272,273,274,275,276,277,1,1,1,1};
enum TokenCode {
  SPACE = 1,
  IDENTIFIER = 258,
  INTEGER = 259,
  STRING = 260,
  COMMENT = 299
};

int state[999][256];

void Init() {
  int i,j,k,n = 300;
  const char kIdChars[]="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
  for(i = 0;kIdChars[i];i++) {
    state[0][kIdChars[i]] = state[IDENTIFIER][kIdChars[i]] = IDENTIFIER;
    for(j = 268; j <= 277;j++)
      state[j][kIdChars[i]] = IDENTIFIER;
  }

  k = state[0]['\"'] = n++;  
  for(i = 32;i < 127;i++)
    state[k][i] = state[n][i] = k;
  state[k]['\\'] = n++;
  state[k]['\"'] = STRING;

  for(i = 0;i < 10;i++)
    state[0][kIdChars[i]] = state[INTEGER][kIdChars[i]] = INTEGER;

  for (i = 0; i < kNumTokens; i++) {
    for (j = k = 0; kToken[i][j+1]; j++) {
      if(state[k][kToken[i][j]] == 0)
        state[k][kToken[i][j]] = n++;
      k = state[k][kToken[i][j]];
    }
    state[k][kToken[i][j]] = kCode[i];
  }

  state[state[0]['/']]['*'] = n;
  for(i = 0;i < 255;i++)
    state[n][i] = state[n+1][i] = n;
  state[n]['*'] = n + 1;
  state[n+1]['/'] = COMMENT;
  n+=2;
}

char buf[65536];
main(){
  Init();
  int k = 0, c, n;
  do {
    c = getchar();
    unsigned u = 255 & (unsigned)c;
    if (k > 0 && state[k][u] == 0) {
      if (k < 300 && k != COMMENT && k != SPACE) printf("%d",k);
      else if (k != COMMENT && k != SPACE) fprintf(stderr,"error");
      buf[n] = 0;
      if (k == IDENTIFIER)
        printf("\t%s",buf);
      if (k == INTEGER) {
        int tmp;
        sscanf(buf,"%d",&tmp);
        printf("\t0x%08x",tmp);
      }
      if (k == STRING) {
        int i;
        printf("\t");
        for (i = 1;i < n-1;i++) {
          if (buf[i] == '\\' &&(buf[i+1] == '\\' || buf[i+1]=='\"'))
            i++;
          putchar(buf[i]);
        }
      }
      if (k != COMMENT && k!=SPACE) puts("");
      k = n = 0;
    }
    if (c == EOF) break;
    buf[n++] = c;
    k = state[k][u];
    if (k == 0) {
      buf[n] = 0;
      fprintf(stderr,"error\t%s\n",buf);
      n = 0;
    }
  } while(c != EOF);
}
