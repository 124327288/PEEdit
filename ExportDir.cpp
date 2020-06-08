// ExportDir.cpp : 实现文件
//

#include "stdafx.h"
#include "PEEdit.h"
#include "ExportDir.h"
#include "afxdialogex.h"
#include "StringUtil.h"
CStringUtil mysttring;


// CExportDir 对话框

IMPLEMENT_DYNAMIC(CExportDir, CDialogEx)

CExportDir::CExportDir(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExportDir::IDD, pParent)
    , m_ExpDirFa(_T(""))
    , m_char(_T(""))
    , m_baseaddr(_T(""))
    , m_exename(_T(""))
    , m_funnums(_T(""))
    , m_funnamenums(_T(""))
    , m_funaddr(_T(""))
    , m_funnameaddr(_T(""))
    , m_funordaddr(_T(""))
    , m_namerva(_T(""))
{

}

CExportDir::~CExportDir()
{
//     free(myexportinfo);

}

void CExportDir::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST3, m_exportlistcrl);
    DDX_Text(pDX, IDC_EDIT1, m_ExpDirFa);
    DDX_Text(pDX, IDC_EDIT2, m_char);
    DDX_Text(pDX, IDC_EDIT3, m_baseaddr);
    DDX_Text(pDX, IDC_EDIT9, m_exename);
    DDX_Text(pDX, IDC_EDIT6, m_funnums);
    DDX_Text(pDX, IDC_EDIT11, m_funnamenums);
    DDX_Text(pDX, IDC_EDIT5, m_funaddr);
    DDX_Text(pDX, IDC_EDIT10, m_funnameaddr);
    DDX_Text(pDX, IDC_EDIT7, m_funordaddr);
    DDX_Text(pDX, IDC_EDIT4, m_namerva);
}


BEGIN_MESSAGE_MAP(CExportDir, CDialogEx)
END_MESSAGE_MAP()


// CExportDir 消息处理程序
void CExportDir::InitImportBar()
{
    ListView_SetExtendedListViewStyle(::GetDlgItem(this->m_hWnd,IDC_LIST1),LVS_EX_GRIDLINES);

    m_exportlistcrl.InsertColumn(0,L"Row",NULL,40);
    m_exportlistcrl.InsertColumn(1,L"Ordinal",NULL,40);
    m_exportlistcrl.InsertColumn(2,L"FuncRva",NULL,80);
    m_exportlistcrl.InsertColumn(3,L"FunctionName",NULL,80);



}

