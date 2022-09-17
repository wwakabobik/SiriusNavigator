//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "daADCompClient.hpp"
#include "daADCompDataSet.hpp"
#include "daADDAptIntf.hpp"
#include "daADDatSManager.hpp"
#include "daADGUIxFormsfAsync.hpp"
#include "daADGUIxFormsfError.hpp"
#include "daADGUIxFormsfLogin.hpp"
#include "daADGUIxFormsfQBldr.hpp"
#include "daADGUIxFormsQBldr.hpp"
#include "daADGUIxFormsWait.hpp"
#include "daADPhysIntf.hpp"
#include "daADPhysManager.hpp"
#include "daADPhysMySQL.hpp"
#include "daADStanDef.hpp"
#include "daADStanIntf.hpp"
#include "daADStanOption.hpp"
#include "daADStanParam.hpp"
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include "CSPIN.h"
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TDataSource *DataSource1;
        TDataSource *DataSource2;
        TDBGrid *DBGrid1;
        TDBNavigator *DBNavigator1;
        TDBEdit *DBEdit1;
        TDBEdit *DBEdit2;
        TDBEdit *DBEdit3;
        TDBEdit *DBEdit4;
        TDBEdit *DBEdit5;
        TDBMemo *DBMemo1;
        TDBImage *DBImage1;
        TADConnection *ADConnection1;
        TADQuery *ADQuery1;
        TADQuery *ADQuery2;
        TADUpdateSQL *ADUpdateSQL1;
        TADGUIxFormsErrorDialog *ADGUIxFormsErrorDialog1;
        TADGUIxFormsLoginDialog *ADGUIxFormsLoginDialog1;
        TADGUIxWaitCursor *ADGUIxWaitCursor1;
        TADGUIxFormsAsyncExecuteDialog *ADGUIxFormsAsyncExecuteDialog1;
        TADGUIxFormsQBldrDialog *ADGUIxFormsQBldrDialog1;
        TADGUIxFormsQBldrEngine *ADGUIxFormsQBldrEngine1;
        TADPhysMySQLDriverLink *ADPhysMySQLDriverLink1;
        TMemo *Memo1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TCSpinEdit *CSpinEdit1;
        TEdit *Edit1;
        TEdit *Edit2;
        TLabel *Label1;
        TCSpinEdit *CSpinEdit2;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit3;
        TLabel *Label5;
        TComboBox *ComboBox1;
        TLabel *Label6;
        TMemo *Memo2;
        TImage *Image1;
        TButton *Button4;
        TButton *Button5;
        TEdit *Edit4;
        TLabel *Label7;
        TButton *Button6;
        TDBEdit *DBEdit6;
        TDBEdit *DBEdit7;
        TEdit *Edit5;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *Edit6;
        TComboBox *ComboBox2;
        TLabel *Label10;
        TLabel *Label11;
        TEdit *Edit7;
        TOpenDialog *OpenDialog1;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TOpenPictureDialog *OpenPictureDialog1;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
        TDBComboBox *DBComboBox1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall CSpinEdit1Change(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Panel1Click(TObject *Sender);
        void __fastcall Panel2Click(TObject *Sender);
        void __fastcall Panel3Click(TObject *Sender);
        void __fastcall Panel4Click(TObject *Sender);
        void __fastcall Panel5Click(TObject *Sender);
        void __fastcall Panel6Click(TObject *Sender);
        void __fastcall Panel7Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
