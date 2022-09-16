//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Directory.h"
//#include "Unit5.h"
#include "Main.h"
//#include "Unit6.h"
#include "library.h"
//#include <Math.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------



void __fastcall TForm4::Panel2Click(TObject *Sender)
{
DirectoryListBox1->Directory=Label1->Caption;
Form4->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Panel1Click(TObject *Sender)
{
try
{
Label2->Caption=DirectoryListBox1->Directory;
if (!CheckBox1->Checked)
{
 for (int i=0; i<FileListBox1->Items->Count; i++)
 {
 FileListBox1->ItemIndex=i;
 Form1->ListBox1->Items->Add(FileListBox1->FileName);
 }
}
else {
SongList->Clear();
SongList=FindDir(DirectoryListBox1->Directory.c_str(),"*.mp3");
for(int i=0;i<SongList->Count;i++)
{
Form1->ListBox1->Items->Add(SongList->Strings[i]);
}
}
}
catch (...) {}
/*
DirectoryListBox1->Directory=Label1->Caption;
AnsiString TR;
//  Main->ListBox2->SelectAll();
//  Main->ListBox2->DeleteSelected();
//  AnsiString TTagMP3;
//  int cursong=-1;
//  for (int i=0; i<Main->ListBox1->Items->Count;i++)
//  {

  //  if (!Form6->CheckBox1->Checked)
  //  Form3->ListBox2->Items->Add(AnsiString(crofilename(Form3->ListBox1->Items->Strings[i])));

  else
  {
//   if (Form3->ListBox1->Items->Strings[i]!=Form3->MediaPlayer1->FileName)
//   {
   TTagMP3=GetMp3Tag_DLL(Form3->ListBox1->Items->Strings[i].c_str(),0);
   AnsiString TT1,TT2,TT3;
   int error=0;
   try { TT1=TTagMP3[1]; } catch (...) {error++;}
   try { TT2=TTagMP3[2]; } catch (...) {error++;}
   try { TT3=TTagMP3[3]; } catch (...) {error++;}
   if (!error)
   {
   if ((TT1=="T") && (TT2=="A") && (TT3=="G"))
   Main->ListBox2->Items->Add(AnsiString(GetMp3Tag_DLL(Form3->ListBox1->Items->Strings[i].c_str(),2))+" - "+AnsiString(GetMp3Tag_DLL(Form3->ListBox1->Items->Strings[i].c_str(),1)));
   else Main->ListBox2->Items->Add(AnsiString(crofilename(Form3->ListBox1->Items->Strings[i])));
   }
   else Main->ListBox2->Items->Add(AnsiString(crofilename(Form3->ListBox1->Items->Strings[i])));
//   }
//   else
//   {
//   cursong=i;
//   Form3->ListBox2->Items->Add(AnsiString(crofilename(Form3->ListBox1->Items->Strings[i])));
//   }
  }
   }
     if (cursong>=0)
  {
//  if (!Form6->CheckBox1->Checked)
//  Form3->ListBox2->Items->Add(AnsiString(crofilename(Form3->ListBox1->Items->Strings[cursong])));
  else
   {
   Form3->MediaPlayer1->Stop();
   Form3->MediaPlayer1->Close();
   TTagMP3=GetMp3Tag_DLL(Form3->ListBox1->Items->Strings[cursong].c_str(),0);
   AnsiString TT1,TT2,TT3;
   int error=0;
   try { TT1=TTagMP3[1]; } catch (...) {error++;}
   try { TT2=TTagMP3[2]; } catch (...) {error++;}
   try { TT3=TTagMP3[3]; } catch (...) {error++;}
   if (!error)
   {
   if ((TT1=="T") && (TT2=="A") && (TT3=="G"))
   Form3->ListBox2->Items->Strings[cursong]=(AnsiString(GetMp3Tag_DLL(Form3->ListBox1->Items->Strings[cursong].c_str(),2))+" - "+AnsiString(GetMp3Tag_DLL(Form3->ListBox1->Items->Strings[cursong].c_str(),1)));
   else Form3->ListBox2->Items->Strings[cursong]=(AnsiString(crofilename(Form3->ListBox1->Items->Strings[cursong])));
   }
   else Form3->ListBox2->Items->Strings[cursong]=(AnsiString(crofilename(Form3->ListBox1->Items->Strings[cursong])));
   }
   Form3->MediaPlayer1->Open();
   Form3->MediaPlayer1->Position=Form3->TrackBar2->Position;
   Form3->MediaPlayer1->Play();
   }
/*for (int i=0; i<Form3->ListBox1->Items->Count; i++)
{
if (Form3->ListBox1->Items->Strings[i]!=Form3->MediaPlayer1->FileName)
{
try
{
Form3->MediaPlayer2->FileName=Form3->ListBox1->Items->Strings[i];
try {
Form3->MediaPlayer2->Open();
}
catch ( EMCIDeviceError& ) { /}
Form3->timetoplay+=Form3->MediaPlayer2->Length;
int retvalue=0,retvalue2=0; retvalue=Floor(((((StrToFloat(Form3->MediaPlayer2->Length))/1000)/60)-(StrToInt(Form3->MediaPlayer2->Length)/1000)/60)*60);
AnsiString TIME0;
if (retvalue>9)
TIME0=FloatToStr((StrToInt(Form3->MediaPlayer2->Length)/1000)/60)+":"+FloatToStr(retvalue);
else
TIME0=FloatToStr((StrToInt(Form3->MediaPlayer2->Length)/1000)/60)+":0"+FloatToStr(retvalue);
Form3->ListBox2->Items->Strings[i]=Form3->ListBox2->Items->Strings[i]+" \("+TIME0+"\) ";
Form3->MediaPlayer2->Close();
}
catch ( EMCIDeviceError& ) {}
}
else
{
Form3->timetoplay+=Form3->MediaPlayer1->Length;
int retvalue=0,retvalue2=0; retvalue=Floor(((((StrToFloat(Form3->MediaPlayer1->Length))/1000)/60)-(StrToInt(Form3->MediaPlayer1->Length)/1000)/60)*60);
AnsiString TIME0;
if (retvalue>9)
TIME0=FloatToStr((StrToInt(Form3->MediaPlayer1->Length)/1000)/60)+":"+FloatToStr(retvalue);
else
TIME0=FloatToStr((StrToInt(Form3->MediaPlayer1->Length)/1000)/60)+":0"+FloatToStr(retvalue);
Form3->ListBox2->Items->Strings[i]=Form3->ListBox2->Items->Strings[i]+" \("+TIME0+"\) ";
}
} */
Form4->Close();
}

//
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TForm4::FormShow(TObject *Sender)
{
Label1->Caption=DirectoryListBox1->Directory;
DirectoryListBox1->Directory=Label2->Caption;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




void __fastcall TForm4::FormCreate(TObject *Sender)
{
Label2->Caption=DirectoryListBox1->Directory;
}
//---------------------------------------------------------------------------

