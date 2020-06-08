#pragma once


typedef struct PEMISCINFO
{
     PIMAGE_NT_HEADERS32 nt_headeras;//pe文件nt头
     LPVOID Dumpaddr;//映射到内存后的地址(注意这里是映射  不是pe文件执行时的地址)
     HANDLE hFile;//文件句柄
     LPCTSTR lpPath;//文件路径

}PeMisicInfo;


//这个类是最开始的时候被加载进去的
static PeMisicInfo mypemisc;
class CPELoad
{
public:

    PeMisicInfo LoadPEFile(LPCTSTR szPePath);
    PeMisicInfo ReturnMiscInfo();//返回pe文件基本混合信息(nt头与映射基址)
    char* MulitByte2WideChar(WCHAR *whar);
  

public:
    CPELoad(void);
    ~CPELoad(void);
private:
    BOOL IsPeFile(LPVOID lpFileImage,DWORD dwFileSize,PIMAGE_NT_HEADERS& NT_Header);

};


