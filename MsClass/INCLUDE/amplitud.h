#ifndef AMPLITUDE_FLAG_H
#define AMPLITUDE_FLAG_H

// ����� - 4
// ����: ���� .F15 � ������ �������� ��������� AMPLITUDE
// �����: ���� .F15 � ������� ����� ��������� AMPLITUDE ������� �������,
//               ������� ������� ������� � Pos ��� ���������������� ����
//               �� ��������������� ������������
#pragma pack(push, 1)
struct AMPLITUDE
{
   WORD   NumLoadDyn;
   WORD   NumLoadGroup;
   WORD   QuantityNode;    //  <= 10
   WORD   NumNode[10];
   double Depl;     // ����������� ����������� ������
   double MinChast;
   double MaxChast;
   double DeltaChast;

// �����
   long   QuantityPoint;
   long   QuantityChast;
   DWORD  PosChast;
   DWORD  Pos[10][3];
};
#pragma pack(pop)
#endif

