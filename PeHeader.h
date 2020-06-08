#pragma once
#include "afxcmn.h"
#include "PELoad.h"

//自己定义的nt头
//自己定义主要是为了更加适应自己的编程要求，不然的化有些信息直接用微软自己的结构体
//会产生冗余信息，而且自己需要的信息又不能携带，所以这是自己定义nt头的初衷

typedef struct _MYIMAGE_NT_HEADERS
{

    DWORD EntryPoint;//程序入口点
    DWORD IamgeBaseAddr;//文件在内存中的首选装入地址
    DWORD ImageSize;//镜像大小
    DWORD CodeBase;
    DWORD DataBase;
    DWORD SectionNums;
    DWORD  TimeStamp;
    DWORD  NT_HeadersSize;
    DWORD SelectHeaderSize;
    DWORD SubSystem;
}MYIMAGE_NT_HEADERS,*PMYIMAGE_NT_HEADERS;


// CPeHeader 对话框

class CPeHeader : public CDialogEx,public CPELoad
{
	DECLARE_DYNAMIC(CPeHeader)

public:
	CPeHeader(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPeHeader();
    virtual 

// 对话框数据
	enum { IDD = IDD_DIA1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
   void GetMiscInfo();
   PMYIMAGE_NT_HEADERS ContainInfo();
   PMYIMAGE_NT_HEADERS m_Nt_HeaderInfo;
        
private:
    
    PeMisicInfo m_miscinfo;

public:
    CString m_header_Enpoint;
    CString m_imagebase;
    CString m_image_size;
    CString m_CodeBase;
    CString m_DataBase;
    CString m_SectionNums;
    CString m_time;
    CString m_ntheadersize;
    CString m_selectsize;
    CString m_SubSystem;
    afx_msg void OnBnClickedButton2();
};
