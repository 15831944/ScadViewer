#ifndef RSU_FLAG_HPP
#define RSU_FLAG_HPP

#pragma pack(push,1)

#include <classwin.hpp>
#include <BaseClass.hpp>

#define   MAX_RSU_CRIT      1024
#define   MAX_GROUP_RSU        5    // �, � ��� ������, � � ���������, � � ��������� � ������., � � ������ ������ 

struct RSU_COMMON  {
       BYTE      YesComb;           // ���� ����������
       BYTE      Alfa;              // ���� ��� ������� ���������. �� 5 �� 90. 
       WORD      QuantityCrane;     // ����� ������������ ����������� ������
	   WORD      ResW;
	   WORD      QuantityLoad;      // ����� ���������� ��� ������� ����������� ���
};


struct RSU_DATA_STR  {
       LPSTR    Text;
       int      QuantityAdd;       // ����� ������������ �����������
       TYPE_DATA_CI  * LoadAdd;    // ������������ �����������
       int      QuantityExclusion; // ����� �����������������
       int    * LoadExclusion;     // ������ �����������������
       int      QuantityFather;    // ����� �����
       int    * LoadFather;        // ����
	   short    TypeLoad;          // ��� ���������
       short    ModeLoad;          // ��� ����������
	   short    Sign;              // variable sign
	   short    Crane;             // ����� ����� 
	   short    CraneRegime;       // ������ ������� ������ �����, 1-8
       short    NoActive;          // �� ��������   
       short    Res[2];
	   double   CoeffSafetyFactor;  //  ����������� ���������� �� ��������
	   double   LongTimeLoadComponent;  // ���� ���������� ������������
	   double   Coeff[16];          // koef-s  rsu
	   double   ResD[1];            // 
};

class SCAD_RSU_CLASS: public SCAD_BASE_CLASS
{

public:
      OBJECT_LIST      ListElem;
      OBJECT_LIST      ListGroupElem;
      OBJECT_LIST      Unification;
      SCAD_BASE_CLASS  Criteria;

 	SCAD_RSU_CLASS()     {  Init();     }
  ~SCAD_RSU_CLASS(void)  {  Destroy();  }

void  SCHEMA_EXPORT  Init();
void  SCHEMA_EXPORT  Delete();
void  SCHEMA_EXPORT  Destroy();

int           Add( RSU_DATA_STR *RD ) {   return AddObject((OBJECT*)RD);   }

void          ChangeListAdd( int Num, int Qnt, TYPE_DATA_CI *List, int Type ) {  ChangeComponent(Num,1,Qnt,List,Type); }
void          ChangeListExclusion( int Num, int Qnt, int *List, int Type ) {  ChangeComponent(Num,2,Qnt,List,Type); }
void          ChangeListFather( int Num, int Qnt, int *List, int Type ) {  ChangeComponent(Num,3,Qnt,List,Type); }

RSU_DATA_STR *  Get(int Num) {  return (RSU_DATA_STR *)SCAD_BASE_CLASS::GetObject(Num); }

RSU_COMMON   *  GetCommon() {  return (RSU_COMMON *)SCAD_BASE_CLASS::GetCommon(); }

void  SCHEMA_EXPORT  Export( FILEPRINT &Work );
void  SCHEMA_EXPORT  Print( void *Inp, int NumDoc, int NumHead, int PosText=15, int NoType=0 );
void  SCHEMA_EXPORT  Add( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control );

void  SCHEMA_EXPORT  Read( FILEBASE &Input, DOCUMENT &Doc );
void  SCHEMA_EXPORT  Write( FILEBASE &Output, DOCUMENT &Doc );
void  SCHEMA_EXPORT  Copy( SCAD_RSU_CLASS * );
int   SCHEMA_EXPORT  GetModify();
void  SCHEMA_EXPORT  IncludeString( int Num ); //  �������� ������ ������

};

struct  RSU_OUT
{
	int       NumElem;      // ����� ��������. ��� ���������� �� �����, ���������� � HEAD_USIL
	WORD      NumSech;      // ����� ������� ��������. ��� ���������� �� �����, ���������� � HEAD_USIL
	short     NumCrit;   	// ����� ��������

	WORD      NumCritPP;   	// ����� �������� �/�. ������������ ��� ����������  
	BYTE      NumColumn;   	// ����� �������
	BYTE      YesSeism;     // ������� ������� ������������ ��������
	BYTE      YesSpec;      // ������� ������� ����������� �� ������������ �������� 
	BYTE      YesCrane;     // ������� ������� ������
	
	BYTE      GroupRsu;     // ������� ���������� 0 - ��� ���������� � ���������� ������
	                        //                    1 - ���� ���������� � ������� ���������� ������ 
	BYTE      YesTransport; // ������� ������������ �������� � ��������
	BYTE      Res[8];

	LONGLONG  AdrDataPrint;
};

struct  RSU_OUT_PRINT
{
    int       Quantity;
    double    Value; 
    int       NumLoad[MAX_SCHEMA_LOAD]; 
	double    Coeff[MAX_SCHEMA_LOAD];        //  �������� ������������
};

#pragma pack(pop)
#endif

