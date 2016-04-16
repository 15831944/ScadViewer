// ��������� ��� ��������������� ������� ����������� ��������

#ifndef _3DISO_HPP
#define _3DISO_HPP
#pragma pack(push,1)
enum eTypeData
{
	Iso_Nothing=0,	// ������ �� ���������� ������ �����
	Iso_Disp,		// ������������
	Iso_Nap,		// ���� ����������
	Iso_Nap_Flat,	// ���� ���������� ("������")
	Iso_Arm,		// ���� ��������
	Iso_Lit,		// ���� �������/������������� ����������
	Iso_Energy		// ���� �������
};

struct TypeInformationOnSchema
{
	BYTE NumFactor; // ��������� �������
	BYTE NumElem;   // ��������� ���������
	BYTE NumNode;   // ��������� �����
	BYTE OutSupport;// ����������� ������
	BYTE OutNode;   // ����������� �����
}; // 1 - ����������

enum EIntegralFunc
{
	EIF_AVG,
	EIF_MIN,
	EIF_MAX,
	EIF_MAXMIN
};

//HWND __declspec(dllimport) OGL_3DIso(RESULT *Res, // ��������� �� ����� �����������
//									 int NPr,     // ����� ������ �����
//									 struct DefMapInfo *Scale, // ��������� �� �������� ����� 
//									 eTypeData TypeData, // ��� ������������ ����������
//									 int TypeFactor,     // ��� ������������ ���������� (������� �� ����)
//									 struct TypeInformationOnSchema *TypeInfo, // ��� ���������� ������������ �� �����
//									 HWND hWndParent    // ������������ ����
//									 );
#define OGL_SETFACTOR 0x500 // ��������� ������������� ������� ��� �������� ���� ���������� 
							// WPARAM  - TypeFactor, LPARAM 0
#define OGL_SETSCALE  0x501 // ��������� ����� WPARAM - 0 LPARAM struct *DefMapInfo
#define OGL_SETTYPEDATA 0x502 // ��������� ���� ������������ ����������
							  // WPARAM - eTypeData TypeData, LPARAM 0
#define OGL_SETOUTINFO 0x503  // ��������� ���� ���������� ������������ �� �����
							  // WPARAM - 0 LPARAM 	struct *TypeInformationOnSchema

#pragma pack(pop,1)

#endif