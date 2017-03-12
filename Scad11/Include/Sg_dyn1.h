#ifndef SG_DYN1_FLAG_H
#define SG_DYN1_FLAG_H
#pragma pack(push,1)

struct   sg_dyn1
{
	BYTE     mod;               //  ������
	WORD     NumLoad;           //  ����� ����������
	WORD     AddLoad;           //  �������������� ����������
	
	WORD     QuantityForm;      //  ����� ����������� ����������� ��������
	WORD     QuantityForce;     //  ����� c������������� ������ ������
	WORD     QuantityDisplace;  //  ����� c������������� �����������
	
	long     QuantityMass;      //  ����� ����
	double   MaxAbsMas;         //  ��� ��������� ������������ ����������
	
	DWORD    ResDubl;
	WORD     ResBuf; // 
	
	LONGLONG AdrMass;
	LONGLONG AdrAddForce;
	
	LONGLONG AdrOften;
	LONGLONG AdrForm;
	LONGLONG AdrDispl;
	LONGLONG AdrForce;
	LONGLONG AdrSum;
	
	long     QuantityPointTime; //   ����� ����� �������� ��������� ��������
	LONGLONG AdrPointTime;      //   �������� ������� ��������
	LONGLONG AdrCoefForm;       //   ������������ �������� ��� ������
                              //   QuantityForm * QuantityPointTime
	LONGLONG AdrCoefFormMax;    //   max. �������� ������������� ��� �����
	LONGLONG AdrTimeCoefFormMax;//   �������� ������� ���������� ��������� �� �����
	
	WORD     NumIter;           //   ����� ��������
	LONGLONG AdrForm1;          //   ������ �������  ����������� ����
	LONGLONG AdrForm2;          //   ������ �������  ����������� ����
	LONGLONG AdrFormR;          //   ������� ������  ��� ������ ����������
	double   Gamma;             //   ����������� ���������
	double   MaxOfften;         //   ������������ ����������� �������
	double   DeltaSpectr;       //   ����������� ������ �������, �� ����������� DeltaSpectr * 1-� �������
	
	WORD     piter;
	WORD     rkf;
	WORD     kft;
	double   osh;
	
	DWORD    QuantityWorkForce; //  ����� �������� � WORK �����
	WORD     MaskMass;
	
	DWORD    AdrHelpInf;        //   ������� ������  ��� ��������������� �������
    BYTE     TypeSum;           //	 1 - ����� ���������. ������ 19-21, 30, 50, 51
	                            //	 2 - ����� ��� �������� �� ��������. ������ 22-23
	                            //	 3 - ������ ������������ �����. ������ 24, 28, 34
	                            //	 4 - ���������� �����. 31.
	                            //	 5 - �������� �� �������. 27, 42,  47.
	                            //   6 - ��������� ����� .  52.
	                            //  11 - ������ 101, �������� �� ������� 
	BYTE     YesSum;            //   �������  ��������� ����������� (������)
	WORD     QuantitySum;       //   �����  ��������� ����������� (������)
	WORD     NumFixedStep;      //   ��� ����������� ����������� ������ ���������� � ��������
	char     Res[70];
};

struct DYN_FORCE  {  long NumStep;  long NumNode;  BYTE Qn;  double d_7[12];  };

struct s_dok15
{
	short  ls_d15;
	short  mod_d15;
	short  kf_d15;
	short  nsq_d15;
	short  spr_d15;
	short  prt_d15;
	double zn_d15[100];
};


struct DYN_IMPULS_VALUE  {
	double Time;
	double Value;  
};

struct DYN_IMPULS  {
	int    Type;
	int    QuantityPoint;
	double Time;
	double Amp;
	double Area;
	DYN_IMPULS_VALUE * Imp;
};

struct DYN031 {
	double   Coeff;      // 0
	double   WindArea;   // 1  �������� �����
	double   TypeArea;   // 2  ��� ���������
	double   fi;         // 3
	double   resd;       // 4
	double   h;          // 5
	double   Gamma;      // 6  >1, < 0.3
	double   AllForm;    // 7 1 �� ���������, 0 ���������
	double   res[10];
};

struct DATA_SNG {
	double   Correction;      //  ����������� �����������. ������������,
	                          //    ��� ����������� �.2.12, ����� �� ����� 1.2
	double   k1xy;            //  �����������, ����������� ��������� ����������
	                          //     ��� �������������� ������������ �� ����. 2.2.
	double   k1H;             //  �����������, ����������� ��������� ����������
                              //     ��� ������������ ������������ �� ����. 2.2. � �.2.14
                              //     � ����. 2.2 ��������� �������� 0.5
	double   k2;              //  ����������� ��������������� ���������� �� ����. 2.3.
	double   TypeA;           //  ��� ������� ������������ ������������
	double   A;               //  ����������� �����������, �.2.9.
	double   KA;              //  ����������� ��������� � � ��� ����. �����������, �.2.14.
	                          //  �� ��������� ����������� �������� 0.7
	double   Ground;          //  ��������� ������:1 -2 -3 -4 - ������
	double   CX, CY, CZ;      //  ��������: CX � ���� X; CY - � ���� Y; CZ - � ���� Z -
	                          //    ������ ����������� �������� �������������� ������������
	                          //    ��������. ������ ����������� � ���������.
	double   Res;
	double   YesMoment;       //  ������� ����������� �������
	double   X0, Y0, Z0;      //  ���������� ����� ��������.�������� �������������
	double   BX, BY, BZ;      //  ��������: BX � ���� X; BY - � ���� Y; BZ - � ���� Z -
	                          //    ������ ����������� ��������  �������� ������������ ��������.
	                          //    ������ ����������� � ���������.
};

