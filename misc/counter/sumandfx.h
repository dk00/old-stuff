//---------------------------------------------------------------------------

#ifndef sumandfxH
#define sumandfxH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tsumandfxbox : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *textstr;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TGroupBox *GroupBox1;
        TLabel *Label4;
        TEdit *tstep;
        TGroupBox *GroupBox2;
        TImage *Image1;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton3;
        TSaveDialog *SaveDialog1;
        TGroupBox *GroupBox3;
        TMemo *Memo1;
        TEdit *maxtext;
        TEdit *mintext;
        TLabel *Label2;
        TLabel *Label3;
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Tsumandfxbox(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tsumandfxbox *sumandfxbox;
//---------------------------------------------------------------------------
#endif
