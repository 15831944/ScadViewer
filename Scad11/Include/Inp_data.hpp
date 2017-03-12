#ifndef INPUT_DATA_FLAG_H
#define INPUT_DATA_FLAG_H
#pragma pack(push,1)

struct INPUT_DATA
{
        long     OrderSystem;      // ������� ������� ���������
        long     MaxOrder;         // ������������� ����� ������� �������
        long     QuantityNode;
        long     QuantityElem;
        DOCUMENT_LONG Format;
        DOCUMENT_LONG Doc05;
        DOCUMENT_LONG DocDynamic;
        DOCUMENT_LONG DocR01;
        DOCUMENT_LONG DocR02;
        DOCUMENT_LONG DocR03;
        DOCUMENT_LONG DocR04;
        DOCUMENT_LONG DocR05;
};

struct PRINT_DATA {
//        BYTE           BegSymbol;
        BYTE           Regime;
//        BYTE StrHead;
        BYTE           YesCont;
        BYTE           QuantityHead;
        BYTE           LenStrHead;
        BYTE           QuantityBlank;
        RESURCE_INFORM Name;
        RESURCE_INFORM Head;
        RESURCE_INFORM Cont;
        }; 

struct PARAM_PRINT  { 
	BYTE  TypePage;     /*  0 - ��p⨪��쭠�,  1 - ��p����⠫쭠�  */
	BYTE  FontSize;
	BYTE  PageHeigth;   /* ��� ⥪�⮢�� ����                    */
	BYTE  PageWidth;    /* ��� ⥪�⮢�� ����                    */
	};

#define  MAX_STRING_HEAD	     100
#define  MAX_KSW                 15

#define  LEN_PAGE  60
#define  LEN_PRINT 72

#define  NumTypeSys     _Schema->TypeSystem.Num
#define  KSW            _Schema->TypeSystem.QuantityStep
#define  NSW(I)         _Schema->TypeSystem.NumStep[(I)]

#define	NPRT            _Schema->TypeSE

#define	KELRS           _Schema->QuantityElem
#define	KURS            _Schema->QuantityNode
#define	KUSE            _Schema->QuantityNodeSE

#define	KKN             _Schema->QuantityCraneForce
#define	KTN             _Schema->QuantityBrakeForce

#pragma pack(pop)
#endif
