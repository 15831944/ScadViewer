#ifndef SCHEMA_OLD_FLAG_H
#define SCHEMA_OLD_FLAG_H
#pragma pack(push,1)

struct SCHEMA_OLD 
{
	WORD            TypeSchema;             // ��� �x��� ����p����
	WORD            QuantityElem;           // ����� ��
	WORD            QuantityAllocElem;      //
	WORD            QuantityNode;           // ����� �����
	WORD            QuantityAllocNode;

	TYPE_SYSTEM     TypeSystem;             // ��� �x���
	WORD            TypeSE;                 // ��� ����p��������
	WORD            QuantityNodeSE;         // ����� ������x ����� ��

	WORD            QuantityCraneForce;     // ����� �p�����x ���p����
	WORD            QuantityBrakeForce;     // ����� ��p�����x ���p��.

	BYTE            FlagPrintDoc[6];        // �p������ ������ ���.
};

struct SCHEMA_OLD_PARAM
{
   WORD     Version;
   BYTE     TypeOptimization;    //  nop, opt
   BYTE     PrecessionGauss;     //  tgs
   BYTE     PrecessionDynamic;   //  erd
   BYTE     PrecessionDockingSE; //  est
   BYTE     CheckSolution;       //  Gauss control   ngs

   WORD     QuantityIter;        //  itr

   float    AngleX;              //  unx
   float    AngleZ;              //  unz
   UNITS    UnitsOut[5];

   BYTE     TypeSolver;
   BYTE     SaveMatrIter;
   WORD     RangIterationSolver;

   BYTE     NoForceInsert;  // �� ��������� ����������-�������. �������� �� �������� � ��������
   BYTE     Res[6];
};

struct  TREE_OLD {
	BYTE      Regime;
	FILETIME  TimeModify;
	};

struct BOUND_LIST {    BYTE  Type;   WORD   Mask;  WORD  Quantity;  };

struct RIGID_LIST {
         WORD           Num;
         BYTE           Type;
         WORD           QuantityRgd;
         WORD           Quantity;  };

#pragma pack(pop)
#endif
