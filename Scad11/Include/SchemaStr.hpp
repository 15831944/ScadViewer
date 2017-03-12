#ifndef SCHEMA_STR_FLAG_H
#define SCHEMA_STR_FLAG_H
#pragma pack(push,1)

struct  TREE {
	BYTE          Regime;
	SYSTEMTIME    TimeModify;
};

struct CK {
	double x, y, z;
    LPSTR  Name;
	WORD   Flag;
};

struct  DefCK
{
	double x,   y,  z;
	double ux, uy, uz;
	int n_unk[16];
};

struct  GrafCK {  int x, y; };

struct  TYPE_SYSTEM {
	BYTE Num;
	BYTE QuantityStep;
	BYTE NumStep[16];  };
	
struct ADD_SCHEMA_DATA  {
   BYTE    TypeCoincidence;     // 0 - ������ �����������, 1 - ����������� �� �����
   WORD    MaskContact;         // ���� �����������x ������
   BYTE    QuantityNodeDocking; // ����� �����, ��p��������x ����������
   BYTE    YesScale;            // ��������p������ �p� ���x �����x ���������
   BYTE    YesCorner1;          // ����� ���� �p� ���x �����x ����������,1-rad,2-grad
   double  Corner1;
   BYTE    YesCorner2;          // ����� ���� �p� ���x �����x ����������,1-rad,2-grad
   double  Corner2;
   int     NumNodeDocking1[3];  // ����p� ����� �  ��p��� �x���
   int     NumNodeDocking2[3];  // ����p� ����� �� ���p�� �x���
   BYTE    YesDelta;            //   ���p������� ���� ������ �����p���
   double  Punct11[3];          //       ���p������ �����,
   double  Punct12[3];          //     �����p����x ���������
   double  Punct13[3];          //    �p������������ ����x���
   double  Punct23[3];          //
   double  PrecesionCoincidence;// �������� ��������
   BYTE    DeleteEqualElem;     // �p����� �������� �����.��������� �� 2-� �x���
   BYTE    AddEfforsGroup;      // �������� ���p���� 2-� �x��� ��� �p����
   BYTE    AddForceEqNode;
   BYTE    NoAddRigid;
};

struct SCHEMA_PARAM
{
   BYTE     TypeOptimization;    //  nop, opt
   BYTE     TypeSolver;          //  ��� �������
   BYTE     PrecessionSolver;    //  tgs
   BYTE     PrecessionDynamic;   //  erd
   BYTE     PrecessionStabil;    //  �������� ������������ ���� ������ ������������
   BYTE     CheckSolution;       //  Gauss control   ngs
   BYTE     CheckGaussError;     //  �������� �������� ������
   WORD     QuantityIter;        //  itr
   BYTE     EpsCheckFE;          //  �������� �������� ��������� � ����������
   BYTE     EfforsNode;          //  ��� ���������� ������ � �����
   BYTE     Res1;                 //  
   BYTE     NoForceInsert;       // �� ��������� ����������-�������. �������� �� �������� � ��������
   BYTE     Res[12];
   UNITS    UnitsOut[5];
};

struct DOC08 {   short  krs[8];  float  rs[18];  };
#define KRS08(I,J)    doc08[(I)].krs[(J)]
#define RS08(I,J)     doc08[(I)].rs[(J)]


struct KOORLINE {	BYTE Type; char Name[16]; double Pos; };
struct S_Doc21  { WORD XLineQuantity; WORD YLineQuantity; WORD HLineQuantity; KOORLINE Line[1]; };

struct  KOF {  short  nnag;   float  rkn;  };
struct  LOAD_COMBINATION {   WORD   Quantity;   KOF  * Kof;	   };

#pragma pack(pop)
#endif
