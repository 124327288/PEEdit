// DataDirectory.cpp : 实现文件
//

#include "stdafx.h"
#include "PEEdit.h"
#include "DataDirectory.h"
#include "afxdialogex.h"


// CDataDirectory 对话框

IMPLEMENT_DYNAMIC(CDataDirectory, CDialogEx)

CDataDirectory::CDataDirectory(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataDirectory::IDD, pParent)
    , m_ExportRva(_T(""))
    , m_ImportDirectoryRva(_T(""))
    , m_ResourceRva(_T(""))
    , m_ExpectionRva(_T(""))
    , m_Safe(_T(""))
    , m_RelocationRva(_T(""))
    , m_DebugRva(_T(""))
    , m_VersionRva(_T(""))
    , m_TlsRva(_T(""))
    , m_GPRva(_T(""))
    , m_ConfirRva(_T(""))
    , m_BoundRva(_T(""))
    , m_FuncRva(_T(""))
    , m_DleadRva(_T(""))
    , m_COMRva(_T(""))
{

}

CDataDirectory::~CDataDirectory()
{
}

void CDataDirectory::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, m_ExportRva);
    DDX_Text(pDX, IDC_EDIT2, m_ImportDirectoryRva);
    DDX_Text(pDX, IDC_EDIT3, m_ResourceRva);
    DDX_Text(pDX, IDC_EDIT4, m_ExpectionRva);
    DDX_Text(pDX, IDC_EDIT5, m_Safe);
    DDX_Text(pDX, IDC_EDIT6, m_RelocationRva);
    DDX_Text(pDX, IDC_EDIT7, m_DebugRva);
    DDX_Text(pDX, IDC_EDIT8, m_VersionRva);
    DDX_Text(pDX, IDC_EDIT10, m_TlsRva);
    DDX_Text(pDX, IDC_EDIT9, m_GPRva);
    DDX_Text(pDX, IDC_EDIT11, m_ConfirRva);
    DDX_Text(pDX, IDC_EDIT12, m_BoundRva);
    DDX_Text(pDX, IDC_EDIT13, m_FuncRva);
    DDX_Text(pDX, IDC_EDIT14, m_DleadRva);
    DDX_Text(pDX, IDC_EDIT15, m_COMRva);
}


BEGIN_MESSAGE_MAP(CDataDirectory, CDialogEx)
    ON_EN_CHANGE(IDC_EDIT2, &CDataDirectory::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CDataDirectory 消息处理程序


void CDataDirectory::OnEnChangeEdit2()
{
    // TODO:  如果该控件是 RICHEDIT 控件，它将不
    // 发送此通知，除非重写 CDialogEx::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

    // TODO:  在此添加控件通知处理程序代码
}

BOOL CDataDirectory::ShowDataDirectoryInfo()
{
    PeMisicInfo mypemisc=ReturnMiscInfo();
    PIMAGE_DATA_DIRECTORY   mydatadir         =mypemisc.nt_headeras->OptionalHeader.DataDirectory;
    PIMAGE_DATA_DIRECTORY   pExportDir        = &mydatadir[IMAGE_DIRECTORY_ENTRY_EXPORT];
    PIMAGE_DATA_DIRECTORY   pExportDir1       = &mydatadir[IMAGE_DIRECTORY_ENTRY_IMPORT];
    PIMAGE_DATA_DIRECTORY   pExportDir2       = &mydatadir[IMAGE_DIRECTORY_ENTRY_RESOURCE];
    PIMAGE_DATA_DIRECTORY   pExportDir3       = &mydatadir[IMAGE_DIRECTORY_ENTRY_EXCEPTION];
    PIMAGE_DATA_DIRECTORY   pExportDir4       = &mydatadir[4];
    PIMAGE_DATA_DIRECTORY   pExportDir5       = &mydatadir[5];
    PIMAGE_DATA_DIRECTORY   pExportDir6       = &mydatadir[6];
    PIMAGE_DATA_DIRECTORY   pExportDir7       = &mydatadir[7];
    PIMAGE_DATA_DIRECTORY   pExportDir8       = &mydatadir[8];
    PIMAGE_DATA_DIRECTORY   pExportDir9       = &mydatadir[9];
    PIMAGE_DATA_DIRECTORY   pExportDir10      = &mydatadir[10];
    PIMAGE_DATA_DIRECTORY   pExportDir11      = &mydatadir[11];
    PIMAGE_DATA_DIRECTORY   pExportDir12      = &mydatadir[12];
    PIMAGE_DATA_DIRECTORY   pExportDir13      = &mydatadir[13];
    PIMAGE_DATA_DIRECTORY   pExportDir14      = &mydatadir[14];
    m_ExportRva.Format(_T("0X%08X"),pExportDir->VirtualAddress);
    m_ImportDirectoryRva.Format(_T("0x%08X"),pExportDir1->VirtualAddress);
    m_ResourceRva.Format(_T("0X%08X"),pExportDir2->VirtualAddress);
    m_ExpectionRva.Format(_T("0X%08X"),pExportDir3->VirtualAddress);
    m_Safe.Format(_T("0X%08X"),pExportDir4->VirtualAddress);
    m_RelocationRva.Format(_T("0X%08X"),pExportDir5->VirtualAddress);
    m_DebugRva.Format(_T("0X%08X"),pExportDir6->VirtualAddress);
    m_VersionRva.Format(_T("0X%08X"),pExportDir7->VirtualAddress);
    m_GPRva.Format(_T("0X%08X"),pExportDir8->VirtualAddress);
    m_TlsRva.Format(_T("0X%08X"),pExportDir9->VirtualAddress);
    m_ConfirRva.Format(_T("0X%08X"),pExportDir10->VirtualAddress);
    m_BoundRva.Format(_T("0X%08X"),pExportDir11->VirtualAddress);
    m_FuncRva.Format(_T("0X%8X"),pExportDir12->VirtualAddress);
    m_DleadRva.Format(_T("0X%08X"),pExportDir13->VirtualAddress);
    m_COMRva.Format(_T("0X%08X"),pExportDir14->VirtualAddress);
    UpdateData(FALSE);
    return TRUE;

}

