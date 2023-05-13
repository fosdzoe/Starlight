//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("starlight.res");
USEFORM("main.cpp", FormMain);
USEUNIT("File1.cpp");
USEFORM("map.cpp", FormMap);
USEFORM("about.cpp", FormAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->ShowHint=true;
                 Application->HintPause = 2000;
                 Application->HintHidePause = 5000;
                 Application->CreateForm(__classid(TFormMain), &FormMain);
                 Application->CreateForm(__classid(TFormMap), &FormMap);
                 Application->CreateForm(__classid(TFormAbout), &FormAbout);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
