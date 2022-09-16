//---------------------------------------------------------------------------

#include <vcl.h>
#include <Graphics.hpp>
#include <Jpeg.hpp>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "daADCompClient"
#pragma link "daADCompDataSet"
#pragma link "daADDAptIntf"
#pragma link "daADDatSManager"
#pragma link "daADGUIxFormsfAsync"
#pragma link "daADGUIxFormsfError"
#pragma link "daADGUIxFormsfLogin"
#pragma link "daADGUIxFormsfQBldr"
#pragma link "daADGUIxFormsQBldr"
#pragma link "daADGUIxFormsWait"
#pragma link "daADPhysIntf"
#pragma link "daADPhysManager"
#pragma link "daADPhysMySQL"
#pragma link "daADStanDef"
#pragma link "daADStanIntf"
#pragma link "daADStanOption"
#pragma link "daADStanParam"
#pragma link "CSPIN"
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
ADQuery1->SQL->Text=Memo1->Text;
ADQuery1->Open();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
ADQuery1->SQL->Text=Memo1->Text;
ADQuery1->ExecSQL();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CSpinEdit1Change(TObject *Sender)
{
CSpinEdit2->Value=1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
CSpinEdit1->Value++;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
ADQuery1->SQL->Text="INSERT INTO TMOVIE  (Disk_No, DM_Num, M_Title, M_Genre, M_YEAR, M_Director) VALUES ("+AnsiString(CSpinEdit1->Value)+","+AnsiString(CSpinEdit2->Value)+", '"+AnsiString(Edit1->Text)+"', '"+AnsiString(ComboBox1->Items->Strings[ComboBox1->ItemIndex])+"', '"+AnsiString(Edit3->Text)+"', '"+AnsiString(Edit2->Text)+"' );";
Memo2->Lines->Clear();
Memo2->Text=ADQuery1->SQL->Text;
ADQuery1->ExecSQL();
CSpinEdit2->Value++;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
//ADQuery1->SQL->Text="select * from TMOVIE where M_Title rlike '"+AnsiString(Edit4->Text)+"' UNION select * from TMOVIE where M_Director rlike '"+AnsiString(Edit4->Text)+"';";
ADQuery1->SQL->Clear();
ADQuery1->SQL->Add("select * from TMOVIE where M_id<>0 ");
//if (Edit4->Text!=NULL && Edit5->Text.ToInt()==0 && Edit6->Text.ToInt()==0 && ComboBox2->ItemIndex==0)
if (Edit4->Text.Length()!=NULL)
ADQuery1->SQL->Add("AND M_Title rlike '"+Edit4->Text+"' ");
if (Edit5->Text.ToInt()!=0)
ADQuery1->SQL->Add("AND M_YEAR>="+Edit5->Text+" ");
if (Edit6->Text.ToInt()!=0)
ADQuery1->SQL->Add("AND M_YEAR<="+Edit6->Text+" ");
if (ComboBox2->ItemIndex!=0)
ADQuery1->SQL->Add("AND M_genre='"+AnsiString(ComboBox2->Items->Strings[ComboBox2->ItemIndex])+"' ");
if (Edit7->Text.Length()!=NULL)
ADQuery1->SQL->Add("AND M_Director rlike '"+Edit7->Text+"' ");
ADQuery1->SQL->Add(";");
Memo1->Lines->Clear();
Memo1->Text=ADQuery1->Text;
ADQuery1->Open();
Edit1->Clear();
Edit2->Text=" ";
Edit3->Text="0";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
try {
ADConnection1->Connected=true;
//ADQuery2->SQL->Text="select * from mov_db.tmovie; ";
//Sleep(2000);
//ADQuery2->Close();
//ShowMessage("?");
ADQuery2->SQL->Text="select max(Disk_no) as DNN from TMOVIE ";
ADQuery2->Open();
ADQuery2->First();
//ShowMessage(AnsiString(ADQuery2->FieldByName("DNN")->AsInteger));
CSpinEdit1->Value=(ADQuery2->FieldByName("DNN")->AsInteger)+1;
ADQuery2->Close();
}
catch (...)
{ }
ADQuery1->SQL->Text="select * from tmovie where M_id=0; ";
ADQuery1->Open();
DataSource1->Enabled=true;
DBEdit7->DataField="M_id";
DBEdit6->DataField="M_YEAR";
DBEdit5->DataField="M_Genre";
DBEdit4->DataField="M_Director";
DBEdit3->DataField="M_Title";
DBEdit2->DataField="DM_Num";
DBEdit1->DataField="Disk_No";
DBMemo1->DataField="M_Text";
DBImage1->DataField="M_Blob";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
/*ADQuery2->SQL->Text="select max(Disk_no) as DNN from tmovie; ";
ADQuery2->Open();
ADQuery2->First();
ShowMessage(AnsiString(ADQuery2->FieldByName("DNN")->AsInteger));
CSpinEdit1->Value=(ADQuery2->FieldByName("DNN")->AsInteger)+1;
ADQuery2->Close();*/
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
void __fastcall TForm1::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_RETURN){
ADQuery1->SQL->Text="INSERT INTO TMOVIE  (Disk_No, DM_Num, M_Title, M_Genre, M_YEAR, M_Director) VALUES ("+AnsiString(CSpinEdit1->Value)+","+AnsiString(CSpinEdit2->Value)+", '"+AnsiString(Edit1->Text)+"', '"+AnsiString(ComboBox1->Items->Strings[ComboBox1->ItemIndex])+"', '"+AnsiString(Edit3->Text)+"', '"+AnsiString(Edit2->Text)+"' );";
Memo2->Lines->Clear();
Memo2->Text=ADQuery1->SQL->Text;
ADQuery1->ExecSQL();
CSpinEdit2->Value++;
Edit1->SelectAll();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel1Click(TObject *Sender)
{
//ADQuery1->SQL->Text="select * from TMOVIE where M_Title rlike '"+AnsiString(Edit4->Text)+"' UNION select * from TMOVIE where UCASE(M_Director) rlike UCASE('"+AnsiString(Edit4->Text)+"');";
ADQuery1->SQL->Clear();
ADQuery1->SQL->Add("select * from TMOVIE where M_id<>0 ");
//if (Edit4->Text!=NULL && Edit5->Text.ToInt()==0 && Edit6->Text.ToInt()==0 && ComboBox2->ItemIndex==0)
if (Edit4->Text.Length()!=NULL)
ADQuery1->SQL->Add("AND UCASE(M_Title) rlike UCASE('"+Edit4->Text+"') ");
if (Edit5->Text.ToInt()!=0)
ADQuery1->SQL->Add("AND M_YEAR>="+Edit5->Text+" ");
if (Edit6->Text.ToInt()!=0)
ADQuery1->SQL->Add("AND M_YEAR<="+Edit6->Text+" ");
if (ComboBox2->ItemIndex!=0)
ADQuery1->SQL->Add("AND M_genre='"+AnsiString(ComboBox2->Items->Strings[ComboBox2->ItemIndex])+"' ");
if (Edit7->Text.Length()!=NULL)
ADQuery1->SQL->Add("AND UCASE(M_Director) rlike UCASE('"+Edit7->Text+"') ");
ADQuery1->SQL->Add(";");
Memo1->Lines->Clear();
Memo1->Text=ADQuery1->Text;
ADQuery1->Open();
Edit1->Clear();
Edit2->Text=" ";
Edit3->Text="0";        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel2Click(TObject *Sender)
{
ADQuery1->SQL->Text="INSERT INTO TMOVIE  (Disk_No, DM_Num, M_Title, M_Genre, M_YEAR, M_Director) VALUES ("+AnsiString(CSpinEdit1->Value)+","+AnsiString(CSpinEdit2->Value)+", '"+AnsiString(Edit1->Text)+"', '"+AnsiString(ComboBox1->Items->Strings[ComboBox1->ItemIndex])+"', '"+AnsiString(Edit3->Text)+"', '"+AnsiString(Edit2->Text)+"' );";
Memo2->Lines->Clear();
Memo2->Text=ADQuery1->SQL->Text;
ADQuery1->ExecSQL();
CSpinEdit2->Value++;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel3Click(TObject *Sender)
{
CSpinEdit1->Value++;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel4Click(TObject *Sender)
{
/*ADQuery2->SQL->Text="select max(Disk_no) as DNN from tmovie; ";
ADQuery2->Open();
ADQuery2->First();
ShowMessage(AnsiString(ADQuery2->FieldByName("DNN")->AsInteger));
CSpinEdit1->Value=(ADQuery2->FieldByName("DNN")->AsInteger)+1;
ADQuery2->Close();*/
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

void __fastcall TForm1::Panel5Click(TObject *Sender)
{
ADQuery1->SQL->Text=Memo1->Text;
ADQuery1->Open();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel6Click(TObject *Sender)
{
ADQuery1->SQL->Text=Memo1->Text;
ADQuery1->ExecSQL();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel7Click(TObject *Sender)
{
DBImage1->Picture->Bitmap->Assign(NULL);
DBImage1->Picture->Bitmap->Height=0;
DBImage1->Picture->Bitmap->Width=0;
}
//---------------------------------------------------------------------------

