#ifndef _VOLUME
#pragma pack(push, 1)

struct   D3PLATE   {
     char   ptg[4];    /* �P��HAK =   '*PL*'              */
     BYTE   p_tk;      /* �P��HAK = '','P','B','D'        */
     BYTE   p_em;      /* �P��HAK = '','I','O','A'        */
     BYTE   p_e3;      /* �P��HAK = '','I','O','A'        */
     BYTE   p_c2;      /* �P��HAK = '','I','O','A'        */
     BYTE   p_tmp;     /* �P��HAK = '','I','O'            */
     BYTE   p_uem;     /* �P��HAK = '','F','X','M','T'    */
     BYTE   p_un;      /* �P��HAK = '','F','X','M','T'    */
     BYTE   p_type;    /* ������� ������������            */
     short  nze3;      /* �KA�ATE�� HA E3                 */
     short  nzci;      /* �KA�ATE�� HA C1,C2              */
     short  nzuem;     /* �KA�ATE�� HA �O�O�EH�E          */
		       /* OCE� OPTOTPO���                 */
     short  nzun;      /* �KA�ATE�� HA �O�O�EH�E          */
		       /* OCE� B��A�� HA�P��EH��          */
     short  nztmp;     /* �KA�ATE�� HA KO��.TEMP.PAC��P.  */
     short  nztype;    /* �KA�ATE�� ������  ������������  */
     double e1;        /* MO���� �H�A �O HA�P. OC� "X"    */
     double e2;        /* MO���� �H�A �O HA�P. OC� "Y"    */
     double nu12;      /* KO��. ��ACCOHA "XY"             */
     double nu21;      /* KO��. ��ACCOHA "YX"             */
     double g12;       /* MO���� C�B��A B OC�X "XY"       */
     double etaxy1;    /* KO��. B�A�MOB���H�� 1-�O PO�A   */
     double etaxy2;    /* KO��. B�A�MOB���H�� 1-�O PO�A   */
     double eta1xy;    /* KO��. B�A�MOB���H�� 2-�O PO�A   */
     double eta2xy;    /* KO��. B�A�MOB���H�� 2-�O PO�A   */
     double delta;     /* TO���HA                         */
     double omega;     /* B��. O�PE�E��TE�� EM            */
     float  dz;        /* �KC�EHTP�C�TET                  */
     float  dlk;       /* KOHTPO�� KOOP��HAT              */
     short  nzn;       /* 㪠��⥫� �� �p�����p殮���     */
     BYTE   nznu;      /* ��� �p�����p殮��� � �ᨫ��x   */
     BYTE   nzres;      /* p���p�                         */
     short  nzko;      /* 㪠���.�������⨢�.����ய��  */
     short  nzsl;      /* 㪠���. �/� �����᫮���� ��     */
     float  ro;        /* ���⭮���                       */
     float  RotorShell;     /* �������⥫�� 童�� �����窨   */
     float  fres;      /* १��                          */
};

#define  P_TK     pd3->p_tk
#define  P_EM     pd3->p_em
#define  P_E3     pd3->p_e3
#define  P_C2     pd3->p_c2
#define  P_TMP    pd3->p_tmp
#define  P_UEM    pd3->p_uem
#define  P_UN     pd3->p_un
#define  P_TYPE   pd3->p_type
#define  NZE3     pd3->nze3
#define  NZCI     pd3->nzci
#define  NZUEM    pd3->nzuem
#define  NZUN     pd3->nzun
#define  NZTMP    pd3->nztmp
#define  NZTYPE   pd3->nztype
#define  NZNEUD   pd3->nztype
#define  E1       pd3->e1
#define  E2       pd3->e2
#define  NU12     pd3->nu12
#define  NU21     pd3->nu21
#define  G12      pd3->g12
#define  ETAXY1   pd3->etaxy1
#define  ETAXY2   pd3->etaxy2
#define  ETA1XY   pd3->eta1xy
#define  ETA2XY   pd3->eta2xy
#define  DELTA    pd3->delta
#define  OMEGA    pd3->omega
#define  DZ       pd3->dz
#define  DLK      pd3->dlk
#define  NZN      pd3->nzn
#define  NZNU     pd3->nznu
#define  NZKO     pd3->nzko
#define  NZSL     pd3->nzsl
#define  RO       pd3->ro

  /*----------------------------------------------------------------*/

  /*  �������  ����������                                           */

  struct EPD  {
     double e3;        /* MO���� �H�A �O HA�P. OC� "Z"    */
     double nu13;      /* KO��. ��ACCOHA "XZ"             */
     double nu31;      /* KO��. ��ACCOHA "ZX"             */
     double nu23;      /* KO��. ��ACCOHA "YZ"             */
     double nu32;      /* KO��. ��ACCOHA "ZY"             */
     double etaxy3;    /* KO��. B�A�MOB���H�� 1-�O PO�A   */
     double eta3xy;    /* KO��. B�A�MOB���H�� 2-�O PO�A   */
  };

#define  E3       pd3e3->e3
#define  NU13     pd3e3->nu13
#define  NU31     pd3e3->nu31
#define  NU23     pd3e3->nu23
#define  NU32     pd3e3->nu32
#define  ETAXY3   pd3e3->etaxy3
#define  ETA3XY   pd3e3->eta3xy
  /*----------------------------------------------------------------*/

  /*  �������  ���������                                            */

  struct CPI  {
     double  cp1;      /* KO��. �OCTE��  C1                */
     double  c2p11;    /* KO��. �OCTE��  C2 �O "X"        */
     double  c2p22;    /* KO��. �OCTE��  C2 �O "Y"        */
     double  c2p12;    /* KO��. �OCTE��  C2 �O "XY"       */
  };

