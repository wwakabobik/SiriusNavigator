//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "library.h"
#include "Directory.h"
#include "login.h"
#include "about.h"
#include <Math.hpp>
#include <Graphics.hpp>
#include <Jpeg.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "daADCompClient"
#pragma link "daADCompDataSet"
#pragma link "daADDAptIntf"
#pragma link "daADDatSManager"
#pragma link "daADPhysIntf"
#pragma link "daADStanDef"
#pragma link "daADStanIntf"
#pragma link "daADStanOption"
#pragma link "daADStanParam"
#pragma link "daADGUIxFormsWait"
#pragma link "daADPhysManager"
#pragma link "daADPhysMySQL"
#pragma link "CGAUGES"
#pragma link "daADPhysMSSQL"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BAddSongsClick(TObject *Sender)
{
Form4->ShowModal();  //
if (ListBox1->Items->Count)
{
LabeledEdit1->Color=clRed;
LabeledEdit1->Text="Ready: " + AnsiString(ListBox1->Items->Count);
}
else { LabeledEdit1->Text="None"; LabeledEdit1->Color=clWhite;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BGenerateHTMLForSingleArtistClick(TObject *Sender)
{
DBMemo1->DataField="";
DBMemo2->DataField="";
DBEdit1->DataField="";
DBComboBox1->DataField="";
try { ADQuery1->Close(); }
catch (...) { }

ADQuery1->SQL->Text="call html_print('"+Edit7->Text+"',"+Edit8->Text+")";
ADQuery1->Open();
DBMemo2->DataField="HTML";
DBMemo2->Lines->SaveToFile("HTML\\"+Edit8->Text+".html");
DBMemo2->DataField="";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BClearTodoClick(TObject *Sender)
{
ListBox1->Clear();
ListBox2->Clear();
if (ListBox1->Items->Count)
{
LabeledEdit1->Color=clRed;
LabeledEdit1->Text="Ready: " + ListBox1->Items->Count;
}
else { LabeledEdit1->Text="None"; LabeledEdit1->Color=clWhite;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BGenerateHTMLClick(TObject *Sender)
{
/* Generate HTML based on all Artist */
DBComboBox1->DataField="";
DBImage1->DataField="";
DBMemo1->DataField="";
DBMemo2->DataField="";
try { ADQuery2->Close(); } //
catch (...) {}
ADQuery2->SQL->Text="select artist from song GROUP BY artist ORDER BY genre, artist";
ADQuery2->Open();
ADQuery2->First();
ListBox3->Items->Clear();
while (!ADQuery2->Eof) {
    ListBox3->Items->Add(ADQuery2->FieldByName("artist")->AsString);
    ADQuery2->Next();
    }
CGauge1->MaxValue=Form1->ListBox3->Items->Count;
CGauge1->Progress=0;
/* Title */
Memo1->Text="<HTML><HEAD><TITLE>Sirius DB</TITLE></HEAD><BODY><TABLE cellSpacing=0 cellPadding=0 width=100% height=100% border=1 align=left> ";
for (int i=0;i<Form1->ListBox3->Items->Count;i++)
{
Memo1->Lines->Add("<TR><TD><IMG src='ARTISTS/"+AnsiString(i)+".jpg' align='center'></TD><TD valign='center'><a href='"+AnsiString(i)+".html'>"+ListBox3->Items->Strings[i]+"</a></TD>");
try { ADQuery1->Close(); }
catch (...) {}
/* Count by artist */
ADQuery1->SQL->Text="select count(id) AS songs from song WHERE song.artist='"+ListBox3->Items->Strings[i]+"'";
ADQuery1->Open();
DBEdit1->DataField="songs";
Memo1->Lines->Add("<TD>Songs: "+DBEdit1->Text+"</TD>");
DBEdit1->DataField="";
try { ADQuery1->Close(); }
catch (...) {}
/* Count by album */
ADQuery1->SQL->Text="select count(id) AS albums from album WHERE album.artist='"+ListBox3->Items->Strings[i]+"'";
ADQuery1->Open();
DBEdit1->DataField="albums";
Memo1->Lines->Add("<TD>Albums: "+DBEdit1->Text+"</TD></TR>");
DBEdit1->DataField="";
CGauge1->Progress=i;
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="call html_print('"+ListBox3->Items->Strings[i]+"',"+AnsiString(i)+");";
ADQuery1->Open();
DBMemo2->DataField="HTML";
DBMemo2->Lines->SaveToFile("HTML\\"+AnsiString(i)+".html");
DBMemo2->DataField="";
if (CheckBox5->Checked)
 {
 /* Artist Picture */
 Graphics::TBitmap *B = new Graphics::TBitmap();
 TJPEGImage* JPEG=new TJPEGImage();
 try { ADQuery1->Close(); }
 catch (...) {}
 ADQuery1->SQL->Text="select picture from artist where artist.artist='"+ListBox3->Items->Strings[i]+"' ORDER BY genre, artist";
 ADQuery1->Open();
 TStream *S2=ADQuery1->CreateBlobStream(ADQuery1->FieldByName("picture"),bmRead);
 S2->Position=0;
 B->LoadFromStream(S2);
 JPEG->Assign(B);
 JPEG->SaveToFile("HTML\\ARTISTS\\"+AnsiString(i)+".jpg");
 /* Album Picture */
 try { ADQuery1->Close(); }
 catch (...) {}
 ADQuery1->SQL->Text="select cover from album where album.artist='"+ListBox3->Items->Strings[i]+"' ORDER BY genre, artist, year, album";
 ADQuery1->Open();
 ADQuery1->First();
 int j=0;
 while (!ADQuery1->Eof)
 {
 j++;
 TStream *S2=ADQuery1->CreateBlobStream(ADQuery1->FieldByName("cover"),bmRead);
 S2->Position=0;
 B->LoadFromStream(S2);
 JPEG->Assign(B);
 JPEG->SaveToFile("HTML\\ALBUMS\\"+AnsiString(i)+"_"+AnsiString(j)+".jpg");
 ADQuery1->Next();
 }
 }
 /* Lyric */
if (CheckBox6->Checked)
{
 try { ADQuery1->Close(); }
 catch (...) {}
 ADQuery1->SQL->Text="select album from song where song.artist='"+ListBox3->Items->Strings[i]+"'  GROUP by album ORDER BY genre, artist, year, album";
 ADQuery1->Open();
 ADQuery1->First();
 int j=0;
 while (!ADQuery1->Eof)
 {
 j++;
 int k=0;
 try { ADQuery2->Close(); }
 catch (...) {}
ADQuery2->SQL->Text="select song, lyric as lyric from song where song.album='"+AnsiString(ADQuery1->FieldByName("album")->AsString)+"' ORDER BY genre, artist, year, album";
ADQuery2->Open();
ADQuery2->First();
DBMemo2->DataSource=DataSource2;
DBMemo2->DataField="lyric";
while (!ADQuery2->Eof)
{
k++;
Memo2->Lines->Clear();
Memo2->Lines->Add("<HTML><HEAD><TITLE>Sirius DB - "+ListBox3->Items->Strings[i]+" - "+AnsiString(ADQuery2->FieldByName("song")->AsString)+"</TITLE></HEAD><BODY>");
for (int h=0;h<DBMemo2->Lines->Count;h++)
Memo2->Lines->Add(DBMemo2->Lines->Strings[h]+"<BR>");
Memo2->Lines->Add("</BODY></HTML>");
Memo2->Lines->SaveToFile("HTML\\LYRICS\\"+AnsiString(i)+"_"+AnsiString(j)+"_"+AnsiString(k)+".html");
ADQuery2->Next();
}
DBMemo2->DataField="";
DBMemo2->DataSource=DataSource1;
ADQuery1->Next();
 }
}
}
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select return_time('%',0,0) AS HTML";
ADQuery1->Open();
DBMemo2->DataField="HTML";
/* Close all HTML tags */
Memo1->Lines->Add("<TD><TR><b>Total Length: "+DBMemo2->Text+"<BR>Generated: "+AnsiString(Now())+" by Sirius Navigator</b></TD><TR>");
DBMemo2->DataField="";
Memo1->Lines->Add("</TABLE></BODY><HTML>");
Memo1->Lines->SaveToFile("HTML\\index.html");
Memo1->Lines->Clear();
CGauge1->Progress=Form1->ListBox3->Items->Count;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BCountClick(TObject *Sender)
{
/* Developed for debug */
ShowMessage(AnsiString(ListBox1->Items->Count)+" - "+AnsiString(ListBox2->Items->Count));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BAddLyricClick(TObject *Sender)
{
/* Add lyric\comment */
// Lyric into Song
if (ComboBox1->ItemIndex==0)
{
if (OpenDialog1->Execute())
{
DataSource1->DataSet->Edit();
DBMemo1->DataField="lyric";
DBMemo1->Lines->LoadFromFile(OpenDialog1->FileName);
DataSource1->DataSet->UpdateRecord();
DBMemo1->DataField="";
}
}
// Comment into Artist
else if (ComboBox1->ItemIndex==1)
{
if (OpenDialog1->Execute())
{
DataSource1->DataSet->Edit();
DBMemo1->DataField="comment";
DBMemo1->Lines->LoadFromFile(OpenDialog1->FileName);
DataSource1->DataSet->UpdateRecord();
DBMemo1->DataField="";
}
}
// Comment into Album
if (ComboBox1->ItemIndex==2)
{
if (OpenDialog1->Execute())
{
DataSource1->DataSet->Edit();
DBMemo1->DataField="comment";
DBMemo1->Lines->LoadFromFile(OpenDialog1->FileName);
DataSource1->DataSet->UpdateRecord();
DBMemo1->DataField="";
}
}
}

//---------------------------------------------------------------------------
void __fastcall TForm1::BExecQueryClick(TObject *Sender)
{
/* Exec Query */
ADQuery1->SQL->Text=Memo2->Text;
ADQuery1->ExecSQL();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BExecSelectClick(TObject *Sender)
{
/* Select Query */
DBMemo1->DataField="";
DBMemo2->DataField="";
DBImage1->DataField="";
DBComboBox1->DataField="";
ADQuery1->SQL->Text=Memo2->Text;
ADQuery1->Open();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BAddSongListClick(TObject *Sender)
{
CGauge1->MaxValue=Form1->ListBox1->Items->Count;
CGauge1->Progress=0;
  try {
  AnsiString TTagMP3;
  //dupe
  AnsiString BArtist=NULL, BAlbum=NULL, BYear=NULL; // local use
  for (int i=0; i<Form1->ListBox1->Items->Count;i++)
  {
CGauge1->Progress=i;
// debug
//  if (i%10==0)
//  Sleep(500);
//  if (i==100)
//  break;
/* Log block - it can be removed if needed */
/* developed for debug on VCL */
  try {
   TTagMP3=GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),0);
   }
   catch (...) { }
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
if (CheckBox4->Checked)
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
/* --- MySQL Query Block --- */
/* Convert ID3V1 Data to MySQL Insert Query */
   int id_error=0;
   ADQuery1->SQL->Text="INSERT INTO song (artist, song, album, year, source, comment, time, full_data) VALUES ( ";
   // artist
   if ((AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),2),30))).Length()>1)
   {
   BArtist=AnsiString(SentenceToSQL(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),2),30),30,'\`'));
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'"+BArtist+  "', ";
   }
   else
   {
    if (!CheckBox2->Checked)
    ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'Unknown Artist', ";
    else
    {
    BArtist=AnsiString(SentenceToSQL(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),1),Form1->ListBox1->Items->Strings[i].Length(),'\`'));
    ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'"+BArtist+"', ";
    }
    id_error++;
   }
   // title
   if ((AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),1),30))).Length()>1)
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'"+AnsiString(SentenceToSQL(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),1),30),30,'\`')) +  "', ";
   else { ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'Unknown Title', "; id_error++;}
   // album
   if ((AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),3),30))).Length()>1)
   {
   BAlbum=AnsiString(SentenceToSQL(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),3),30),30,'\`'));
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'"+BAlbum +  "', ";
   }
   else
    {
     if (!CheckBox2->Checked)
     ADQuery1->SQL->Text=ADQuery1->SQL->Text+"' ', ";
     else
     {
     BAlbum=AnsiString(SentenceToSQL(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),4),Form1->ListBox1->Items->Strings[i].Length(),'\`'));
     ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'"+BAlbum+"', ";
     }
    }
   // year
   if ((AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),4),30))).Length()==4 && isdigit((AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),4),30)))[1]) && isdigit((AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),4),30)))[2]) && isdigit((AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),4),30)))[3]))
   {
   BYear=AnsiString(SentenceToSQL(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),4),4),4,'\`'));
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+BYear +  ", ";
   }
   else
   {
    if (CheckBox2->Checked)
     {
     if (AnsiString(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),3))!="NULL" && AnsiString(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),3)).Length()>3)
     {
     BYear=AnsiString(SentenceToSQL(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),3),Form1->ListBox1->Items->Strings[i].Length(),'\`'));
     ADQuery1->SQL->Text=ADQuery1->SQL->Text+BYear+", ";
     }
     else ADQuery1->SQL->Text=ADQuery1->SQL->Text+"NULL, ";
     }
     else ADQuery1->SQL->Text=ADQuery1->SQL->Text+"NULL, ";
   }
   // source
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'"+AnsiString(SentenceToSQL(Form1->ListBox1->Items->Strings[i].c_str(),(Form1->ListBox1->Items->Strings[i]).Length(),'\`'))+"', ";
   //ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'source', '"; // debug
   // comment
   if ((AnsiString(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),5),30))).Length()>2)
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'"+AnsiString(SentenceToSQL(NullRemoval(GetMp3Tag_DLL(Form1->ListBox1->Items->Strings[i].c_str(),5),28),28,'\`')) +  "', ";
   else ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'NONE', ";
   // time
   /* he-he from Jim ;) */
   if (CheckBox1->Checked)
   {
   MediaPlayer1->FileName=Form1->ListBox1->Items->Strings[i];
   try {
   MediaPlayer1->Open();
   int retvalue=0,retvalue2=0;
   retvalue=Floor(((((StrToFloat(MediaPlayer1->Length))/1000)/60)-(StrToInt(MediaPlayer1->Length)/1000)/60)*60);
   retvalue2=Floor(((StrToInt(MediaPlayer1->Length)/1000)/60)-(((StrToInt(MediaPlayer1->Length)/1000)/60)/60)*60);
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'" + FloatToStr(((StrToInt(MediaPlayer1->Length)/1000)/60)/60)+ ":" + FloatToStr(retvalue2) + ":" + FloatToStr(retvalue)+"', ";
   }
   catch (...) { ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'00:00:00', "; id_error++;}
   }
   else ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'00:00:00', ";
   //
   //true-false conditions //
   if (!id_error)
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'T')";
   else
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'F')";
   Memo2->Text=ADQuery1->SQL->Text;
   ADQuery1->ExecSQL();
   /* --- end of MySQL Query Block */
   }
   /* If ID3V1 Tag is wrong */
   else {
   Form1->ListBox2->Items->Add(AnsiString(crofilename(Form1->ListBox1->Items->Strings[i].c_str())));
   Edit1->Text = AnsiString(crofilename(Form1->ListBox1->Items->Strings[i].c_str()));
   Edit2->Text = "";   Edit3->Text = "";   Edit4->Text = "";   Edit5->Text = "";   Edit6->Text = "FALSE";
   ADQuery1->SQL->Text="INSERT INTO song (artist, song, album, year, source, full_data, time) VALUES (";
//artist
   if (!CheckBox2->Checked)
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'Unknown Artist', '";
   else
   {
   BArtist=AnsiString(SentenceToSQL(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),1),Form1->ListBox1->Items->Strings[i].Length(),'\`'));
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'"+BArtist+"', ";
   }
// Song
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'Unknown Title', ";
//album
   if (!CheckBox2->Checked)
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"' ', ";
   else
   {
   BAlbum=AnsiString(SentenceToSQL(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),4),Form1->ListBox1->Items->Strings[i].Length(),'\`'));
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'"+BAlbum+"', ";
   }
//year
   if (CheckBox2->Checked)
   {
   if (AnsiString(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),3))!="NULL" && AnsiString(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),3)).Length()>3)
   {
   BYear=AnsiString(SentenceToSQL(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),3),Form1->ListBox1->Items->Strings[i].Length(),'\`'));
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+BYear+", ";
   }
   else ADQuery1->SQL->Text=ADQuery1->SQL->Text+"NULL, ";
   }
   else ADQuery1->SQL->Text=ADQuery1->SQL->Text+"NULL, ";
   ADQuery1->SQL->Text=ADQuery1->SQL->Text +"'"+AnsiString(SentenceToSQL(Form1->ListBox1->Items->Strings[i].c_str(),(Form1->ListBox1->Items->Strings[i]).Length(),'\`')) +"', 'F', ";
   // time
   if (CheckBox1->Checked)
   {
   MediaPlayer1->FileName=Form1->ListBox1->Items->Strings[i];
   try {
   MediaPlayer1->Open();
   int retvalue=0,retvalue2=0;
   retvalue=Floor(((((StrToFloat(MediaPlayer1->Length))/1000)/60)-(StrToInt(MediaPlayer1->Length)/1000)/60)*60);
   retvalue2=Floor(((StrToInt(MediaPlayer1->Length)/1000)/60)-(((StrToInt(MediaPlayer1->Length)/1000)/60)/60)*60);
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'" + FloatToStr(((StrToInt(MediaPlayer1->Length)/1000)/60)/60)+ ":" + FloatToStr(retvalue2) + ":" + FloatToStr(retvalue)+"')";
   }
   catch (...) { ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'00:00:00')";}
   }
   else ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'00:00:00');";

   Memo2->Text=ADQuery1->SQL->Text;
   ADQuery1->ExecSQL();
   }
   }
   /* If file haven't ID3V1 Tag */
   else { Form1->ListBox2->Items->Add(AnsiString(crofilename(Form1->ListBox1->Items->Strings[i].c_str()))); error=0;
ADQuery1->SQL->Text="INSERT INTO song (artist, song, album, year, source, full_data, time) VALUES (";
//artist
   if (!CheckBox2->Checked)
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'Unknown Artist', '";
   else
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'"+AnsiString(SentenceToSQL(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),1),Form1->ListBox1->Items->Strings[i].Length(),'\`'))+"', ";
// Song
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'Unknown Title', ";
//album
   if (!CheckBox2->Checked)
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"' ', ";
   else
   {
   BAlbum=AnsiString(SentenceToSQL(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),4),Form1->ListBox1->Items->Strings[i].Length(),'\`'));
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'"+BAlbum+"', ";
   }
//year
   if (CheckBox2->Checked)
   {
   if (AnsiString(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),3))!="NULL" && AnsiString(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),3)).Length()>3)
   {
   BYear=AnsiString(SentenceToSQL(PathToData(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),3),Form1->ListBox1->Items->Strings[i].Length(),'\`'));
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+BYear+", ";
   }
   else ADQuery1->SQL->Text=ADQuery1->SQL->Text+"NULL, ";
   }
   else ADQuery1->SQL->Text=ADQuery1->SQL->Text+"NULL, ";
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'"+AnsiString(SentenceToSQL(Form1->ListBox1->Items->Strings[i].c_str(),(Form1->ListBox1->Items->Strings[i]).Length(),'\`')) +"', 'F', ";
   /*--- end ---*/
   // time
   if (CheckBox1->Checked)
   {
   MediaPlayer1->FileName=Form1->ListBox1->Items->Strings[i];
   try {
   MediaPlayer1->Open();
   int retvalue=0,retvalue2=0;
   retvalue=Floor(((((StrToFloat(MediaPlayer1->Length))/1000)/60)-(StrToInt(MediaPlayer1->Length)/1000)/60)*60);
   retvalue2=Floor(((StrToInt(MediaPlayer1->Length)/1000)/60)-(((StrToInt(MediaPlayer1->Length)/1000)/60)/60)*60);
   ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'" + FloatToStr(((StrToInt(MediaPlayer1->Length)/1000)/60)/60)+ ":" + FloatToStr(retvalue2) + ":" + FloatToStr(retvalue)+"')";
   }
   catch (...) { ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'00:00:00')";}
   }
   else ADQuery1->SQL->Text=ADQuery1->SQL->Text+"'00:00:00')";

   Memo2->Text=ADQuery1->SQL->Text;
   ADQuery1->ExecSQL();
   Edit1->Text = AnsiString(crofilename(Form1->ListBox1->Items->Strings[i].c_str()));
   Edit2->Text = "";   Edit3->Text = "";   Edit4->Text = "";   Edit5->Text = "";   Edit6->Text = "FALSE";
   }
   if (CheckBox4->Checked)
   Memo1->Lines->Add(AnsiString(i+1)+ ". " + Edit1->Text + " - " + Edit2->Text + " \\ " + Edit3->Text + " \\ " + Edit4->Text + " \\ " + Edit5->Text + " && " + Edit6->Text);
/* Auto-Add Artist - To Album and Artist tables */
       if (CheckBox3->Checked)
       {
        if (BArtist.Length() && BArtist!="0")
        {
         ADQuery2->SQL->Text="select artist.id, UPPER(artist.artist) from artist where artist=UPPER('"+BArtist+"')";
         ADQuery2->Open();
         if(!ADQuery2->FieldByName("id")->AsInteger)
         {
         ADQuery2->Close();
         ADQuery2->SQL->Text="INSERT INTO artist (artist,source) VALUES ('"+BArtist+"', '"+AnsiString(SentenceToSQL(PathToDestination(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),1),Form1->ListBox1->Items->Strings[i].Length(),'\`'))+"')";
         Memo2->Text=ADQuery2->SQL->Text;
         ADQuery2->ExecSQL();
         }
         else ADQuery2->Close();
        }
        if (BArtist.Length() && BAlbum.Length() && BAlbum!="0" && BArtist!="0")
        {
         ADQuery2->SQL->Text="select album.id, UPPER(album.album) from album where album=UPPER('"+BAlbum+"')";
         ADQuery2->Open();
         if(!ADQuery2->FieldByName("id")->AsInteger)
         {
         ADQuery2->Close();
         ADQuery2->SQL->Text="INSERT INTO album (artist,album,year,source) VALUES ('"+BArtist+"', '"+BAlbum+"', ";
         if (BYear.Length() && BYear!="0")
         ADQuery2->SQL->Text=ADQuery2->SQL->Text+BYear+", ";
         else
         ADQuery2->SQL->Text=ADQuery2->SQL->Text+"NULL, ";
         ADQuery2->SQL->Text=ADQuery2->SQL->Text+"'"+AnsiString(SentenceToSQL(PathToDestination(Form1->ListBox1->Items->Strings[i].c_str(),Form1->ListBox1->Items->Strings[i].Length(),2),Form1->ListBox1->Items->Strings[i].Length(),'\`'))+"')";
         Memo2->Text=ADQuery2->SQL->Text;
         ADQuery2->ExecSQL();
         }
         else ADQuery2->Close();
        }
       BArtist=NULL;
       BAlbum=NULL;
       BYear=NULL;
       }
// end of Auto-Add Artist //
  }
  }
  catch(...)
  {  }
CGauge1->Progress=CGauge1->MaxValue;
ListBox1->Items->Clear();
LabeledEdit1->Text="None";
LabeledEdit1->Color=clWhite;
// comment next line to debug SQL
Memo2->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBMemo1Change(TObject *Sender)
{
MediaPlayer1->FileName=AnsiString(SentenceToSQL((DBMemo1->Text).c_str(),DBMemo1->Text.Length(),'\''));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BMCIClick(TObject *Sender)
{
/* MCI - you may have troubles without soundcard! */
try {
MediaPlayer1->Stop();
MediaPlayer1->Close();
}
catch (...) { }
MediaPlayer1->Open();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BAddArtistPicInHTMLClick(TObject *Sender)
{
DBComboBox1->DataField="";
DBImage1->DataField="";
DBMemo1->DataField="";
DBMemo2->DataField="";

try { ADQuery2->Close(); } //
catch (...) {}
ADQuery2->SQL->Text="select artist from song GROUP BY artist ORDER BY genre, artist";
ADQuery2->Open();
ADQuery2->First();
ListBox3->Items->Clear();
while (!ADQuery2->Eof) {
    ListBox3->Items->Add(ADQuery2->FieldByName("artist")->AsString);
    ADQuery2->Next();
    }
CGauge1->MaxValue=Form1->ListBox3->Items->Count;
CGauge1->Progress=0;
for (int i=0;i<Form1->ListBox3->Items->Count;i++)
{
CGauge1->Progress=i;
 /* Artist Picture */   //
 Graphics::TBitmap *B = new Graphics::TBitmap();
 TJPEGImage* JPEG=new TJPEGImage();
 try { ADQuery1->Close(); }
 catch (...) {}
 ADQuery1->SQL->Text="select picture from artist where artist.artist='"+ListBox3->Items->Strings[i]+"' ORDER BY genre, artist";
 ADQuery1->Open();
 TStream *S2=ADQuery1->CreateBlobStream(ADQuery1->FieldByName("picture"),bmRead);
 S2->Position=0;
 B->LoadFromStream(S2);
 JPEG->Assign(B);
 JPEG->SaveToFile("HTML\\ARTISTS\\"+AnsiString(i)+".jpg");
 }
CGauge1->Progress=Form1->ListBox3->Items->Count;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BAddPictureClick(TObject *Sender)
{
/* Add Picture */
if(OpenPictureDialog1->Execute())
{
Graphics::TBitmap *B = new Graphics::TBitmap();
TJPEGImage* J=new TJPEGImage();
/* JPEG Image*/
if(ExtractFileExt(OpenPictureDialog1->FileName)==".jpg" || ExtractFileExt(OpenPictureDialog1->FileName)==".JPG" || ExtractFileExt(OpenPictureDialog1->FileName)==".jpeg" || ExtractFileExt(OpenPictureDialog1->FileName)==".JPEG")
{
J->LoadFromFile(OpenPictureDialog1->FileName);
B->Assign(J);
/* Conditions based on maximum blob size in MySQL 5.x,  about 4m */
if ((B->Width<600 || B->Height<600) && (B->Width*B->Height<300000))
{         //
DataSource1->DataSet->Edit();
DBImage1->Picture->Assign(B);
DataSource1->DataSet->UpdateRecord();
}
delete B; delete J;
}
/* BMP Image */
else
{
B->LoadFromFile(OpenPictureDialog1->FileName);
/* Conditions based on maximum blob size in MySQL 5.x,  about 4m */
if ((B->Width<600 || B->Height<600) && (B->Width*B->Height<300000))
{
DBImage1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
DataSource1->DataSet->UpdateRecord();
}
delete B; delete J;   //
}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
/* Select Query by ComboBox */
if (ComboBox1->ItemIndex==0 && admin)
{
ADUpdateSQL1->InsertSQL->Text="INSERT INTO song  (id, artist, song, album, year, genre, source, time, lyric, comment, full_data) VALUES   (:id, :artist, :song, :album, :year, :genre, :source, :time, :lyric, :comment, :full_data)";
ADUpdateSQL1->ModifySQL->Text="UPDATE song SET  id = :id, artist = :artist, song = :song, album = :album, year = :year, genre = :genre, source = :source, time = :time, lyric = :lyric, comment = :comment, full_data = :full_data WHERE  id = :Old_id";
ADUpdateSQL1->DeleteSQL->Text="DELETE FROM song WHERE  id = :Old_id";
ADQuery1->SQL->Text="SELECT song.id, song.artist, song.song, song.album, song.year, song.genre, song.source, song.time, song.lyric, song.comment, song.full_data FROM song";
DBMemo1->DataField="source";
DBMemo2->DataField="lyric";
DBImage1->DataField="";
DBComboBox1->DataField="genre";
ADQuery1->Open();
}
else if (ComboBox1->ItemIndex==1  && admin)
{
ADUpdateSQL1->InsertSQL->Text="INSERT INTO artist  (id, artist, genre, source, comment, picture) VALUES  (:id, :artist, :genre, :source, :comment, :picture)";
ADUpdateSQL1->ModifySQL->Text="UPDATE artist SET  id = :id, artist = :artist, genre = :genre, source = :source, comment = :comment, picture = :picture WHERE  id = :Old_id";
ADUpdateSQL1->DeleteSQL->Text="DELETE FROM artist WHERE  id = :Old_id";
ADQuery1->SQL->Text="SELECT artist.id, artist.artist, artist.genre, artist.source, artist.comment, artist.picture FROM artist";
DBMemo1->DataField="source";
DBMemo2->DataField="comment";
DBImage1->DataField="picture";
DBComboBox1->DataField="genre";
ADQuery1->Open();
}
else if (ComboBox1->ItemIndex==2  && admin)
{
ADUpdateSQL1->InsertSQL->Text="INSERT INTO album  (id, artist, album, year, genre, source, comment, cover) VALUES  (:id, :artist, :album, :year, :genre, :source, :comment, :cover)";
ADUpdateSQL1->ModifySQL->Text="UPDATE album SET  id = :id, artist = :artist, album = :album, year = :year, genre = :genre, source = :source, comment = :comment, cover = :cover WHERE  id = :Old_id";
ADUpdateSQL1->DeleteSQL->Text="DELETE FROM album WHERE  id = :Old_id";
ADQuery1->SQL->Text="SELECT album.id, album.artist, album.album, album.year, album.genre, album.source, album.comment, album.cover FROM album";
DBMemo1->DataField="source";
DBMemo2->DataField="comment";
DBImage1->DataField="cover";
DBComboBox1->DataField="genre";
ADQuery1->Open();
}
// USER
else if (ComboBox1->ItemIndex==3)
{
DBMemo1->DataField="";
DBMemo2->DataField="";
DBImage1->DataField="";
DBComboBox1->DataField="";
ADUpdateSQL1->InsertSQL->Text="";
ADUpdateSQL1->ModifySQL->Text="";
ADUpdateSQL1->DeleteSQL->Text="";
ADQuery1->SQL->Text="SELECT song, artist, album, year, time FROM user_cut_songs ORDER BY artist, year, album, song ASC;";
ADQuery1->Open();
}
else if (ComboBox1->ItemIndex==4)
{
DBMemo1->DataField="";
DBMemo2->DataField="";
DBImage1->DataField="";
DBComboBox1->DataField="";
ADUpdateSQL1->InsertSQL->Text="";
ADUpdateSQL1->ModifySQL->Text="";
ADUpdateSQL1->DeleteSQL->Text="";
ADQuery1->SQL->Text="SELECT artist, album, year, total FROM user_cut_albums";
ADQuery1->Open();
}
else if (ComboBox1->ItemIndex==5)
{
DBMemo1->DataField="";
DBMemo2->DataField="";
DBImage1->DataField="";
DBComboBox1->DataField="";
ADUpdateSQL1->InsertSQL->Text="";
ADUpdateSQL1->ModifySQL->Text="";
ADUpdateSQL1->DeleteSQL->Text="";
ADQuery1->SQL->Text="SELECT artist, songs, albums FROM user_cut_artist";
ADQuery1->Open();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BAddLyricInHTMLClick(TObject *Sender)
{
DBComboBox1->DataField="";
DBImage1->DataField="";
DBMemo1->DataField="";
DBMemo2->DataField="";
try { ADQuery2->Close(); } //
catch (...) {}
ADQuery2->SQL->Text="select artist from song GROUP BY artist ORDER BY genre, artist";
ADQuery2->Open();
ADQuery2->First();
ListBox3->Items->Clear();
while (!ADQuery2->Eof) {
    ListBox3->Items->Add(ADQuery2->FieldByName("artist")->AsString);
    ADQuery2->Next();
    }
CGauge1->MaxValue=Form1->ListBox3->Items->Count;
CGauge1->Progress=0;
for (int i=0;i<Form1->ListBox3->Items->Count;i++)
{
CGauge1->Progress=i;
 try { ADQuery1->Close(); }
 catch (...) {}
 ADQuery1->SQL->Text="select album from song where song.artist='"+ListBox3->Items->Strings[i]+"'  GROUP by album ORDER BY genre, artist, year, album";
 ADQuery1->Open();
 ADQuery1->First();
 int j=0;
 while (!ADQuery1->Eof)
 {
j++;
int k=0;
try { ADQuery2->Close(); }
catch (...) {}
ADQuery2->SQL->Text="select song, lyric as lyric from song where song.album='"+AnsiString(ADQuery1->FieldByName("album")->AsString)+"' ORDER BY genre, artist, year, album";
ADQuery2->Open();
ADQuery2->First();
DBMemo2->DataSource=DataSource2;
DBMemo2->DataField="lyric";
while (!ADQuery2->Eof)
{
k++;
Memo2->Lines->Clear();
Memo2->Lines->Add("<HTML><HEAD><TITLE>Sirius DB - "+ListBox3->Items->Strings[i]+" - "+AnsiString(ADQuery2->FieldByName("song")->AsString)+"</TITLE></HEAD><BODY>");
for (int h=0;h<DBMemo2->Lines->Count;h++)
Memo2->Lines->Add(DBMemo2->Lines->Strings[h]+"<BR>");
Memo2->Lines->Add("</BODY></HTML>");
Memo2->Lines->SaveToFile("HTML\\LYRICS\\"+AnsiString(i)+"_"+AnsiString(j)+"_"+AnsiString(k)+".html");
ADQuery2->Next();
}
DBMemo2->DataField="";
DBMemo2->DataSource=DataSource1;
ADQuery1->Next();
 }
}
CGauge1->Progress=Form1->ListBox3->Items->Count;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BAddAlbumPicInHTMLClick(TObject *Sender)
{
DBComboBox1->DataField="";
DBImage1->DataField="";
DBMemo1->DataField="";
DBMemo2->DataField="";

 Graphics::TBitmap *B = new Graphics::TBitmap();
 TJPEGImage* JPEG=new TJPEGImage();
try { ADQuery2->Close(); } //
catch (...) {}
ADQuery2->SQL->Text="select artist from song GROUP BY artist ORDER BY genre, artist";
ADQuery2->Open();
ADQuery2->First();
ListBox3->Items->Clear();
while (!ADQuery2->Eof) {
    ListBox3->Items->Add(ADQuery2->FieldByName("artist")->AsString);
    ADQuery2->Next();
    }
CGauge1->MaxValue=Form1->ListBox3->Items->Count;
CGauge1->Progress=0;
for (int i=0;i<Form1->ListBox3->Items->Count;i++)
{
CGauge1->Progress=i;
 try { ADQuery1->Close(); }
 catch (...) {}
 ADQuery1->SQL->Text="select cover from album where album.artist='"+ListBox3->Items->Strings[i]+"' ORDER BY genre, artist, year, album";
 ADQuery1->Open();
 ADQuery1->First();
 int j=0;
 while (!ADQuery1->Eof)
 {
 j++;
 TStream *S2=ADQuery1->CreateBlobStream(ADQuery1->FieldByName("cover"),bmRead);
 S2->Position=0;
 B->LoadFromStream(S2);
 JPEG->Assign(B);
 JPEG->SaveToFile("HTML\\ALBUMS\\"+AnsiString(i)+"_"+AnsiString(j)+".jpg");
 ADQuery1->Next();
 }
 }
CGauge1->Progress=Form1->ListBox3->Items->Count;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BAddOneSongClick(TObject *Sender)
{
if (OpenDialog2->Execute())
{
ListBox1->Items->Add(OpenDialog2->FileName);
if (ListBox1->Items->Count)
{
LabeledEdit1->Color=clRed;
LabeledEdit1->Text="Ready: " + AnsiString(ListBox1->Items->Count);
}
else { LabeledEdit1->Text="None"; LabeledEdit1->Color=clWhite;}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BSearchClick(TObject *Sender)
{
DBMemo1->DataField="";
DBMemo2->DataField="";
DBEdit1->DataField="";
DBImage1->DataField="";
DBComboBox1->DataField="";
ADUpdateSQL1->InsertSQL->Text="";
ADUpdateSQL1->DeleteSQL->Text="";
ADUpdateSQL1->ModifySQL->Text="";
//USER
if (CBSearch->ItemIndex==0)   // by song
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from user_cut_songs where song LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album, song LIMIT 20";
ADQuery1->Open();
}
if (CBSearch->ItemIndex==1)  // by album
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from user_cut_songs where album LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album, song LIMIT 20";
ADQuery1->Open();
}
else if (CBSearch->ItemIndex==2) // by artist
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from user_cut_songs where artist LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album, song LIMIT 20";
ADQuery1->Open();
}
else if (CBSearch->ItemIndex==3) // albums
{
try { ADQuery1->Close(); }
catch (...) {}
if (!CheckBox5->Checked)
ADQuery1->SQL->Text="select * from user_cut_albums where album LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album LIMIT 20";
else
{
ADQuery1->SQL->Text="select * from user_cut_albums_full where album LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album LIMIT 20";
DBImage1->DataField="cover";
}
ADQuery1->Open();

}
else if (CBSearch->ItemIndex==4) // artists
{
try { ADQuery1->Close(); }
catch (...) {}
if (!CheckBox5->Checked)
ADQuery1->SQL->Text="select * from user_cut_artist where artist LIKE '%"+ESearch->Text+"%' ORDER BY artist LIMIT 20";
else
{
ADQuery1->SQL->Text="select * from user_cut_artist_full where artist LIKE '%"+ESearch->Text+"%' ORDER BY artist LIMIT 20";
DBImage1->DataField="picture";
}
ADQuery1->Open();
}
else if (CBSearch->ItemIndex==5) // anywhere
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from user_cut_songs where artist LIKE '%"+ESearch->Text+"%' OR album LIKE '%"+ESearch->Text+"%' OR song LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album, song LIMIT 20";
ADQuery1->Open();
}
// ADMIN
else if (CBSearch->ItemIndex==6 && admin)  // song
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from song where song LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album, song";
ADQuery1->Open();
DBMemo1->DataField="source";
DBMemo2->DataField="lyric";
DBComboBox1->DataField="genre";
}
else if (CBSearch->ItemIndex==7 && admin) // album
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from song where album LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album, song";
ADQuery1->Open();
DBMemo1->DataField="source";
DBMemo2->DataField="lyric";
DBComboBox1->DataField="genre";
}
else if (CBSearch->ItemIndex==8 && admin) // artist
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from song where artist LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album, song";
ADQuery1->Open();
DBMemo1->DataField="source";
DBMemo2->DataField="lyric";
DBComboBox1->DataField="genre";
}
else if (CBSearch->ItemIndex==9  && admin) // anywhere
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from song where artist LIKE '%"+ESearch->Text+"%' OR album LIKE '%"+ESearch->Text+"%' OR song LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album, song";
ADQuery1->Open();
DBMemo1->DataField="source";
DBMemo2->DataField="lyric";
DBComboBox1->DataField="genre";
}
else if (CBSearch->ItemIndex==10  && admin)  // song-album
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from song where album LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album, song";
ADQuery1->Open();
DBMemo1->DataField="source";
DBMemo2->DataField="lyric";
DBComboBox1->DataField="genre";
}
else if (CBSearch->ItemIndex==11  && admin)  // song-artist
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from song where artist LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album, song";
ADQuery1->Open();
DBMemo1->DataField="source";
DBMemo2->DataField="lyric";
DBComboBox1->DataField="genre";
}
else if (CBSearch->ItemIndex==12  && admin)  // album-artist
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from album where artist LIKE '%"+ESearch->Text+"%' ORDER BY artist, year, album";
ADQuery1->Open();
DBMemo1->DataField="source";
DBMemo2->DataField="comment";
DBImage1->DataField="cover";
DBComboBox1->DataField="genre";
}
else if (CBSearch->ItemIndex==13  && admin)  // album-year
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from album where year = "+ESearch->Text+" ORDER BY artist, year, album";
ADQuery1->Open();
DBMemo1->DataField="source";
DBMemo2->DataField="comment";
DBImage1->DataField="cover";
DBComboBox1->DataField="genre";
}
else if (CBSearch->ItemIndex==14  && admin)  // song-year
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from song where year = "+ESearch->Text+" ORDER BY artist, year, album, song";
ADQuery1->Open();
DBMemo1->DataField="source";
DBMemo2->DataField="lyric";
DBComboBox1->DataField="genre";
}
// FUNCTIONS
else if (CBSearch->ItemIndex==19  && admin) // time by artist
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select return_time('"+ESearch->Text+"',2,0) as Full_Time";
ADQuery1->Open();
DBMemo2->DataField="Full_Time";
}
else if (CBSearch->ItemIndex==20  && admin) // time by album
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select return_time('"+ESearch->Text+"',1,0) as Full_Time";
ADQuery1->Open();
DBMemo2->DataField="Full_Time";
}
else if (CBSearch->ItemIndex==21  && admin) // time by genre
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select return_time('"+ESearch->Text+"',3,0) as Full_Time";
ADQuery1->Open();
DBMemo2->DataField="Full_Time";
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CBSearchChange(TObject *Sender)
{
DBMemo1->DataField="";
DBMemo2->DataField="";
DBEdit1->DataField="";
DBImage1->DataField="";
DBComboBox1->DataField="";
if (CBSearch->ItemIndex==15 && admin) // songs
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select count(id) as Songs_Total from song";
ADQuery1->Open();
}
else if (CBSearch->ItemIndex==16  && admin) // artists
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select count(id) as Artists_Total from artist";
ADQuery1->Open();
}
else if (CBSearch->ItemIndex==17  && admin) // albums
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select count(id) as Albums_Total from album";
ADQuery1->Open();
}
else if (CBSearch->ItemIndex==18  && admin) // full time
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select return_time('%',0,0) as Full_Time";
ADQuery1->Open();
DBMemo2->DataField="Full_Time";
}
else if (CBSearch->ItemIndex==22  && admin) // min_time
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from song where time=(Select min(time) AS mtime from song GROUP BY time LIMIT 1)";
ADQuery1->Open();
}
else if (CBSearch->ItemIndex==23  && admin) //max_time
{
try { ADQuery1->Close(); }
catch (...) {}
ADQuery1->SQL->Text="select * from song where time=(Select max(time) AS mtime from song GROUP BY time  LIMIT 1)";
ADQuery1->Open();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BRunDBFunctionsClick(TObject *Sender)
{
/* DB Functions */
/* Step-by-step call system procedures */
ShowMessage("Be patient!\nThis process will take a lot of time.\nIt may hang up your PC\nIf progress bar in motion - do not shut down system!\nIf process once or twice failed, then maintain DB manually.");
CGauge1->MaxValue=8;
CGauge1->Progress=0;
ADQuery1->SQL->Text="call delete_artist_dupe()";
ADQuery1->ExecSQL();
CGauge1->Progress=1;
ADQuery1->SQL->Text="call delete_album_dupe(0)";
ADQuery1->ExecSQL();
CGauge1->Progress=2;
ADQuery1->SQL->Text="call delete_song_dupe(0)";
ADQuery1->ExecSQL();
CGauge1->Progress=3;
ADQuery1->SQL->Text="call insert_song_artist()";
ADQuery1->ExecSQL();
CGauge1->Progress=4;
ADQuery1->SQL->Text="call insert_song_album()";
ADQuery1->ExecSQL();
CGauge1->Progress=5;
ADQuery1->SQL->Text="call insert_album_artist()";
ADQuery1->ExecSQL();
CGauge1->Progress=6;
ADQuery1->SQL->Text="call delete_empty_artist()";
ADQuery1->ExecSQL();
CGauge1->Progress=7;
ADQuery1->SQL->Text="call delete_empty_album()";
ADQuery1->ExecSQL();
CGauge1->Progress=8;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BAESClick(TObject *Sender)
{
/* AES - for developer only */
Memo1->Lines->Clear();
for (int i=0;i<Memo2->Lines->Count;i++)
{
ADQuery1->SQL->Text="Select AES_ENCRYPT(\""+Memo2->Lines->Strings[i]+"\",\"qwertyuiop\") AS AESEC";
ADQuery1->Open();
DBEdit1->DataField="AESEC";
Memo1->Lines->Add(DBEdit1->Text);
}
Memo1->Lines->SaveToFile(Edit7->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
//Form1->Visible=false;
LoginForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button19Click(TObject *Sender)
{
Form2->ShowModal();
}
//---------------------------------------------------------------------------

