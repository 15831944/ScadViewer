#ifndef D3ROD_FLAG_H
#pragma pack(push,1)

   struct D3ROD {

      double ema[6];  //  EF,EIY,EIZ,GKP,GFY,GFZ        

      BYTE  ntpr;     //  HOMEP T��A �PO�E��P�          
      BYTE  ntkf;     //  HOMEP T��A F, FK, FD          
      BYTE  nwgx;     //  HA����E B��. �/X              
      BYTE  ntsw1;    //  HOMEP C/K �/B  ���� 1         
      BYTE  ntsw2;    //  HOMEP C/K �/B  ���� 2         
      BYTE  nsdw;     //  HA����E C�B��A                
      BYTE  nob;      //  ������� �������               
      BYTE  TypeEPM;  //  ��� EF ��� EF/L ��� ��������� 55, 352 �� ����������� �

      WORD  nzhd;     //  HOMEP ��C�A HA�A�A HD         
      WORD  kzhd;     //  HOMEP ��C�A KOH�A  HD         
      WORD  nzcy;     //  HOMEP ��C�A HA�A�A CY         
      WORD  nzcz;     //  HOMEP ��C�A HA�A�A CZ         

      WORD  wRes[4];  //                              

	  double  Corner[3];      //  ���������� �� Corner        
      double  Alfa;           //  ������� �������             
      double  DeltaStressed;  // ��������� ����� ����� ����� ��������������. ����������

      double e;       //  E                             
      double A;       //  ������� ������
      double ro;      //  ���������                     
      double nu;      //  ����������� ��������          
      double n;       //  BE����HA N                    
      double dRes[2];

      double axn;     //                                
      double axk;     //                                
      double ayn;     //       �ECTK�E                  
      double ayk;     //       BCTABK�                  
      double azn;     //                                
      double azk;     //                                

      double yi1;     //                                
      double yi2;     //       ��PA                     
      double zi1;     //       CE�EH��                  
      double zi2;     //                                

      double Data[1];  //  

};

#define SFE     d3rod->sfe
#define CFE     d3rod->cfe
#define NTPR    d3rod->ntpr
#define NTKF    d3rod->ntkf
#define NWGX    d3rod->nwgx
#define NTSW1   d3rod->ntsw1
#define NTSW2   d3rod->ntsw2
#define NSDW    d3rod->nsdw
#define NOB     d3rod->nob
#define NZHD    d3rod->nzhd
#define KZHD    d3rod->kzhd

#define EMA(I)  d3rod->ema[(I)]
#define EF      d3rod->ema[0]
#define EIY     d3rod->ema[1]
#define EIZ     d3rod->ema[2]
#define GKR     d3rod->ema[3]
#define GFY     d3rod->ema[4]
#define GFZ     d3rod->ema[5]
#define KZST    d3rod->kzst
#define NZCY    d3rod->nzcy
#define NZCZ    d3rod->nzcz
#define EME     d3rod->e
#define RO      d3rod->ro
#define N       d3rod->n
#define NU      d3rod->nu
#define AXH     d3rod->axn
#define AXK     d3rod->axk
#define AYH     d3rod->ayn
#define AYK     d3rod->ayk
#define AZH     d3rod->azn
#define AZK     d3rod->azk
#define YI1     d3rod->yi1
#define YI2     d3rod->yi2
#define ZI1     d3rod->zi1
#define ZI2     d3rod->zi2
#define RNTS    d3rod->rnts
#define RodData(I)  d3rod->Data[(I)]

#pragma pack(pop)
#endif
