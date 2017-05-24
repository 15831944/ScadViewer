#ifndef CALC_DATA__H
#define CALC_DATA__H
#pragma pack(push, 1)

#include <fe_form.h>
#include <sg_dyn1.h>

struct CALC_DATA
{
   char       Ident[8];
   WORD       Length;          // ����� CTG
   WORD       Version;

   FILE_MARK  FileMark[100];   //  �������� ��� ��������

   BYTE       TypeProcess;
   WORD       QuantityNodeSE;

   WORD       QuantityElem;    // ���������� ���������
   WORD       QuantityNode;    // ����� �����
   BYTE       YesZEL;          // null elem yes
   BYTE       MaxLayer;        // ������������ ����� ����� � ������������
   BYTE       QuantityElemStep;  // � ����� ���� ������� ��������

   WORD       QuantityLoad;    // ����� ����������� ����������
   WORD       QuantityLoadDyn;
   WORD       QuantityLoading; // ���������� ������ ������
   WORD       MaxFormD15;
   long       SumQuantityForm;

   long       OrderDispl;      // ������� ������� �����������
   long       OrderSystem;     // ������� �������
   long       OrderSE;         // ������� ������������

   long       HSystem;         // ������ �����
   WORD       HElem;           // ����� H-��������

   long       MaxLenFormat;    // len format
   long       MaxLenAddFormat; // len format
   long       MaxQuantityValue;// max �������� ������������� �����.����.

   BYTE       MODE;             //  ���������  ������, ������ 100
   WORD       YesAvtoMass;      // ???????

   WORD       MaxNodeElem;
   WORD       MaxKD;
   WORD       MaxKN;
   WORD       MaxKR;
   long       MaxKDxKN;
   long       MaxKG;
   WORD       MaxKNLitera;
   DWORD      MaxLengthEq;

   BYTE       WorkStep;         // ������� ����������

   long       NumLineMatr;      //  ����� ���������� ��� ����������� �������

   BYTE       YesData;
   BYTE       YesOptimize;
   BYTE       YesMatr;
   BYTE       YesGauss;         // ������ ������ ��� ������
   BYTE       YesStartVector;
   BYTE       YesMass;
   BYTE       YesForm;
   long       MaxForm;
   BYTE       YesDynForce;
   BYTE       YesForce;
   BYTE       YesDisplace;
   BYTE       YesEffors;

   BYTE       YesRSU;
   WORD       QuantityGroupUnific;

   BYTE       YesComb;
   WORD       QuantityComb;

   BYTE       YesStab;

   BYTE       YesStabCoef;
   BYTE       YesStabForm;
   BYTE       YesRodFree;
   BYTE       YesStabCoefComb;
   BYTE       YesStabFormComb;
   BYTE       YesRodFreeComb;

   BYTE       YesFragment;
   BYTE       YesLitera;
   BYTE       NusLitera[8];

   BYTE       YesRes[10];

   BYTE       NullStringMatrize;
   BYTE       GIS;

   DOCUMENT   Format;
   DOCUMENT   Doc05;

   DOCUMENT   DocDynamic;
   DOCUMENT   HeadDispl;
   DOCUMENT   PositionEffors;
   DOCUMENT   PositionEfforsComb;
   DOCUMENT   DocStepData;
   DOCUMENT   DocUnite;
   DOCUMENT   DocSE;
   DOCUMENT   DocR01;
   DOCUMENT   DocR02;
   DOCUMENT   DocR03;

   DWORD      AdrNewNumber;     // ����� ������� ����������� ����� �����������
   DWORD      AdrProfMatr;      //
   DWORD      AdrFormPos;       // adrel
   DWORD      PosGaussWork;     // ������� ��������� ������� ����
   DWORD      LenGaussWork;     // �����
   DWORD      AdrPosEquation;   // ������� ��������� � �������
   long       MaxLengthH;

   BYTE       SumNus[8];
   DWORD      MaxLenUS;
   DWORD      MaxLenReak;
   DWORD      MaxLenUsRSU;
   DWORD      MaxLenRsRSU;

   float      UnixCoef[5];
   double     PrecisionGauss;   // �������� ������
   float      SumTimeCPU;       // ��������� ����� ����������

   BYTE       SumNur[2];
   BYTE       CharacterElement[50]; // �������� ������ ���������:
                                    // ��� 0 - ������� ���������
   int        QuantityLoadStep;
   int        QuantityFixedStep;
   int        QuantityStep;

   int        NumWorkStep;
   int        NumIteration;
   int        NumFixedStep;
   int        NumStepFile;
   int        NumWorkFile;

   BYTE       NoData;

   BYTE       TypeIterationSolver;
   WORD       RangIterationSolver;
   BYTE       SaveMatrIter;

   WORD       QuantityMatrIter;
   long       QuantityElemIter;
   long       MaxOrderMatrize;
   long       SumOrderIter;

   DWORD      AdrNumNodeStep;

   DWORD      AdrElemNode;
   DWORD      MaxLengthMatrIter;
   long       NumMatrGaussIter;

   double     FuncIter;

   BYTE       ReservEnd[200];

};

	/* Descriptor of the right hand side column */

struct HEAD_DISPLACE
{
	short NQ; // Load number
   BYTE  Type;  // 0 - OrderSystem, 1 - OrderDisplace
	BYTE  PQ; /* Load flag: 0 - static with node and local forces;
			1 - static with local forces;
			2,3,4,5,... - dynamic forces                  */
	short NF; // Form number for the dynamic load
	short KF; // Number of the forms for the dynamic load
};

struct HEAD_USIL
{
	DWORD PosForm;   // Adress on the disk of the internal data
	WORD  NumEl;     // NumBer FE
	WORD  Res;       //
	DWORD L_US;      // Length in the bait of the stresses array
	WORD  KD_US;     // Quantity of the seshenij
	WORD  NS_US;     // Number of the secheniq
	DWORD L_RS;      // Length of the combination characteristic
	short KR1_RS;    // Number of the combinations of the first group
	short KR2_RS;    // Number of the combinations of the second group
};

#include <s_rsu.h>

struct Combinations  /* Structure of combinations */
{
	short KCQ;
	short nComb;      /* Number of combinations    */
	float *CombCoef;  /* Chain of coefficients of combinations: */
							/* Its number = (KCQ + KCQ * (nComb - 1)) * nComb / 2  */
};

struct FORMAT_POSITION {
   long   min;
   long   max;
   DWORD  Pos;  };

struct ITER_SOLVER
{
   WORD    QuantityElem;
   WORD    QuantityNode;
   long    Order;
   long    SumOrder;
   DWORD   PosMatrize;
   DWORD   LenMatrize;
};
#pragma pack(pop)

#endif
