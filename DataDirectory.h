#pragma once
#include "PELoad.h"


// CDataDirectory �Ի���

class CDataDirectory : public CDialogEx,public CPELoad
{
	DECLARE_DYNAMIC(CDataDirectory)

public:
	CDataDirectory(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDataDirectory();

// �Ի�������
	enum { IDD = IDD_DIA2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CString m_ExportRva;
    afx_msg void OnEnChangeEdit2();
    CString m_ImportDirectoryRva;
    CString m_ResourceRva;
    CString m_ExpectionRva;
    CString m_Safe;
    CString m_RelocationRva;
    CString m_DebugRva;
    CString m_VersionRva;
    CString m_TlsRva;
    CString m_GPRva;
    CString m_ConfirRva;
    CString m_BoundRva;
    CString m_FuncRva;
    CString m_DleadRva;
    CString m_COMRva;
public:
    BOOL  ShowDataDirectoryInfo();

};
