#ifndef SOLVER_FORMAT_FLAG_H
#define SOLVER_FORMAT_FLAG_H
#pragma pack(push, 1)
struct   FE_COORD {  double x;  double y;  double z; };
struct   FE_FORCE {  WORD  NumLoad;  WORD  NumList;  };

#include <loadcomb.h>
#include <stepdata.h>
#include <fe_data.h>

struct  FE_FORMAT
{
	WORD   Length;      // ����� ����७���� �ଠ�
	WORD   NumElem;     // ����� ����筮�� �����
   WORD   TypeElem;    //  ��� ��

	BYTE   QuantityStepNode; // ���⭮� �᫮ ��. ᢮����
	WORD   MaskStep;         // ��᪠ ����. ��. ᢮����
   WORD   QuantityStepElem; // ࠧ��� ����� �⥯���� ᢮����

 	WORD   PosJoint;    // ���� ���ᨢ� 㪠����� �୨஢
 	WORD   PosStep;     // ���� ���ᨢ� ����஢ �⥯���� ᢮���� ��

   WORD   QuantityRigid;  //  ������⢮ �/�
	WORD   PosRigid;       // ���� ���ᨢ� ���⪮�⥩

	WORD   QuantityForce;  // ������⢮ �����. � ����묨 ����㧪���
 	WORD   PosForce;       // ���� ���ᨢ� ������ ����㧮�
                               // (ᬥ饭�� � ����� �� iz)

 	WORD   PosHelp;     // ���� �������⥫쭮�� ���ᨢ�
	                    // (ᬥ饭�� � ����� �� iz)

	BYTE   QuantityUs;         // ������⢮ �������� ��⮢ � NUS
	BYTE   OutQuantityPointUs; // ������⢮ �祪 �뢮�� �ᨫ��
	BYTE   QuantityPointUs;    // ������⢮ �祪 ���᫥��� �ᨫ��
	BYTE   TypeUs[8];          // �����䨪��� �ᨫ��

	BYTE   TypeMatrCos; // ⨯ ������ ��ᨭ�ᮢ
	BYTE   YesReak;     // �ਧ��� ���᫥��� ॠ�権

   DWORD  PosStepData; //  ������ � 䠩�� STEP

   BYTE   Res[11];

   FE_DATA * Data;

};

#define  TypeRigidFE         FormElem->Data->FormatFE->TypeRigid
#define  QuantityNodeFE      FormElem->Data->FormatFE->QuantityNode
#define  NodeFE              FormElem->Data->FormatFE->pNode

#define  SchemaFE            FormElem->Data->Schem
#define  CoordFE             FormElem->Data->CoordEl
#define  JointFE             FormElem->Data->JointEl
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

double EXPORT ReadForceElem( FE_FORMAT *,  int &NumStr, int &NumForce,
          int &NumLoad, int &QW, int &QN, int &QuantityValue, double **Value, int YesComb=1 );

void  EXPORT ReadFormat( FILEWORK &, FE_FORMAT *, FE_DATA &, DWORD adr );
#pragma pack(pop)

#endif