#ifndef SOLVER_FORMAT_FLAG_H
#define SOLVER_FORMAT_FLAG_H
#pragma pack(push,1)

#ifdef  FEM_EXPORTS
#define FEM_EXPORT __declspec(dllexport)
#else
#define FEM_EXPORT __declspec(dllimport)
#endif

struct   FE_COORD {  double x;  double y;  double z; };
struct   FE_FORCE {  WORD  NumLoad;  WORD  NumList;  };

#include <stepdata.h>
#include <fe_data.h>

struct  FE_FORMAT
{
	DWORD     Length;           // ����� ����������� �������
	int       NumElem;          // ����� ��������� ��������
    WORD      TypeElem;         //  ��� ��

	BYTE      QuantityStepNode; // ������� ����� ��. �������
	WORD      MaskStep;         // ����� �����. ��. �������
    WORD      QuantityStepElem; // ������ ������� �������� ������� 
	                            // Link ������ ��� ����������� �����. ��������

 	WORD      PosJoint;         // ����� ������� �������� �������� � ������� ������� ���������
	WORD      PosJointSystem;   // ����� ������� �������� �������� � ����� ������� ���������
 	WORD      PosStep;          // ����� ������� ������� �������� ������� ��

    WORD      QuantityRigid;    //  ���������� �/�
	WORD      PosRigid;         // ����� ������� ����������

	WORD      QuantityForce;    // ���������� ������. � �������� ����������
 	WORD      PosForce;         // ����� ������� ������� ��������
                                // (�������� � ������ �� iz)

	WORD      PosHelp;          // ����� ��������������� �������
	                            // (�������� � ������ �� iz)

	BYTE      QuantityUs;         // ���������� ��������� ����� � NUS
	BYTE      OutQuantityPointUs; // ���������� ����� ������ ������
	BYTE      QuantityPointUs;    // ���������� ����� ���������� ������
	BYTE      TypeUs[8];          // ������������� ������

	BYTE      TypeMatrCos;        // ��� ������� ���������
	BYTE      YesReak;            // ������� ���������� �������

    LONGLONG  PosStepData;        //  ������� � ����� STEP
    WORD      LengthStepDataElem;  //  ����� �������������� ������ ��

    BYTE   Res[18];

    FE_DATA * Data;

};

#define  TypeRigidFE         FormElem->Data->FormatFE->TypeRigid
#define  QuantityNodeFE      FormElem->Data->FormatFE->QuantityNode
#define  NodeFE              FormElem->Data->FormatFE->pNode

#define  SchemaFE            FormElem->Data->Schem
#define  CoordFE             FormElem->Data->CoordEl
#define  JointFE             FormElem->Data->JointEl
#define  JointSystemFE       FormElem->Data->JointSystemEl
#define  RigidFE             FormElem->Data->RigidEl
#define  StepFE              FormElem->Data->StepEl
#define  InfForceFE          FormElem->Data->ForceEl

#define  LenFormFE           FormElem->Length
#define  NumFE               FormElem->NumElem
#define  TypeFE              FormElem->TypeElem

#define  QuantityStepFE      FormElem->QuantityStepElem
#define  MaskStepFE          FormElem->MaskStep
#define  QuantityStepNodeFE  FormElem->QuantityStepNode

#define  QuantityRigidFE     FormElem->QuantityRigid
#define  QuantityForceFE     FormElem->QuantityForce

#define  PosStepFE           FormElem->PosStep
#define  PosRigidFE          FormElem->PosRigid
#define  PosJointFE          FormElem->PosJoint
#define  PosJointSystemFE    FormElem->PosJointSystem
#define  PosForceFE          FormElem->PosForce
#define  PosHelpFE           FormElem->PosHelp

#define  OutQuantityPointUsFE FormElem->OutQuantityPointUs
#define  QuantityPointUsFE    FormElem->QuantityPointUs
#define  QuantityUsFE         FormElem->QuantityUs
#define  TypeUsFE             FormElem->TypeUs

#define  TypeMatrCosFE       FormElem->TypeMatrCos

#define  YesReakFE           FormElem->YesReak

#define  PosStepDataFE       FormElem->PosStepData

#define  xFE(i)              FormElem->Data->CoordEl[(i)].x
#define  yFE(i)              FormElem->Data->CoordEl[(i)].y
#define  zFE(i)              FormElem->Data->CoordEl[(i)].z

FEM_EXPORT double ReadForceElem( FE_FORMAT *,  int &NumStr, int &NumLoad, int &QW, int &QN, int &QuantityValue, double **Value, int YesComb=1 );

void   FEM_EXPORT  ReadFormat( FILEWORK &, FE_FORMAT *, FE_DATA &, LONGLONG adr );
void   FEM_EXPORT  ReadFormatStep( FILEWORK &Work, FE_FORMAT *FormElem, FE_DATA &DataFE,  LONGLONG PosBase );
void   FEM_EXPORT  WriteFormatStep( FILEWORK &Work, FE_FORMAT *FormElem, FE_DATA &DataFE );

#pragma pack(pop)
#endif