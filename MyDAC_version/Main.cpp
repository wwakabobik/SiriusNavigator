//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Directory.h"
#include "library.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "MyAccess"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
Form4->Show();  //
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  try {
  AnsiString TTagMP3, Buf;
  for (int i=0; i<Form1->ListBox1->Items->Count;i++)
  {
   TTagMP3=GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),0);
   AnsiString TT1,TT2,TT3;
   int error=0;
   if (TTagMP3.Length()<3)
   error=3;
   else
   {
   try { TT1=TTagMP3[1]; } catch (...) {error++;}
   try { TT2=TTagMP3[2]; } catch (...) {error++;}
   try { TT3=TTagMP3[3]; } catch (...) {error++;}
   }
   if (!error)
   {
   if ((TT1=="T") && (TT2=="A") && (TT3=="G"))
   {
   if ((AnsiString(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),2)).Length()<2) && (AnsiString(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),1)).Length()<2))
   {
   Form1->ListBox2->Items->Add(AnsiString(crofilename(Form1->ListBox1->Items->Strings[i].c_str())));
   Edit1->Text="Unknown Artist"; Edit2->Text=AnsiString(crofilename(Form1->ListBox1->Items->Strings[i].c_str())); Edit3->Text=""; Edit4->Text=""; Edit5->Text=""; Edit6->Text="FALSE";
   }
   else if (AnsiString(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),2)).Length()<2)
   {
   Form1->ListBox2->Items->Add("Unknown Artist - "+AnsiString(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),1)));
   Edit1->Text="Unknown Artist";
   Edit2->Text=AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),1),30));
   Edit3->Text=""; Edit4->Text=""; Edit5->Text=""; Edit6->Text="FALSE";
   }
   else if (AnsiString(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),1)).Length()<2)
   {
   Form1->ListBox2->Items->Add(AnsiString(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),2))+" - Unknown Song");
   Edit2->Text="Unknown Song";
   Edit1->Text=AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),2),30));;
   Edit3->Text=""; Edit4->Text=""; Edit5->Text=""; Edit6->Text="FALSE";
   }
   else
   {
   Form1->ListBox2->Items->Add(AnsiString(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),2))+" - "+AnsiString(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),1)));
   Edit1->Text=AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),2),30));
   Edit2->Text=AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),1),30));
   Edit3->Text=AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),3),30));
   Edit4->Text=AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),4),4));
   Edit5->Text=AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),5),28));
   Edit6->Text="TRUE";
   }
   }
   else Form1->ListBox2->Items->Add(AnsiString(crofilename(Form1->ListBox1->Items->Strings[i].c_str())));
   }
   else { Form1->ListBox2->Items->Add(AnsiString(crofilename(Form1->ListBox1->Items->Strings[i].c_str()))); error=0;}
  Memo1->Lines->Add(AnsiString(i+1)+ ". " + Edit1->Text + " - " + Edit2->Text + " \\ " + Edit3->Text + " \\ " + Edit4->Text + " \\ " + Edit5->Text + " && " + Edit6->Text);
  }
  }
  catch(...)
  {  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
ListBox1->Clear();
ListBox2->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
AnsiString Buf;
  try {
  AnsiString TTagMP3;
  for (int i=0; i<Form1->ListBox1->Items->Count;i++)
  {
   TTagMP3=GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),0);
   AnsiString TT1,TT2,TT3;
   int error=0;
   if (TTagMP3.Length()<3)
   error=3;
   else
   {
   try { TT1=TTagMP3[1]; } catch (...) {error++;}
   try { TT2=TTagMP3[2]; } catch (...) {error++;}
   try { TT3=TTagMP3[3]; } catch (...) {error++;}
   }
   if (!error)
   {
   if ((TT1=="T") && (TT2=="A") && (TT3=="G"))
   {
   ListBox2->Items->Strings[i]=ListBox2->Items->Strings[i]+" // "+AnsiString(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),3))+" // "+AnsiString(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),4));
   }
   }
   }
   }
  catch(...)
  {  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
ShowMessage(AnsiString(ListBox1->Items->Count)+" - "+AnsiString(ListBox2->Items->Count));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
MyQuery1->Open();
MyQuery1->Execute();
}
//---------------------------------------------------------------------------


