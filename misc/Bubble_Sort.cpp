//希望三種排序都能看一看,然後寫一寫,增加對 C 語法的熟悉度
//也可以訓練對迴圈的使用,能夠寫到 3 分鐘一種排序是最好的
//以後的話,只要會三種之中的一個就可以了

/*
氣泡排序 (Bubble Sort)

演算法:
s[0] 與 s[1] 比較,把大的放到 s[1];
s[1] 與 s[2] 比較,把大的放到 s[2];
s[2] 與 s[3] 比較,把大的放到 s[3];
......不斷重覆......
s[n-1] 與 s[n] 比,把大的放到 s[n];
這個時候可以確定:最大最大的值已經放到 s[n] 中了.
我們如果再做一定上面的步驟,可以再把次大的放到 s[n-1] 裡面,
而總共有 n 個數要排序,所以這些步聚必須重覆 n 次.

重覆 n 次:  i 迴圈
交換的步驟: j 迴圈
*/
#include <stdio.h>
main(){
    int i,j,t,n,s[1000];
    while(1){
        printf("請輸入有幾個數字要排序(Sort): ");
        if(scanf("%d",&n)==EOF)         //n 是將有幾個數字要排序,CTRL+Z 可以跳出
            break;
        printf("請輸入 %d 個數字: ",n);
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);          //這裡要輸入 n 個數字等一下要排序用的
        for(i=0;i<n;i++)
            for(j=1;j<n;j++)            //兩層迴圈進行氣泡排序
                if(s[j]<s[j-1]){        //如果前面的小於後面的,就交換
                    t=s[j];             //交換:詳見最下方
                    s[j]=s[j-1];
                    s[j-1]=t;
                }
        for(i=0;i<n;i++)
            printf("%d ",s[i]);
        puts("");                       //puts("") 意思等於 printf("\n") 就是換行
    }
}
/*
關於交換 a 和 b,我們必須用一個臨時變數 (t) 來幫忙,
1) t=a  2) a=b  3) b=t(=之前的 a)
如果沒有先令 t=a 的話,在第二步 a=b 時,a 的值就永遠沒有人知道是多少了,
舉個例,a=10,b=20,現在要把 a 和 b 交換:
1) t=a=10 ==> t=10
2) a=b=20 ==> a=20
3) b=t=10 ==> b=10
完成後的結果是 a=20,b=10,兩者成功交換了.
*/

/*
再來請大家看一下程式的結構,裡面會故意的去空白,
這是為了方便閱讀而做的事,一開始我也是不知道哪裡該空哪裡不空,
但後來會慢慢了解,習慣之後,看程式真的清楚許多,
現在以上面的 Code 舉例說明哪裡要空白 (空白可按 TAB 鍵):

1) 一開始是全部沒有空白的情況

#include <stdio.h>
main(){
int i,j,t,n,s[1000];
while(1){
printf("請輸入有幾個數字要排序(Sort): ");
if(scanf("%d",&n)==EOF)
break;
printf("請輸入 %d 個數字: ",n);
for(i=0;i<n;i++)
scanf("%d",&s[i]); 
for(i=0;i<n;i++)
for(j=1;j<n;j++)
if(s[j]<s[j-1]){
t=s[j];
s[j]=s[j-1];
s[j-1]=t;
}
for(i=0;i<n;i++)
printf("%d ",s[i]);
puts("");
}
}

2) 我們先發現,所有的程式,都是在 main(){...} 之中,所以把裡面的東西往內縮

#include <stdio.h>
main(){
    int i,j,t,n,s[1000];
    while(1){
    printf("請輸入有幾個數字要排序(Sort): ");
    if(scanf("%d",&n)==EOF)
    break;
    printf("請輸入 %d 個數字: ",n);
    for(i=0;i<n;i++)
    scanf("%d",&s[i]);
    for(i=0;i<n;i++)
    for(j=1;j<n;j++)
    if(s[j]<s[j-1]){
    t=s[j];
    s[j]=s[j-1];
    s[j-1]=t;
    }
    for(i=0;i<n;i++)
    printf("%d ",s[i]);
    puts("");
    }
}

3) 再發現大部分的程式是在 while(1){...} 裡面,於是再把裡面的往內縮

#include <stdio.h>
main(){
    int i,j,t,n,s[1000];
    while(1){
        printf("請輸入有幾個數字要排序(Sort): ");
        if(scanf("%d",&n)==EOF)
        break;
        printf("請輸入 %d 個數字: ",n);
        for(i=0;i<n;i++)
        scanf("%d",&s[i]);
        for(i=0;i<n;i++)
        for(j=1;j<n;j++)
        if(s[j]<s[j-1]){
        t=s[j];
        s[j]=s[j-1];
        s[j-1]=t;
        }
        for(i=0;i<n;i++)
        printf("%d ",s[i]);
        puts("");
    }
}

4) break; 這一行是屬於 if(...) 的,所以向內縮
   scanf("%d",&s[i]); 屬於 for 迴圈,也往內縮
   最下面的 printf("%d ",s[i]); 同理的向內縮

#include <stdio.h>
main(){
    int i,j,t,n,s[1000];
    while(1){
        printf("請輸入有幾個數字要排序(Sort): ");
        if(scanf("%d",&n)==EOF)
            break;
        printf("請輸入 %d 個數字: ",n);
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        for(i=0;i<n;i++)
        for(j=1;j<n;j++)
        if(s[j]<s[j-1]){
        t=s[j];
        s[j]=s[j-1];
        s[j-1]=t;
        }
        for(i=0;i<n;i++)
            printf("%d ",s[i]);
        puts("");
    }
}

5) 最後我們處理這一塊比較複雜的:
        for(i=0;i<n;i++)
        for(j=1;j<n;j++)
        if(s[j]<s[j-1]){
        t=s[j];
        s[j]=s[j-1];
        s[j-1]=t;
        }
   這裡是兩個 for 疊在一起,再加一個 if,
   意思是這樣: if 屬於第二個 for,而第二個 for 又屬於第一個 for
   那就可以轉換啦:
        for(i=0;i<n;i++)
            for(j=1;j<n;j++)
                if(s[j]<s[j-1]){
                    t=s[j];
                    s[j]=s[j-1];
                    s[j-1]=t;
                }
                
6) 就是這樣而已,這很重要,非~非~非常重要!
   建議大家可以把另外兩份 Code 的縮排刪掉,然後自己試試看...
