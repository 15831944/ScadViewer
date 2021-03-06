#pragma pack(push, 1)
   struct D3ROD {
      float  Corner[3]; /*  ¨­ä®à¬ æ¨ï ¨§ Corner        */
      float  Alfa;      /*  ®¢®à®â á¥ç¥­¨ï             */
      float  fRes;      /*  à¥§¥à¢                      */
      WORD   NumConstr;  /* ááë«ª  ­  SECTION_NAME      */     
      WORD   wRes;       /*                             */     
      char ptg[2];    /*  PHAK PTG='EM'  ' '      */
      BYTE ntpr;      /*  HOMEP TA POEP          */
      BYTE ntkf;      /*  HOMEP TA F, FK, FD          */
      BYTE nwgx;      /*  HAE B. /X              */
      BYTE ntsw;      /*  HOMEP C/K /B                 */
      BYTE nsdw;      /*  HAE CBA                */
      BYTE nob;       /*                  */
      double ema[6];  /*  EF,EIY,EIZ,GKP,GFY,GFZ        */
      short kzst;     /*  K-BO CE B SI               */
      short nzcy;     /*  HOMEP CA HAAA CY         */
      short nzcz;     /*  HOMEP CA HAAA CZ         */
      short nzhd;     /*  HOMEP CA HAAA HD         */
      short kzhd;     /*  HOMEP CA KOHA  HD         */
      short kztype;   /*    ¤ ­­ë¥ "" ¨ ¤à.  */
      float e;        /*  E                             */
      float ntp;      /*                 */
      float ro;       /*  ¯«®â­®áâì                     */
      float nu;       /*  ®íää¨æ¨¥­â ã áá®­           */
      float n;        /*  BEHA N                    */
      double axn;     /*                                */
      double axk;     /*                                */
      double ayn;     /*       ECTKE                  */
      double ayk;     /*       BCTABK                  */
      double azn;     /*                                */
      double azk;     /*                                */
      double yi1;     /*                                */
      double yi2;     /*       PA                     */
      double zi1;     /*       CEEH                  */
      double zi2;     /*                                */
      double rnts;    /*  HOMEP TA CEEH            */
      double gxs[6];  /*   CEEH               */
       };

#define SFE     d3rod->sfe
#define CFE     d3rod->cfe
#define PF      d3rod->pf
#define PTG(I)  d3rod->ptg[(I)]
#define NTPR    d3rod->ntpr
#define NTKF    d3rod->ntkf
#define NWGX    d3rod->nwgx
#define NTSW    d3rod->ntsw
#define NSDW    d3rod->nsdw
#define NOB     d3rod->nob
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
#define NZHD    d3rod->nzhd
#define KZHD    d3rod->kzhd
#define KZTYPE  d3rod->kztype
#define NTP     d3rod->ntp
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
#define GXS(I)  d3rod->gxs[(I)]

#ifdef INPUT_FLAG_H

      void EXPORT RodSection00( float rodsize, WORD QuantityDbl, TYPE_DATA_SF *f, D3ROD * d3rod, BYTE & Control );
      void EXPORT RodSection01( float rodsize, WORD QuantityDbl, TYPE_DATA_SF *f, D3ROD * d3rod, BYTE & Control );
      void EXPORT RodSection02( float rodsize, WORD QuantityDbl, TYPE_DATA_SF *f, D3ROD * d3rod, BYTE & Control );
      void EXPORT RodSection03( float rodsize, WORD QuantityDbl, TYPE_DATA_SF *f, D3ROD * d3rod, BYTE & Control );
      void EXPORT RodSection04( float rodsize, WORD QuantityDbl, TYPE_DATA_SF *f, D3ROD * d3rod, BYTE & Control );
      void EXPORT RodSection05( float rodsize, WORD QuantityDbl, TYPE_DATA_SF *f, D3ROD * d3rod, BYTE & Control );
      void EXPORT RodSection06( float rodsize, WORD QuantityDbl, TYPE_DATA_SF *f, D3ROD * d3rod, BYTE & Control );
      void EXPORT RodSection07( float rodsize, WORD QuantityDbl, TYPE_DATA_SF *f, D3ROD * d3rod, BYTE & Control );
      void EXPORT RodSection08( float rodsize, WORD QuantityDbl, TYPE_DATA_SF *f, D3ROD * d3rod, BYTE & Control, double &Alfa );
      void EXPORT RodSectionBase(INPUT &,WORD ntg,INFRGD *infrab,D3ROD *d3rod, BYTE &knt, double &Alfa);

#endif
#pragma pack(pop)
