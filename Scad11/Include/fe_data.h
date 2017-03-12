#ifndef FE_DATA_H
#define FE_DATA_H
#pragma pack(push,8)

struct FE_DATA
{       
       void (*PutMsg)    (int...);
       void (*PutMsgFE)  (int Num,int NQ);

       void              * Calc;         //  ����� CALCUL
       SCHEMA            * Schem;
       FORMAT            * FormatFE;

       RSN_STR           * LoadComb;
       RSN_STR           * LoadCombFull;

       FE_COORD          * CoordEl;
       WORD              * JointEl;
       WORD              * JointSystemEl;
       double            * RigidEl;
       long              * StepEl;
       FE_FORCE          * ForceEl;

       double              MKA[15*15];
       short               OrderMK;  
       double            * Matr;
       double            * MatrElem;          //   ������� �� ��������� �� ��
       int                 NumElemMatrBuf;    //   ������� ���� ��� �� ���������� ������ ������, ��������� ���� �� ������
       BYTE              * EqualMatrElem;

       double            * Force;

       int                 LengthHelp;        //  ����������� ���� ��� ������ �� ( �������� � �.�. )
       void              * Help;

       short               QuantityPoint;     //  ���������� ����� ������ ������ � ����������� ��������������
       double            * CoordX;

//     ������ ��� ����������� ����������  
       void              * StepData;          //  ������ ����������� ����, ��������� �� ����� ��

       double            * Displace;          // ���������� �� ����, ��������
       double            * Reak;              // Step

       double            * DisplaceFull;
       double            * DisplaceMG;
       double            * UsFull;
       double            * ReakFull;
       double            * Differ;            //  �� ����������� ��������� �������� �� ���� (��������, ������. �����)
       double            * DifferVariation;   //  ��������� �������� �� �������� (��������, �����),
	                                          //  ��������� �� ������ ����

       STEP_LOAD         * pSL;               // ������ ���� 
       int                 NumIter; 
       int                 EndIter;
       double              Epsilon;

       BYTE                QuantityInt;  //  ��� ���������� ������ � �������� ��������
       BYTE                WorkStress;  //  ������� �������� ��� ���������� ��������������
       BYTE                NoForceInsert;   // �� ��������� ����������-�������. �������� �� �������� � ��������

       double            * DiagMatr;       //  ������������ �������� ��    

       double              RotorShell;
	   FILEWORK          * FilePoly; 
	   BYTE                EfforsDynamic;  //  ��� ������� �������� �� ��������� ��������������
       BYTE                Res[11];
};

#pragma pack(pop)
#endif
