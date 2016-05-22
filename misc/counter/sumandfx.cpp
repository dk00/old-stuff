//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "sumandfx.h"
#include "midtofin.cpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tsumandfxbox *sumandfxbox;
//---------------------------------------------------------------------------
__fastcall Tsumandfxbox::Tsumandfxbox(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall Tsumandfxbox::SpeedButton4Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall Tsumandfxbox::SpeedButton1Click(TObject *Sender)
{
        int isword(char a);
        AnsiString instead(AnsiString t,double i);
        double step=StrToFloat(tstep->Text);
        double i;
              //分析字串
        AnsiString a=textstr->Text;
        for(i=1;i<a.Length();i++)
        {
                if(isnum(a[i]) && isnum(a[i+1])==0 && a[i+1]!=' ')
                        a.Insert(" ",i+1);
                if(isnum(a[i])==0 && isnum(a[i+1])==0 && isword(a[i]) &&  isword(a[i+1])){
                        a.Insert(" ",i+1);
                }
        }
        textstr->Text=a;
        //over

        //Sum
        double result=0;
        double min=StrToFloat(mintext->Text);
        double max=StrToFloat(maxtext->Text);
        for(i=min;i <= max; i=i+step)
        {

                result=result+  midtofin(instead(textstr->Text,i));
        }
        Memo1->Lines->Add("結果:"+FloatToStr(result));
}
//---------------------------------------------------------------------------
int isword(char a)
{
        if(a=='%' || a=='+' || a=='-' || a=='*' || a=='/' || a=='!' || a=='%' || a=='^' || a=='(' || a=='[' || a=='{' || a==')' || a==']' || a=='}')
                return 1;
        return 0;
}

AnsiString instead(AnsiString t,double i)
{
        int j;
        for(j=1;j<=t.Length();j++)
        {
                if(t[j]=='x')
                {
                        t.Delete(j,1);
                        t.Insert(FloatToStr(i),j);
                }
        }
        return t;

}
//---------------------------------------------------------------------------

void __fastcall Tsumandfxbox::SpeedButton2Click(TObject *Sender)
{
       int isword(char a);
        AnsiString instead(AnsiString t,double i);
        double min=StrToFloat(mintext->Text);
        double max=StrToFloat(maxtext->Text);
        double step=StrToFloat(tstep->Text);
        double i;
              //分析字串
        AnsiString a=textstr->Text;
        for(i=1;i<a.Length();i++)
        {
                if(isnum(a[i]) && isnum(a[i+1])==0 && a[i+1]!=' ')
                        a.Insert(" ",i+1);
                if(isnum(a[i])==0 && isnum(a[i+1])==0 && isword(a[i]) &&  isword(a[i+1])){
                        a.Insert(" ",i+1);
                }
        }
        textstr->Text=a;
        //over

        //青空
        Image1->Canvas->Brush->Color=clWhite;
        Image1->Canvas->FillRect(Rect(0,0,264,264));
        //十字線
        Image1->Canvas->Pen->Width=1;
        Image1->Canvas->Pen->Color=clRed;
        //橫
        Image1->Canvas->MoveTo(0,132);
        Image1->Canvas->LineTo(264,132);
        //縱
        Image1->Canvas->MoveTo(132,0);
        Image1->Canvas->LineTo(132,264);
        //初始化
        Image1->Canvas->Pen->Color=clBlack;
        Image1->Canvas->Pen->Width=1;
        double result=0,result2=0;
        result=  midtofin(instead(textstr->Text,min));
        result2=result;
        for(i=-140;i < 132; i++)
        {
                result=  midtofin(instead(textstr->Text,i));
                if(Image1->Height-((result)+132) <= Image1->Height && Image1->Height-((result)+132) >= -20)
                {
                        Image1->Canvas->MoveTo(i+132-1,Image1->Height-((result2)+132));
                        Image1->Canvas->LineTo(i+132,Image1->Height-((result)+132));
                }
                result2=result;
        }

}
//---------------------------------------------------------------------------

void __fastcall Tsumandfxbox::SpeedButton3Click(TObject *Sender)
{
        //Save picture
        if(SaveDialog1->Execute())
        {
                Image1->Picture->SaveToFile(SaveDialog1->FileName);
        }
}
//---------------------------------------------------------------------------


