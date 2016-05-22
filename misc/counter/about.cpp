//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "about.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Taboutbox *aboutbox;
//---------------------------------------------------------------------------
__fastcall Taboutbox::Taboutbox(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall Taboutbox::Button1Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------
void __fastcall Taboutbox::Button2Click(TObject *Sender)
{
        ShellExecute(0,0,"mailto:j741119@ethome.net.tw","","",1);        
}
//---------------------------------------------------------------------------
void __fastcall Taboutbox::Button3Click(TObject *Sender)
{
        ShellExecute(0,0,"http://www.tacocity.com.tw/jmmj","","",1);        
}
//---------------------------------------------------------------------------
