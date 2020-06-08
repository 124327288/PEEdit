#pragma once
#include "PELoad.h"
#include "afxcmn.h"
#include<vector>
using std::vector;


// CExportDir 对话框
typedef struct _EXPORTINFO
{
    DWORD Ordinal;
    DWORD FuncRva;
    DWORD FuncOffset;
    LPCWCH  funcname;
}EXPORTINFO,*PEXPORTINFO;

class CExportDir : public CDialogEx,public CPELoad
{
	DECLARE_DYNAMIC(CExportDir)

public:
	CExportDir(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExportDir();

// 对话框数据
	enum { IDD = IDD_DIA5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
    void InitImportBar();

    DWORD Rva2FileA(DWORD dwRVA, PIMAGE_NT_HEADERS32 pNT32 );
    vector<EXPORTINFO> m_vec_myexportinfo;
    

    void GetExportInfo();
    void Showinfo();
    CListCtrl m_exportlistcrl;
    CString m_ExpDirFa;
    CString m_char;
    CString m_baseaddr;
    CString m_exename;
    CString m_funnums;
    CString m_funnamenums;
    CString m_funaddr;
    CString m_funnameaddr;
    CString m_funordaddr;
    CString m_namerva;
};
