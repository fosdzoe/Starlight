//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Dialogs.hpp>
#include <jpeg.hpp>
#include <TeeFunci.hpp>
#include <FileCtrl.hpp>



//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TButton *ButtonClear;
        TMainMenu *MainMenu1;
        TMenuItem *Plik1;
        TStatusBar *StatusBar1;
        TCoolBar *CoolBar1;
        TToolBar *ToolBar1;
        TTabSheet *TabSheet1;
        TGroupBox *GroupBox1;
        TLabel *Label3;
        TEdit *EditIle;
        TButton *ButtonLosuj;
        TListBox *ListBox1;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox2;
        TButton *ButtonMacierz;
        TMemo *Memo1;
        TTabSheet *TabSheet3;
        TRadioGroup *RadioGroup1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TButton *ButtonRozwStart;
        TLabel *Label1;
        TListBox *ListBox4;
        TListBox *ListBox5;
        TTabSheet *TabSheet4;
        TGroupBox *GroupBox3;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit4;
        TEdit *Edit5;
        TEdit *Edit6;
        TButton *ButtonGo;
        TUpDown *UpDown1;
        TUpDown *UpDown2;
        TBevel *Bevel1;
        TImage *Image1;
        TTreeView *TreeView1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TToolButton *ToolButton6;
        TToolButton *ToolButton7;
        TImageList *ImageList1;
        TToolButton *ToolButton5;
        TToolButton *ToolButton8;
        TGroupBox *GroupBox4;
        TPageControl *PageControl1;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label4;
        TGroupBox *GroupBox5;
        TChart *Chart1;
        TPieSeries *Series1;
        TCheckBox *CheckBoxMin;
        TCheckBox *CheckBoxMax;
        TGroupBox *GroupBox6;
        TChart *Chart2;
        TBarSeries *Series2;
        TLabel *Label7;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label19;
        TLabel *Label20;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label23;
        TCheckBox *CheckBoxCzasy;
        TCheckBox *CheckBoxRozmiary;
        TButton *ButtonRozwPor;
        TListBox *ListBox7;
        TListBox *ListBox8;
        TGroupBox *GroupBox7;
        TLabel *Label2;
        TLabel *Label25;
        TLabel *Label26;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TLabel *Label27;
        TLabel *Label28;
        TLabel *Label29;
        TLabel *Label30;
        TLabel *Label31;
        TLabel *Label32;
        TLabel *Label33;
        TLabel *Label34;
        TLabel *Label35;
        TLabel *Label36;
        TLabel *Label37;
        TLabel *Label38;
        TLabel *Label39;
        TLabel *Label40;
        TLabel *Label41;
        TLabel *Label42;
        TEdit *Edit7;
        TStaticText *StaticText1;
        TSaveDialog *SaveDialog1;
        TOpenDialog *OpenDialog1;
        TListBox *ListBox10;
        TLabel *Label44;
        TLabel *Label18;
        TEdit *Edit1;
        TLabel *Label24;
        TCheckBox *CheckBox1;
        TMenuItem *Nowy1;
        TMenuItem *Otwrz1;
        TMenuItem *Zapiszniebo1;
        TMenuItem *Wyczy1;
        TMenuItem *Edycja1;
        TMenuItem *Opcje1;
        TMenuItem *Pomoc1;
        TMenuItem *ZobaczplikPomocy1;
        TMenuItem *Oprogramie1;
        TMenuItem *Auto1;
        TMenuItem *Losujgwiazdy1;
        TMenuItem *Twrzmacierz1;
        TMenuItem *Rozwizaniestartowe1;
        TMenuItem *Porwnajrozwstartowe1;
        TMenuItem *Wyzarzanie1;
        TMenuItem *Zapiszobraznieba1;
        TToolButton *ToolButton9;
        TGroupBox *GroupBox8;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton5;
        TGroupBox *GroupBox9;
        TChart *Chart3;
        TLineSeries *Series3;
        TAddTeeFunction *TeeFunction1;
        TLineSeries *Series4;
        TLineSeries *Series5;
        TBitBtn *BitBtn1;
        TMemo *Memo2;
        TChart *Chart4;
        TLineSeries *Series7;
        TLineSeries *Series8;
        TMenuItem *Generujraport1;
        TBitBtn *BitBtn2;
        TMenuItem *Zobaczraport1;
        TLabel *Label13;
        TLabel *Label43;
        TRadioButton *RadioButton4;
        void __fastcall ButtonLosujClick(TObject *Sender);
        void __fastcall ButtonClearClick(TObject *Sender);
        void __fastcall ButtonMacierzClick(TObject *Sender);
        void __fastcall ButtonRozwStartClick(TObject *Sender);
        void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
        void __fastcall UpDown2Click(TObject *Sender, TUDBtnType Button);
        void __fastcall ButtonGoClick(TObject *Sender);
        void __fastcall RadioButton3Click(TObject *Sender);
        void __fastcall CheckBoxMinClick(TObject *Sender);
        void __fastcall CheckBoxMaxClick(TObject *Sender);
        void __fastcall CheckBoxCzasyClick(TObject *Sender);
        void __fastcall CheckBoxRozmiaryClick(TObject *Sender);
        void __fastcall ButtonRozwPorClick(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall ToolButton3Click(TObject *Sender);
        void __fastcall ToolButton2Click(TObject *Sender);
        void __fastcall CheckFileSave(void);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Otwrz1Click(TObject *Sender);
        void __fastcall Zapiszniebo1Click(TObject *Sender);
        void __fastcall Nowy1Click(TObject *Sender);
        void __fastcall ToolButton1Click(TObject *Sender);
        void __fastcall Losujgwiazdy1Click(TObject *Sender);
        void __fastcall Twrzmacierz1Click(TObject *Sender);
        void __fastcall Rozwizaniestartowe1Click(TObject *Sender);
        void __fastcall Porwnajrozwstartowe1Click(TObject *Sender);
        void __fastcall Wyzarzanie1Click(TObject *Sender);
        void __fastcall Auto1Click(TObject *Sender);
        void __fastcall ToolButton7Click(TObject *Sender);
        void __fastcall Zapiszobraznieba1Click(TObject *Sender);
        void __fastcall ToolButton9Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall Generujraport1Click(TObject *Sender);
        void __fastcall Oprogramie1Click(TObject *Sender);
        void __fastcall ToolButton8Click(TObject *Sender);
        void __fastcall EditIleKeyPress(TObject *Sender, char &Key);
        void __fastcall EditIleExit(TObject *Sender);
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        void __fastcall Edit1Exit(TObject *Sender);
        void __fastcall Edit7KeyPress(TObject *Sender, char &Key);
        void __fastcall Edit7Exit(TObject *Sender);
        void __fastcall Edit2KeyPress(TObject *Sender, char &Key);
        void __fastcall Edit2Exit(TObject *Sender);
        void __fastcall Edit3KeyPress(TObject *Sender, char &Key);
        void __fastcall Edit3Exit(TObject *Sender);
        void __fastcall Edit4KeyPress(TObject *Sender, char &Key);
        void __fastcall Edit4Exit(TObject *Sender);
        void __fastcall Edit5KeyPress(TObject *Sender, char &Key);
        void __fastcall Edit5Exit(TObject *Sender);
        void __fastcall Edit6KeyPress(TObject *Sender, char &Key);
        void __fastcall Edit6Exit(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall Zobaczraport1Click(TObject *Sender);
        void __fastcall ToolButton6Click(TObject *Sender);
        void __fastcall ZobaczplikPomocy1Click(TObject *Sender);


       
private:
        //int Ile;
        
        //int* tbKolejnosc;
        //int *tbTymcz1,*tbTymcz2,*tbTymcz3;
        //int Licznik0,Licznik1,Licznik2;
        //int Rozmiar;
        //float *(*wskMacierz);
        TDateTime tWynik,tPunkty[10];
        int Ilosc,Limit;
        int* wskOst;
        bool Saved;

        void Resetuj(void);
        void Tworz_JPG(AnsiString Sciezka);
public:

        //Obiekt Gwiazda;
        bool flTworzycMacierz;

        //---Pozostale---
        __fastcall TFormMain(TComponent* Owner);
        
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
