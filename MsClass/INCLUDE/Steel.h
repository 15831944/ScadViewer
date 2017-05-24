#ifndef STEEL_FLAG_H
#define STEEL_FLAG_H
#pragma pack(push, 1)

#include "profile.h"

#define MAX_STRING_STEEL_NAME  80

struct STEEL_DATA
{
       char   SteelMark[MAX_STRING_STEEL_NAME];       // ����� �����
       double Ry;                  // ��������� ������������� Ry
       double Koef_nad;       // ����. ���������� �� ����������
       double Koef_usl_rab; // ����� ������� ������
       double Lim_gibk;        // ���������� ��������
};

struct STEEL_ELEMENT
{
       BYTE What_is;                     // 0 - �������������� ������� 1 - ������ ���������
       char Name[MAX_SECTION_NAME];      // ��
       TYPE_DATA_SF    BaseName;         // �������
       TYPE_DATA_SF    SectionName;      // �������
       int             NumStringSection; // �������
       float Koef_RasLen_XoZ;            // ����. ����.����� � ��������� XoZ
       float Koef_RasLen_YoZ;            // ����. ����.����� � ��������� YoZ
};

struct STEEL_LIST {

       STEEL_ELEMENT  SteelEl;
       STEEL_DATA     Data;

       WORD           Quantity;
       WORD         * List;
       LPSTR          Text;
};


class STEEL : private MEMORY
{

private :
        STEEL_DATA       User;
        WORD             QuantityGroup;
	     WORD             QuantityAllocGroup;
	     BYTE             Modify;
        STEEL_LIST     * pSteel;
        FILEBASE       * File;
	     DWORD          * PosFile;

	     friend class SCHEMA;

public:
        int Version;

	STEEL() {  Init();  }
       ~STEEL(void) {  Delete();  }

inline void    Init() {  memset(this,0,sizeof(STEEL));	}
EXPORT void    Delete();
EXPORT void    Delete(WORD NumPP);

EXPORT WORD    Include(STEEL_ELEMENT &, STEEL_DATA &, WORD Qnt,WORD *Lst );
EXPORT void    Change(WORD NumPP, STEEL_ELEMENT &, STEEL_DATA &, WORD Qnt,WORD *Lst );
EXPORT STEEL_LIST  *  GetSteel(WORD NumPP);
EXPORT void    GetSteel(WORD NumPP, STEEL_ELEMENT **, STEEL_DATA **, WORD &Qntt, WORD ** Lst );

void    Compress(WORD QnttElem);

EXPORT WORD    GetQuantityGroup();
EXPORT STEEL_DATA *  GetSteelData();
EXPORT void          SetSteelData(STEEL_DATA &);

inline BYTE     GetModify()         {  return Modify;  }

void    Write(FILEBASE&,WORD Quantity);
void    Write(FILEBASE&, WORD QuantityOld, WORD Quantity, WORD Num[] );
void    Read();

EXPORT LPSTR  GetText(WORD Num);
EXPORT void   SetText(LPSTR Text,WORD Num);

};

#pragma pack(pop)
#endif