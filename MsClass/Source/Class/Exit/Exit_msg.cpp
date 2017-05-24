#include <stdafx.h>
#include <classwin.h>

void EXPORT ExitMessage( DWORD Type )
{
   int Num;

	switch(Type)
	{
		case EXCEPTION_ACCESS_VIOLATION:      // "��������� � ��������� ������ ������"
         Num =  1;   break;
		case EXCEPTION_DATATYPE_MISALIGNMENT: //	"��������� ������������";
         Num =  2; 	break;
		case EXCEPTION_BREAKPOINT:            //  "�������� ����� ��������";
         Num =  3;  	break;
		case EXCEPTION_SINGLE_STEP:           //  "�������� �����������";
         Num =  4;	break;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: //  "����� �� ������� �������";
         Num = 5;		break;
		case EXCEPTION_FLT_DENORMAL_OPERAND:  //  "����������������� �������������� �����";
         Num = 6;		break;
		case EXCEPTION_FLT_INEXACT_RESULT:    //  "��������� ��������� ��������� ��������"
         Num = 7;		break;
		case EXCEPTION_FLT_INVALID_OPERATION: //  "������ ��������� ����������";
         Num = 8;		break;
		case EXCEPTION_FLT_OVERFLOW:          //  "������������ � ��������� ������";
         Num = 9;		break;
		case EXCEPTION_FLT_STACK_CHECK:       //  "������������ �����(��������� ����������)";
         Num = 10;	break;
		case EXCEPTION_FLT_UNDERFLOW:         //  "������������ � ��������� ������";
         Num = 11;	break;
		case EXCEPTION_INT_DIVIDE_BY_ZERO:    //  "������� �� ����(�������������)";
         Num = 12;	break;
		case EXCEPTION_INT_OVERFLOW:          //  "������������ �������������";
         Num = 13;	break;
		case EXCEPTION_PRIV_INSTRUCTION:      //  "������������������ ��������";
         Num = 14;	break;
		case EXCEPTION_IN_PAGE_ERROR:         //  "������ ��������";
         Num = 15;   break;
		case EXCEPTION_ILLEGAL_INSTRUCTION:   //  "������������ ����������";
         Num = 16;   break;
		case EXCEPTION_NONCONTINUABLE_EXCEPTION: // "���������� ���������� ����������";
         Num = 17;	break;
		case EXCEPTION_STACK_OVERFLOW:        //  "������������ �����";
         Num = 18;	break;
		case EXCEPTION_INVALID_DISPOSITION:   //  "Exeption ERROR";
         Num = 19;	break;
		case EXCEPTION_GUARD_PAGE:            //  "��������� � ���������� ��������";
         Num = 20;	break;
		case EXCEPTION_INVALID_HANDLE:        //  "INVALID HANDLE";
         Num = 21;
			break;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:    //  "������� �� 0";
         Num = 22;   break;
		default:                              //  "������������ ���������� ���������";
         CrashMessage();
         Num = 51;	break;
}
   CrashMessage(NULL,Num);
}