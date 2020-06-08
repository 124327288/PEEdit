#include "stdafx.h"
#include "PELoad.h"
#include<string>
using namespace  std;


CPELoad::CPELoad(void)
{
}


CPELoad::~CPELoad(void)
{



}


//载入pe文件
PeMisicInfo CPELoad::LoadPEFile(LPCTSTR lpszPath)
{
    DWORD PeFileSize=0;
    LPVOID DumpAddr=nullptr;
    BOOL CanBeRead;
    PIMAGE_NT_HEADERS32 Nt_headers;
    //创建文件映射
    HANDLE hFile=CreateFile(lpszPath,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_WRITE|FILE_SHARE_READ,NULL,OPEN_EXISTING,SECURITY_IMPERSONATION,NULL);
    if(!hFile) goto EndProcess;
    PeFileSize=GetFileSize(hFile,NULL);
    if(PeFileSize==0)goto EndProcess;

    DumpAddr=VirtualAlloc(NULL,PeFileSize,MEM_COMMIT | MEM_RESERVE,PAGE_READWRITE);
    if(!DumpAddr)goto EndProcess;
    DWORD dwRet;

    CanBeRead=ReadFile(hFile,DumpAddr,PeFileSize,&dwRet,NULL);
    int a=GetLastError();
    if(!CanBeRead)goto EndProcess;//判断是不是pe文件
    // 判断是不是pe文件
    BOOL isPeFile=IsPeFile(DumpAddr,PeFileSize,Nt_headers);
    if(!isPeFile) goto EndProcess;
    mypemisc.Dumpaddr=DumpAddr;
    mypemisc.nt_headeras=Nt_headers;
    mypemisc.hFile=hFile;
    mypemisc.lpPath=lpszPath;
    return mypemisc;

EndProcess:
    if(hFile)CloseHandle(hFile);
    ExitProcess(0);


}

//判断是不是pe文件
BOOL CPELoad::IsPeFile(LPVOID lpFileImage,DWORD dwFileSize,PIMAGE_NT_HEADERS& NT_Header)
{

    PIMAGE_DOS_HEADER pImageDosHead=(PIMAGE_DOS_HEADER)lpFileImage;
    if(pImageDosHead->e_magic!=IMAGE_DOS_SIGNATURE)  goto endProcess;
    NT_Header= (PIMAGE_NT_HEADERS)((ULONG)pImageDosHead->e_lfanew+(ULONG)lpFileImage);
    if(NT_Header->Signature!=IMAGE_NT_SIGNATURE)
        goto endProcess;
    return TRUE;
endProcess:
    //printf("the last error is %d",GetLastError());
    return  FALSE;

}

PeMisicInfo CPELoad::ReturnMiscInfo()
{    
    return mypemisc;

}

