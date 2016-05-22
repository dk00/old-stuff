//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class Tmainform : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TEdit *textstr;
        TGroupBox *GroupBox2;
        TEdit *tempstatus;
        TStatusBar *StatusBar1;
        TSpeedButton *c1;
        TSpeedButton *c2;
        TSpeedButton *c3;
        TSpeedButton *c4;
        TSpeedButton *c5;
        TSpeedButton *c6;
        TSpeedButton *c7;
        TSpeedButton *c8;
        TSpeedButton *c9;
        TSpeedButton *cplus;
        TSpeedButton *SpeedButton11;
        TSpeedButton *SpeedButton13;
        TSpeedButton *SpeedButton14;
        TSpeedButton *SpeedButton15;
        TSpeedButton *SpeedButton16;
        TSpeedButton *SpeedButton17;
        TSpeedButton *SpeedButton18;
        TSpeedButton *c0;
        TSpeedButton *cpoint;
        TSpeedButton *cce;
        TSpeedButton *SpeedButton24;
        TSpeedButton *SpeedButton25;
        TSpeedButton *SpeedButton26;
        TSpeedButton *cmplus;
        TSpeedButton *SpeedButton23;
        TSpeedButton *SpeedButton27;
        TSpeedButton *SpeedButton28;
        TSpeedButton *SpeedButton29;
        TSpeedButton *SpeedButton31;
        TSpeedButton *SpeedButton34;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton5;
        TMainMenu *MainMenu1;
        TMenuItem *T1;
        TMenuItem *N1;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N7;
        TSpeedButton *SpeedButton6;
        TEdit *Memoresult;
        TSpeedButton *SpeedButton19;
        TSpeedButton *SpeedButton7;
        TSpeedButton *SpeedButton8;
        void __fastcall ccloseClick(TObject *Sender);
        void __fastcall c1Click(TObject *Sender);
        void __fastcall c2Click(TObject *Sender);
        void __fastcall c3Click(TObject *Sender);
        void __fastcall c4Click(TObject *Sender);
        void __fastcall c5Click(TObject *Sender);
        void __fastcall c6Click(TObject *Sender);
        void __fastcall c7Click(TObject *Sender);
        void __fastcall c8Click(TObject *Sender);
        void __fastcall c9Click(TObject *Sender);
        void __fastcall c0Click(TObject *Sender);
        void __fastcall cpointClick(TObject *Sender);
        void __fastcall cceClick(TObject *Sender);
        void __fastcall cplusClick(TObject *Sender);
        void __fastcall SpeedButton15Click(TObject *Sender);
        void __fastcall SpeedButton16Click(TObject *Sender);
        void __fastcall SpeedButton11Click(TObject *Sender);
        void __fastcall SpeedButton14Click(TObject *Sender);
        void __fastcall SpeedButton18Click(TObject *Sender);
        void __fastcall SpeedButton24Click(TObject *Sender);
        void __fastcall SpeedButton26Click(TObject *Sender);
        void __fastcall SpeedButton13Click(TObject *Sender);
        void __fastcall SpeedButton17Click(TObject *Sender);
        void __fastcall SpeedButton25Click(TObject *Sender);
        void __fastcall cmplusClick(TObject *Sender);
        void __fastcall SpeedButton23Click(TObject *Sender);
        void __fastcall SpeedButton27Click(TObject *Sender);
        void __fastcall SpeedButton28Click(TObject *Sender);
        void __fastcall SpeedButton29Click(TObject *Sender);
        void __fastcall SpeedButton31Click(TObject *Sender);
        void __fastcall SpeedButton34Click(TObject *Sender);
        void __fastcall center(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall textstrKeyPress(TObject *Sender, char &Key);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
        void __fastcall SpeedButton7Click(TObject *Sender);
        void __fastcall SpeedButton8Click(TObject *Sender);
private:	// User declarations


public:		// User declarations
        //double float temper;
        __fastcall Tmainform(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tmainform *mainform;
//---------------------------------------------------------------------------
#endif
