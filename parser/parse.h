//---------------------------------------------------------------------------

#ifndef parseH
#define parseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
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
#include <DBGrids.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMemo *Memo1;
        TButton *Button1;
        TButton *Button2;
        TOpenDialog *OpenDialog1;
        TADConnection *ADConnection1;
        TADQuery *ADQuery1;
        TADPhysMySQLDriverLink *ADPhysMySQLDriverLink1;
        TADGUIxFormsQBldrEngine *ADGUIxFormsQBldrEngine1;
        TADGUIxFormsQBldrDialog *ADGUIxFormsQBldrDialog1;
        TADGUIxFormsErrorDialog *ADGUIxFormsErrorDialog1;
        TADGUIxFormsLoginDialog *ADGUIxFormsLoginDialog1;
        TADGUIxFormsAsyncExecuteDialog *ADGUIxFormsAsyncExecuteDialog1;
        TADGUIxWaitCursor *ADGUIxWaitCursor1;
        TButton *Button3;
        TButton *Button4;
        TMemo *Memo2;
        TDataSource *DataSource1;
        TDBGrid *DBGrid1;
        TChart *Chart1;
        TLineSeries *Series1;
        TLineSeries *Series2;
        TADQuery *ADQuery2;
        TLineSeries *Series3;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
