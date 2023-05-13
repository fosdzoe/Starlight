//---------------------------------------------------------------------------

#ifndef mapH
#define mapH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "File1.h"
//#include "main.h"

#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMap : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TStatusBar *StatusBar1;
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
private:	// User declarations
public:

        
        //void __fastcall RysujNiebo(float De,float Re,int Ws,int i);
        void __fastcall RysujNiebo(Obiekt* wskNiebo,int r);
        void RysujDroge(Obiekt* wskNiebo,int* wskKolej,int Ilosc);
        void RysujPodzialke(void);
        __fastcall TFormMap(TComponent* Owner);
        
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMap *FormMap;
//---------------------------------------------------------------------------
#endif
