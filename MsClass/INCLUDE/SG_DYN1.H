#ifndef SG_DYN1_FLAG_H
#define SG_DYN1_FLAG_H
#pragma pack(push, 1)

struct sg_dyn1
{
	BYTE  mod;     //  �����
	WORD  ndn;     //  ����� ����㦥���
	WORD  nsg;     //  ��ᮥ�������� ����㦥���
	WORD  kfp;     //  �᫮ ���᫥���� ᮡ�⢥���� ����஢
	WORD  kfs;     //  �᫮ c�ନ஢����� �ࠢ�� ��⥩
	long  kmas;    //  �᫮ ����
        double MaxAbsMas;
	DWORD sd15;
	WORD  kk;      //  �᫮ ������ � ���. 15
	DWORD adr_mas;
	DWORD adr_sng;
	DWORD adr_cht;
	DWORD adr_form;
	DWORD adr_syl;

        WORD       NumIter;     //   ����� ���樨
        DWORD      AdrForm1;    //   ����� ��ࢮ��  �ਡ������� ��
        DWORD      AdrForm2;    //   ����� ��ண�  �ਡ������� ��
        DWORD      AdrFormR;    //   ࠡ�稩 �����  ��� ०��� ���뢠���
	WORD  kv0;              //   ࠡ�稩 ��ࠬ���
        int piter;
        int rkf;
        int kft;
        double osh;

};

struct DYN_FORCE  {  float d_7[10];  };

struct s_dok15
{
	short ls_d15;
	short mod_d15;
	short kf_d15;
	short nsq_d15;
	short spr_d15;
	short prt_d15;
	float zn_d15[100];
};

#pragma pack(pop)
#endif
