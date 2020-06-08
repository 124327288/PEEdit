
// PEEditDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "DataDirectory.h"
#include "ImportDir.h"
#include "ExportDir.h"
#include "PeHeader.h"
#include "SectionBlock.h"


// CPEEditDlg �Ի���
class CPEEditDlg : public CDialogEx,public CPELoad
{
// ����
public:
	CPEEditDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PEEDIT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
