// ImportDir.cpp : 实现文件
//

#include "stdafx.h"
#include "PEEdit.h"
#include "ImportDir.h"
#include "afxdialogex.h"
#include "StringUtil.h"
#include <string>
using namespace std;
CStringUtil MyUtil;




// CImportDir 对话框

IMPLEMENT_DYNAMIC(CImportDir, CDialogEx)

CImportDir::CImportDir(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImportDir::IDD, pParent)
{

}

CImportDir::~CImportDir()
{


}

void CImportDir::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_LIST2, m_modulelist);
    DDX_Control(pDX, IDC_LIST1, m_funlist);
}


BEGIN_MESSAGE_MAP(CImportDir, CDialogEx)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CImportDir::OnLvnItemchangedList2)
END_MESSAGE_MAP()
        
// CImportDir 消息处理程序
void CImportDir::InitImportBar()
{
    ListView_SetExtendedListViewStyle(::GetDlgItem(this->m_hWnd,IDC_LIST2),LVS_EX_GRIDLINES);
    m_modulelist.InsertColumn(0,L"Row",NULL,40);
    m_modulelist.InsertColumn(1,L"DLLName",NULL,80);
    m_modulelist.InsertColumn(2,L"OriginalFirstThunk",NULL,80);
    m_modulelist.InsertColumn(3,L"ForwardChain",NULL,80);
    m_modulelist.InsertColumn(4,L"名称",NULL,80);
    m_modulelist.InsertColumn(5,L"FirstThunk",NULL,80);

}

