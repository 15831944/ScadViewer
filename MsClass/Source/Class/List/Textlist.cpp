#include <stdafx.h>
#include "defclass.h"
#include "convert.h"
#include "bit.h"
#include "memclass.h"
/*---------------------------------------------------------------*/
/*   �x���� ��p����p�:                                          */
/*         Text  - ⥪�� ��p���       	                         */
/*         MaxNum     - max �����⨬� ����p � ��p���            */
/*   ��x���� ��p����p� :                                        */
/*         Quantity - �᫮ ����⮢ ᯨ᪠                     */
/*         List     - ᯨ᮪                                     */
/*         Contpol  - ���� ����p���. ����p����� ��⮢:           */
/*            0 - �������⨬� ᨬ���                            */
/*            1 - �訡�� � ���p��p� ����p�                     */
/*            2 - � ᯨ᪥ ��� ���p��樨                        */
/*            3 - ����筮� ���祭�� � ����p� ����� ��砫쭮��  */
/*            4 - ᯨ᮪ ᮤ�p��� ����p� > MaxNum                */
/*            5 - ᯨ᮪ ᮤ�p��� ����p� �����p�x ����⮢     */
/*                ����� ������ p���                             */
/*    ���� ����p��                                              */
/*         0 - ��⮢�� ��p��� ����p�����                       */
/*         1 - �訡��, 㪠����� � ��p��x 4-x ���x              */
/*        -1 - �p���p�������, 㪠����� � 4 � 5 ���x           */
/*---------------------------------------------------------------*/

EXPORT BYTE  Separate( LPCSTR InpString,  DWORD LengthInpString,
	       DWORD &CurrentPos, LPCSTR SeparateSymbol, HPSTR OutString);

EXPORT int   TextList( LPCSTR Text, WORD MaxNum, WORD &Quantity, WORD *List, BYTE &Control )
{
    /*  P����p⪠ ᯨ᪮��x ��p���p  */

	BYTE *kz, c, q, knt;
	int  i, NumBeg, NumEnd, NumStep;
	DWORD LenText = strlen(Text), Pos = 0;
	HPSTR Out;
	MEMORY MEM;

	Control = 0;

	Out = (LPSTR)MemAlloc(LenText+2);
	kz  = (BYTE*)MemAlloc(MaxNum+1);

	while ( 1 )  {

	    c = Separate(Text,LenText,Pos,"rR-; ",Out);
	    if ( c == 'r' || c == 'R' || c == '-' ) {
	       BitOn(&Control,1);  goto _20; }
	    if ( c == ';' ) continue;
	    if ( Out[0] == 0 ) break;

_10:	    NumBeg = CharWord(Out,knt);
	    if ( knt ) {  BitOn(&Control,0);  goto _20; }
	    if ( NumBeg < 1 || NumBeg > MaxNum ) {
	       BitOn(&Control,4);  continue;  }
	    if ( kz[NumBeg] ) BitOn(&Control,5);
	    kz[NumBeg] = 1;

	    NumStep = 1;

	    c = Separate(Text,LenText,Pos,"rR;- ",Out);
	    if ( c == 0 ) if ( Out[0] ) goto _10;
			  else break;
	    if ( c == ';' ) continue;

	    q = Separate(Text,LenText,Pos," ",Out);
	    if ( q || Out[0] == 0 ) {   BitOn(&Control,1);  continue;  }
	    NumEnd = CharWord(Out,knt);
	    if ( knt )  {    BitOn(&Control,1);  goto _10;  }
	    if ( c != '-' ) {
	       q = Separate(Text,LenText,Pos,"; ",Out);
	       if ( q || Out[0] == 0 )  {  BitOn(&Control,1);   goto _20;  }
	       NumStep = CharWord(Out,knt);
	       if ( knt ) {    BitOn(&Control,1);  goto _10;  }
	       }
	   if ( NumEnd < NumBeg ) BitOn(&Control,3);

	   for ( i=NumBeg+NumStep; i<=NumEnd; i+=NumStep ) {
	      if ( i < 1 || i > MaxNum ) {
		 BitOn(&Control,4);  continue;  }
	      if ( kz[i] ) {  BitOn(&Control,5);  continue;  }
	      kz[i] = 1;   }

	   }

	for ( i=1,Quantity=0; i<=MaxNum; i++ )
	   if ( kz[i] ) List[Quantity++] = (WORD)i;

	if ( Quantity == 0 ) BitOn(&Control,2);

_20:	MemFree (kz);
	MemFree (Out);

	if ( BitRead(&Control,0) || BitRead(&Control,1) ||
	     BitRead(&Control,2) || BitRead(&Control,3) ) return 1;
	if ( BitRead(&Control,4) || BitRead(&Control,4) ) return -1;
	return 0;

}

EXPORT int   TextListFull( LPCSTR Text, WORD MaxNum, WORD &Quantity, WORD *List, BYTE &Control )
{
    /*  P����p⪠ ᯨ᪮��x ��p���p  */

	BYTE c, q, knt;
	int  i, n, NumBeg, NumEnd, NumStep;
	DWORD LenText = strlen(Text), Pos = 0;
	LPSTR Out;
	MEMORY MEM;

	Control = 0;  n = 0;

	Out = (LPSTR)MemAlloc(LenText+2);

	while ( 1 )  {

	    c = Separate(Text,LenText,Pos,"rR-; ",Out);
	    if ( c == 'r' || c == 'R' || c == '-' ) {
	       BitOn(&Control,1);  goto _20; }
	    if ( c == ';' ) continue;
	    if ( Out[0] == 0 ) break;

_10:	 NumBeg = CharWord(Out,knt);
	    if ( knt ) {  BitOn(&Control,0);  goto _20; }
	    if ( NumBeg < 1 || NumBeg > MaxNum ) {
	       BitOn(&Control,4);  continue;  }
       List[n++] = NumBeg;
	    NumStep = 1;

	    c = Separate(Text,LenText,Pos,"rR;- ",Out);
	    if ( c == 0 ) if ( Out[0] ) goto _10;
			  else break;
	    if ( c == ';' ) continue;

	    q = Separate(Text,LenText,Pos," ",Out);
	    if ( q || Out[0] == 0 ) {   BitOn(&Control,1);  continue;  }
	    NumEnd = CharWord(Out,knt);
	    if ( knt )  {    BitOn(&Control,1);  goto _10;  }
	    if ( c != '-' ) {
	       q = Separate(Text,LenText,Pos,"; ",Out);
	       if ( q || Out[0] == 0 )  {  BitOn(&Control,1);   goto _20;  }
	       NumStep = CharWord(Out,knt);
	       if ( knt ) {    BitOn(&Control,1);  goto _10;  }
	       }
	   if ( NumEnd < NumBeg ) BitOn(&Control,3);

	   for ( i=NumBeg+NumStep; i<=NumEnd; i+=NumStep ) {
	      if ( i < 1 || i > MaxNum ) {
		   BitOn(&Control,4);  continue;  }
         List[n++] = i;  }

	   }

   Quantity = n;
	if ( Quantity == 0 ) BitOn(&Control,2);

_20:
	MemFree (Out);

	if ( BitRead(&Control,0) || BitRead(&Control,1) ||
	     BitRead(&Control,2) || BitRead(&Control,3) ) return 1;
	if ( BitRead(&Control,4) || BitRead(&Control,4) ) return -1;
	return 0;

}