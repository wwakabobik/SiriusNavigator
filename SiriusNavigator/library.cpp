//---------------------------------------------------------------------------

#include <vcl.h>
#include <errno.h>
#include <windows.h>
#include "library.h"
#include <SysUtils.hpp>
#include <fstream.h>
#include <stdio.h>
#include <string.h>
//#include <dos.h>
//#include <dir.h>
#pragma hdrstop
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
        return 1;
}

//---------------------------------------------------------------------------

int __fastcall getlenght(char* database)
{
int param=0;
char temp[1024];
fstream e;
e.open(database);
if (e)
{
//ShowMessage("Unable to open temp file "+AnsiString(database));
while (!e.eof())
{
e.getline(temp,1024);
param++;
}
e.close();
return(param-1);
}
else
return 0;
}

char* __fastcall crofilename(char* S)
{
int i=0;
char tempword[1024];
for (;;)
{
i++;
if (S[i]=='.' && S[i+1]=='m' && S[i+2]=='p' && S[i+3]=='3')
break;
if (S[i]=='.' && S[i+1]=='M' && S[i+2]=='P' && S[i+3]=='3')
break;
if (S[i]=='.' && S[i+1]=='M' && S[i+2]=='p' && S[i+3]=='3')
break;
if (S[i]=='.' && S[i+1]=='m' && S[i+2]=='P' && S[i+3]=='3')
break;
}
for(;;)
{
i--;
if (S[i]=='\\')
break;
}
i++;
int j=0;
for (;;)
{
tempword[j]=S[i];
j++; i++;
if (S[i]=='.' && S[i+1]=='m' && S[i+2]=='p' && S[i+3]=='3')
break;
if (S[i]=='.' && S[i+1]=='M' && S[i+2]=='P' && S[i+3]=='3')
break;
if (S[i]=='.' && S[i+1]=='M' && S[i+2]=='p' && S[i+3]=='3')
break;
if (S[i]=='.' && S[i+1]=='m' && S[i+2]=='P' && S[i+3]=='3')
break;
}
tempword[j]='\0';
return tempword;
}


char* __fastcall GetMp3Tag_DLL ( char fName[] , int callparam )
{
	HANDLE          hFile;
	DWORD           dwFileSize;
	DWORD           dwBytesRead;
	DWORD           dwTagSize;
	DWORD           dwStartPos;
	TAG             tMp3;
    char			c[31];

	hFile = CreateFile ( fName, GENERIC_READ, 0, NULL, OPEN_EXISTING,
    	FILE_ATTRIBUTE_NORMAL, NULL );
	if ( hFile != INVALID_HANDLE_VALUE )
    {
    	dwFileSize = GetFileSize ( hFile, NULL );
        dwTagSize = sizeof ( TAG );
        dwStartPos = dwFileSize - dwTagSize;
    	SetFilePointer ( hFile, dwStartPos, NULL, FILE_BEGIN );
        ReadFile ( hFile, &tMp3, dwTagSize, &dwBytesRead, NULL );
    }
	CloseHandle ( hFile );
    memmove( c, tMp3.tag, 30 ); c[30] = 0;
    if (callparam==0)
    return c;
    memmove( c, tMp3.title, 30 ); c[30] = 0;
    if (callparam==1)
    return c;
    memmove( c, tMp3.artist, 30 ); c[30] = 0;
    if (callparam==2)
    return c;
    memmove( c, tMp3.album, 30 ); c[30] = 0;
    if (callparam==3)
    return c;
    memmove( c, tMp3.year, 4 ); c[4] = 0;
    if (callparam==4)
    return c;
    memmove( c, tMp3.comment, 28 ); c[28] = 0;
    if (callparam==5)
    return c;
}

TStringList* __fastcall FindDir(char* path,char* mask)
{
//    const int MAX_PATH_TO_FILE = 16384; //260
    WIN32_FIND_DATA wfd;
    HANDLE hfound;
    /*char newpath[MAX_PATH_TO_FILE];
    char fpath[MAX_PATH_TO_FILE];
    char pathifile[MAX_PATH_TO_FILE]; //полный путь до файла
    char delpath[MAX_PATH_TO_FILE]; */
    AnsiString pathifile;
    AnsiString delpath;
    AnsiString newpath;
    AnsiString fpath;
    //char myTMP[MAX_PATH];
    /*
    strcpy(fpath,path);
    strcat(fpath,"\\");
    strcpy(delpath,fpath);
    strcat(fpath,mask);
    */
    fpath=AnsiString(path)+"\\";
    delpath=fpath;
    fpath=fpath+AnsiString(mask);


    if((hfound=FindFirstFile(fpath.c_str(),&wfd))!=INVALID_HANDLE_VALUE)
        {
        if(!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)&&strcmp(wfd.cFileName,"..")&&strcmp(wfd.cFileName,"."))
            {
            //нашли первый файл в папке path
                                  SongList->Add(AnsiString(path)+"\\"+AnsiString(wfd.cFileName));
            }
        while(FindNextFile(hfound,&wfd))
            {
            if(!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)&&strcmp(wfd.cFileName,"..")&&strcmp(wfd.cFileName,"."))
                {
                // файл в папке path
                // delpath - папка, с которой начинается реккурсия
                // wfd.cFileName - имя найденного файла

                // копируем строку delpath в pathifile
                //strcpy(pathifile, delpath);
                pathifile=delpath;
                // прибавляем к строке pathifile значение
                // переменной wfd.cFileName - имя файла
                //strcat(pathifile, wfd.cFileName);
                pathifile=pathifile+AnsiString(wfd.cFileName);
                // делаем что-либо с найденным файлом
                            SongList->Add(pathifile);
                }
            }
        }

    FindClose(hfound);
    //поиск файлов закончили, теперь ищем подпапки
    //strcpy(fpath,path);
    //strcat(fpath,"\\*.*");
    fpath=AnsiString(path)+"\\*.*";

    if((hfound=FindFirstFile(fpath.c_str(),&wfd))!=INVALID_HANDLE_VALUE)
        {
        if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)&&strcmp(wfd.cFileName,"..")&&strcmp(wfd.cFileName,"."))
            {
            //strcpy(newpath,path);
            //strcat(newpath,"\\");
            //strcat(newpath,wfd.cFileName);
            newpath=AnsiString(path)+"\\"+AnsiString(wfd.cFileName);
            FindDir(newpath.c_str(),mask); //Рекурсивный вызов
            }

        while(FindNextFile(hfound,&wfd))
            {
            if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)&&strcmp(wfd.cFileName,"..")&&strcmp(wfd.cFileName,"."))
                {
                //strcpy(newpath,path);
                //strcat(newpath,"\\");
                //strcat(newpath,wfd.cFileName);
                newpath=AnsiString(path)+"\\"+AnsiString(wfd.cFileName);
                FindDir(newpath.c_str(),mask); //Рекурсивный вызов
                }
            }
        }
        return SongList;
    }