void CImportDir::InitDllBar()
{
     LVCOLUMN lvc = {0};
     lvc.mask = LVCF_WIDTH|LVCF_TEXT;
     lvc.cx = 80;
     lvc.iImage = 1;
     lvc.fmt = LVCFMT_LEFT;

    ListView_SetExtendedListViewStyle(::GetDlgItem(this->m_hWnd,IDC_LIST1),LVS_EX_GRIDLINES);
    m_funlist.InsertColumn(0,L"Row",NULL,40);
    m_funlist.InsertColumn(1,L"ApiName",NULL,180);
    m_funlist.InsertColumn(2,L"ThunkRVA",NULL,70);
    m_funlist.InsertColumn(3,L"ThunkOffset",NULL,70);
    m_funlist.InsertColumn(4,L"ThunkValue",NULL,70);
    m_funlist.InsertColumn(5,L"Hint",NULL,70);

}
void CImportDir::ShowModuleInfo(vector<PIMAGE_SECTION_HEADER> Section)
{
    //删除掉模块栏的所有条目
    m_modulelist.DeleteAllItems();
    //删除所有vector中模块
    mymodulename.clear();
    PeMisicInfo miscinfo=ReturnMiscInfo();
    PIMAGE_NT_HEADERS32 LocalHeaders=miscinfo.nt_headeras;
    DWORD dumpaddr=(DWORD)miscinfo.Dumpaddr;
    m_dumpaddr=dumpaddr;
    WORD optional_header_size=LocalHeaders->FileHeader.SizeOfOptionalHeader;
    PIMAGE_OPTIONAL_HEADER32  Optional_header=&LocalHeaders->OptionalHeader;
    PIMAGE_DATA_DIRECTORY pDataDir = (PIMAGE_DATA_DIRECTORY)Optional_header->DataDirectory;
    //导入表的地址
    DWORD my_export_rva=pDataDir[1].VirtualAddress;
    DWORD Import_Table_Section_ShiftAddr;
    DWORD OA;
   //数据段的RVA
    for(int a=0;a<Section.size();a++)
    {
        if(Section[a]->VirtualAddress>my_export_rva)
        {
            m_OA=OA=Section[a-1]->VirtualAddress-Section[a-1]->PointerToRawData;
            Import_Table_Section_ShiftAddr=my_export_rva-OA;
            break;
        }

    }
    if(Import_Table_Section_ShiftAddr==0xcccccccc)
    {
        MessageBox(L"未初始化",L"错误",MB_OK);
        return;
    }
    //获取输入表信息
    IMAGE_IMPORT_DESCRIPTOR *my_Import_Data=(PIMAGE_IMPORT_DESCRIPTOR)(Import_Table_Section_ShiftAddr+(DWORD)dumpaddr);
  
    PIMAGE_THUNK_DATA32 pInt;
    //判断的条件是因为大多数情况IMAGE_THUNK_DATA 会指向一个IMPORT_BY_NAME 结束的时候会以一个
    //全零的IMAGE_THUNK_DATA结束
    if(pInt=(PIMAGE_THUNK_DATA32)my_Import_Data->OriginalFirstThunk)
    {

        while(my_Import_Data->Name)
        {
            MYIMAGE_IMPORT_DESCRIPTOR my_image_des={0};
            DWORD pszDllName_Addr=my_Import_Data->Name-OA+dumpaddr;
            my_image_des.dllname=pszDllName_Addr;
            my_image_des.my_image_descriptor.FirstThunk=my_Import_Data->FirstThunk;
            my_image_des.my_image_descriptor.OriginalFirstThunk=my_Import_Data->OriginalFirstThunk;
            my_image_des.my_image_descriptor.ForwarderChain=my_Import_Data->ForwarderChain;
            my_image_des.my_image_descriptor.Name=my_Import_Data->Name;
            mymodulename.push_back(my_image_des);
            my_Import_Data++;

        }
        for(int a=0;a<mymodulename.size();a++)
        {
            CString myid;
            myid.Format(L"%d",a);
            char* mychar;
            m_modulelist.InsertItem(LVIF_TEXT | LVIF_STATE,a, myid,(a % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED,0,0);
            for(int i=1;i<6;i++)
            {
                LPCWCH OutputChar[4]={0};
                CString mymoduleinfo;
                switch (i)
                {
                case 1:
                    MyUtil.ConvertUtf8ToUnicode((char*)mymodulename[a].dllname,*OutputChar);
                    mymoduleinfo.Format(L"%s",*OutputChar);
                    m_modulelist.SetItemText(a,i,mymoduleinfo);
                    break;
                case 2:
                    mymoduleinfo.Format(L"0x%X",mymodulename[a].my_image_descriptor.OriginalFirstThunk);
                    m_modulelist.SetItemText(a,i,mymoduleinfo);
                    break;
                case 3:
                    mymoduleinfo.Format(L"0x%X",mymodulename[a].my_image_descriptor.ForwarderChain);
                    m_modulelist.SetItemText(a,i,mymoduleinfo);
                    break;
                case 4:
                    mymoduleinfo.Format(L"0x%X",mymodulename[a].my_image_descriptor.Name);
                    m_modulelist.SetItemText(a,i,mymoduleinfo);
                    break;
                case 5:
                    mymoduleinfo.Format(L"0x%X",mymodulename[a].my_image_descriptor.FirstThunk);
                    m_modulelist.SetItemText(a,i,mymoduleinfo);
                    break;
                default:
                    break;
                }
            }
        }
    }
}


void CImportDir::ShowImportFuncInfo(PIMAGE_IMPORT_DESCRIPTOR my_Import_Data,DWORD OA,DWORD dumpaddr)
{
    m_funlist.DeleteAllItems();
    //先清空Func vector
    myfunlist.clear();
    //指向输入名称地址表(INT) 绝对地址
    DWORD pInt=my_Import_Data->OriginalFirstThunk-OA;
    DWORD pInt_addr=pInt+dumpaddr;
    PIMAGE_THUNK_DATA32 Pint=(PIMAGE_THUNK_DATA32)pInt_addr;
    //循环打印INT的内容
    if (Pint->u1.Ordinal)
    {
        while (Pint->u1.Ordinal)
        {
            DWORD i=0;
            if(!IMAGE_SNAP_BY_ORDINAL32(Pint->u1.Ordinal))
            {
                MYFUNCINFO myfun={0};
                DWORD  my_import_rva_data=(DWORD)Pint->u1.AddressOfData;
                DWORD  My_importFunciton_name_addr=my_import_rva_data-OA+dumpaddr;
                PIMAGE_IMPORT_BY_NAME My_importFunciton_name_struct=(PIMAGE_IMPORT_BY_NAME)(My_importFunciton_name_addr);
                myfun.FunName=(LPCTSTR)My_importFunciton_name_struct->Name;
                myfun.ThunkRVA=my_Import_Data->OriginalFirstThunk+i*4;
                myfun.Hint=My_importFunciton_name_struct->Hint;
                myfun.ThunkValue=my_import_rva_data;
                myfunlist.push_back(myfun);
                Pint++;
                i++;
                continue;
            }
            Pint++;

        }
        for(int a=0;a<myfunlist.size();a++)
        {
            CString myid;
            myid.Format(L"%d",a+1);
            m_funlist.InsertItem(LVIF_TEXT | LVIF_STATE,a, myid,(a % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED,0,0);
            for(int i=1;i<6;i++)
            {
                LPCWCH outputfun[8]={0};
                CString mymoduleinfo;
                switch (i)
                {
                case 1:
                    MyUtil.ConvertUtf8ToUnicode((char*)myfunlist[a].FunName,*outputfun);
                    mymoduleinfo.Format(L"%s",*outputfun);
                    m_funlist.SetItemText(a,i,mymoduleinfo);
                    break;
                case 2:
                    mymoduleinfo.Format(L"0x%X",myfunlist[a].ThunkRVA+4*a);
                    m_funlist.SetItemText(a,i,mymoduleinfo);
                    break;
                case 3:
             
                    mymoduleinfo.Format(L"0x%X",myfunlist[a].ThunkRVA-OA+4*a);
                    m_funlist.SetItemText(a,i,mymoduleinfo);
                    break;
                case 4:
                    mymoduleinfo.Format(L"0x%X",myfunlist[a].ThunkValue);
                    m_funlist.SetItemText(a,i,mymoduleinfo);
                    break;
                case 5:
                    mymoduleinfo.Format(L"0X%X",myfunlist[a].Hint);
                    m_funlist.SetItemText(a,i,mymoduleinfo);
                    break;
                default:
                    break;

                }
          
            }
        
        }
    }
}



void CImportDir::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    int a=pNMLV->iItem;
    PeMisicInfo miscinfo=ReturnMiscInfo();
    ShowImportFuncInfo((&(mymodulename[a]).my_image_descriptor),m_OA,m_dumpaddr);
    *pResult = 0;
}
