#include <vcl.h>
#include <stdio.h>
int sort(char t)
{
        switch (t)
        {
        case '+':
        case '-':
                return 10;
        break;
        case '%':
                return 15;
        break;
        case '*':
        case '/':
                return 20;
        break;
        case '^':
                return 30;
        break;
        case '!':
                return 40;
        break;
        case 'a':
        case 'l':
        case 's':
        case 'c':
        case 't':
        case 'i':
        case 'q':
                return 50;
        break;
        case '(':
        case '[':
        case '{':
                return 100;
        break;
        }
        return 0;
}

int isnum(char t) //判斷是否為數字
{
        if( (t > 47 && t < 58) || t==46 ) //46='.'
                return 1;
        return 0;
}

AnsiString readnum(AnsiString str,int pos,int max) //從字串中讀出數字
{
        AnsiString t="";
	while(isnum(str[pos])==1)
        {
                t = t + str[pos] ;
                pos++;
                if(pos > max)
                        break;
	}
	return t;
}

AnsiString searchleftright(AnsiString t)
{
        int i,left=0,right=0;
        for(i=1;i<=t.Length();i++)
        {
                if(t[i]=='(' || t[i]=='[' || t[i]=='{')
                        left++;
                if(t[i]==')' || t[i]==']' || t[i]=='}')
                        right++;
                if(right==left)
                        break;
        }
        return t.SubString(2,i);
}
 