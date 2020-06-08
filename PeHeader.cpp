// PeHeader.cpp : 实现文件
//

#include "stdafx.h"
#include "PEEdit.h"
#include "PeHeader.h"
#include "afxdialogex.h"
#include "Strsafe.h"


// CPeHeader 对话框

IMPLEMENT_DYNAMIC(CPeHeader, CDialogEx)

CPeHeader::CPeHeader(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPeHeader::IDD, pParent)
    , m_header_Enpoint(_T(""))
    , m_imagebase(_T(""))
    , m_image_size(_T(""))
    , m_CodeBase(_T(""))
    , m_DataBase(_T(""))
    , m_SectionNums(_T(""))
    , m_time(_T(""))
    , m_ntheadersize(_T(""))
    , m_selectsize(_T(""))
    , m_SubSystem(_T(""))
{
    m_Nt_HeaderInfo=new MYIMAGE_NT_HEADERS;
}

CPeHeader::~CPeHeader()
{
}

void CPeHeader::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);

    DDX_Text(pDX, IDC_EDIT1, m_header_Enpoint);
    DDX_Text(pDX, IDC_EDIT11, m_imagebase);
    DDX_Text(pDX, IDC_EDIT5, m_image_size);
    DDX_Text(pDX, IDC_EDIT7, m_CodeBase);
    DDX_Text(pDX, IDC_EDIT9, m_DataBase);
    DDX_Text(pDX, IDC_EDIT2, m_SectionNums);
    DDX_Text(pDX, IDC_EDIT4, m_time);
    DDX_Text(pDX, IDC_EDIT6, m_ntheadersize);
    DDX_Text(pDX, IDC_EDIT8, m_selectsize);
    DDX_Text(pDX, IDC_EDIT10, m_SubSystem);
}


BEGIN_MESSAGE_MAP(CPeHeader, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON2, &CPeHeader::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPeHeader 消息处理程序


void CPeHeader::GetMiscInfo()
{
  PeMisicInfo miscinfo=ReturnMiscInfo();
  m_miscinfo=miscinfo;

 }


 PMYIMAGE_NT_HEADERS CPeHeader::ContainInfo( )
 {
 
    m_Nt_HeaderInfo->EntryPoint=m_miscinfo.nt_headeras->OptionalHeader.AddressOfEntryPoint;
    m_Nt_HeaderInfo->IamgeBaseAddr=m_miscinfo.nt_headeras->OptionalHeader.ImageBase;
    m_Nt_HeaderInfo->ImageSize=m_miscinfo.nt_headeras->OptionalHeader.SizeOfImage;
    m_Nt_HeaderInfo->CodeBase=m_miscinfo.nt_headeras->OptionalHeader.BaseOfCode;
    m_Nt_HeaderInfo->DataBase=m_miscinfo.nt_headeras->OptionalHeader.BaseOfData;
    m_Nt_HeaderInfo->SectionNums=m_miscinfo.nt_headeras->FileHeader.NumberOfSections;
    m_Nt_HeaderInfo->TimeStamp=m_miscinfo.nt_headeras->FileHeader.TimeDateStamp;
    m_Nt_HeaderInfo->NT_HeadersSize=m_miscinfo.nt_headeras->OptionalHeader.SizeOfHeaders;
    m_Nt_HeaderInfo->SubSystem=m_miscinfo.nt_headeras->OptionalHeader.Subsystem;

    m_header_Enpoint.Format(L"0x%08X", m_Nt_HeaderInfo->EntryPoint);
    m_imagebase.Format(L"0x%08X", m_Nt_HeaderInfo->IamgeBaseAddr);
    m_image_size.Format(L"0x%08X",m_Nt_HeaderInfo->ImageSize);
    m_CodeBase.Format(L"0x%08X",m_Nt_HeaderInfo->CodeBase);
    m_DataBase.Format(L"0x%08X",m_Nt_HeaderInfo->DataBase);
    m_SectionNums.Format(L"0x%08X",m_Nt_HeaderInfo->SectionNums);
    m_time.Format(L"0x%08X",m_Nt_HeaderInfo->TimeStamp);
    m_ntheadersize.Format(L"0x%08X",m_Nt_HeaderInfo->NT_HeadersSize);
    m_SubSystem.Format(L"0x%08X",m_Nt_HeaderInfo->SubSystem);
    UpdateData(FALSE);
    return m_Nt_HeaderInfo;
 }
 

 //保存已经修改的pe头信息

 void CPeHeader::OnBnClickedButton2()
 {
     UpdateData(TRUE);
     //将控件传回来的值给内存中的pe文件映射的对应的变量
     m_miscinfo.nt_headeras->OptionalHeader.AddressOfEntryPoint=_tcstoul( m_header_Enpoint, NULL, 16 );;
     m_miscinfo.nt_headeras->OptionalHeader.ImageBase=_tcstoul( m_imagebase, NULL, 16 );
     m_miscinfo.nt_headeras->OptionalHeader.SizeOfImage=_tcstoul( m_image_size, NULL, 16 );
     m_miscinfo.nt_headeras->OptionalHeader.BaseOfCode=_tcstoul( m_CodeBase, NULL, 16 );
     m_miscinfo.nt_headeras->OptionalHeader.BaseOfData=_tcstoul( m_DataBase, NULL, 16 );
     m_miscinfo.nt_headeras->FileHeader.NumberOfSections=_tcstoul( m_SectionNums, NULL, 16 );
     m_miscinfo.nt_headeras->FileHeader.TimeDateStamp=_tcstoul( m_time, NULL, 16 );
     m_miscinfo.nt_headeras->OptionalHeader.SizeOfHeaders=_tcstoul( m_ntheadersize, NULL, 16 );
     m_miscinfo.nt_headeras->OptionalHeader.Subsystem=_tcstoul( m_SubSystem, NULL, 16 );
     DWORD dwRet=0;
     DWORD lenght=  GetFileSize(m_miscinfo.hFile,NULL);
     SetFilePointer(m_miscinfo.hFile,0,0,FILE_BEGIN);
     BOOL  aa=WriteFile(m_miscinfo.hFile,m_miscinfo.Dumpaddr,lenght,&dwRet,NULL);
     //刷新缓存！！
     BOOL Flush=FlushFileBuffers(m_miscinfo.hFile);
     int ss=GetLastError();
     MessageBox(L"保存成功!");
     UpdateData(FALSE);
 }
