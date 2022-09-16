#ifndef __LIBRARY_H
#define __LIBRARY_H
#ifdef __DLL__
#define DLL_EI __declspec(dllexport)
#else
#define DLL_EI __declspec(dllimport)
#endif

TStringList* SongList = new TStringList;

struct TAG
{
unsigned char   tag     [ 03 ];
unsigned char   title   [ 30 ];
unsigned char   artist  [ 30 ];
unsigned char   album   [ 30 ];
unsigned char   year    [ 04 ];
unsigned char   comment [ 28 ];
unsigned char   sep     [ 01 ];
unsigned char   track   [ 01 ];
unsigned char   genre   [ 01 ];
};


extern int DLL_EI __fastcall getlenght(char* database);
extern char* DLL_EI __fastcall crofilename(char* S);
extern char* DLL_EI __fastcall GetMp3Tag_DLL ( char* fName , int callparam );
extern TStringList* DLL_EI __fastcall FindDir(char* path,char* mask);
extern char* DLL_EI __fastcall NullRemoval(char* word,int length);
extern char* DLL_EI __fastcall SentenceToSQL(char* sentence, int length, char separator);
extern char* DLL_EI __fastcall PathToData(char* path, int length, int param);
extern char* DLL_EI __fastcall PathToDestination(char* path,int length, int param);
//extern char* DLL_EI __fastcall AdressToSQL(char* sentence, int length);
#endif;
