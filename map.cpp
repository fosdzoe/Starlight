//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop


#include "map.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMap *FormMap;
//---------------------------------------------------------------------------
__fastcall TFormMap::TFormMap(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

//void __fastcall TFormMap::RysujNiebo(float De,float Re,int Ws,int i)
void __fastcall TFormMap::RysujNiebo(Obiekt* wskNiebo,int r)
{
        int i,PodzialkaDekl,PodzialkaRekt,ZeroDekl,ZeroRekt;
        int x1,x2,y1,y2;



        PodzialkaDekl=floor(270/90);
        PodzialkaRekt=floor(600/24);
        ZeroDekl=278;
        ZeroRekt=40;
        //while ((l==1) && (j<r))
        for(i=0;i<r;i++)
        {
                x1=ZeroRekt+wskNiebo[i].Rektascencja*PodzialkaRekt;
                y1=ZeroDekl-wskNiebo[i].Deklinacja*PodzialkaDekl;
                x2=x1+5;
                y2=y1+5;
                
                if(wskNiebo[i].Wsp==0)
                {
                        Image1->Canvas->Pen->Color=clWhite;
                        Image1->Canvas->Brush->Color=clWhite;
                }
                if(wskNiebo[i].Wsp==1)
                {
                        Image1->Canvas->Pen->Color=clYellow;
                        Image1->Canvas->Brush->Color=clYellow;
                }
                if(wskNiebo[i].Wsp==2)
                {
                        Image1->Canvas->Pen->Color=clRed;
                        Image1->Canvas->Brush->Color=clRed;
                }
                
                if(i<10) Image1->Canvas->TextOutA(x1-10,y1-5,IntToStr(i));
                if(i>=10 && i<100) Image1->Canvas->TextOutA(x1-20,y1-5,IntToStr(i));
                if(i>100) Image1->Canvas->TextOutA(x1-30,y1-5,IntToStr(i));

                Image1->Canvas->Ellipse(x1,y1,x2,y2);
                //if(Niebo.OdczytTabela(j)==Niebo.Ost) i=0;
                //j++;
        }

};
//--------------------------------------------------------------------------
void TFormMap::RysujDroge(Obiekt* wskNiebo,int* wskKolej,int Ilosc)
{
        int i,PodzialkaDekl,PodzialkaRekt,ZeroDekl,ZeroRekt;
        int x1,x2,y1,y2;

        PodzialkaDekl=floor(270/90);
        PodzialkaRekt=floor(600/24);
        ZeroDekl=278;
        ZeroRekt=40;

        
        for (i=0;i<(Ilosc-1);i++)
        {

                x1=ZeroRekt+wskNiebo[wskKolej[i]].Rektascencja*PodzialkaRekt+3;
                y1=ZeroDekl-wskNiebo[wskKolej[i]].Deklinacja*PodzialkaDekl+3;
                x2=ZeroRekt+wskNiebo[wskKolej[i+1]].Rektascencja*PodzialkaRekt+3;
                y2=ZeroDekl-wskNiebo[wskKolej[i+1]].Deklinacja*PodzialkaDekl+3;
                if (i==0)
                {
                       Image1->Canvas->Pen->Color=clGreen;
                       Image1->Canvas->Brush->Color=clBlack;
                       Image1->Canvas->Ellipse(x1-4,y1-4,x1+4,y1+4);
                       Image1->Canvas->Ellipse(x1-3,y1-3,x1+3,y1+3);
                       Image1->Canvas->Ellipse(x1-2,y1-2,x1+2,y1+2);

                }
                if (i==(Ilosc-2))
                {
                       Image1->Canvas->Pen->Color=clBlue;
                       Image1->Canvas->Brush->Color=clBlack;
                       Image1->Canvas->Ellipse(x2-4,y2-4,x2+4,y2+4);
                       Image1->Canvas->Ellipse(x2-3,y2-3,x2+3,y2+3);
                       Image1->Canvas->Ellipse(x2-2,y2-2,x2+2,y2+2);


                }
                Image1->Canvas->Pen->Color=clBlue;
                Image1->Canvas->Brush->Color=clBlack;
                Image1->Canvas->MoveTo(x1,y1);
                Image1->Canvas->LineTo(x2,y2);
        }
        

};
//--------------------------------------------------------------------------
void TFormMap::RysujPodzialke()
{
        int i;


        Image1->Canvas->Pen->Color=clBlack;
        Image1->Canvas->Brush->Color=clBlack;
        Image1->Canvas->Rectangle(40,8,640,278);
        //Image1->Canvas->Pen->Color=clBlack;
        Image1->Canvas->Brush->Color=clWhite;
        for (i=0;i<10;i++)
        {
                Image1->Canvas->MoveTo(40-10,8+i*30);
                Image1->Canvas->LineTo(40,8+i*30);
                Image1->Canvas->TextOutA(40-20,8+(i*30)-2,IntToStr(90-i*10));
        }
        for (i=0;i<13;i++)
        {
                Image1->Canvas->MoveTo(40+i*50,278+10);
                Image1->Canvas->LineTo(40+i*50,278);
                Image1->Canvas->TextOutA(40+(i*50)-2,278+15,IntToStr(0+i*2));
        }
        

};
//-----------------------------------------------------------------------------
void __fastcall TFormMap::Image1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
         float PodzialkaDekl,PodzialkaRekt;


        PodzialkaDekl=270/90;
        PodzialkaRekt=600/24;
        if ((X>=40) && (X<=640)
                && (Y>=8) && (Y<=278))
       // {
                StatusBar1->SimpleText="Wspó³rzêdne: <Rektascencja-"
                                +FormatFloat("00.00",(X-40)/PodzialkaRekt)
                                + " h : Deklinacja-"
                                + FormatFloat("00.00",90-(Y-8)/PodzialkaDekl)+" >";
                                //+ " COLOR "+Format("#%.2x%.2x%.2x", args, 3);

        ///}
}
//---------------------------------------------------------------------------

