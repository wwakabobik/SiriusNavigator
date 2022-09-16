//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "daADCompClient.hpp"
#include "daADCompDataSet.hpp"
#include "daADDAptIntf.hpp"
#include "daADDatSManager.hpp"
#include "daADPhysIntf.hpp"
#include "daADStanDef.hpp"
#include "daADStanIntf.hpp"
#include "daADStanOption.hpp"
#include "daADStanParam.hpp"
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "daADGUIxFormsWait.hpp"
#include "daADPhysManager.hpp"
#include "daADPhysMySQL.hpp"
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <MPlayer.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "CGAUGES.h"
#include <Mask.hpp>
#include "daADPhysMSSQL.hpp"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TListBox *ListBox1;
        TListBox *ListBox2;
        TMemo *Memo1;
        TButton *BAddSongs;
        TButton *BClearTodo;
        TButton *BCount;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit4;
        TEdit *Edit5;
        TEdit *Edit6;
        TDataSource *DataSource1;
        TDBGrid *DBGrid1;
        TADConnection *ADConnection1;
        TADQuery *ADQuery1;
        TADGUIxWaitCursor *ADGUIxWaitCursor1;
        TADPhysMySQLDriverLink *ADPhysMySQLDriverLink1;
        TButton *BExecQuery;
        TMemo *Memo2;
        TButton *BExecSelect;
        TADUpdateSQL *ADUpdateSQL1;
        TDBNavigator *DBNavigator1;
        TButton *BAddSongList;
        TDBMemo *DBMemo1;
        TMediaPlayer *MediaPlayer1;
        TButton *BMCI;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TADQuery *ADQuery2;
        TCheckBox *CheckBox3;
        TDBImage *DBImage1;
        TOpenPictureDialog *OpenPictureDialog1;
        TButton *BAddPicture;
        TComboBox *ComboBox1;
        TDBMemo *DBMemo2;
        TDBComboBox *DBComboBox1;
        TCGauge *CGauge1;
        TCheckBox *CheckBox4;
        TLabeledEdit *LabeledEdit1;
        TButton *BGenerateHTMLForSingleArtist;
        TButton *BGenerateHTML;
        TDataSource *DataSource2;
        TListBox *ListBox3;
        TDBEdit *DBEdit1;
        TCheckBox *CheckBox5;
        TButton *BAddLyric;
        TOpenDialog *OpenDialog1;
        TCheckBox *CheckBox6;
        TButton *BAddArtistPicInHTML;
        TButton *BAddAlbumPicInHTML;
        TButton *BAddLyricInHTML;
        TEdit *Edit7;
        TEdit *Edit8;
        TComboBox *CBSearch;
        TLabel *Label1;
        TEdit *ESearch;
        TButton *BSearch;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TOpenDialog *OpenDialog2;
        TButton *BAddOneSong;
        TButton *BRunDBFunctions;
        TLabel *Label6;
        TButton *BAES;
        TButton *Button19;
        TADPhysMSSQLDriverLink *ADPhysMSSQLDriverLink1;
        void __fastcall BAddSongsClick(TObject *Sender);
        void __fastcall BGenerateHTMLForSingleArtistClick(TObject *Sender);
        void __fastcall BClearTodoClick(TObject *Sender);
        void __fastcall BGenerateHTMLClick(TObject *Sender);
        void __fastcall BCountClick(TObject *Sender);
        void __fastcall BAddLyricClick(TObject *Sender);
        void __fastcall BExecQueryClick(TObject *Sender);
        void __fastcall BExecSelectClick(TObject *Sender);
        void __fastcall BAddSongListClick(TObject *Sender);
        void __fastcall DBMemo1Change(TObject *Sender);
        void __fastcall BMCIClick(TObject *Sender);
        void __fastcall BAddArtistPicInHTMLClick(TObject *Sender);
        void __fastcall BAddPictureClick(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall BAddLyricInHTMLClick(TObject *Sender);
        void __fastcall BAddAlbumPicInHTMLClick(TObject *Sender);
        void __fastcall BAddOneSongClick(TObject *Sender);
        void __fastcall BSearchClick(TObject *Sender);
        void __fastcall CBSearchChange(TObject *Sender);
        void __fastcall BRunDBFunctionsClick(TObject *Sender);
        void __fastcall BAESClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button19Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        bool admin;
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
