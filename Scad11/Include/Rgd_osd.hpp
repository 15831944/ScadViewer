#ifndef ONESIDE_H
#define ONESIDE_H
#pragma pack(push,1)

struct D3OSD 
{
       char  Check[4]; 
       float EF;         //  ��������� �� ������
       float ET;         //  ��������� ����������� ( �� ������������ )
       float Delta;
       char  TypeDelta;  //  0 = �����, 1 - ���������
       char  Sign; 
       BYTE  TypeOrt;  // 0-2Node, 1-x,y,z
       BYTE  TypeEPM;  //  ��� EF ��� EF/L ��� ��������� 55, 352 �� ����������� �
       float x,y,z;  
       float DeltaStressed;
       float Res2;
};

#pragma pack(pop)
#endif
