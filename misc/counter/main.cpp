//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "midtofin.cpp"
#include "main.h"
#include "sumandfx.h"
#include "about.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

float tempm=0;
Tmainform *mainform;
//---------------------------------------------------------------------------
__fastcall Tmainform::Tmainform(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tmainform::ccloseClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------



void __fastcall Tmainform::c1Click(TObject *Sender)
{
        textstr->SelText="1";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::c2Click(TObject *Sender)
{
        textstr->SelText="2";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::c3Click(TObject *Sender)
{
        textstr->SelText="3";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::c4Click(TObject *Sender)
{
        textstr->SelText="4";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::c5Click(TObject *Sender)
{
        textstr->SelText="5";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::c6Click(TObject *Sender)
{
        textstr->SelText="6";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::c7Click(TObject *Sender)
{
        textstr->SelText="7";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::c8Click(TObject *Sender)
{
        textstr->SelText="8";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::c9Click(TObject *Sender)
{
        textstr->SelText="9";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::c0Click(TObject *Sender)
{
        textstr->SelText="0";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::cpointClick(TObject *Sender)
{
        textstr->SelText=".";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::cceClick(TObject *Sender)
{
        textstr->Text="";      
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::cplusClick(TObject *Sender)
{
        textstr->SelText="+";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton15Click(TObject *Sender)
{
        textstr->SelText="-";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton16Click(TObject *Sender)
{
        textstr->SelText="*";
}
//---------------------------------------------------------------------------


void __fastcall Tmainform::SpeedButton11Click(TObject *Sender)
{
        textstr->SelText="/";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton14Click(TObject *Sender)
{
        textstr->SelText="^";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton18Click(TObject *Sender)
{
        textstr->SelText="cos(";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton24Click(TObject *Sender)
{
        textstr->SelText="log(";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton26Click(TObject *Sender)
{
        textstr->SelText="!";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton13Click(TObject *Sender)
{
        textstr->SelText="sin(";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton17Click(TObject *Sender)
{
        textstr->SelText="sqr(";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton25Click(TObject *Sender)
{
        textstr->SelText="tan(";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::cmplusClick(TObject *Sender)
{
        tempm+=StrToFloat(textstr->Text);
        tempstatus->Text=FloatToStr(tempm);
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton23Click(TObject *Sender)
{
        tempm-=StrToFloat(textstr->Text);
        tempstatus->Text=FloatToStr(tempm);
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton27Click(TObject *Sender)
{
        textstr->Text=FloatToStr(tempm);
        Memoresult->Text="暫存變數值:"+FloatToStr(tempm)+"\r\n";
        tempstatus->Text=FloatToStr(tempm);
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton28Click(TObject *Sender)
{
 tempm=0;
 tempstatus->Text=FloatToStr(tempm);       
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton29Click(TObject *Sender)
{
        textstr->SelText="3.14159265358979";        
}
//---------------------------------------------------------------------------


void __fastcall Tmainform::SpeedButton31Click(TObject *Sender)
{
textstr->SelText="(";        
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton34Click(TObject *Sender)
{
textstr->SelText=")";        
}
//---------------------------------------------------------------------------
int isword(char a)
{
        if(a=='%' || a=='+' || a=='-' || a=='*' || a=='/' || a=='!' || a=='%' || a=='^' || a=='(' || a=='[' || a=='{' || a==')' || a==']' || a=='}')
                return 1;
        return 0;
}

void __fastcall Tmainform::center(TObject *Sender)
{
        //分析字串
        AnsiString a=textstr->Text.LowerCase(); //轉小寫
        int i;
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

        AnsiString result=FloatToStr(midtofin(textstr->Text));
        Memoresult->Text="計算結果 : "+result;
        textstr->SelStart=0;
        textstr->SelLength=textstr->Text.Length();
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::FormCreate(TObject *Sender)
{
        start();
        //初始化動態堆疊
}
//---------------------------------------------------------------------------


void __fastcall Tmainform::SpeedButton1Click(TObject *Sender)
{
        textstr->SelText="exp(";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::FormClose(TObject *Sender, TCloseAction &Action)
{
        free(hp);
        free(hp2);
}
//---------------------------------------------------------------------------


void __fastcall Tmainform::SpeedButton2Click(TObject *Sender)
{
textstr->SelText="[";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton3Click(TObject *Sender)
{
textstr->SelText="]";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton5Click(TObject *Sender)
{
textstr->SelText="{";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton4Click(TObject *Sender)
{
textstr->SelText="}";
}
//---------------------------------------------------------------------------


void __fastcall Tmainform::textstrKeyPress(TObject *Sender, char &Key)
{
        if(Key==13)
        {
                center(this);
                Key=0;
        }

}
//---------------------------------------------------------------------------


void __fastcall Tmainform::N4Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::N1Click(TObject *Sender)
{
        sumandfxbox->Show();
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::N7Click(TObject *Sender)
{
        aboutbox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::N6Click(TObject *Sender)
{
    AnsiString exepath = Application->ExeName;
    exepath.SetLength(exepath.Length()-11);
    AnsiString exepath2=exepath+"index.htm";
    ShellExecute(0,0,exepath2.c_str(),"","",1);
}
//---------------------------------------------------------------------------


void __fastcall Tmainform::SpeedButton6Click(TObject *Sender)
{
        textstr->SelText="%";
}
//---------------------------------------------------------------------------
void __fastcall Tmainform::SpeedButton7Click(TObject *Sender)
{
        textstr->SelText="ceil(";
}
//---------------------------------------------------------------------------

void __fastcall Tmainform::SpeedButton8Click(TObject *Sender)
{
        textstr->SelText="abs(";
}
//---------------------------------------------------------------------------

