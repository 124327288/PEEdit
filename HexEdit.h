#pragma once
#include "PELoad.h"
#include "16EditDll.h"
#pragma comment(lib,"16Edit.lib")

// CHexEdit 对话框

class CHexEdit : public CDialogEx,public CPELoad
{
	DECLARE_DYNAMIC(CHexEdit)

public:
	CHexEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHexEdit();
    void ShowHexEdit();
	void GetPeInfo();
// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangeEdit2();
	afx_msg void OnClose();
	afx_msg void OnIddDialog2();
	virtual void OnCancel();
};
