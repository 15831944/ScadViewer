#include <stdafx.h>
#include <defclass.h>
#include <math.h>

EXPORT void  MultMatr(double *a, double *b, int ia, int ja,int jb,double *c )

  /* ��������� ������ �� ������:
	  a[abs(ia),ja] * b[ja,abs(jb)]
	  �᫨ ia<0 �࠭ᯮ������� a, �࠭����� � ���� a[ja,-ia]
	  �᫨ jb<0 �࠭ᯮ������� b, �࠭����� � ���� b[-jb,ja]       */
#define  A(i,j)  a[ja * (i) + (j)]
#define  B(i,j)  b[jb * (i) + (j)]
#define  C(i,j)  c[jb * (i) + (j)]

{
     int i, j, k, l=0;
     double r, *pa, q;

     for ( i=0; i<abs(ia); i++)  {
 	     pa = &A(i,0);
	     for ( j=0; j<abs(jb); j++ ) 	{
	        r = 0;
	        for ( k=0; k<ja; k++ ) {
	           if ( ia>0 ) q = pa[k];    else q = a[i-k*ia];
	           if ( jb>0 ) q *= B(k,j);  else q *= b[k+j*ja];
	           r += q ;   }
	        c[l++] = r;  }  }

}