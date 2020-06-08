#pragma once
#include "afxcmn.h"
#include "PELoad.h"
#include <vector>
#include "afxwin.h"
using std::vector;

// CSrc 对话框

//资源结构体的定义


typedef struct SRCSTRUCT
{
	CString str;
	DWORD ID;
	DWORD subID;
	DWORD secid;

}SRCSTRUCT,*PSRCSTRUCT;
class CSrc : public CDialogEx,public CPELoad
{
	DECLARE_DYNAMIC(CSrc)

public:
	CSrc(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSrc();
// 对话框数据
	enum { IDD = IDD_SRC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    vector<SRCSTRUCT>Level1;
    vector<SRCSTRUCT>Level2;
    vector<SRCSTRUCT>Level3;
    void ShowInfo();
    void RealShowInfo();
    CTreeCtrl m_srcTreecrl;
    afx_msg void OnBnClickedButton5();
    CString m_rootstring;
    CEdit m_rootidnum;
    CString m_secondstring;
    CEdit m_secondIDNums;
    CString m_secidnums;
    CString m_rootIdnums;
    vector<HTREEITEM>m_hLevel1item;
    vector<HTREEITEM> m_hLevel2item;


    afx_msg void OnSelchangingTree1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnItemchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
    CString m_Rva;
    CString m_offset;
    CString m_size;
};
