//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "main.h"

#include "map.h"
#include "about.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
Starlight Niebo;        //nowy obiekt klasy Starlight

//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
        Ilosc=0;
        Limit=0;
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonLosujClick(TObject *Sender)
{
        int j;
        double Procent0,Procent1,Procent2;
        AnsiString Rekord;

        EditIle->Enabled=false;
        Saved=false;
        ButtonLosuj->Enabled=False;
        Losujgwiazdy1->Enabled=False;
        Auto1->Enabled=false;
        ToolButton7->Enabled=false;
        Ilosc=StrToInt(EditIle->Text);
        tPunkty[1]=Now();                //punkt pomiaru czasu
        Niebo.LosujGwiazdy(Ilosc);
        tPunkty[2]=Now();                //punkt pomiaru czasu
        Series1->AddPie(Niebo.Liczniki[0],"Wsp 0",clWhite);
        Series1->AddPie(Niebo.Liczniki[1],"Wsp 1",clYellow);
        Series1->AddPie(Niebo.Liczniki[2],"Wsp 2",clRed);
        for (j=0;j<Ilosc;j++)
        {
                Rekord=Niebo.Nazwa(j)+"   Rektascencja:  "
                +FormatFloat("00.00",Niebo.Rektascencja(j))+"   Deklinacja:  "
                +FormatFloat("00.00",Niebo.Deklinacja(j))+"   Wsp:  "
                +IntToStr(Niebo.Wsp(j));

                ListBox1->Items->Add(Rekord);
        }

        FormMap->Show();
        FormMap->RysujPodzialke();
        FormMap->RysujNiebo(Niebo.ZwrocWskaznik(),Ilosc);
        Zapiszobraznieba1->Enabled=true;
        ToolButton6->Enabled=true;
        ToolButton9->Enabled=true;
        Label6->Caption="dane wygenerowano losowo";
        tWynik=tPunkty[2]-tPunkty[1];
        Label43->Caption=tWynik.TimeString();
        Niebo.KolejnoscInicjuj();
        ButtonMacierz->Enabled=True;
        Twrzmacierz1->Enabled=True;
        TreeView1->Items->Item[1]->Expand(true);
        TreeView1->Items->Item[2]->ImageIndex=6;
};
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonClearClick(TObject *Sender)
{
        CheckFileSave();
        Resetuj();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonMacierzClick(TObject *Sender)
{
        int i,j,_i,_j;
        int* wskLicznik;
        float Wartosc,Min,Maks,Roz;
        AnsiString Lancuch="  ";

        ButtonMacierz->Enabled=False;
        Twrzmacierz1->Enabled=False;
        Niebo.ZadajLimit(StrToInt(Edit1->Text));
        if (CheckBoxCzasy->Checked==true) tPunkty[3]=Now();
        Niebo.MacierzBuduj();
        
        wskLicznik=new int[6];
        for (i=0;i<6;i++) wskLicznik[i]=0;
        for (i=0;i<Ilosc;i++)
        {
                for (j=0;j<Ilosc;j++)
                {
                        Wartosc=Niebo.OdczytMacierz(i,j);
                        Lancuch=Lancuch+"  "+FormatFloat("00.00",Wartosc);
                        if(i>=j+1)
                        {
                                if(Wartosc<10) wskLicznik[0]++;     //histogram po≥πczeÒ
                                if((Wartosc>=10) && (Wartosc<20)) wskLicznik[1]++;
                                if((Wartosc>=20) && (Wartosc<30)) wskLicznik[2]++;
                                if((Wartosc>=30) && (Wartosc<40)) wskLicznik[3]++;
                                if((Wartosc>=40) && (Wartosc<50)) wskLicznik[4]++;
                                if(Wartosc>50) wskLicznik[5]++;
                        }
                }
                Memo1->Lines->Add(Lancuch);
                 if (CheckBoxCzasy->Checked==true)
        {
                tPunkty[4]=Now();
                tWynik=tPunkty[4]-tPunkty[3];
                Label21->Caption=tWynik.TimeString();
        }
                Lancuch="  ";
        }
        Series2->AddBar(wskLicznik[0],"0-10",clGreen);
        Series2->AddBar(wskLicznik[1],"10-20",clGreen);
        Series2->AddBar(wskLicznik[2],"20-30",clYellow);
        Series2->AddBar(wskLicznik[3],"30-40",clYellow);
        Series2->AddBar(wskLicznik[4],"40-50",clRed);
        Series2->AddBar(wskLicznik[5],"50-",clRed);
        if(CheckBoxMin->Checked)
        {
                Min=100;
                for (i=0;i<Ilosc;i++)
                {
                        for (j=0;j<Ilosc;j++)
                        {
                                if(i>=j+1)
                                {
                                        if(Niebo.OdczytMacierz(i,j)<Min)
                                        {
                                                Min=Niebo.OdczytMacierz(i,j);
                                                _i=i;
                                                _j=j;
                                        }
                                }
                        }
                }
                Label19->Caption="("+IntToStr(_i)+";"+IntToStr(_j)+")  "+FormatFloat("00.00",Min);
        }
        if(CheckBoxMax->Checked)
        {
                Maks=0;
                for (i=0;i<Ilosc;i++)
                {
                        for (j=0;j<Ilosc;j++)
                        {
                                if(i>=j+1)
                                {
                                        if(Niebo.OdczytMacierz(i,j)>Maks)
                                        {
                                                Maks=Niebo.OdczytMacierz(i,j);
                                                _i=i;
                                                _j=j;
                                        }
                                }
                        }
                }
                Label22->Caption="("+IntToStr(_i)+";"+IntToStr(_j)+")  "+FormatFloat("00.00",Maks);
        }
        if(CheckBoxRozmiary->Checked) Label23->Caption=IntToStr(Ilosc*Ilosc*4);

        ButtonRozwStart->Enabled=True;
        ButtonRozwPor->Enabled=True;
        Rozwizaniestartowe1->Enabled=True;
        Porwnajrozwstartowe1->Enabled=True;
        TreeView1->Items->BeginUpdate();
        TreeView1->Items->Item[1]->ImageIndex=6;
        TreeView1->Items->Item[3]->ImageIndex=6;
        TreeView1->Items->EndUpdate();

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonRozwStartClick(TObject *Sender)
{
        int i=1,j=0;

        ButtonRozwStart->Enabled=False;
        ButtonRozwPor->Enabled=False;
        Rozwizaniestartowe1->Enabled=False;
        Porwnajrozwstartowe1->Enabled=False;
        Edit1->Enabled=false;
        Edit7->Enabled=false;
        if (RadioButton1->Checked)
        {
                Niebo.algNN_TSP(StrToInt(Edit7->Text));
                Label42->Caption="NN_TSP";
        }
        if (RadioButton2->Checked)
        {
                Niebo.algPo_kolei(StrToInt(Edit7->Text));
                Label42->Caption="Po kolei";
        }
        if (RadioButton4->Checked)
        {
                Niebo.algLosowo(StrToInt(Edit7->Text));
                Label42->Caption="Losowo";
        }

        while ((i==1) && (j<Ilosc))
        {
                ListBox4->Items->Add(IntToStr(Niebo.OdczytTabela(j)));
                if(Niebo.OdczytTabela(j)==Niebo.Ost) i=0;
                j++;
        };
        Label30->Caption=FormatFloat("00.00",Niebo.ObliczKosztDrogi());
        Label31->Caption=IntToStr(ListBox4->Items->Count);
        FormMap->RysujDroge(Niebo.ZwrocWskaznik(),Niebo.ZwrocWskKolejnosc(),ListBox4->Items->Count);
        ButtonGo->Enabled=True;
        Wyzarzanie1->Enabled=True;
        TreeView1->Items->BeginUpdate();
        TreeView1->Items->Item[4]->ImageIndex=6;
        TreeView1->Items->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonRozwPorClick(TObject *Sender)
{

        int i=1,j=0;


        ButtonRozwStart->Enabled=False;
        ButtonRozwPor->Enabled=False;
        Rozwizaniestartowe1->Enabled=False;
        Porwnajrozwstartowe1->Enabled=False;
        Edit1->Enabled=false;
        Edit7->Enabled=false;
        wskOst=new int[3];
        wskOst[0]=0;
        wskOst[1]=0;
        wskOst[2]=0;
        Label2->Enabled=True;
        Label25->Enabled=True;
        Label26->Enabled=True;
        ListBox5->Enabled=True;
        ListBox7->Enabled=True;
        ListBox8->Enabled=True;
        Button3->Enabled=True;
        Button4->Enabled=True;
        Button5->Enabled=True;
        GroupBox7->Enabled=True;
        Niebo.algPo_kolei(StrToInt(Edit7->Text));
        wskOst[0]=Niebo.Ost;
        while ((i==1) && (j<Ilosc))

        {
                ListBox5->Items->Add(IntToStr(Niebo.OdczytTabela(j)));
                if(Niebo.OdczytTabela(j)==Niebo.Ost) i=0;
                j++;
        };
        Label34->Caption=IntToStr(ListBox5->Items->Count);
        Label33->Caption=FormatFloat("00.00",Niebo.ObliczKosztDrogi());
        Niebo.algLosowo(StrToInt(Edit7->Text));
        wskOst[1]=Niebo.Ost;
        i=1;
        j=0;
        while ((i==1) && (j<Ilosc))
        {
                ListBox7->Items->Add(IntToStr(Niebo.OdczytTabela(j)));
                if(Niebo.OdczytTabela(j)==Niebo.Ost) i=0;
                j++;
        };
        Label37->Caption=IntToStr(ListBox7->Items->Count);
        Label36->Caption=FormatFloat("00.00",Niebo.ObliczKosztDrogi());
        Niebo.algNN_TSP(StrToInt(Edit7->Text));
        wskOst[2]=Niebo.Ost;
        i=1;
        j=0;
        while ((i==1) && (j<Ilosc))
        {
                ListBox8->Items->Add(IntToStr(Niebo.OdczytTabela(j)));
                if(Niebo.OdczytTabela(j)==Niebo.Ost) i=0;
                j++;
        };
        Label40->Caption=IntToStr(ListBox8->Items->Count);
        Label39->Caption=FormatFloat("00.00",Niebo.ObliczKosztDrogi());

        

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Button3Click(TObject *Sender)
{
        int i,j;
        AnsiString Wartosc;

        Button4->Enabled=False;
        Button5->Enabled=False;
        Button3->Enabled=False;

        i=1;
        j=0;
        while ((i==1) && (j<Ilosc))
        {
                Wartosc=ListBox5->Items->Strings[j];
                Niebo.ZapisTabela(j,StrToInt(Wartosc));
                ListBox4->Items->Add(Wartosc);
                if(Niebo.OdczytTabela(j)==wskOst[0]) i=0;
                j++;
        };
        Niebo.algPo_kolei(StrToInt(Edit7->Text));
        Label42->Caption="Po kolei";
        Label30->Caption=(Label33->Caption);
        Label31->Caption=(Label34->Caption);
        Label32->Caption=(Label35->Caption);
        FormMap->RysujDroge(Niebo.ZwrocWskaznik(),Niebo.ZwrocWskKolejnosc(),Ilosc);
        Wyzarzanie1->Enabled=True;
        ButtonGo->Enabled=True;
        TreeView1->Items->BeginUpdate();
        TreeView1->Items->Item[4]->ImageIndex=6;
        TreeView1->Items->EndUpdate();


}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button4Click(TObject *Sender)
{
        int i,j;
        AnsiString Wartosc;

        Button3->Enabled=False;
        Button5->Enabled=False;
        Button4->Enabled=False;

        i=1;
        j=0;
        while ((i==1) && (j<Ilosc))

        {
                Wartosc=ListBox7->Items->Strings[j];
                Niebo.ZapisTabela(j,StrToInt(Wartosc));
                ListBox4->Items->Add(Wartosc);
                if(Niebo.OdczytTabela(j)==wskOst[1]) i=0;
                j++;
        };
        Niebo.algLosowo(StrToInt(Edit7->Text));
        Label42->Caption="Losowo";
        Label30->Caption=(Label36->Caption);
        Label31->Caption=(Label37->Caption);
        Label32->Caption=(Label38->Caption);
        FormMap->RysujDroge(Niebo.ZwrocWskaznik(),Niebo.ZwrocWskKolejnosc(),Ilosc);
        Wyzarzanie1->Enabled=True;
        ButtonGo->Enabled=True;
        TreeView1->Items->BeginUpdate();
        TreeView1->Items->Item[4]->ImageIndex=6;
        TreeView1->Items->EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button5Click(TObject *Sender)
{
        int i,j;
        AnsiString Wartosc;

        Button3->Enabled=False;
        Button4->Enabled=False;
        Button5->Enabled=False;

        i=1;
        j=0;
        while ((i==1) && (j<Ilosc))
        {
                Wartosc=ListBox8->Items->Strings[j];
                Niebo.ZapisTabela(j,StrToInt(Wartosc));
                ListBox4->Items->Add(Wartosc);
                if(Niebo.OdczytTabela(j)==wskOst[2]) i=0;
                j++;
        };
        Niebo.algNN_TSP(StrToInt(Edit7->Text));
        Label42->Caption="NN_TSP";
        Label30->Caption=(Label39->Caption);
        Label31->Caption=(Label40->Caption);
        Label32->Caption=(Label41->Caption);
        FormMap->RysujDroge(Niebo.ZwrocWskaznik(),Niebo.ZwrocWskKolejnosc(),Ilosc);
        ButtonGo->Enabled=True;
        Wyzarzanie1->Enabled=True;
        TreeView1->Items->BeginUpdate();
        TreeView1->Items->Item[4]->ImageIndex=6;
        TreeView1->Items->EndUpdate();
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
Edit2->Text=IntToStr(UpDown1->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::UpDown2Click(TObject *Sender, TUDBtnType Button)
{
Edit3->Text=IntToStr(UpDown2->Position);
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::ButtonGoClick(TObject *Sender)
{
int i;

Wyzarzanie1->Enabled=False;
ButtonGo->Enabled=False;
Edit2->Enabled=false;
Edit3->Enabled=false;
Edit4->Enabled=false;
Edit5->Enabled=false;
Edit6->Enabled=false;
Niebo.AlgPopraw(StrToFloat(Edit6->Text),StrToFloat(Edit4->Text),StrToInt(Edit5->Text),StrToInt(Edit2->Text),StrToInt(Edit3->Text));
Niebo.Wyzarzanie();
TreeView1->Items->BeginUpdate();
TreeView1->Items->Item[5]->ImageIndex=6;
TreeView1->Items->EndUpdate();
BitBtn1->Enabled=true;
Generujraport1->Enabled=true;

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RadioButton3Click(TObject *Sender)
{
        CheckBoxMin->Enabled=True;
        CheckBoxMax->Enabled=True;
        CheckBoxCzasy->Enabled=True;
        CheckBoxRozmiary->Enabled=True;
        flTworzycMacierz=True;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CheckBoxMinClick(TObject *Sender)
{
        if (CheckBoxMin->Checked==True)
        {
                Label7->Enabled=True;
                Label19->Enabled=True;
        }
        if (CheckBoxMin->Checked==False)
        {
                Label7->Enabled=False;
                Label19->Enabled=False;
        }
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::CheckBoxMaxClick(TObject *Sender)
{
        if (CheckBoxMax->Checked==True)
        {
                Label14->Enabled=True;
                Label22->Enabled=True;
        }
        if (CheckBoxMax->Checked==False)
        {
                Label14->Enabled=False;
                Label22->Enabled=False;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CheckBoxCzasyClick(TObject *Sender)
{
        if (CheckBoxCzasy->Checked==True)
        {
                Label15->Enabled=True;
                Label21->Enabled=True;
                Label16->Enabled=True;
                Label20->Enabled=True;
        }
        if (CheckBoxCzasy->Checked==False)
        {
                Label15->Enabled=False;
                Label21->Enabled=False;
                Label16->Enabled=False;
                Label20->Enabled=False;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CheckBoxRozmiaryClick(TObject *Sender)
{
        if (CheckBoxRozmiary->Checked==True)
        {
                Label17->Enabled=True;
                Label23->Enabled=True;
                Label18->Enabled=True;
                
        }
        if (CheckBoxRozmiary->Checked==False)
        {
                Label17->Enabled=False;
                Label23->Enabled=False;
                Label18->Enabled=False;
                
        }
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::ToolButton3Click(TObject *Sender)
{
        SaveDialog1->InitialDir=Application->ExeName;
        SaveDialog1->DefaultExt=".nbo";
        SaveDialog1->FilterIndex=0;
        SaveDialog1->FileName="plik1.nbo";
        if (SaveDialog1->Execute())
        {

                ListBox1->Items->SaveToFile(SaveDialog1->FileName);
        }
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::ToolButton2Click(TObject *Sender)
{
        AnsiString Lancuch,Pomoc;
        AnsiString* wskString;
        TListBox* wskLista=ListBox1;

        CheckFileSave();
        ListBox1->Clear();
        OpenDialog1->InitialDir=Application->ExeName;
        if (OpenDialog1->Execute())
        {
                Resetuj();
                ListBox1->Items->LoadFromFile(OpenDialog1->FileName);
                ButtonLosuj->Enabled=false;
                Losujgwiazdy1->Enabled=false;
                ToolButton6->Enabled=true;
                ToolButton9->Enabled=true;
                Ilosc=ListBox1->Items->Count;
                wskString=&(ListBox1->Items->Strings[0]);
                Niebo.LoadGwiazdy(wskLista,Ilosc);
                Series1->AddPie(Niebo.Liczniki[0],"Wsp 0",clWhite);
                Series1->AddPie(Niebo.Liczniki[1],"Wsp 1",clYellow);
                Series1->AddPie(Niebo.Liczniki[2],"Wsp 2",clRed);
                FormMap->Show();
                FormMap->RysujPodzialke();
                FormMap->RysujNiebo(Niebo.ZwrocWskaznik(),Ilosc);
                Label6->Caption="dane wczytano z pliku";
                Niebo.KolejnoscInicjuj();
                ButtonMacierz->Enabled=True;
        }


}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CheckFileSave(void)
{
     if (!(ListBox1->Items->Count==0) && Saved==false)
       {
        switch(MessageBox(NULL, "ZawartoúÊ okna zosta≥a"
                            " zmieniona. ZapisaÊ zmiany?", "Uwaga!",
                            MB_YESNOCANCEL | MB_ICONQUESTION))
         {
           case ID_YES    : ToolButton3Click(this);
           case ID_CANCEL : Abort();
         };
        Saved=true;
      }
}


//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
        Application->ShowHint=true;
        Application->HintPause = 2000;
        Application->HintHidePause = 5000;
        HANDLE Mutex = CreateMutex (NULL, true, "starlight");
        int iResult = GetLastError();
        if (iResult == ERROR_ALREADY_EXISTS)
        {
                Application->MessageBox("Program jest ju uruchomiony", "Info", MB_ICONINFORMATION);
                Application->Terminate();
        }
        tPunkty[0]=Now();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
        Resetuj();
        tPunkty[9]=Now();        
}
//---------------------------------------------------------------------------
void TFormMain::Resetuj(void)
{
        int i;

        ButtonLosuj->Enabled=True;
        ButtonRozwStart->Enabled=False;
        ButtonRozwPor->Enabled=False;
        ButtonMacierz->Enabled=False;
        ButtonGo->Enabled=False;
        Losujgwiazdy1->Enabled=True;
        Twrzmacierz1->Enabled=False;
        Rozwizaniestartowe1->Enabled=False;
        Porwnajrozwstartowe1->Enabled=False;
        Wyzarzanie1->Enabled=False;
        Auto1->Enabled=true;
        Zapiszobraznieba1->Enabled=false;
        ToolButton6->Enabled=false;
        ToolButton9->Enabled=false;
        ToolButton7->Enabled=true;
        Generujraport1->Enabled=false;
        Zobaczraport1->Enabled=false;
        RadioButton2->Checked=True;
        CheckBoxMin->Checked=True;
        CheckBoxMax->Checked=True;
        CheckBoxCzasy->Checked=True;
        CheckBoxRozmiary->Checked=True;
        for (i=1;i<8;i++)
        {
               dynamic_cast<TEdit*>(FindComponent("Edit"+IntToStr(i)))->Enabled=true;
        }
        EditIle->Enabled=true;
        EditIle->Text="5";
        Edit1->Text="1000";
        Edit2->Text="5";
        Edit3->Text="5";
        Edit4->Text="0,9";
        Edit5->Text="1";
        Edit6->Text="100";
        Edit7->Text="1";
        TreeView1->Items->BeginUpdate();
        for (i=1;i<6;i++) TreeView1->Items->Item[i]->ImageIndex=-1;
        TreeView1->Items->Item[1]->Collapse(true);
        TreeView1->Items->EndUpdate();
        Memo1->Clear();
        Series1->Clear();
        Series2->Clear();
        Series3->Clear();
        Series4->Clear();
        Series5->Clear();
        Series7->Clear();
        Series8->Clear();
        for (i=1;i<11;i++)
        {
                if((i!=2) && (i!=3) && (i!=6) && (i!=9)) dynamic_cast<TListBox*>(FindComponent("ListBox"+IntToStr(i)))->Clear();
                if((i>2) && (i<6)) dynamic_cast<TButton*>(FindComponent("Button"+IntToStr(i)))->Enabled=False;
        }
        Label6->Caption="brak danych";
        for (i=19;i<24;i++)
        {
                dynamic_cast<TLabel*>(FindComponent("Label"+IntToStr(i)))->Caption="0";
        }
        for (i=30;i<42;i++)
        {
                dynamic_cast<TLabel*>(FindComponent("Label"+IntToStr(i)))->Caption="---";
        }
        Label42->Caption="Nie wybrano";
        BitBtn1->Enabled=false;
        BitBtn2->Enabled=false;
        FormMap->Hide();
}


void __fastcall TFormMain::Otwrz1Click(TObject *Sender)
{
ToolButton2Click(Otwrz1);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Zapiszniebo1Click(TObject *Sender)
{
ToolButton3Click(Zapiszniebo1);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Nowy1Click(TObject *Sender)
{
        CheckFileSave();
        Resetuj();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolButton1Click(TObject *Sender)
{
       CheckFileSave();
       Resetuj();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Losujgwiazdy1Click(TObject *Sender)
{
ButtonLosujClick(Losujgwiazdy1);
Losujgwiazdy1->Enabled=False;
Twrzmacierz1->Enabled=True;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Twrzmacierz1Click(TObject *Sender)
{
ButtonMacierzClick(Twrzmacierz1);
Twrzmacierz1->Enabled=False;
Rozwizaniestartowe1->Enabled=True;
Porwnajrozwstartowe1->Enabled=True;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Rozwizaniestartowe1Click(TObject *Sender)
{
ButtonRozwStartClick(Rozwizaniestartowe1);
Rozwizaniestartowe1->Enabled=False;
Porwnajrozwstartowe1->Enabled=False;
Wyzarzanie1->Enabled=True;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Porwnajrozwstartowe1Click(TObject *Sender)
{
ButtonRozwPorClick(Porwnajrozwstartowe1);
Rozwizaniestartowe1->Enabled=False;
Porwnajrozwstartowe1->Enabled=False;
Wyzarzanie1->Enabled=True;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Wyzarzanie1Click(TObject *Sender)
{
ButtonGoClick(Wyzarzanie1);
Wyzarzanie1->Enabled=False;
ButtonGo->Enabled=False;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Auto1Click(TObject *Sender)
{
        ButtonLosujClick(Auto1);
        ButtonMacierzClick(Auto1);
        ButtonRozwStartClick(Auto1);
        ButtonGoClick(Auto1);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolButton7Click(TObject *Sender)
{
        ButtonLosujClick(ToolButton7);
        ButtonMacierzClick(ToolButton7);
        ButtonRozwStartClick(ToolButton7);
        ButtonGoClick(ToolButton7);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Zapiszobraznieba1Click(TObject *Sender)
{
        SaveDialog1->InitialDir=Application->ExeName;
        SaveDialog1->DefaultExt=".bmp";
        SaveDialog1->FilterIndex=1;
        SaveDialog1->FileName="plik1.bmp";
        
        if (SaveDialog1->Execute())
        {

                FormMap->Image1->Picture->SaveToFile(SaveDialog1->FileName);
        }

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolButton9Click(TObject *Sender)
{
FormMap->Show();
}
//---------------------------------------------------------------------------
void TFormMain::Tworz_JPG(AnsiString Sciezka)
{
        Graphics::TBitmap *BMP = new Graphics::TBitmap();
        TJPEGImage *JPG = new TJPEGImage();
        BMP->LoadFromFile(Sciezka+".bmp");
        JPG->Assign(BMP);
        JPG->SaveToFile(Sciezka+".jpg");

        delete JPG;
        delete BMP;

}
//-----------------------------Funkcja Tworzenia Raportu------------------
void __fastcall TFormMain::BitBtn1Click(TObject *Sender)
{
        AnsiString SciezkaProgr,StrCzas,strPom;
        TDateTime czas;

        BitBtn1->Enabled=false;
        Generujraport1->Enabled=false;
        strPom=Application->ExeName;
        SciezkaProgr=strPom.SubString(1,strPom.Length()-13);
        if(!(DirectoryExists(SciezkaProgr+"\\raport"))) //sprawdzenie, czy istnieje katalog RAPORT
                CreateDir(SciezkaProgr+"\\raport");     //ew. utworzenie

        Chart1->SaveToBitmapFile(SciezkaProgr+"\\raport\\chart1.bmp"); //zapisanie rysunkow
        Chart2->SaveToBitmapFile(SciezkaProgr+"\\raport\\chart2.bmp");
        Chart3->SaveToBitmapFile(SciezkaProgr+"\\raport\\chart3.bmp");
        Chart4->SaveToBitmapFile(SciezkaProgr+"\\raport\\chart4.bmp");
        FormMap->Image1->Picture->SaveToFile(SciezkaProgr+"\\raport\\skymap.bmp");
        Tworz_JPG(SciezkaProgr+"\\raport\\chart1");  //konwersja na format JPG
        Tworz_JPG(SciezkaProgr+"\\raport\\chart2");
        Tworz_JPG(SciezkaProgr+"\\raport\\chart3");
        Tworz_JPG(SciezkaProgr+"\\raport\\chart4");
        Tworz_JPG(SciezkaProgr+"\\raport\\skymap");

        ListBox1->Items->SaveToFile(SciezkaProgr+"\\raport\\stars.txt");
        Memo1->Lines->SaveToFile(SciezkaProgr+"\\raport\\matrix.txt");
        ListBox4->Items->SaveToFile(SciezkaProgr+"\\raport\\start.txt");
        ListBox10->Items->SaveToFile(SciezkaProgr+"\\raport\\sa.txt");
        Memo2->Lines->Add("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Final//EN\">");
        Memo2->Lines->Add("<HTML>");
        Memo2->Lines->Add("<HEAD>");
        Memo2->Lines->Add("<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=iso-8859-2\">");
        czas=Now();
        StrCzas=czas.FormatString("dd-mm-yyyy hh-nn-ss");
        Memo2->Lines->Add("<META HTTP-EQUIV=\"Creation-date\" CONTENT=\""+StrCzas+"\">");
        Memo2->Lines->Add("<META NAME=\"Authoring_tool\" CONTENT=\"STARLIGHT\">");
        Memo2->Lines->Add("<META NAME=\"Description\" CONTENT=\"Raport HTML wygenerowany przez program Starlight\">");
        Memo2->Lines->Add("<META NAME=\"Keywords\" CONTENT=\"badania operacyjne,TSP,simulated annealing,symulowane wyøarzanie\">");
        Memo2->Lines->Add("<META NAME=\"Language\" CONTENT=\"pl\">");
        Memo2->Lines->Add("<META NAME=\"Author\" CONTENT=\"Bart≥omiej Juszczyk\">");
        Memo2->Lines->Add("<TITLE>Raport HTML programu STARLIGHT</TITLE>");
        Memo2->Lines->Add("</HEAD>");
        Memo2->Lines->Add("<BODY STYLE=\"background: #FFFFFF; text-color: #00000\">");
        Memo2->Lines->Add("<h1>Raport programu Starlight</h1><br><br>");
        Memo2->Lines->Add("<b>Data: &nbsp &nbsp"+StrCzas+"</b><br><br>");
        Memo2->Lines->Add("<h2>Podstawowe dane eksperymentu:</h2><br><br>");
        Memo2->Lines->Add("<h3>Dane wejúciowe</h3><br>");
        Memo2->Lines->Add("Liczba gwiazd: <b>"+(EditIle->Text)+" </b>&nbsp &nbsp &nbsp<A href=\"stars.txt\">ZOBACZ TABELE GWIAZD</a><br>");
        Memo2->Lines->Add("èrÛd≥o danych: <b>"+Label6->Caption+"</b><br>");
        if (CheckBox1->Checked==true) strPom="Limit uwzglÍdniony";
        else strPom="Limit nieuwzglÍdniony";
        Memo2->Lines->Add("Limit paliwa: <b> "+(Edit1->Text)+"</b> &nbsp &nbsp "+strPom+"<br><br>");
        Memo2->Lines->Add("<center><img src=\"chart1.jpg\" border=\"0\" alt=\"Struktura gwiazd\"></center><br>");
        Memo2->Lines->Add("<i>Rysunek powyøej przedstawia procentowπ zawartoúÊ poszczegÛlnych typÛw gwiazd na ca≥ym niebie.</i><br><br>");
        Memo2->Lines->Add("<h3>Macierz</h3><br>");
        Memo2->Lines->Add("Rozmiar macierzy: <b>"+Label23->Caption+" </b>&nbsp &nbsp &nbsp<A href=\"matrix.txt\">ZOBACZ MACIERZ</a><br>");
        Memo2->Lines->Add("Czas tworzenia:  <b> "+Label21->Caption+"</b><br>");
        Memo2->Lines->Add("Element minimalny: <b>"+Label19->Caption+"</b><br>");
        Memo2->Lines->Add("Element maksymalny: <b>"+Label22->Caption+"</b><br><br>");
        Memo2->Lines->Add("<center><img src=\"chart2.jpg\" border=\"0\" alt=\"Histogram po≥πczeÒ w grafie\"></center><br>");
        Memo2->Lines->Add("<i>Rysunek powyøej przedstawia rozk≥ad d≥ugoúci po≥πczeÒ miÍdzy gwiazdami, mierzony zuøyciem paliwa.</i><br><br>");
        Memo2->Lines->Add("<h3>Rozwiπzanie startowe:</h3><br>");
        Memo2->Lines->Add("Rodzaj algorytmu: <b>"+Label42->Caption+"</b><br>");
        Memo2->Lines->Add("Koszt drogi (paliwo): <b>"+ Label30->Caption+"</b><br>");
        Memo2->Lines->Add("Ilosc gwiazd: <b> "+Label31->Caption+"</b><br>");
        Memo2->Lines->Add("Czas Tworzenia: <b> "+Label32->Caption+"</b><br>");
        
        Memo2->Lines->Add("<i>PostaÊ rozwiπzania startowego najlepiej obserwowaÊ na mapie nieba.</i>&nbsp &nbsp &nbsp<A href=\"start.txt\">ZOBACZ ROZWI•ZANIE STARTOWE W FORMIE TEKSTOWEJ</a><br><br>");
        Memo2->Lines->Add("<h3>Algorytm popraw - Symulowane wyøarzanie</h3><br>");
        Memo2->Lines->Add("Ilosc serii: <b> "+Edit3->Text+"</b><br>");
        Memo2->Lines->Add("Ilosc prob w serii: <b> "+Edit2->Text+"</b><br>");
        Memo2->Lines->Add("Alfa: <b> "+Edit4->Text+"</b><br>");
        Memo2->Lines->Add("Beta: <b> "+Edit5->Text+"</b><br>");
        Memo2->Lines->Add("Temperatura poczatkowa: <b>"+Edit6->Text+"</b><br>");
        if (RadioButton3->Checked==true) Memo2->Lines->Add("Metoda generacji otoczenia: <b>\"przez zamiane\"</b>");
        if (RadioButton5->Checked==true) Memo2->Lines->Add("Metoda generacji otoczenia: <b>\"przez wstawienie\"</b>");
        Memo2->Lines->Add("&nbsp &nbsp &nbsp<A href=\"sa.txt\">ZOBACZ ZAREJESTROWANE WARTOSCI PARAMETROW</a><br><br>WYKRESY:<BR><BR>");
        Memo2->Lines->Add("<center><img src=\"chart3.jpg\" border=\"0\" alt=\"Wartosci funkcji kosztow\"></center><br><br>");
        Memo2->Lines->Add("<center><img src=\"chart4.jpg\" border=\"0\" alt=\"Wartosci parametrow\"></center><br><br>MAPA NIEBA Z ROZWIAZANIEM:<BR><BR>");
        Memo2->Lines->Add("<center><img src=\"skymap.jpg\" border=\"0\" alt=\"Mapa nieba\"></center><br><br>");
        Memo2->Lines->Add("</body>");
        Memo2->Lines->Add("</html>");
        Memo2->Lines->SaveToFile(SciezkaProgr+"\\raport\\raport.html");
        BitBtn2->Enabled=true;
        Zobaczraport1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Generujraport1Click(TObject *Sender)
{
BitBtn1Click(Generujraport1);
BitBtn1->Enabled=false;
Generujraport1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Oprogramie1Click(TObject *Sender)
{
FormAbout->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolButton8Click(TObject *Sender)
{
        AnsiString SciezkaPomocy,strPom;
        strPom=Application->ExeName;
        SciezkaPomocy=strPom.SubString(1,strPom.Length()-13)+"\\help\\index.html";
        ShellExecute(FormMain->Handle,NULL,SciezkaPomocy.c_str(),NULL,NULL,SW_SHOWNORMAL);
}
//-----------------ZABEZPIECZENIA P”L TEKSTOWYCH "EDIT"-------------------

void __fastcall TFormMain::EditIleKeyPress(TObject *Sender, char &Key)
{
        if (!(isdigit(Key) || Key == VK_BACK || Key == DecimalSeparator))
        {
                Key = 0;
        }
        else
        {
                if ((Key == DecimalSeparator) && (EditIle->Text.Pos(DecimalSeparator) > 0))
                Key = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EditIleExit(TObject *Sender)
{
        if(StrToInt(EditIle->Text)<3) EditIle->Text=3;
        if(StrToInt(EditIle->Text)>500) EditIle->Text=500;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit1KeyPress(TObject *Sender, char &Key)
{
        if (!(isdigit(Key) || Key == VK_BACK || Key == DecimalSeparator))
        {
                Key = 0;
        }
        else
        {
                if ((Key == DecimalSeparator) && (Edit1->Text.Pos(DecimalSeparator) > 0))
                Key = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit1Exit(TObject *Sender)
{
        if(StrToInt(Edit1->Text)<5) Edit1->Text=5;
        if(StrToInt(Edit1->Text)>100000) Edit1->Text=100000;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit7KeyPress(TObject *Sender, char &Key)
{
        if (!(isdigit(Key) || Key == VK_BACK || Key == DecimalSeparator))
        {
                Key = 0;
        }
        else
        {
                if ((Key == DecimalSeparator) && (Edit7->Text.Pos(DecimalSeparator) > 0))
                Key = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit7Exit(TObject *Sender)
{
        if(StrToInt(Edit7->Text)<0) Edit7->Text=0;
        if(StrToInt(Edit7->Text)>Ilosc) Edit7->Text=IntToStr(Ilosc);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit2KeyPress(TObject *Sender, char &Key)
{
        if (!(isdigit(Key) || Key == VK_BACK || Key == DecimalSeparator))
        {
                Key = 0;
        }
        else
        {
                if ((Key == DecimalSeparator) && (Edit2->Text.Pos(DecimalSeparator) > 0))
                Key = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit2Exit(TObject *Sender)
{
        if(StrToInt(Edit2->Text)<1) Edit2->Text=1;
        if(StrToInt(Edit2->Text)>32700) Edit2->Text=32700;
        if(StrToInt(Edit2->Text)*StrToInt(Edit3->Text)>32700)
        {
                Edit2->Text=1000;
                Edit3->Text=30;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit3KeyPress(TObject *Sender, char &Key)
{
        if (!(isdigit(Key) || Key == VK_BACK || Key == DecimalSeparator))
        {
                Key = 0;
        }
        else
        {
                if ((Key == DecimalSeparator) && (Edit3->Text.Pos(DecimalSeparator) > 0))
                Key = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit3Exit(TObject *Sender)
{
        if(StrToInt(Edit3->Text)<1) Edit3->Text=1;
        if(StrToInt(Edit3->Text)>32700) Edit3->Text=32700;
        if(StrToInt(Edit2->Text)*StrToInt(Edit3->Text)>32700)
        {
                Edit2->Text=1000;
                Edit3->Text=30;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit4KeyPress(TObject *Sender, char &Key)
{
        if (!(isdigit(Key) || Key == VK_BACK || Key == DecimalSeparator))
        {
                Key = 0;
        }
        else
        {
                if ((Key == DecimalSeparator) && (Edit4->Text.Pos(DecimalSeparator) > 0))
                Key = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit4Exit(TObject *Sender)
{
        if(StrToInt(Edit4->Text)<0) Edit4->Text=0;
        if(StrToInt(Edit4->Text)>=1) Edit4->Text="0,99";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit5KeyPress(TObject *Sender, char &Key)
{
        if (!(isdigit(Key) || Key == VK_BACK || Key == DecimalSeparator))
        {
                Key = 0;
        }
        else
        {
                if ((Key == DecimalSeparator) && (Edit5->Text.Pos(DecimalSeparator) > 0))
                Key = 0;
        }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Edit5Exit(TObject *Sender)
{
        if(StrToInt(Edit5->Text)<1) Edit5->Text=1;
        if(StrToInt(Edit5->Text)>10) Edit5->Text=10;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit6KeyPress(TObject *Sender, char &Key)
{
        if (!(isdigit(Key) || Key == VK_BACK || Key == DecimalSeparator))
        {
                Key = 0;
        }
        else
        {
                if ((Key == DecimalSeparator) && (Edit6->Text.Pos(DecimalSeparator) > 0))
                Key = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Edit6Exit(TObject *Sender)
{
        if(StrToInt(Edit6->Text)<60) Edit6->Text=60;
        if(StrToInt(Edit6->Text)>3000) Edit6->Text=3000;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::BitBtn2Click(TObject *Sender)
{
        BitBtn2->Enabled=false;
        Zobaczraport1->Enabled=false;
        AnsiString SciezkaPomocy,strPom;
        strPom=Application->ExeName;
        SciezkaPomocy=strPom.SubString(1,strPom.Length()-13)+"\\raport\\raport.html";
        ShellExecute(FormMain->Handle,NULL,SciezkaPomocy.c_str(),NULL,NULL,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Zobaczraport1Click(TObject *Sender)
{
        BitBtn2Click(Zobaczraport1);
        BitBtn2->Enabled=false;
        Zobaczraport1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolButton6Click(TObject *Sender)
{
Zapiszobraznieba1Click(ToolButton6);        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ZobaczplikPomocy1Click(TObject *Sender)
{
ToolButton8Click(ZobaczplikPomocy1);        
}
//---------------------------------------------------------------------------

