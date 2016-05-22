#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<sstream>
using namespace std;
int n,sum;
int inv[130], par[130],count[130],vow[130],bit[130],trans[130];
int num[30][2],root[30][2],subl,vowl[]={'A','E','I','O','U'};
bool use[128];
int find(int x){
  if(par[x] != x){
    par[x] = find(par[x]);
  }
  return par[x];
}
bool uni(int a,int b){
  if(inv[a]!=a && find(inv[a]) == find(b) )
    return false;
  if(find(a) == find(b))
    return true;
  if(count[find(a)] < count[find(b)]){
    count[find(b)] += count[find(a)];
    par[find(a)] = find(b);
  }
  else{
    count[find(a)] += count[find(b)];
    par[find(b)] = find(a);
  }
  return true;
}
bool dfs(int x){
  if(x==n){
    if(sum==5)
      return true;
    else
      return false;
  }
  bit[x] = 0;
  sum += num[x][0];
  if(sum<=5 && dfs(x+1))
    return true;
  sum -= num[x][0];

  bit[x] = 1;
  sum+= num[x][1];
  if(sum<=5 && dfs(x+1))
    return true;
  sum -= num[x][1];
  return false;
}
int next(int isvow){
  if(isvow){
    for(int i=0;i<5;++i)
      if(!use[vowl[i]]){
        use[vowl[i]] = 1;
        return vowl[i];
      }
  }
  else{
    while(1){
      while(use[subl]){
        subl++;
      }
      bool isvow=0;
      for(int i=0;i<5;++i)
        if(vowl[i]==subl){
          isvow=1;
          break;
        }
      if(!isvow){
        use[subl]=1;
        return subl++;
      }
      else
        subl++;
    }
  }
}

string lines;

int main(void){
  bool ok;
  vector<string> word;
  vector<char> sep;
  string line,in;

  char c;
  bool appear[128];
  cin.sync_with_stdio(false);
  while(getline(cin, line)){
    vector<string> lineVector;
    word.clear();
    do{
      if(line.size()==0)
        break;
      lineVector.push_back(line);
      stringstream sin;
      sin.str(line);
      while(sin>>in)
        word.push_back(in);
    }while(getline(cin, line));
    //init
    memset(trans, 0 , sizeof(trans));
    memset(use, 0 , sizeof(use));
    memset(appear, 0, sizeof(appear));
    memset(vow, 0, sizeof(vow));
    memset(bit, 0, sizeof(bit));
    for(int i='A';i<='Z';++i){
      par[i] = i;
      inv[i] = i;
      count[i] = 1;
    }

    ok = true;
    for(int i=0;ok && i<word.size();++i){
      for(int j=1;j<word[i].size();++j){
        if(inv[word[i][j]] == word[i][j]){
          inv[word[i][j]] = word[i][j-1];
        }
        else{
          if(!uni(inv[word[i][j]], word[i][j-1]))
            ok = false;
        }
        if(inv[word[i][j-1]] == word[i][j-1]){
          inv[word[i][j-1]] = word[i][j];
        }
        else{
          if(!uni(inv[word[i][j-1]], word[i][j]))
            ok = false;
        }

        if(j>1){
          if(!uni(par[word[i][j]], par[word[i][j-2]]))
            ok = false;
        }
      }
    }
    if(!ok)
      cout<<"impossible"<<endl;
    else{
      n=0;
      for(int i='A';i<='Z';++i){
        if(!appear[find(i)]){
          num[n][0] = count[par[i]];
          root[n][0] = par[i];
          if(inv[i] == i){
            num[n][1] = 0;
            root[n][1] = 0;
          }
          else{
            num[n][1] = count[find(inv[i])];
            root[n][1] = find(inv[i]);
          }
          appear[par[i]] = 1;
          appear[find(inv[i])] = 1;
          ++n;
          //cout<<n-1<<" "<<num[n-1][0]<<" "<<num[n-1][1]<<endl;
        }
      }
      for(int i=0;i<n;++i){
        bit[i] = 0;
      }
      sum = 0;
      subl='B';
      if(dfs(0)){
        for(int i=0;i<n;++i){
          //cout<<bit[i]<<(char)root[i][bit[i]]<<" ";
          if(bit[i]){
            vow[root[i][1]]=1;
          }
          else
            vow[root[i][0]]=1;
        }
        for(int r=0;r<lineVector.size();++r){
          for(int i=0;i<lineVector[r].size();++i){
            if(isalpha(lineVector[r].at(i))){
              if(trans[lineVector[r].at(i)]==0)
                trans[lineVector[r].at(i)]= next(vow[par[lineVector[r].at(i)]]);           
              cout<<(char)trans[lineVector[r].at(i)];
            }else
              cout<<(char)lineVector[r].at(i);
          }
          cout << endl;
        }
        /*for(int i=0,k=0;i<word.size();++i){
          if(i!=0)
            cout<<" ";
          for(int j=0;j<word[i].size();++j){
            if(trans[word[i][j]]==0)
              trans[word[i][j]]= next(vow[par[word[i][j]]]);           
            cout<<(char)trans[word[i][j]];
          }
        }
        cout<<endl;*/
      }
      else{
        cout<<"impossible"<<endl;
      }
    }
  }
  return 0;
}
