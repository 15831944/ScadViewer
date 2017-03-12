#ifndef CALC_DATA__H
#define CALC_DATA__H
#pragma pack(push,1)

#include <fe_form.h>
#include <sg_dyn1.h>

struct CALC_DATA
{
   char       Ident[8];
   WORD       Length;          // ����� CTG
   WORD       Version;

   FILE_MARK  FileMark[100];   //  �������� ��� ��������

   BYTE       TypeProcess;

   int        QuantityElem;    // ���������� ���������
   int        QuantityNode;    // ����� �����

   int        MaxLayer;        // ������������ ����� ����� � ������������
   int        QuantityLinkFE;     // Link FE 
   BYTE       YesZEL;          // null elem yes
   BYTE       QuantityElemStep;  // � ����� ���� ������� ��������

   WORD       QuantityLoad;    // ����� ����������� ����������
   WORD       QuantityLoadDyn;

   WORD       QuantityForce;   // ���������� ������ ������
   WORD       QuantityLoading; // ���������� ����������� � ������
   WORD       MaxFormLoad;     // ���. ���������� ����� ���� 
   int        SumQuantityForm;
  

   int        OrderDispl;      // ������� ������� �����������
   int        OrderSystem;     // ������� �������
   int        OrderSE;         // ������� ������������

   int        HSystem;         // ������ �����
   int        HElem;           // ����� H-��������

   int        MaxLenFormat;    // len format
   int        MaxLenAddFormat; // len format
   int        MaxQuantityValue;// max �������� ������������� �����.����.

   BYTE       MODE;             //  ���������  ������, ������ 100
   BYTE       YesTimeHistory;      //  ������ 101

   BYTE       TypeSolver;       //  ����� ������� ������� ���������

   BYTE       YesAvtoMass;      // ???????

   WORD       MaxNodeElem;
   WORD       MaxKD;
   WORD       MaxSechOut;
   WORD       MaxKN;
   WORD       MaxKR;
   int        MaxKDxKN;
   int        MaxKG;
   WORD       MaxKNLitera;
   DWORD      MaxLengthEq;

   BYTE       WorkStep;         // ������� ����������

   int        NumLineMatr;      //  ����� ���������� ��� ����������� �������

   BYTE       YesData;
   BYTE       YesOptimize;
   BYTE       YesMatr;
   BYTE       YesGauss;         // ������ ������ ��� ������
   BYTE       YesStartVector;
   BYTE       YesMass;
   BYTE       YesForm;
   int        MaxForm;          // ����. ����������� ����� ����

   BYTE       YesDynForce;
   BYTE       YesForce;
   BYTE       YesDisplace;
   BYTE       YesEffors;

   BYTE       YesRSU;
   WORD       QuantityGroupUnific;

   BYTE       YesNewRSU;

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
   BYTE       NoStartVector;

   BYTE       YesDestruction;

   BYTE       YesRes[9];

   BYTE       NullStringMatrize;
   BYTE       GIS;

   DOCUMENT_LONG   Format;
   DOCUMENT_LONG   Doc05;

   DOCUMENT_LONG   DocWork;
   DOCUMENT_LONG   HeadDispl;
   DOCUMENT_LONG   PositionEffors;
   DOCUMENT_LONG   PositionEfforsComb;
   DOCUMENT_LONG   DocUnite;
   DOCUMENT_LONG   FormStep;
   DOCUMENT_LONG   DocR02;
   DOCUMENT_LONG   DocR03;

   LONGLONG        AdrNewNumber;     // ����� ������� ����������� ����� �����������
   LONGLONG        AdrProfMatr;      //
   LONGLONG        AdrFormPos;       // adrel
   LONGLONG        PosGaussWork;     // ������� ��������� ������� ����
   LONGLONG        LenGaussWork;     // �����
   LONGLONG        AdrPosEquation;   // ������� ��������� � �������
   LONGLONG        AdrLoadCalc;      // ������� ������ � �����������

   int             MaxLengthH;

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