char* __fastcall NullRemoval(char* word,int length)
{
 int errs=0;
 for (int j=1;j<length;j++)
 {
    if (errs==length)
    break;
    if (j<length)
    {
    if (word[j]==' ' && word[j+1]==' ')
        {
        errs++;
        int h=j;
        for (h=j;h<length;h++)
        {
        if(h+1<length)
        word[h]=word[h+1];
        }
//        j--;
        }
  }
 }        // for j
 if (errs!=0)
 {
 if(word[length-errs-1]==' ')
 word[length-errs-1]='\0';
 else
 word[length-errs]='\0';
 }
 else    word[length-errs]='\0';
 return word;
}

char* __fastcall SentenceToSQL(char* sentence,int length,char separator)
{
for (int i=0;i<length;i++)
{
if (sentence[i]=='\\')
sentence[i]='\/';
else if (sentence[i]=='\'')
sentence[i]='\`';
else if (sentence[i]=='\"')
sentence[i]=separator;
else if (sentence[i]=='\!')
sentence[i]=separator;
//else if (sentence[i]=='\?')
//sentence[i]=separator;
}
return sentence;
}

/* char* __fastcall AdressToSQL(char* sentence,int length)
{
int additional=0;
for (int i=0;i<length;i++)
{
if (sentence[i]=='\'')
additional++;
else if (sentence[i]=='\"')
additional++;
}
char *new_sentence = (char*) malloc((additional+length) * sizeof (char));
int j=0;
for (int i=0;i<length;i++,j++)
{
if (sentence[i]=='\\')
{
sentence[i]='\/';
new_sentence[i]=sentence[i];
}
else if (sentence[i]=='\'')
{
new_sentence[j]='\'';
new_sentence[j+1]='\'';
j++;
}
else if (sentence[i]=='\"')
{
new_sentence[j]='\"';
new_sentence[j+1]='\"';
j++;
}
else
new_sentence[j]=sentence[i];
}
new_sentence[j]='\0';
return new_sentence;
}  */

char* __fastcall PathToDestination(char* path,int length, int param)
{
int status=0;
for (int i=(length-1);i!=0;i--)
{
if (path[i]=='\\')
status++;
if (param==1 && status==2)
{path[i]='\0'; return path;}
else if (param==2 && status==1)
{path[i]='\0'; return path;}
}
}


char* __fastcall PathToData(char* path, int length, int param)
{
const int MAX_DATA = 30;
char new_data[MAX_DATA];
int i=length-1, status=0;
for (i=(length-1);i!=0;i--)
{
if (path[i]=='\\')
status++;
if (param==1 && status==3)
break;
else if (param==2 && status==2)
break;
else if (param==3 && status==2)
break;
else if (param==4 && status==2)
break;
}
i++;
// artist & album data
if (param==1 || param==2)
{
for (int j=0;j<MAX_DATA,i<length;j++,i++)
{
//ShowMessage(AnsiString(j) + " " + AnsiString(i));
if (path[i]=='\\' || j==(MAX_DATA-1))
{new_data[j]='\0'; break; }
new_data[j]=path[i];
}
}
// album without year
else if (param==4)
{
for (int j=0;j<MAX_DATA,i<length;j++,i++)
{
if ((isdigit(path[i]) || path[i]=='\)' || path[i]=='\(' || path[i]=='\ ') && j==0)
{ j--; continue; }
else if (path[i]=='\\' || j==(MAX_DATA-1))
{new_data[j]='\0'; break;}
new_data[j]=path[i];
}
}
// year
else if (param==3)
{
for (int j=0;j<MAX_DATA,i<length;j++,i++)
{
 if (path[i]=='\\')
 {
 if (j==4)
 { new_data[j]='\0'; break;}
 else
 { strcpy(new_data,"NULL"); break; }
 }
 if ((isdigit(path[i]) && j<4))
 { new_data[j]=path[i]; }
 else j--;
}
}
strcpy(path,new_data);
return path;
}
