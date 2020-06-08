// SectionBlock.cpp : 实现文件
//

#include "stdafx.h"
#include "PEEdit.h"
#include "SectionBlock.h"
#include "afxdialogex.h"
#include "ATLCONV.H"
#include "StringUtil.h"
CStringUtil MyUtil1;

vector<PIMAGE_SECTION_HEADER> GetSectionInfo(PIMAGE_NT_HEADERS32 nt_headers);




// CSectionBlock 对话框

IMPLEMENT_DYNAMIC(CSectionBlock, CDialogEx)

CSectionBlock::CSectionBlock(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSectionBlock::IDD, pParent)
{

}

CSectionBlock::~CSectionBlock()
{
}

void CSectionBlock::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_sectionlist);
}


BEGIN_MESSAGE_MAP(CSectionBlock, CDialogEx)
END_MESSAGE_MAP()


//给ControlBar 中插入列


void CSectionBlock::InitContrlBar()
{
    ListView_SetExtendedListViewStyle(::GetDlgItem(this->m_hWnd,IDC_LIST1),LVS_EX_GRIDLINES);

    m_sectionlist.InsertColumn(0,L"Row",NULL,40);
    m_sectionlist.InsertColumn(1,L"SectionName",NULL,80);
    m_sectionlist.InsertColumn(2,L"VOffset",NULL,80);
    m_sectionlist.InsertColumn(3,L"VSize",NULL,80);
    m_sectionlist.InsertColumn(4,L"ROffset",NULL,80);
    m_sectionlist.InsertColumn(5,L"RSize",NULL,80);
}



//插入数据
 vector<PIMAGE_SECTION_HEADER> CSectionBlock::ShowSectionInfo()
{
   m_sectionlist.DeleteAllItems();
    PeMisicInfo miscinfo=ReturnMiscInfo();
    vector<PIMAGE_SECTION_HEADER>my_section_vec=GetSectionInfo(miscinfo.nt_headeras);
   for(int a=0;a<my_section_vec.size();a++)
    {
        CString myid;
        myid.Format(L"%d",a);
     m_sectionlist.InsertItem(LVIF_TEXT | LVIF_STATE,a, myid,(a % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED,0,0);
     //打印条目
     for(int i=1;i<6;i++)
     {
         CString mysectioninfo;
         LPCWCH outputchar[30]={0};
         switch (i)
         {
         case 1:
             //区段名称
             MyUtil1.ConvertUtf8ToUnicode((char*)my_section_vec[a]->Name,*outputchar);
             mysectioninfo.Format(L"%s",*outputchar);
             m_sectionlist.SetItemText(a,i,mysectioninfo);
             break;
         case 2:
             //区段的rva
             mysectioninfo.Format(L"0x%x",my_section_vec[a]->VirtualAddress);
             m_sectionlist.SetItemText(a,i,mysectioninfo); 
             break;
         case 3:
             //区段在内存大小
             mysectioninfo.Format(L"0x%x",my_section_vec[a]->Misc.VirtualSize);
             m_sectionlist.SetItemText(a,i,mysectioninfo);
             break;
         case 4:
             //文件偏移
             mysectioninfo.Format(L"0x%x",my_section_vec[a]->PointerToRawData);
             m_sectionlist.SetItemText(a,i,mysectioninfo);
             break;
         case 5:
             //文件大小
             mysectioninfo.Format(L"0x%x",my_section_vec[a]->SizeOfRawData);
             m_sectionlist.SetItemText(a,i,mysectioninfo);
             break;
         default:
             break;
         }

     }

 }
   return my_section_vec;
}

 vector<PIMAGE_SECTION_HEADER> CSectionBlock::GetSectionInfo1()
 {
     PeMisicInfo miscinfo=ReturnMiscInfo();
     vector<PIMAGE_SECTION_HEADER>my_section_vec=GetSectionInfo(miscinfo.nt_headeras);
     return my_section_vec;
 }


vector<PIMAGE_SECTION_HEADER> CSectionBlock::GetSectionInfo(PIMAGE_NT_HEADERS32 nt_headers)
{
    int a=nt_headers->FileHeader.NumberOfSections;
    //存放节表信息
    vector<PIMAGE_SECTION_HEADER>myvec_section_headers;
    /*PIMAGE_SECTION_HEADER mys=IMAGE_FIRST_SECTION(nt_headers)+3;*/
    for(int i=0;i<a;i++)
    {
        PIMAGE_SECTION_HEADER Some_Section_Info=IMAGE_FIRST_SECTION(nt_headers)+i;
        myvec_section_headers.push_back(Some_Section_Info);
    }
    
    return myvec_section_headers;
}


