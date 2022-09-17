//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "parse.h"
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
AnsiString DD,MM,YY,HH,MI,SS,GMT,RID,LI,ART,TIT;
char FLC[1024];
//if (OpenDialog1->Execute())
//{
//Memo1->Lines->LoadFromFile(OpenDialog1->FileName);
Memo1->Lines->LoadFromFile("c:\\playlist.log");
for (int i=0;i<Memo1->Lines->Count;i++)
//for (int i=0;i<10;i++)
        {
        bool err=false, err2=true;
        int j=0; char printout;
        // date
        for (int k=0;k<Memo1->Lines->Strings[i].Length()-j;k++)
                {
                printout=Memo1->Lines->Strings[i][j+1];
//                while(err2)
//                {
                if (k==0)
                try {
                err2=false;
                AnsiString(printout).ToInt();
                }
                catch(...)
                {i++;k=0;j=0;err2=true;}
//                }
                if (printout=='\/')
                { FLC[k]='\0'; j++; break; }
                else
                { FLC[k]=printout; j++; }
                }
        //StringGrid1->Cells[1][i+1]=AnsiString(FLC);
        DD=AnsiString(FLC);
        // month
        for (int k=0;k<Memo1->Lines->Strings[i].Length()-j;k++)
                {
                printout=Memo1->Lines->Strings[i][j+1];
                if (printout=='\/')
                { FLC[k]='\0'; j++; break; }
                else
                { FLC[k]=printout; j++; }
                }
        //StringGrid1->Cells[2][i+1]=AnsiString(FLC);
        MM=AnsiString(FLC);
        if (MM=="Jan")
        MM="1";
        else if (MM=="Jan")
        MM="1";
        else if (MM=="Feb")
        MM="2";
        else if (MM=="Mar")
        MM="3";
        else if (MM=="Apr")
        MM="4";
        else if (MM=="May")
        MM="5";
        else if (MM=="Jun")
        MM="6";
        else if (MM=="Jul")
        MM="7";
        else if (MM=="Aug")
        MM="8";
        else if (MM=="Sep")
        MM="9";
        else if (MM=="Oct")
        MM="10";
        else if (MM=="Nov")
        MM="11";
        else if (MM=="Dec")
        MM="12";
        // year
        for (int k=0;k<Memo1->Lines->Strings[i].Length()-j;k++)
                {
                printout=Memo1->Lines->Strings[i][j+1];
                if (printout=='\:')
                { FLC[k]='\0'; j++; break; }
                else
                { FLC[k]=printout; j++; }
                }
//        StringGrid1->Cells[3][i+1]=AnsiString(FLC);
        YY=AnsiString(FLC);
        // hour
        for (int k=0;k<Memo1->Lines->Strings[i].Length()-j;k++)
                {
                printout=Memo1->Lines->Strings[i][j+1];
                if (printout=='\:')
                { FLC[k]='\0'; j++; break; }
                else
                { FLC[k]=printout; j++; }
                }
        //StringGrid1->Cells[4][i+1]=AnsiString(FLC);
        HH=AnsiString(FLC);
        // minute
        for (int k=0;k<Memo1->Lines->Strings[i].Length()-j;k++)
                {
                printout=Memo1->Lines->Strings[i][j+1];
                if (printout=='\:')
                { FLC[k]='\0'; j++; break; }
                else
                { FLC[k]=printout; j++; }
                }
        //StringGrid1->Cells[5][i+1]=AnsiString(FLC);
        MI=AnsiString(FLC);
        // second
        for (int k=0;k<Memo1->Lines->Strings[i].Length()-j;k++)
                {
                printout=Memo1->Lines->Strings[i][j+1];
                if (printout=='\ ')
                { FLC[k]='\0'; j++; break; }
                else
                { FLC[k]=printout; j++; }
                }
        //StringGrid1->Cells[6][i+1]=AnsiString(FLC);
        SS=AnsiString(FLC);
        // gmt
        j=j+1;
        for (int k=0;k<Memo1->Lines->Strings[i].Length()-j;k++)
                {
                printout=Memo1->Lines->Strings[i][j+1];
                if (printout=='\|')
                { FLC[k]='\0'; j++; break; }
                else
                { FLC[k]=printout; j++; }
                }
        //StringGrid1->Cells[7][i+1]=AnsiString(FLC);
        GMT=AnsiString(FLC);
        j=j+1;
        // radio_id
                for (int k=0;k<Memo1->Lines->Strings[i].Length();k++)
                {
                printout=Memo1->Lines->Strings[i][j+1];
                //ShowMessage(AnsiString(printout)+"\/"+AnsiString(i)+":"+AnsiString(k));
                if (printout=='\|')
                { FLC[k]='\0'; j++; break; }
                else
                { FLC[k]=printout; j++; }
                }
        //StringGrid1->Cells[8][i+1]=AnsiString(FLC);
        RID=AnsiString(FLC);
//        ShowMessage("!");
        // listeners
                for (int k=0;k<Memo1->Lines->Strings[i].Length();k++)
                {
                printout=Memo1->Lines->Strings[i][j+1];
                if (printout=='\|')
                { FLC[k]='\0'; j++; break; }
                else
                { FLC[k]=printout; j++; }
                }
        //StringGrid1->Cells[9][i+1]=AnsiString(FLC);
        LI=AnsiString(FLC);
//        ShowMessage("!!");
        // artist
                for (int k=0;k<Memo1->Lines->Strings[i].Length()-j;k++)
                {
                printout=Memo1->Lines->Strings[i][j+1];
                if (printout=='\)' || printout=='\(' || printout=='\'' || printout=='\"' || printout=='\\' || printout=='\,' )
                printout='\?';
                if (k==0 && printout=='\ ')
                { err=true; FLC[0]='?'; FLC[1]='\0'; j+=2; }
                else
                {
                if (((j)>=Memo1->Lines->Strings[i].Length()) || k>31)
                { FLC[k]='\0'; break; }
                else if (k>1 && (FLC[k]=='\-') && (FLC[k-1]=='\ '))
                { FLC[k-1]='\0'; j+=2; break; }
                else
                { FLC[k]=printout; j++; }
                }
                }
        //StringGrid1->Cells[10][i+1]=AnsiString(FLC);
        ART=AnsiString(FLC);
//        ShowMessage("!!!");
        // title
                for (int k=0;k<Memo1->Lines->Strings[i].Length()-j;k++)
                {
                if (err)  {FLC[0]='?'; FLC[1]='\0';}
                else
                {
                printout=Memo1->Lines->Strings[i][j+1];
                if ((j)>=Memo1->Lines->Strings[i].Length() || k>31)
                { FLC[k]='\0'; break; }
                else if (j>=Memo1->Lines->Strings[i].Length())
                { FLC[k]='\0'; j++; break; }
                else
                { FLC[k]=printout; j++; }
                }
                }
        //StringGrid1->Cells[11][i+1]=AnsiString(FLC);
        TIT=AnsiString(FLC);
ADQuery1->SQL->Text="INSERT INTO A_DATA  (s_day,s_mon,s_year,s_hour,s_minute,s_second,s_station,s_list,s_gmt,s_artist,s_title) VALUES ("+DD+","+MM+","+YY+","+HH+","+MI+","+SS+",\'"+RID+"\',"+GMT+","+LI+",\""+ART+"\",\""+TIT+"\");";
//ShowMessage(ADQuery1->SQL->Text);
try {
ADQuery1->ExecSQL();
}
catch (...) {}
        } //
