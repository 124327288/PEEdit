#pragma once
#include"StringUtil.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "peload.h"
#include<vector>
using std::vector;

typedef struct _MYIMAGE_IMPORT_DESCRIPTOR {
    IMAGE_IMPORT_DESCRIPTOR my_image_descriptor;
    DWORD dllname;
            
} MYIMAGE_IMPORT_DESCRIPTOR,*MYPIMAGE_IMPORT_DESCRIPTOR;



typedef struct _MYFUNCINFO
{
    DWORD ThunkRVA;
    DWORD ThunkValue;
    DWORD Hint;
    LPCTSTR FunName;
}MYFUNCINFO,*PMYFUNCINFO;





// CImportDir �Ի���

class CImportDir : public CDialogEx,CPELoad
{
	DECLARE_DYNAMIC(CImportDir)

public:
	CImportDir(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CImportDir();

// �Ի�������
	enum { IDD = IDD_DIA4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

    void InitImportBar();
    void InitDllBar();
    void ShowImportFuncInfo(PIMAGE_IMPORT_DESCRIPTOR ,DWORD,DWORD);
    void ShowModuleInfo(vector<PIMAGE_SECTION_HEADER> myvec );
  //  MYPIMAGE_IMPORT_DESCRIPTOR my_image_des;
    CListCtrl m_modulelist;
    CListCtrl m_funlist;
    vector<MYIMAGE_IMPORT_DESCRIPTOR>mymodulename;
    vector<MYFUNCINFO>myfunlist;
    DWORD m_OA;
    DWORD m_dumpaddr;
    DWORD m_FuncOffsetShift;//ƫ������ֵ
    afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
   
};
