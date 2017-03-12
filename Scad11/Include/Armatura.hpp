#ifndef ARMATUR_FLAG_HPP
#define ARMATUR_FLAG_HPP
#pragma pack(push,1)

//#define MAX_CONSTRUCTION_NAME 	        40
//#define MAX_NODE_NAME 	              40
//#define NODE_SENCETIVE   	            3
//#define MAX_QUANTITY_GRAF_FILE_NODE    4
//#define MAX_COMPANY_NAME 		        40
//#define MAX_CUSTOMER_NAME 		        40
//#define MAX_OBJECT_NAME 		        40
//#define MAX_GROUP_NAME               256     // 40

#define MAX_KSTR                     100

#include "classwin.hpp"
#include "beton.h"
//#include "baseclass.hpp"

 /* ��������� ��������� 11 (����������� �����������)*/

struct  ARMATUR_MINIMUM
{
        double  NumSech;      //   ����� ���������� ������� � �������� ���. ��-��
        double  AreaAs1;      //   ������� �������� �p����p� AS1
        double  AreaAs2;      //   ������� �������� �p����p� AS2
        double  AreaAs3;      //   ������� �������� �p����p� AS3
        double  AreaAs4;      //   ������� �������� �p����p� AS4
        double  AreaClampFZ;  //   ������� �������� ������� FZ
        double  StepClampFZ;  //   ��� ������� FZ
        double  AreaClampFY;  //   ������� �������� ������� FY
        double  StepClampFY;  //   ��� ������� FY
        double  Res[2];       //
};

struct  ARMATUR_DATA_STR
{
//     ������
       BYTE              Modul;           // ����� ������
       BYTE              Type;            // ���������� �����������(1) ��� �������������(0)
       BYTE              CrackResisting;   // ������ �� ������������������� 0 - ���, 1 - ����
       BYTE              MinArmatur;      // ������ �� ����������� ��������. 0 - ���, 1 - ����
       BYTE              YesExpert;       //  ������ �� ���������� 0 - ���, 1 - ����
       BYTE              YesLengthOfFactor;  //  ��������� �����, 0 - Length, 1 - Factor
       BYTE              ResByte[2];

       double            Range[4];        // ���������� �� ������ ������� ��������
       double            EffectiveLength[2];  //  ��������� �����
       double            FactorEffectiveLength[2];  //  ����������� ��������� �����
       double            Displacement[2]; //  ��������� ��������������
       double            SeismFactor[2];  //  ������������ ����� ������������� �����������
       double            ResD[2];

//     �����
       BYTE              TypeBeton;       //  ��� ������, ���������� ����� �������
       BYTE              ConditionsHardening; // ������� ���������, ���������� ����� �������
       BYTE              Filler;          // �����������, ���������� ����� �������
       BYTE              ResByte2;        //
       char              ClassBeton[16];  //  ����� ������
       char              SortBeton[16];   //  ����� ������ �� ������� ���������
       double            FactorHardening; // ����������� ������� ���������
       double            FactorForce;     // ����������� ����� �������� ����������� ��������
       double            FactorTotal;     // �������������� �����������
       double            ResD2[2];

//     ��������
       char              ClassArm[2][16]; // ����� ���������� � ���������� ��������
       double            FactorWork[2];   // �����������s ������� ������ ���������� � ���������� ��������
       double            MaxDiam;         // ����. ������� �������� �������
       double            MaxProcent;      // ����.������� �����������
       double            ResD3[2];

//     ����������������
       BYTE              Category;       // ��������� ����������������
       BYTE              ConditionsOperation;  // ������� ������������, ���������� ����� �������
       BYTE              RegimeBeton;    // ����� ��������� ������, ���������� ����� �������
       BYTE              Dampness;       // ��������� �������, ���������� ����� �������
       BYTE              YesSeicmRSU;    //  ��������� ��� � ���������
       BYTE              Res3[3];
       double            DiamRod[2];     // �������� ��������
       double            WidthCrack[2];  //   ������ ��������� ������
       double            Interval;       //   ���������� �� ��������� ����
       double            ResD4[2];
};

struct ARMATUR_STR {

       LPSTR             Text;

       int               Quantity;
       int             * List;
       int               QuantityStr;
       ARMATUR_MINIMUM * ArmaturMin;

//     ������
       ARMATUR_DATA_STR  Data;
};

class   ARMATURA : public SCAD_BASE_CLASS
{
public:

    ARMATURA()      {  Init();    }
   ~ARMATURA(void)  {  Destroy();  }

void Init()  {
         SCAD_BASE_CLASS::Init(0,0,sizeof(ARMATUR_DATA_STR),sizeof(ARMATUR_DATA_STR),2,10);
         LenData[0] = sizeof(int);
         LenData[1] = sizeof(ARMATUR_MINIMUM);
         }

inline   ARMATUR_STR  * GetGroup( int n ) {  return (ARMATUR_STR *)GetObject(n); };
void    SCHEMA_EXPORT   GetTextGroup( int Num, LPSTR Buf, int MaxLenText );

int     SCHEMA_EXPORT   Include( LPSTR Text, ARMATUR_DATA_STR &Data, int Qnt, int * Lst,  int QntAM, ARMATUR_MINIMUM *);

void     SCHEMA_EXPORT  Change( int Num, LPSTR Text, ARMATUR_DATA_STR &, int Qnt,int *Lst, int QntAM, ARMATUR_MINIMUM  * );
void     SCHEMA_EXPORT  ChangeData( int Num, ARMATUR_DATA_STR &GroupData);

void     SCHEMA_EXPORT  Compress( int QntOld, int NewNumber[] );

void     SCHEMA_EXPORT  Add( ARMATURA &, int Quantity, int NumNew[] );

void     SCHEMA_EXPORT  Export( int NumDoc, FILEPRINT &Work );
void     SCHEMA_EXPORT  Print( void *Inp, int NumDoc, int NumHead );

void     SCHEMA_EXPORT  ConvertInOld( BETON & );
void     SCHEMA_EXPORT  ConvertBeton( BETON & );
void     SCHEMA_EXPORT  Add( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control );

void     SCHEMA_EXPORT  WriteOld( FILEBASE &FilePrj, DOCUMENT &Doc );

};

#pragma pack(pop)
#endif
