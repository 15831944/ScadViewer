#ifndef SCADHASP_H
#define SCADHASP_H

#include <windows.h>
#include <time.h>
#include "hasp.h"

#define MAX_CUSTOMER_NAME_HASP 71
/*
   ������ ���������:
      0 - ������������
      1 - ��������� ��������
      2 - ���������� ����������
      3 - ������������
      4 - �����������
      5 - ������������
      6 - ������
      7 - �������
      8 - ���������
      9 - ��������
     10 - ������
     11 - AutoCAD
     12 - ������
     13 - �����
     14 - ������
     15 - �������
     16 - ������� 2
     17 - �������
     18 - �����
     19 - ��������
     20 - ���
     21 - �������� �������
     22 - �����
     23 - FORUM
     24 - ����
*/
extern struct SCADProtection
{
   WORD  ControlSum;    // ����������� �����
   WORD  TRIALPeriod;   // ������������ TRIAL ������� � ����
   WORD  SCADMode;      // 0 - �����; 1 - trial; 2 - �����
   time_t StartTrial;   // ����� ������ trial �������
   time_t LastTrial;    // ����� ��������� ��������� SCAD,
   char  SubSystems[8]; // ���� ���������
                        // ����������� � trial ������
   char  Serial1[8];    // �������� ����� 1
   char  Serial2[8];    // �������� ����� 2
   char  Limit;         // 0 - 32000, 1 - Unlimited, 2 - Junior, 3 - 750x750
   char  Customer[MAX_CUSTOMER_NAME_HASP];   // �������� �����-���������
   WORD  Version;       // �����
} Protect;

#define SCADPASSWORD1   28455
#define SCADPASSWORD2   26190
#define SCADSeedCode1   1956
#define SCADSeedCode2   1987
#define PASSWORD        101

BOOL IsSCADHasp(void);
BOOL ReadSCADHasp(void);
void HASPError(int Status);
BOOL CALLBACK AskPasswordDlg(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK PayMeDlg(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam);
void UpdateHASP(void);
BOOL IsRgmEnabled(SCHEMA *Prj);
void  HASPDisconnect(void);

#endif
