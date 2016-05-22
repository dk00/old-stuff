#include "MOVESTAC.CPP"  //stack struct
#include "dealword.cpp"
stackmodel *hp ;
stackmodel *hp2;
void start() //初始化
{
        hp = createstack();
        hp2= createstack();
}

long double countresult()
{
        long double stair(int t);
        long double radian(long double t);
        stack *t,*sel;
        long double n1,n2;
                sel=out(hp);
                if (sel->index=='+' || sel->index=='*' || sel->index=='/' || sel->index=='^' || sel->index=='%' || sel->index=='-')
                {
                        t=out(hp);
                        if(t->index != 0 )
                        {
                                add(hp,t->value,t->index);
                                n1=countresult();
                        }
                        else
                                n1=t->value;
                        t=out(hp);
                        if(t->index != 0){
                                add(hp,t->value,t->index);
                                n2=countresult();
                        }
                        else
                                {n2=t->value;}
                        if(sel->index=='+')
                                return n2+n1;
                        else if(sel->index=='-')
                                return n2-n1;
                        else if(sel->index=='*')
                                return n2*n1;
                        else if(sel->index=='/')
                                return n2/n1;
                        else if(sel->index=='^')
                                return powl(n2,n1);
                        else if(sel->index=='%')
                        {
                                int tn1=(__int64)n1,tn2=(__int64)n2;
                                return tn2 % tn1;
                        }
                }
                else if (sel->index=='!' || sel->index=='l' || sel->index=='s'
                || sel->index=='c' || sel->index=='t' || sel->index=='e'
                || sel->index=='i' || sel->index=='a' || sel->index=='q')//階乘,log,sin,cos,tan,ceil
                {
                        t=out(hp);
                        if(t->index != 0 )
                        {
                                add(hp,t->value,t->index);
                                n1=countresult();
                        }
                        else
                        n1=t->value;
                        if(sel->index=='!')
                                return stair((__int64)n1);
                        else if(sel->index=='l')
                                return log10l(n1);
                        else if(sel->index=='s')
                                return sinl(radian(n1));
                        else if(sel->index=='c')
                                return cosl(radian(n1));
                        else if(sel->index=='t')
                                return tanl(radian(n1));
                        else if(sel->index=='e')
                                return expl(n1);
                        else if(sel->index=='i')
                                return ceill(n1);
                        else if(sel->index=='a')
                                return fabsl(n1);
                        else if(sel->index=='q')
                                return powl(n1,0.5);
                }
        return sel->value;
}
//AnsiString midtofin(AnsiString textStr)
long double midtofin(AnsiString textStr)
{
        int sort(char t);
        int isnum(char t);
        long double countresult();
        AnsiString readnum(AnsiString str,int pos,int max);
        AnsiString searchleftright(AnsiString t);
        stack *t,*now;
	int pos=1,lastindex=0,posindex;
        long double t2;
        bool lastbool=0; //0表示上一個處理的是符號或無
        //1表示上一個處理的是數字
        //posindex紀錄上一個index的大小
        //index為運算之優先順序.越大越前面
        //中序轉後續
	while(pos<=textStr.Length())
	{
		if( isnum(textStr[pos]) ) // is common number
		{
			t2=StrToFloat(readnum(textStr,pos,textStr.Length()));
                        add(hp,t2,0);
			pos+=FloatToStr(t2).Length();
                        lastbool=1;
                        continue;
		}
		else      //符號
		{
			if(textStr[pos]=='+')
				posindex=10;
                        else if(textStr[pos]=='-')
                        {
                                if(lastbool==0) //上一個是空or符號
                                {
                                        do
                                        {
                                                pos++;
                                        }while(isnum(textStr[pos])==0);
                                        t2=StrToFloat(readnum(textStr,pos,textStr.Length()));
                                        add(hp,-t2,0); //負數
			                pos+=FloatToStr(t2).Length();
                                        lastbool=1;
                                        continue;
                                }
                                posindex=10;
                        }
                        else if(textStr[pos]=='%')
                                posindex=15;
                        else if(textStr[pos]=='*' || textStr[pos]=='/')
				posindex=20;
			else if(textStr[pos]=='^')
				posindex=30;
			else if(textStr[pos]=='!')
				posindex=40;
                        else if(textStr.SubString(pos,3)=="log" ||
                        textStr.SubString(pos,3)=="sin" ||
                        textStr.SubString(pos,3)=="cos" ||
                        textStr.SubString(pos,3)=="tan" ||
                        textStr.SubString(pos,3)=="exp" ||
                        textStr.SubString(pos,3)=="abs" )
                                posindex=50;
                        else if(textStr.SubString(pos,4)=="ceil")
                        {
                                posindex=50;
                                pos=pos+2;
                        }
                        else if(textStr.SubString(pos,3)=="sqr")
                        {
                                posindex=50;
                                pos=pos+1;
                        }
                        else if(textStr[pos]=='(' || textStr[pos]=='[' || textStr[pos]=='{')
                        {
                                AnsiString tstring=searchleftright(textStr.SubString(pos,textStr.Length()-pos+1));
                                add(hp2,0,'(');
                                add(hp,midtofin(tstring),0);
                                pos=pos+tstring.Length();
                                lastbool=1;
                                continue;
			}
                        else
                        {
                                posindex=0;
                                textStr.Delete(pos,1);
                                continue;
                        }
                        t=out(hp2);
			while(lastindex >= posindex) //若上一個index大於等於等於目前的index
			{
                                if(sort(t->index)==100)
                                        break;
                                if(sort(t->index)!=0)
                                {
				add(hp,t->value,t->index);
                                t=out(hp2);
                                lastindex=sort(t->index);
                                }
                                else
                                        break;

			}
                        if(t->index!=0)
                                add(hp2,t->value,t->index);
                        add(hp2,0,textStr[pos]);
                        lastindex=posindex;
                        lastbool=0;
		}
                pos++;
	}
        //把hp2的東西全加到hp
        t=out(hp2);
        while(t->value!=0 || t->index!=0 )
        {
                if(sort(t->index)==100)
                {
                        t=out(hp2);
                        continue;
                }
                add(hp,t->value,t->index);
                t=out(hp2);
        }
        return countresult();
}


long double stair(int t)
{
        int i;
        long double result=1;
        for(i=2;i<=t;i++)
                result=result*i;
        return result;
}

long double radian(long double t)
{
        long double pi=3.14159265358979;
        return t*pi/180;
}