//}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
ADQuery1->SQL->Text=Memo2->Text;
ADQuery1->ExecSQL();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
ADQuery1->SQL->Text=Memo2->Text;
ADQuery1->Open();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
Series1->Clear();
Series2->Clear();
Series3->Clear();
int DD,MM,YY,MI,HO,SE,LI,TIMES;//
ADQuery2->SQL->Text="select s_day, s_mon, s_year, s_hour, s_minute, s_second, s_station, s_gmt from A_DATA WHERE s_station='radio' ORDER BY s_year, s_mon, s_day, s_hour, s_minute, s_second";
ADQuery2->Open();
int i=0;
while (!ADQuery2->Eof)
{
DD=ADQuery2->FieldByName("s_day")->AsInteger;
MM=ADQuery2->FieldByName("s_mon")->AsInteger;
YY=ADQuery2->FieldByName("s_year")->AsInteger;
HO=ADQuery2->FieldByName("s_hour")->AsInteger;
MI=ADQuery2->FieldByName("s_minute")->AsInteger;
SE=ADQuery2->FieldByName("s_second")->AsInteger;
LI=ADQuery2->FieldByName("s_gmt")->AsInteger;
//ShowMessage(LI);
TIMES=SE+MI*60+HO*60*60+DD*24*60*60+MM*24*31*60*60;
ADQuery2->Next();
i++;
if (LI>100)
{ if (CheckBox4->Checked) if (CheckBox1->Checked) Series1->AddXY(TIMES,LI); }
else
if (CheckBox1->Checked)
Series1->AddXY(TIMES,LI);
//Series1->AddXY(i,LI);
}
ADQuery2->Close();
ADQuery2->SQL->Text="select s_day, s_mon, s_year, s_hour, s_minute, s_second, s_station, s_gmt from A_DATA WHERE s_station='radio-low' ORDER BY s_year, s_mon, s_day, s_hour, s_minute, s_second";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
DD=ADQuery2->FieldByName("s_day")->AsInteger;
MM=ADQuery2->FieldByName("s_mon")->AsInteger;
YY=ADQuery2->FieldByName("s_year")->AsInteger;
HO=ADQuery2->FieldByName("s_hour")->AsInteger;
MI=ADQuery2->FieldByName("s_minute")->AsInteger;
SE=ADQuery2->FieldByName("s_second")->AsInteger;
LI=ADQuery2->FieldByName("s_gmt")->AsInteger;
//ShowMessage(LI);
TIMES=SE+MI*60+HO*60*60+DD*24*60*60+MM*24*31*60*60;
ADQuery2->Next();
i++;
if (LI>100)
{ if (CheckBox4->Checked) if (CheckBox2->Checked) Series2->AddXY(TIMES,LI); }
else
if (CheckBox2->Checked)
Series2->AddXY(TIMES,LI);
//Series1->AddXY(i,LI);
}
ADQuery2->Close();
//full
ADQuery2->SQL->Text="select s_day, s_mon, s_year, s_hour, s_minute, s_station, sum(s_gmt) as a_gmt from A_DATA GROUP BY  s_year, s_mon, s_day, s_hour, s_minute ORDER BY s_year, s_mon, s_day, s_hour, s_minute";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
DD=ADQuery2->FieldByName("s_day")->AsInteger;
MM=ADQuery2->FieldByName("s_mon")->AsInteger;
YY=ADQuery2->FieldByName("s_year")->AsInteger;
HO=ADQuery2->FieldByName("s_hour")->AsInteger;
MI=ADQuery2->FieldByName("s_minute")->AsInteger;
//SE=ADQuery2->FieldByName("s_second")->AsInteger;
LI=ADQuery2->FieldByName("a_gmt")->AsInteger;
//ShowMessage(LI);
TIMES=SE+MI*60+HO*60*60+DD*24*60*60+MM*24*31*60*60;
ADQuery2->Next();
i++;
if (LI>120)
{ if (CheckBox4->Checked) if (CheckBox3->Checked) Series3->AddXY(TIMES,LI); }
//ShowMessage(LI);
else
if (CheckBox3->Checked)
Series3->AddXY(TIMES,LI);
//Series1->AddXY(i,LI);
}
ADQuery2->Close();
}
//---------------------------------------------------------------------------

