#pragma pack(push, 1)
struct DECART {
	float x, y, z;
};

struct ELEM_BODY {
	WORD NumElem;
	BYTE Type;  /* 1-4 - n - �������                            */
	/*  5  - 3-x �������, �p����p������� � ��p����  */
	/*  6  - 3-x �������, �p����p������� � ��p����  */
	BYTE DifferNode;   
	long Node[4];
};

struct LOOK_BODY {
	
	ELEM_BODY       * ElemBody;
	DWORD             QuantityElemBody;
	double            MK[3][3];
	BYTE              TypeBase;
	long            * Order;
	
	BYTE              TypeProfile;
	BYTE              TypePlate;
	BYTE              FragmParam;
	BYTE              Fragm;
	BYTE              DeleteProcess;
	BYTE              Res[3];
	WORD              QuantityElemMask;
	BYTE            * MaskElem;  /* ����� ���������                               */
	BYTE            * MaskFragm;  /* ����� ���������                               */
	
	DWORD             QuantityNodeBody;
	CK              * Coord;      /* ���p������ �������������� ����� ��� ��������  */
	GrafCK          * GrafCoord;  /* �p��������� ���p������ �������������� ����� ��� �������� */
	float             DelProfile; /*  ������� ��� ����������� ��������  */
	
};

struct LINE_BODY {
	DECART     *pD1;
	DECART     *pD2;
	float      xp, yp, zp;  /*  �����p, ��p��������� �����    */
	float      c;           /*  �p������� �p������            */
	/*    zb * x - xb * z + c = 0     */
};

struct ELEM_BODY_GEOM {
	float       a, b, c, d;  /*  �p������� ���������            */
				/*   a * x + b * y + c * z + d = 0 */
	float       xMax, xMin, yMax, yMin, zMax, zMin;
};

struct ELEM_BODY_FULL {
	ELEM_BODY      * pEB;
	ELEM_BODY_GEOM * pEBG;
	BYTE        QuantityLine;
	LINE_BODY   LineBody[4];
	float Eps;
};

#define  EPSILON   1e-4
#pragma pack(pop)
