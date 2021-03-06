#ifndef DATA_RIGID_ROD_FLAG_H
#define DATA_RIGID_ROD_FLAG_H
#pragma pack(push,1)

#include <schema.hpp>

class DATA_RIGID_ROD : MEMORY {

public:
      SCHEMA        * Schem;
      DATA_RIGID    * SchemaRigid;
	  
	  IDENTIFICATOR   Ident;
      UNITS           UnitsHelp;

      char            Name[512];
      int             NumRgd;
      int             Group;
      int             GroupSection;
      int             YesVanta;

      int             QuantityGeom;   //  ��� ����������������� ������
      double       *  Geom;

      int             QuantityHelpData;
      double       *  HelpData;

      char            NameBase[MAXPATH];  // ��� ���
      char            FileSection[16];
      int             NumString;

      char            NameSection[MAX_SECTION_NAME];   //   �� ����
      char            NameString[MAX_STRING_NAME];

      int             QuantityDataSection;  //  ��� ��������� �������
      double          DataDoubleSection[4]; //  ��� ���������� ��� ������������,
                                            //  ����� ���������� ��� ������ �� Z � �.�.

      int             YesConstructor;           //  ����������� �������
      char            NameFileConstructor[MAXPATH]; //  ��� ������������
      char            TypeConstructor[10];      //  ���������� �����
      double          DataConstructor[13];      //  ������ � ���������� 
      int             NumFileConstr;

      int             TypeElem;             //  ��� ���������� �������
      int             YesN;
      double          N;

      double          ema[6];  //  EF,EIY,EIZ,GKP,GFY,GFZ        ��� ���������� ������������

      double          E;
      double          ro;
      double          nu;

      double          yi1;
      double          yi2;     //       ��PA
      double          zi1;     //       CE�EH��
      double          zi2;

      double          res[20];
	  
	  STRING_PROFILE * pSP;

      double          End;

 	DATA_RIGID_ROD()      {  Init();    }
  ~DATA_RIGID_ROD(void)  {  Delete();  }

void  SCHEMA_EXPORT  Init();
void  SCHEMA_EXPORT  Delete();

void  SCHEMA_EXPORT  SetPointer( SCHEMA &, DATA_RIGID &, UNITS &UnitsHelp );

void  SCHEMA_EXPORT  Get( int NumRgd );

void  SCHEMA_EXPORT  SetUser( int NumSection, int Qnt, double *, int DelNumber=0);
void  SCHEMA_EXPORT  SetNumUser( int TypeEl, double *Em, int NumSection , int Qnt, double *Dbl );
void  SCHEMA_EXPORT  SetConstructor( LPSTR Name, double *DataE );
void  SCHEMA_EXPORT  SetProf( LPSTR Base, LPSTR FileSection, int NumStr, int QntDbl=0, double *Data=NULL );

void  SCHEMA_EXPORT  SetIn();
int   SCHEMA_EXPORT  Set( int Num=0);
SCHEMA_EXPORT STRING_PROFILE * GetStrProf();

};

#pragma pack(pop)
#endif
