#ifndef INFORM_FLAG_H
#define INFORM_FLAG_H
#pragma pack(push, 1)

#include "filetext.h"
#include "crash.h"

struct ACCESS {
	     DWORD Pos;               /*   ������� � �����               */
	     WORD Length;             /*   ����� ���������               */
	     };

struct TEXT_INFORM {
	     WORD Length;              //   ����� ��������
	     BYTE QuantityString;      //   ����� ��p�� ��������
	     LPSTR Point;
	     BYTE Type;                //   ���   ��������
	     LPSTR Text;               //   ��p��� ��������
	     };

class INFORM : MEMORY
{

private:

	 short   MinNumInform;        //   ��������� ����p �p���
	 short   MaxNumInform;        //   ��������  ����p �p���
	 DWORD   PosAccess;           //   ������� � ����� Access
	 WORD    MaxLength;           //   max ����� ����p�����
	 WORD    NumBase;             //   ������� �����
    ACCESS  FAR * Access;
	 TEXT_INFORM Inform;          //   � ��� ��p����p�
	 FILEBASE FileWork;

EXPORT 	 void   Init();
EXPORT 	 void   Error(LPCSTR,long);

public:

EXPORT      INFORM() { Init(); };
EXPORT      INFORM(LPCSTR FileName) { Init(FileName); };
EXPORT      ~INFORM() {   Delete();  };

EXPORT void    SetNumBase( int Num ) {  NumBase = (WORD)Num;  };
EXPORT int     Init(LPCSTR FileName, int Num=0 );
EXPORT void    Delete();
EXPORT void    Code(LPCSTR,LPCSTR);
EXPORT TEXT_INFORM FAR * Load(int);

EXPORT int     InformIn(int Num);

};
#pragma pack(pop)

#endif