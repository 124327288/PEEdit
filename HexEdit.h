#pragma once
#include "PELoad.h"
#include "16EditDll.h"
#pragma comment(lib,"16Edit.lib")

// CHexEdit �Ի���

class CHexEdit : public CDialogEx,public CPELoad
{
	DECLARE_DYNAMIC(CHexEdit)

public:
	CHexEdit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHexEdit();
    void ShowHexEdit();
	void GetPeInfo();
// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangeEdit2();
	afx_msg void OnClose();
	afx_msg void OnIddDialog2();
	virtual void OnCancel();
};
