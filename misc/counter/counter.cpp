//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("counter.res");
USEFORM("main.cpp", mainform);
USEUNIT("midtofin.cpp");
USEUNIT("MOVESTAC.cpp");
USEFORM("sumandfx.cpp", sumandfxbox);
USEFORM("about.cpp", aboutbox);
USEUNIT("dealword.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(Tmainform), &mainform);
                 Application->CreateForm(__classid(Tsumandfxbox), &sumandfxbox);
                 Application->CreateForm(__classid(Taboutbox), &aboutbox);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