void CExportDir::GetExportInfo()
{
    LPCWCH outputchar={0};
    LPCWCH outputchar1={0};
    m_exportlistcrl.DeleteAllItems();
    m_vec_myexportinfo.clear();
    PeMisicInfo miscinfo=ReturnMiscInfo();//获取pe基本信息
    PIMAGE_NT_HEADERS32   pNT32    = miscinfo.nt_headeras;
    PIMAGE_DATA_DIRECTORY pDataDir = (PIMAGE_DATA_DIRECTORY)pNT32->OptionalHeader.DataDirectory;
    PIMAGE_DATA_DIRECTORY   pExportDir      = &pDataDir[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if(pExportDir->Size!=0)
    {
    DWORD                   dwExportOfffset = Rva2FileA(pExportDir->VirtualAddress, pNT32);//输出表地文件偏移
    PIMAGE_EXPORT_DIRECTORY pExport         = (PIMAGE_EXPORT_DIRECTORY)((DWORD)miscinfo.Dumpaddr+dwExportOfffset);
    PDWORD pEAT = (PDWORD)((DWORD)miscinfo.Dumpaddr + Rva2FileA(pExport->AddressOfFunctions, pNT32));
    PDWORD pENT = (PDWORD)((DWORD)miscinfo.Dumpaddr + Rva2FileA(pExport->AddressOfNames, pNT32));
    PWORD  pEIT = (PWORD)((DWORD)miscinfo.Dumpaddr  + Rva2FileA(pExport->AddressOfNameOrdinals, pNT32));
    PCHAR exenameaddr=(PCHAR)((DWORD)miscinfo.Dumpaddr + Rva2FileA(pExport->Name, pNT32));  
    mysttring.ConvertUtf8ToUnicode((char*)exenameaddr,outputchar1);
    /////////////////////////////////////////////
    //格式化输出
    m_ExpDirFa.Format(L"0x%X",dwExportOfffset);
    m_funaddr.Format(L"0x%X",pExport->AddressOfFunctions);
    m_funnameaddr.Format(L"0x%X",pExport->AddressOfNames);
    m_funnamenums.Format(L"%d",pExport->NumberOfNames);
    m_char.Format(L"%d",pExport->Characteristics);
    m_exename.Format(L"%s",outputchar1);
    m_funordaddr.Format(L"0x%X",pExport->AddressOfNameOrdinals);
    m_funnums.Format(L"0x%X",pExport->NumberOfFunctions);
    m_baseaddr.Format(L"0x%X",pExport->Base);
    m_namerva.Format(L"0x%X",pExport->Name);
    for ( DWORD dwOrdinal=0; dwOrdinal<pExport->NumberOfFunctions; dwOrdinal++ )
    {
        if ( !pEAT[dwOrdinal] )
            continue;
        for ( DWORD dwIndex=0; dwIndex<pExport->NumberOfFunctions; dwIndex++ )
        {
         EXPORTINFO myexportinfo={0};

            if ( pEIT[dwIndex] == dwOrdinal )
            {
                PCHAR pszFunName = (PCHAR)((DWORD)miscinfo.Dumpaddr+Rva2FileA(pENT[dwIndex], pNT32));
                myexportinfo.Ordinal=pExport->Base+dwOrdinal;
                myexportinfo.FuncRva=pEAT[dwOrdinal];
                mysttring.ConvertUtf8ToUnicode(pszFunName,outputchar);
                myexportinfo.funcname=outputchar;
                m_vec_myexportinfo.push_back(myexportinfo);
                break;
            }
            else if ( dwIndex == pExport->NumberOfFunctions-1 )
            {
                myexportinfo.Ordinal=pExport->Base+dwOrdinal;
                myexportinfo.FuncRva=pEAT[dwOrdinal];
                myexportinfo.funcname=(LPCWCH) L"(Null)" ;
                m_vec_myexportinfo.push_back(myexportinfo);
                break;
            }
          /// free(myexportinfo); 
           
        }

    }
    ///////////////////////////////////./////
    //显示信息
    ////////////////////////////////////////
    UpdateData(FALSE);
    Showinfo();
    }
    else
    {
        MessageBox(L"没有导出表!",L"错误",MB_OK|MB_ICONSTOP);
    }
}


DWORD CExportDir::Rva2FileA(DWORD dwRVA, PIMAGE_NT_HEADERS32 pNT32 )
{

    PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNT32);
    for ( DWORD i=0; i<pNT32->FileHeader.NumberOfSections; i++ )
    {
        if ( dwRVA < pSection[i].VirtualAddress )
        {
            DWORD dwR_Offset = dwRVA - pSection[i-1].VirtualAddress;
            DWORD dwOffset   = dwR_Offset + pSection[i-1].PointerToRawData;
            return dwOffset;
        }
    }
}



void CExportDir::Showinfo()
{
    for(int a=0;a<m_vec_myexportinfo.size();a++)
    {
      //  LPCWCH* outputfun=new LPCWCH[4];
        CString myid;
        myid.Format(L"%d",a+1);
        m_exportlistcrl.InsertItem(LVIF_TEXT | LVIF_STATE,a, myid,(a % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED,0,0);
        for(int i=1;i<4;i++)
        {
            CString mymoduleinfo;
            switch (i)
            {
      
            case 1:
                mymoduleinfo.Format(L"0x%X",m_vec_myexportinfo[a].Ordinal);
                m_exportlistcrl.SetItemText(a,i,mymoduleinfo);
                break;
            case 2:
                mymoduleinfo.Format(L"0x%X",m_vec_myexportinfo[a].FuncRva);
                m_exportlistcrl.SetItemText(a,i,mymoduleinfo);

                break;
            case 3:
                mymoduleinfo.Format(L"%s",m_vec_myexportinfo[a].funcname);
                m_exportlistcrl.SetItemText(a,i,mymoduleinfo);

                break;
     
            default:
                break;
        }

    }
    }

}