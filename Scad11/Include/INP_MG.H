#pragma pack(push,1)
  struct   D3MG   {
     char ptg[4];    /* ������� =   "**MG**"          */
     BYTE  ksw;      /* ����� �������� ������� ����   */
     BYTE  nsw[15];  /* ������ �������� ������� ����  */
     BYTE  mk;       /* ��� ������� ���������         */
     short  kmg;      /* ����� ����� � MG              */
     char type;      /* ��� �����: 'Z' - ���������� .aez � ��������� ����
				   'M' - ���������� .aem � ���� F04.*     */
     char name[MAXPATH];  /* ��� �����                     */
     double mg[1];    /* ������� ���������, ���� ����  */
     };

#define  MGPTG     pd3mg->ptg
#define  MGKSW     pd3mg->ksw
#define  MGNSW(i)  pd3mg->nsw[i]
#define  MGMK      pd3mg->mk
#define  MGKMG     pd3mg->kmg
#define  MGTYPE    pd3mg->type
#define  MGNAME    pd3mg->name
#define  MGMG(i)   pd3mg->mg[i]
#pragma pack(pop)

