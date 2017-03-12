#ifndef OBJECT_STRING_FLAG_H
#define OBJECT_STRING_FLAG_H

#include <BaseClass.hpp>


class OBJECT_STRING : public SCAD_BASE_CLASS
{
public:
	     OBJECT_STRING()     {  Init(0);    }
       ~OBJECT_STRING(void) {  Destroy();  }

int     CLASS_EXPORT Add(LPSTR Text, int LenText, BYTE &Control );
int     CLASS_EXPORT Add(LPSTR Text ) {  return AddObject(NULL,Text);     }

};


#endif
