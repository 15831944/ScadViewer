#ifndef DYNAMIC_METOD_FLAG_H
#define DYNAMIC_METOD_FLAG_H

struct  DYNAMIC_METOD
{
       BYTE    TypeMetod;     // 0 -  �������� ��������������,
                               // 1 -  ������������� ������, 2 - ������
        BYTE    YesDiapazon;   // 1 - Yes  �������� ��� ��������
        BYTE    YesProcMass;   // 1 - Yes (������ ��� ��������)
                               // ��� ������� ����� ������� ������������ ��������
                               // �� ini �����. ������ [ScadCalcul],
                               // �������� DynamicProcMass   90, 90, 75
        BYTE    ResByte[3];    //     ������
        double  MinD;          //  �������� ���������
        double  MaxD;
        double  ProcentX;      // ������ ��� ��������
        double  ProcentY;
        double  ProcentZ;
        double  Shift;        //  ����� ��� ���������� ����������� ������ ��� ������ 100
                              //  �������� � ���� "��������� ������". �� ��������� - 0.
        int     BlockSizeLanzos;        //  �� ini �����. ������ [ScadCalcul],
                                        //  �������� BlockSizeLanzos, �� ��������� 3.
        int     MaxNumberLanzosVector;  //  �� ini �����. ������ [ScadCalcul],
                                        //  �������� MaxNumberLanzos, �� ��������� 150.
        int     NumberIntervalLanzos;   //  �� ini �����. ������ [ScadCalcul],
                                        //  �������� NumberIntervalLanzos, �� ��������� 20.

        int     ResI;
        double  Res[10];
};

#endif
