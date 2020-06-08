#pragma once
#include "afxcmn.h"
#include "PELoad.h"

//�Լ������ntͷ
//�Լ�������Ҫ��Ϊ�˸�����Ӧ�Լ��ı��Ҫ�󣬲�Ȼ�Ļ���Щ��Ϣֱ����΢���Լ��Ľṹ��
//�����������Ϣ�������Լ���Ҫ����Ϣ�ֲ���Я�������������Լ�����ntͷ�ĳ���

typedef struct _MYIMAGE_NT_HEADERS
{

    DWORD EntryPoint;//������ڵ�
    DWORD IamgeBaseAddr;//�ļ����ڴ��е���ѡװ���ַ
    DWORD ImageSize;//�����С
    DWORD CodeBase;
    DWORD DataBase;
    DWORD SectionNums;
    DWORD  TimeStamp;
    DWORD  NT_HeadersSize;
    DWORD SelectHeaderSize;
    DWORD SubSystem;
}MYIMAGE_NT_HEADERS,*PMYIMAGE_NT_HEADERS;


// CPeHeader �Ի���

class CPeHeader : public CDialogEx,public CPELoad
{
	DECLARE_DYNAMIC(CPeHeader)

public:
	CPeHeader(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPeHeader();
    virtual 

// �Ի�������
	enum { IDD = IDD_DIA1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
