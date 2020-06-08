
// PEEditDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "DataDirectory.h"
#include "ImportDir.h"
#include "ExportDir.h"
#include "PeHeader.h"
#include "SectionBlock.h"


// CPEEditDlg 对话框
class CPEEditDlg : public CDialogEx,public CPELoad
{
// 构造
public:
	CPEEditDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PEEDIT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CTabCtrl m_tabCrl;
    int  m_TabIndex;
    CDataDirectory mydata;
    CExportDir myexport;
    CImportDir myimport;
    CPeHeader myheader;
    CSectionBlock mySecetion;

    afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
    BOOL SelectFloder(HWND hWnd ,LPWSTR lpszFloder );
    LPCTSTR GetPePath();
    afx_msg void OnBnClickedButton1();
private:
    CString m_szPath;
public:
    afx_msg void OnBnClickedButton2();
     vector<PIMAGE_SECTION_HEADER> Vec_SectionInfo;
     afx_msg void OnBnClickedButton4();
};
