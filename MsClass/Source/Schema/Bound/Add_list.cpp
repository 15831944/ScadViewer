#include <stdafx.h>
#include "bound.h"
/*---------------------------------------------------------------*/
/*   �x���� ��p����p�:                                          */
/*         Text  - ⥪�� ��p���       	                         */
/*         Num   - ����p ᯨ᪠  = 0 - Add                       */
/*                 �p� Num = 0 - Add, ���� ��pp���p����        */
/*         Type  - ⨯ ��p���                                    */
/*         Mask  - ��⮢�� ��᪠ ��� ����⮢ ��p���            */
/*         MaxNum     - max �����⨬� ����p � ��p���            */
/*   ��x���� ��p����p� :                                        */
/*         Bound - ����� BOUND ���������� ���p��樨             */
/*         Contpol  - ���� ����p���. ����p����� ��⮢:           */
/*            0 - �������⨬� ᨬ���                            */
/*            1 - �訡�� � ���p��p� ����p�                     */
/*            2 - � ᯨ᪥ ��� ���p��樨                        */
/*            3 - ����筮� ���祭�� � ����p� ����� ��砫쭮��  */
/*            4 - ᯨ᮪ ᮤ�p��� ����p� > MaxNum                */
/*            5 - ᯨ᮪ ᮤ�p��� ����p� �����p�x ����⮢     */
/*                ����� ������ p���                             */
/*         QuantityNumList  - �᫮ ᯨ᪮�, � ���p�x           */
/*                �����p������ ��x������ ���� �����            */
/*    ���� ����p��                                              */
/*         0 - ��⮢�� ��p��� ���������                         */
/*         1 - �訡��, 㪠����� � ��p��x 4-x ���x              */
/*         2 - ���⮩ ᯨ᮪                                     */
/*         3 - ����pp���� ����p ᯨ᪠ �p� ������              */
/*        -1 - �p���p�������, 㪠����� � 4 � 5 ���x           */
/*             ��⮢�� ��p��� ��������� � Bound                 */
/*---------------------------------------------------------------*/

EXPORT int AddList( LPCSTR Text, WORD Num,
	      BOUND &Bound,BYTE Type, WORD Mask, WORD MaxNum,
	      BYTE &Control, BYTE &QuantityNumList )
{
    /*  P����p⪠ ᯨ᪮��x ��p���p  */

	WORD  i, j, k, n, Quantity;
	MEMORY MEM;
  WORD *List;
	BOUND_LIST *BndLst;
	BYTE *kz;
	int iRet = 0;

	QuantityNumList = 0;
	List = (WORD*)MemAlloc(MaxNum+2,sizeof(WORD));
	kz   = (BYTE*)MemAlloc(MaxNum+2);

	if ( TextList(Text,MaxNum,Quantity,List,Control) ) goto _10;
	if ( Quantity == 0 ) {  iRet = 2;   goto _10;  }

	if ( Num == 0 || Num > Bound.GetQuantityBound() )
      Bound.Include(Type,Mask,Quantity,List);
	else iRet = Bound.Change(Num,Type,Mask,Quantity,List);
	if ( iRet ) return 3;

	for ( i=0; i<Quantity; i++ ) {
	   n = List[i];
           if ( n == 0 || n > MaxNum ) continue;
	   for ( j=1; j<=Bound.GetQuantityBound(); j++ ) {
	      BndLst = Bound.GetBound(j);
	      for ( k=0; k<BndLst->Quantity; k++ )
		 if ( BndLst->List[k] == n ) {
 		    kz[n]++;
		    if ( QuantityNumList < kz[n] ) QuantityNumList = kz[n];
		    if ( kz[n] > 2 ) kz[n] = 3;  }
	      }  }

_10:	MemFree (kz);
	MemFree (List);

	if ( BitRead(&Control,0) || BitRead(&Control,1) ||
	     BitRead(&Control,2) || BitRead(&Control,3) ) return 1;
	if ( iRet == 0 )
	   if ( BitRead(&Control,4) || BitRead(&Control,4) ) return -1;
	return 0;

}