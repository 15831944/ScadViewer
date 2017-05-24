#ifndef SCAD_SE_FLAG_H
#define SCAD_SE_FLAG_H
#pragma pack(push, 1)
#include <schema.h>

struct  SUPER_DATA {

	short          Level;              /* �஢��� SE � �᭮���� �奬�       */
 	short          TypeError;          /* ����稥 � ⨯ �訡�� �� ��몮��� */

   short          NumSchema;
   short          NumVorSE;
   short          NumElemInVorSE;
   BYTE         * NumNextSE;
   long           NumNodeBase;

	WORD           QuantityNodeSE;     /* �-�� 㧫�� SE             */
	long         * NumNodeVorSE;       /* ����� 㧫�� SE           */

	double         XA, YA, ZA;         /* �ਢ離� SE  � �᭮���� �奬�      */
	double         MatrCosCoord[9];    /*                                    */

	double         MatrCosSE[9];       /* �ਢ離� SE � ��஦���饬� SE     */

	int            QuantitySE;         /* �᫮ ����몮������ �㯥�����⮢ */
	int            NumBeginSE;         /* ��砫� � ᯨ᪥                     */

   long           NumBeginElem;
   long           NumBeginNode;
   long           NumStepBegin;
   long           OrderMatrize;


};

class SUPER : MEMORY
{
public:
	int             MaxLevel;
	int             QuantitySE;
	int             QuantityAllocSE;
	SUPER_DATA    * SuperData;

	int             QuantitySchema;
	int             QuantityAllocSchema;
   SCHEMA       ** Schem;

   int             QuantityLoad;
   long            QuantityNode;

   char            Catalog[MAXPATH];
   int             Error;
   int             TypeRead;

int   EXPORT  AddSuper(int);
void  EXPORT  AddSuper(SCHEMA &, SUPER_DATA &);
int   EXPORT  AddSchema(LPCSTR Name);
int   EXPORT  AddSchema(int);

public:

EXPORT	SUPER()     {   Init();    }
EXPORT ~SUPER(void) {   Delete();  }

void  EXPORT  Init()  {  memset(this,0,sizeof(SUPER));  };
void  EXPORT  Delete();
int   EXPORT  Init(SCHEMA &, char WorkCatalog[], int );
void  EXPORT  Init(SCHEMA &, int );

void  GetNextSE( SUPER_DATA &, SUPER_DATA &, int Num );

int   EXPORT   Access(LPCSTR filename,int NumSchem=0);
void  EXPORT   Remove(LPCSTR filename,int NumSchem=0);
LPSTR EXPORT   GetFileName(LPCSTR Extension,int NumSchem=0);
LPSTR EXPORT   GetFileName(int Num,int NumSchem=0);

};

#pragma pack(pop)
#endif
