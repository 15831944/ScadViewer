#ifndef FORCE_TIME_FLAG_H
#define FORCE_TIME_FLAG_H
#pragma pack(push,1)

#include "scadload.hpp"

struct FORCE_TIME_STR
{
    LPSTR         Text;
	int           QuantityTimeResult;  
	double      * TimeResult;

	int           TypeTimeStep; //  ��� ������ ����. ���� 0 - �� �����. �����   
	
	double        TimeStep;     //  ��� ��������������. 
	double        TimeProcess;  //  ����������������� ��������
	double        Rksi[2];      //  ��������� ������������ � ����� �� ������������ ��� ������ ���� ����
	double        DeltaTime;    //  ��� ���������� ����������� ����� ������
	
	double        Res[19];
	
};

class  FORCE_TIME : public SCAD_BASE_CLASS
{
public: 
	 FORCE_TIME()      {  Init();    }
	~FORCE_TIME(void)  {  Destroy();  }

void Init()     {  
	 SCAD_BASE_CLASS::Init(0,0,sizeof(FORCE_TIME_STR)-12,sizeof(FORCE_TIME_STR)-12,1,500);
	 LenData[0] = sizeof(double);	  }

void               SetTimeResult( int Num, int Qnt, double *Time, int Type=0 ) {  ChangeComponent(Num,1,Qnt,Time,Type);    }
void  SCHEMA_EXPORT SetTimeFixed( double Dl, double TM ); 

FORCE_TIME_STR    * Get( int Num = 1 ) {  return (FORCE_TIME_STR*)GetObject(Num);  }

void  SCHEMA_EXPORT Add( void *, int LenSent, BYTE &Control );

void  SCHEMA_EXPORT Export( void *Schem, FILEPRINT &Work );

void  SCHEMA_EXPORT Write( SCAD_LOAD_LIST &_LoadList, FILEBASE &Output, DOCUMENT &Doc );

};

#pragma pack(pop)
#endif
