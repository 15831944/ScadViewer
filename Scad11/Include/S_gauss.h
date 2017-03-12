#ifndef S_GAUSS_FLAG_H
#define S_GAUSS_FLAG_H
#pragma pack(push,1)

#define MAX_MATR_COS_ORDER 9*9

struct EQUATION_STR
{
	long  NumBeg;                  // ��������� ����� ������������ ���������
	long  NumEnd;                  // �������� ����� ������������ ���������
//	long  Pos;                     // ����� ������������ ��������� � ������
	long  DeltaPos;                // �������� ������ � ������� ������������ ��������� NumBeg
};

struct EQUATION
{
   long         Length;           // ����� ������ ���������
   long         QuantityStr;      // ����� �������� EQUATION_STR ( > 0 )
   long         QuantityDbl;      // ����� �������������, ���������� � ���������
   long         PosDouble;        // ������� �������������
   long         Except;           // ����� ���������� ������������ ���������
   long         PosStr;           // ����� ��������� EQUATION_STR, � ������� ����������
                                  //    ��������� ���������, �� �������� � ����
	char         gis;              // =1 - �������������� ������������
	char         Zero;             // =1 - ��� ����� ��������� ����� ����. ��������������
                                  //      �� ������ ����
   char         Res[2];           //
	double       mim;              // ������� �� ���������
   EQUATION_STR Str[1];           // � Str[0].NumBeg ��������� ������ ����� ���������
                                  // � Str[QuantityStr-1].NumEnd - ����� ���������� �������
};

struct GAUSS_WORK  {
	long   NumBegin;
	long   NumEnd;
   long   Res[3];
   BYTE * Zero;
   BYTE * GIS;
};

#pragma pack(pop)
#endif