#define  CP1      pd3ci->cp1
#define  C2P11    pd3ci->c2p11
#define  C2P22    pd3ci->c2p22
#define  C2P12    pd3ci->c2p12

  /*----------------------------------------------------------------*/

  /* �O�O�EH�E OCE� OPTOTP. X2Y2Z2                                  */

  struct UEM  {  double  uemx, uemy, uemz;  };

     /* P_UEM='F' - ��O� B �P.OTH.X1Y1  */
     /* P_UEM='R' - ��O� B PA�.         */
     /* P_UEM='X' - OC� X2 B CK XYZ     */
     /* P_UEM='M' - OC� X2 B CK X1Y1Z1  */
     /* P_UEM='T' - KOOP�.TO�K� B XYZ   */
     /*        X2 OT 1-�O ���A K HE�    */

#define  UEMX     pd3uem->uemx
#define  UEMY     pd3uem->uemy
#define  UEMZ     pd3uem->uemz
  /*----------------------------------------------------------------*/

  /* �O�O�EH�E OCE� OPTOTP. X3Y3Z3                                  */

   struct UN  {  double unx, uny, unz;  };

      /* P_UN ='F' - ��O� B �P.OTH.X1Y1  */
      /* P_UN ='R' - ��O� B PA�.         */
      /* P_UN ='X' - OC� X3 B CK XYZ     */
      /* P_UN ='M' - OC� X3 B CK X1Y1Z1  */
      /* P_UN ='T' - KOOP�.TO�K� B XYZ   */
      /*        X3 OT 1-�O ���A K HE�    */

#define UNX       pd3un->unx
#define UNY       pd3un->uny
#define UNZ       pd3un->unz
  /*----------------------------------------------------------------*/

  /* KO��.TEMP.PAC��PEH��                                           */

   struct TMP  {  double tmpalx, tmpaly;  };

#define TMPALX    pd3tmp->tmpalx
#define TMPALY    pd3tmp->tmpaly

  /*----------------------------------------------------------------*/

  /* �������������� ����������� ���������                           */

   struct EKO {  double eax, eay, nua, fax, fay, sax, say; };
#define EAX  pd3eko->eax
#define EAY  pd3eko->eay
#define NUA  pd3eko->nua
#define FAX  pd3eko->fax
#define FAY  pd3eko->fay
#define SAX  pd3eko->sax
#define SAY  pd3eko->say

  /* ���������  �/�  ������������  ��                               */

  /*================================================================*/

     struct D3SL {
		   short ksl;
		   short nsp;
		   BYTE  po;
		   BYTE  fr;
		   BYTE  gf;
		   BYTE  pwg;
		   WORD  lsl1, lsl2;
		   float kfa1;
		   float kfa2;
		   float kr11;
		   float kr22;
		   float kr12;
		   };

#define  KSL     pd3sl->ksl
#define  NSP     pd3sl->nsp
#define  POSL    pd3sl->po
#define  FRSL    pd3sl->fr
#define  GFSL    pd3sl->gf
#define  PWG     pd3sl->pwg
#define  LSL1    pd3sl->lsl1
#define  LSL2    pd3sl->lsl2
#define  KFA1    pd3sl->kfa1
#define  KFA2    pd3sl->kfa2
#define  KR11    pd3sl->kr11
#define  KR22    pd3sl->kr22
#define  KR12    pd3sl->kr12

     /*  --------------------------------------------------------------  */

      struct ELAST_LAYER {
		      char  p_em;      /* �P��HAK = '','I','T','O'        */
		      char  p_res;
		      short nzemsl;
		      short nzres[2];
		      float e1;        /* MO���� �H�A �O HA�P. OC� "X"    */
		      float e2;        /* MO���� �H�A �O HA�P. OC� "Y"    */
		      float e3;        /* MO���� �H�A �O HA�P. OC� "Z"    */
		      float nu12;      /* KO��. ��ACCOHA "XY"             */
		      float nu21;      /* KO��. ��ACCOHA "YX"             */
		      float nu13;      /* KO��. ��ACCOHA "XZ"             */
		      float nu31;      /* KO��. ��ACCOHA "ZX"             */
		      float nu23;      /* KO��. ��ACCOHA "YZ"             */
		      float nu32;      /* KO��. ��ACCOHA "ZY"             */
		      float g12;       /* MO���� C�B��A B OC�X "XY"       */
		      float g13;       /* MO���� C�B��A B OC�X "XZ"       */
		      float g23;       /* MO���� C�B��A B OC�X "YZ"       */
		      float delta;     /* TO���HA ����                    */
		      float omega;    /* B��. O�PE�E��TE�� EM            */
		    };

#define  SLP_EM     ElastLayer->p_em
#define  SLNZEM     ElastLayer->nzemsl
#define  SLE1       ElastLayer->e1
#define  SLE2       ElastLayer->e2
#define  SLE3       ElastLayer->e3
#define  SLNU12     ElastLayer->nu12
#define  SLNU21     ElastLayer->nu21
#define  SLNU13     ElastLayer->nu13
#define  SLNU31     ElastLayer->nu31
#define  SLNU23     ElastLayer->nu23
#define  SLNU32     ElastLayer->nu32
#define  SLG12      ElastLayer->g12
#define  SLG13      ElastLayer->g13
#define  SLG23      ElastLayer->g23
#define  SLDELTA    ElastLayer->delta
#define  SLOMEGA    ElastLayer->omega

     /*  --------------------------------------------------------------  */

#include <rgd_pl_n.h>

#pragma pack(pop)
#endif
