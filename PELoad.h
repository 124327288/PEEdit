#pragma once


typedef struct PEMISCINFO
{
     PIMAGE_NT_HEADERS32 nt_headeras;//pe�ļ�ntͷ
     LPVOID Dumpaddr;//ӳ�䵽�ڴ��ĵ�ַ(ע��������ӳ��  ����pe�ļ�ִ��ʱ�ĵ�ַ)
     HANDLE hFile;//�ļ����
     LPCTSTR lpPath;//�ļ�·��

}PeMisicInfo;


//��������ʼ��ʱ�򱻼��ؽ�ȥ��
static PeMisicInfo mypemisc;
class CPELoad
{
public:

    PeMisicInfo LoadPEFile(LPCTSTR szPePath);
    PeMisicInfo ReturnMiscInfo();//����pe�ļ����������Ϣ(ntͷ��ӳ���ַ)
    char* MulitByte2WideChar(WCHAR *whar);
  

public:
    CPELoad(void);
    ~CPELoad(void);
private:
    BOOL IsPeFile(LPVOID lpFileImage,DWORD dwFileSize,PIMAGE_NT_HEADERS& NT_Header);

};