   LONGLONG   LengthStepData;   // ����� ����� �������������� ������ ������ ����
   int        MaxLenStepFormatElem;    // ��� ����� ����������� �� ���������� ���� ������
   BYTE       YesStressed;
   BYTE       YesOneSide;
   
   int        QuantityFixedStep;    // ����� ������������� ����� ���.�������� 
   int        QuantityStep;         // ����� ���� ����� ���.��������   

   int        NumWorkStep;          // ����� �������� ���� 
   int        NumIteration;
   int        NumFixedStep;
   int        NumStepFile;
   int        NumWorkFile;

   BYTE       NoData;

   BYTE       TypeIterationSolver;
   WORD       RangIterationSolver;
   BYTE       SaveMatrIter;

   WORD       QuantityMatrIter;
   int        QuantityElemIter;
   int        MaxOrderMatrize;
   int        SumOrderIter;

   LONGLONG   AdrNumNodeStep;

   LONGLONG   AdrElemNode;
   DWORD      MaxLengthMatrIter;
   int        NumMatrGaussIter;

   double     FuncIter;

   LONGLONG   PosForceCenter;

   DWORD      MaxMemory;
   DWORD      MatrPortion;

   int        MatrMinus;

   LONGLONG   AdrRSU;
   LONGLONG   AdrNewRSU;
   LONGLONG   AdrDestructionRSU;

   int        QuantityForceTime;
   LONGLONG   AdrForceTime;

   BYTE       ReservEnd[172];

};

	/* Descriptor of the right hand side column */

struct HEAD_DISPLACE
{
	WORD  NQ;           //  ����� ����������
    WORD  NumStep;      //  ��� ��� ����������� �������� 
    WORD  NumFixedStep; //  ����� �/� ���������� � ������� �������� 
	WORD  PQ;           //	1-10 - ����������� ����������
		                //  11-199 - ������������ ����������
		                //  200 - SD - ������������ ���������
		                //  201, 202, 203 � -  S1, S2, � - ������������ ���������. NF - �����
		                //  250 - ��� �������� �������������� �� �������.
				        //  ��� �������� NumStep � ������ ���������� ����������� �������� ����.

	int   NF;           // ����� �����������/������/���������
	int   KF;           // �����
	WORD  NumUnite;     //  ����� ������ �������� 
	WORD  NumLoadSchemUnite; //  ����� ���������� � ������ �������� 
    WORD  Res[2]; 
};

struct LOAD_CALC
{
	WORD  NumStringForce;    
	WORD  QuantityStringForce;
	WORD  NumString;    //  Us | Displace - ������
	WORD  Res1;         
	WORD  QuantityString;
	WORD  NumAddString;        //  ������ 
	WORD  QuantityEnvelope;    //  ����� ���������
	WORD  NumStringEnvelope;   //  ��������� - ������
	WORD  TypeEnvelope;        //  ��� ���������
	WORD  NumDyn; 
	WORD  NumStepLoad;
	WORD  Res[2];
};

struct HEAD_USIL
{
	LONGLONG PosForm;   // Adress on the disk of the internal data

	int      NumEl;     // ����� �� ��� ������ ���������� ���
	DWORD    L_US;      // Length in the bait of the stresses array

	WORD     KD_US;     // Quantity of the seshenij
	WORD     NS_US;     // Number of the secheniq
	DWORD    L_RS;      // Length of the combination characteristic
	
	WORD     KR1_RS;    // Number of the combinations of the first group
	WORD     KR2_RS;    // Number of the combinations of the second group
	BYTE     TypeUnif;  // ��� ���������� ���
	BYTE     TypeConstr;   // ��� ����������� �� ������ � ���
	BYTE     QuantityUs; 
	BYTE     TypeUs[8];          // ������������� ������
    BYTE     Res[9];
};

#include <s_rsu.h>

struct FORMAT_POSITION {
   int       min;
   int       max;
   LONGLONG  Pos;  };

struct FORMAT_UNITE
{
   FILEWORK   Form;
   FILEWORK   Step;
   FILEWORK   Work;    //  ������� ����� ��� ����������� ����������
   CALC_DATA  CalcData;
};

#pragma pack(pop)
#endif
