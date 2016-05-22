/*
Q10004 Bicoloring
基本想法:
    1.只有兩種顏色，而且相鄰的點顏色必須不同，所以確定一個點的顏色之後
    和他相鄰的點就填上另一種顏色。
    2.對於所有的解法，把兩種顏色換過來之後，也是可用的解，這表示我們
    第一個選的點，顏色並不重要。
*/
#include<stdio.h>
int n,v[200],c[200][200];
/*
note:
    遇到已經走過的點，只要判斷顏色對不對即可，不用再向下搜尋，
    這個時候可以用 return 結束這個 function。
    沒有走過的點則標上顏色，再往下搜。
*/
int dfs(int s,int color)    // 如果可以的話回傳 1, 否則 0
{
    if(v[s])                 // v[s] 不是 0, 表示已經著色了
    {
        if(v[s]==color)return 1; // 如果他的顏色和現在要用的顏色一樣
        return 0;                // 就表示可以，否則不行
    }                            // 這個點已經走過了，所以不用再走下去
    v[s]=color;                  // 標顏色
    for(int i=0;i<n;i++)
        if(c[s][i]==1)           // 以另一種顏色在相鄰的點著色
            if(dfs(i,-color)==0) // 如果不行的話就回傳 0
                return 0;
   return 1;    //如果都可以的話回傳 1
}
main()
{
    int i,j,m;
    while(scanf("%d %d",&n,&m) && n)
    {
        for(i=0;i<n;i++)         // 這裡先把所有的數值歸零
        {
            v[i]=0;              // v[i]代表點 i 的顏色，0 表示尚未著色
            for(j=0;j<n;j++)     // 1, -1 代表兩種不同的顏色
                c[i][j]=0;       // c[i][j] 代表 i,j 之間是否有邊存在
        }                        // 1 -> 有, 0 -> 無
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i][j]=c[j][i]=1;
        }
        if(dfs(0,1))puts("BICOLORABLE.");
        else puts("NOT BICOLORABLE.");
    }
}
