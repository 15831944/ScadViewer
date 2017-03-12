#ifndef INFORM_FLAG_H
#define INFORM_FLAG_H
#pragma pack(push,1)

#include "filetext.h"

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

     void  CLASS_EXPORT   Init();
     void  CLASS_EXPORT   Error(LPCSTR,long);

public:

 CLASS_EXPORT      INFORM() { Init(); };
 CLASS_EXPORT      INFORM(LPCSTR FileName) { Init(FileName); };
 CLASS_EXPORT      ~INFORM() {   Delete();  };

void  CLASS_EXPORT   SetNumBase( int Num ) {  NumBase = (WORD)Num;  };
int   CLASS_EXPORT   Init(LPCSTR FileName, int Num=0 );
void  CLASS_EXPORT   Delete();
void  CLASS_EXPORT  Code(LPCSTR,LPCSTR);
CLASS_EXPORT TEXT_INFORM * Load(int);

int  CLASS_EXPORT InformIn(int Num);

};

#pragma pack(pop)
#endif
