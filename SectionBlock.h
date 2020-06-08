#pragma once
#include "afxcmn.h"
#include"peload.h"
#include <vector>
using  namespace std;
typedef struct _MYSECTIONINFO
{
    DWORD VOffset;
    DWORD VSize;
    DWORD ROffset;
    DWORD Rsize;

}MYSECTIONINFO,*PMYSECTIONINFO;






// CSectionBlock 对话框

class CSectionBlock : public CDialogEx, public CPELoad
{
	DECLARE_DYNAMIC(CSectionBlock)

public:
	CSectionBlock(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSectionBlock();

// 对话框数据
	enum { IDD = IDD_DIA3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_sectionlist;
    vector<MYSECTIONINFO>myvec_sectioninfo;
    void InitContrlBar();
    vector<PIMAGE_SECTION_HEADER> GetSectionInfo1();
    vector<PIMAGE_SECTION_HEADER> ShowSectionInfo();
    vector<PIMAGE_SECTION_HEADER> GetSectionInfo(PIMAGE_NT_HEADERS32 nt_headers);

};
