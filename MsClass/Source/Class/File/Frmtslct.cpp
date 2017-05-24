#include <stdafx.h>
#include "string.h"

int FormatSelect(LPSTR &pF, LPSTR  &pN )
{
	 static char TypeFormat[] = {
	 /* ᯥ�䨪�樨 �++                   */
	'd', 'i', 'o', 'u', 'x', 'X',
	'e', 'E', 'f', 'g', 'G',
	'c', 's',
	'p', 'n',
	 /* ᯥ樠��� ᯥ�䨪�樨           */
	'F', /* %nF, %nlF - �������� float ��� double   */
		  /*             � ������p������� �p��� g  */
	'T', /* %nF, %nlF - �������� != 0 float ��� double   */
		  /*             � ������p������� �p��� g      */
	'Z', /* %nF, %nlF - �������⭮ F, �᫨ arg != 0.*/
		  /*             ���� �p�����                 */
	'K', /* %nK - �������� ⮫쪮 ᫥���騥 n �p��  */
	'N', /* %nn - ��������  n �����x ��p��          */
	'r', /* %nr - ����p��� n p�� ᨬ���, ᫥����x   */
		  /*       ��p�� ᯥ�䨪�樥�                 */
	'b', /* %nb - ��������  n �p������              */
	'B', /* %nB - �p�������  n ���� � ��p���p�      */
	'?', /*       �⠢��� ���. 8                      */
	'S', /* %nS - ����� ��p���p� Clf                */
	'Z', /* %nZ - column(n)                           */
	'W', 'A', 'P',
	0  };

	 pF = pN;
	 if ( *pN == '%' && *(pN+1) == '%' ) {
	    pF++;  pN = pN + 2;
	    return 0;   }

	 for ( ; *pN; pN++ ) {
	    if ( *pN == '%' ) {
	       if ( pN > pF ) goto _10;
	       for ( ; *pN; pN++ )
		  if ( strchr(TypeFormat,*pN) ) {  pN++;   goto _10;  }
	       return 2;   }
	    }
_10:	 if ( *pF == '%' && *(pF+1) != '%' ) return 1;
	 return 0;
}