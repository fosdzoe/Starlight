//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "about.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAbout *FormAbout;
//---------------------------------------------------------------------------
__fastcall TFormAbout::TFormAbout(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormAbout::Button2Click(TObject *Sender)
{
FormAbout->Close();        
}
//---------------------------------------------------------------------------
