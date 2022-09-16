//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "login.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLoginForm *LoginForm;
//---------------------------------------------------------------------------
__fastcall TLoginForm::TLoginForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TLoginForm::Panel3Click(TObject *Sender)
{
AnsiString login,password,role; int j=0;
try {
Form1->ListBox1->Items->LoadFromFile("account.ini");
}
catch (...)
{
 ShowMessage("Can't open ini file!\nError: 5");
 Application->Terminate();
}
if (Form1->ListBox1->Items->Strings[0]=="true")
{
ShowMessage("First run! Be patient!\nIf programm crashes after login,\nuse your root login and pass\n");
 Form1->ADConnection1->Connected=false;
 Form1->ADConnection1->Params->BeginUpdate();
 Form1->ADConnection1->Params->Clear();
 Form1->ADConnection1->Params->Add("User_Name="+Edit1->Text);
 Form1->ADConnection1->Params->Add("Password="+Edit2->Text);
  Form1->ADConnection1->Params->Add("Host=192.168.1.2");
  Form1->ADConnection1->Params->Add("Port=3306");
 Form1->ADConnection1->Params->Add("DriverID=MySQL");  //
 Form1->ADConnection1->DriverName="MySQL";
 Form1->ADConnection1->Params->EndUpdate();
// Form1->ADConnection1->Params->SaveToFile("params.txt");
 try {
 Form1->ADConnection1->Connected=true;
 }
 catch (...)
 {
 ShowMessage("Wrong login\\password combination!\nError: 3");
 Application->Terminate();
 }
 try
{
 Form1->Memo2->Lines->LoadFromFile("setup.cfg");
 ShowMessage(AnsiString(Form1->Memo2->Lines->Count));
}
catch (...)
{
 ShowMessage("Can't open cfg file!\nError: 6");
 Application->Terminate();
}
Form1->Memo1->Lines->Clear();
for (int i=0;i<Form1->Memo2->Lines->Count;i++)
{
if (Form1->Memo2->Lines->Strings[i]=="###")
{
 j++;
 Form1->ADQuery2->SQL->Text=Form1->Memo1->Text;
 try {
 //ShowMessage(AnsiString(j));
 Form1->ADQuery2->ExecSQL();
 if (i==1)
 Sleep(500);
 }
 catch (...)
 {
 ShowMessage("SQL conflict or script error!\nError: 4-44");
 Application->Terminate();
 }
Form1->Memo1->Lines->Clear();
}
else
Form1->Memo1->Lines->Add(Form1->Memo2->Lines->Strings[i]);
}
Form1->ADQuery2->SQL->Text=Form1->Memo1->Text;
try {
Form1->ADQuery2->ExecSQL();
}
 catch (...)
 {
 ShowMessage("SQL conflict or script error!\nError: 4-4");
 Application->Terminate();
 }
Form1->ListBox1->Items->Strings[0]="false";
Form1->ListBox1->Items->SaveToFile("account.ini");
ShowMessage("Restarting programm now.\nNext time use admin or user logins.");
Application->Terminate();
}
bool error = true;
for (int i=1; i < Form1->ListBox1->Items->Count;i+=3)
{
role=Form1->ListBox1->Items->Strings[i];
if (role!="[ADMIN]" && role!="[USER]")
{
ShowMessage("Wrong ini file!\nError: 1");
Application->Terminate();
}
//if (Form1->ListBox1->Items->Strings[i+1]==login && Form1->ListBox1->Items->Strings[i+2]==password)
// {
 Form1->ADConnection1->Connected=false;
 Form1->ADConnection1->Params->BeginUpdate();
 Form1->ADConnection1->Params->Clear();
 Form1->ADConnection1->Params->Add("User_Name="+Edit1->Text);
 Form1->ADConnection1->Params->Add("Password="+Edit2->Text);
 Form1->ADConnection1->Params->Add("Database=sirius_db");
  Form1->ADConnection1->Params->Add("Host=192.168.1.2");
  Form1->ADConnection1->Params->Add("Port=3306");
 Form1->ADConnection1->Params->Add("DriverID=MySQL");  //
 Form1->ADConnection1->DriverName="MySQL";
 Form1->ADConnection1->Params->EndUpdate();
// Form1->ADConnection1->Params->SaveToFile("params.txt");
 try {
 Form1->ADConnection1->Connected=true;
 }
 catch (...)
 {
 ShowMessage("Wrong login\\password combination!\nError: 3");
 Application->Terminate();
 }
Form1->ADQuery1->SQL->Text="Select PASSWORD('"+Edit1->Text+"') As Log, PASSWORD('"+Edit2->Text+"') As Pass";
Form1->ADQuery1->Open();
Form1->DBEdit1->DataField="Log";
login=Form1->DBEdit1->Text;
Form1->DBEdit1->DataField="Pass";
password=Form1->DBEdit1->Text;
Form1->DBEdit1->DataField="";
Form1->ADQuery1->Close();
// Form1->ListBox1->Items->Clear();
if (!(Form1->ListBox1->Items->Strings[i+1]==login && Form1->ListBox1->Items->Strings[i+2]==password))
error=true;
else error=false;

 if (role=="[ADMIN]" && !error)
 {
 ShowMessage("Logged as admin on "+Now());
 Form1->admin=true;
 }
 else if (role=="[USER]" && !error)
 {
 ShowMessage("Logged as user on "+Now());
 Form1->admin=false;
 Form1->BAddAlbumPicInHTML->Enabled=false;
 Form1->BAddArtistPicInHTML->Enabled=false;
 Form1->BAddLyric->Enabled=false;
 Form1->BAddLyricInHTML->Enabled=false;
 Form1->BAddOneSong->Enabled=false;
 Form1->BAddPicture->Enabled=false;
 Form1->BAddSongList->Enabled=false;
 Form1->BAddSongs->Enabled=false;
 Form1->BClearTodo->Enabled=false;
 Form1->BExecQuery->Enabled=false;
 Form1->BExecSelect->Enabled=false;
 Form1->BGenerateHTML->Enabled=false;
 Form1->BGenerateHTMLForSingleArtist->Enabled=false;
 Form1->BRunDBFunctions->Enabled=false;
 Form1->BMCI->Enabled=false;
 Form1->BAES->Enabled=false;
 Form1->BCount->Enabled=false;
 Form1->DBNavigator1->Enabled=false;
 }
 Form1->Visible=true;
 LoginForm->Close();
if (Form1->ListBox1->Items->Strings[i+1]==login && Form1->ListBox1->Items->Strings[i+2]==password)
break;
// }
}
if (error)
{
ShowMessage("Wrong login\\password combination!\nError: 2");
Application->Terminate();
}
}
//---------------------------------------------------------------------------


