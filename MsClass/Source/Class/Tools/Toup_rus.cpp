#include <stdafx.h>
#include <defclass.h>

EXPORT void ToupRus(LPSTR Text)
{
       static char RusLow[] =
	      "��������������������������������";
       static char RusUp[] =
	      "���KEH����X���BA�PO������CM�T���";

       LPCSTR p;
       LPSTR  pT = Text;

       for ( ; *pT; pT++ )  {
	  p = strchr(RusLow, *pT = toupper(*pT));
	  if ( p ) *pT = RusUp[p-RusLow];   }

}