struct DATA_Arm {
	double   Correction;      //  ����������� �����������
	double   k0;              //  ����������� ��������� ������� (����.1.3)
	double   k1;              //  �����������, ����������� ���������� �����������
						   	  //    ����������� (����.2.4)
	double   k2;              //  ����������� ��������������� ���������� �� ����. 2.5
	double   A;               //  ����������� �����������, �.2.9.
	double   KA;              //  ����������� ��������� � � ��� ����. �����������, �.2.14.
	                          //  �� ��������� ����������� �������� 0.7
	double   Ground;          //  ��������� ������:1 -2 -3 -4 - ������
	double   CX, CY, CZ;      //  ��������: CX � ���� X; CY - � ���� Y; CZ - � ���� Z -
	                          //    ������ ����������� �������� �������������� ������������
	                          //    ��������. ������ ����������� � ���������.
	double   Res;
};

struct DATA_Atom {
	double   ke;              //  �����������, ����������� ������ ������� ������������ ��
	double   TypeGraf;        //  ��� ������� ������������ ������������
							  //  0 - �� ���.�3.1.
							  //  1 - ������ ��� ����  �����������
							  //  2 - ��������� ��� ���� �����������
	double   Dl;              //  ��������������� ��������� ���������
	double   Axy;             //  ������������ ��������� ������ � �������������� ���������
	double   KA;              //  ������������ ��������� ������ � ����������� Z
	double   CX, CY, CZ;      //  ��������: CX � ���� X; CY - � ���� Y; CZ - � ���� Z -
							  //    ������ ����������� �������� �������������� ������������
							  //    ��������. ������ ����������� � ���������.
};

struct SEISM_UKR_WORK 
{
	double Correct;           //   �������� ������������ �������������
	double k1;                //   ����. 2.3. ����� ������
	double k2;                //   ����. 2.4  ��������
	double Seism;             //   ������������ 6-9
	double Map;               //   ����� ������ ����. 2.5 � 1.  
	double Ground;            //   ����� 1-4
	double kg;                //   ����. 2.6. �������� ��� ������ 4-� ���������
	double Floor;             //   ���������
	double X;                 //   ����������� �����������
	double Y;
	double Z;
	double TypeGrafic;        //   ��� ������� �������� 0 - �� ���, 1 - ���� ������, 2 - 3-� �������
	double YesMoment;         //   ���� ���������� �
	double B;                 //   ����������� ������ � �����
	double X0;                //   ���������� ������ ��������
	double Y0;
	double Z0;
	double ax;                //   ���������� �������� 
	double ay;
	double az;
};

struct SEISM_SP_RF_WORK 
{
	double Correct;           //   �������� ������������ �������������
	double k1;                //   ����. 3. �������� 
	double Seism;             //   ������������ 7-9
	double Ground;            //   ����� 1-3
	double kg;                //   ����. 6. �������� ������ ��� ������ 4-� ���������
	double X;                 //   ����������� �����������
	double Y;
	double Z;
	double TypeGrafic;        //   ��� ������� �������� 0 - �� ���, 1 - ���� ������, 2 - 3-� �������
	double YesMoment;         //   ���� ���������� �
	double B;                 //   ����������� ������ � �����
	double X0;                //   ���������� ������ ��������
	double Y0;
	double Z0;
	double ax;                //   ���������� �������� 
	double ay;
	double az;
};

struct SEISM_KAZ_2006_WORK 
{
	double Correct;           //   �������� ������������ �������������
	double k1;                //   ����. 5.2. ����� ������ 
	double k1z;               //   �������� 
	double k2;                //   ����. 5.3 � 5.4. ����� ������ 
	double k2z;               //   �������� 
	double Head;              //   ��� ����� ������: 0 - ���������, 1 - 1.8, 2 - 2.0
	double Floor;             //   ��������� >=5
	double ks;                //   �������� ����. 5.6
	double kg;                //   ����� ������ ����. 5.7
	double Seism;             //   ������������ 7-10
	double Ground;            //   ����� 1-3
	double YesA;              //   ��������� �� ������. ������
	double ax;                //   ���������
	double az;                //   ���������
	double X;                 //   ����������� �����������
	double Y;
	double Z;
	double TypeGrafic;        //   ��� ������� �������� 0 - �� ���, 1 - ���� ������, 2 - 3-� �������
	double TypeQuantityForm;  //   ������� ����� ����� ����. 0 - �� ����, 1 - ���
	double P522;              //   ������� ����� �.5.22, 0 - �� ���������
	double P523;              //   ������� ����� �.5.23, 0 - �� ���������
	double P524;              //   ������� ����� �.5.24, 0 - �� ���������
	double P525;              //   ������� ����� �.5.25, 0 - �� ���������
};

struct SUM_DYN_DATA {
    double    QuantityChast;
    double  * Chast;
    int       QuantityPoint;
	double  * PointTime;
	double  * CoefForm;  //  QuantityPointTime * QuantityChast
	double  * CoefFormMax;
};

#pragma pack(pop)
#endif
