// Src.cpp : 实现文件
//

#include "stdafx.h"
#include "PEEdit.h"
#include "Src.h"
#include "afxdialogex.h"
#include"StringUtil.h"
#include<string>
#include <sstream>
CStringUtil mySrcStirng;
// CSrc 对话框
DWORD RVA2Memaddr( DWORD dwRVA, PVOID lpImage, PIMAGE_NT_HEADERS32 pNT32 );

IMPLEMENT_DYNAMIC(CSrc, CDialogEx)

CSrc::CSrc(CWnd* pParent)
	: CDialogEx(CSrc::IDD, pParent)
    , m_secidnums(_T(""))
    , m_rootIdnums(_T(""))
    , m_Rva(_T(""))
{
    
}

CSrc::~CSrc()
{
//     CWnd* aa=GetDlgItem(IDD_SRC);
//     CloseHandle(aa->m_hWnd);
}

void CSrc::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE1, m_srcTreecrl);
    DDX_Text(pDX, IDC_EDIT6, m_secidnums);
    DDX_Text(pDX, IDC_EDIT4, m_rootIdnums);
    DDX_Text(pDX, IDC_EDIT7, m_Rva);

}


BEGIN_MESSAGE_MAP(CSrc, CDialogEx)
   ON_NOTIFY(TVN_SELCHANGING, IDC_TREE1, &CSrc::OnSelchangingTree1)
    ON_NOTIFY(TVN_ITEMCHANGED, IDC_TREE1, &CSrc::OnItemchangedTree1)
END_MESSAGE_MAP()

WCHAR szResourceType[17][16] = {
    L"0000"		,L"鼠标指针"	,L"位图"			,L"图标"		,L"菜单"			,L"对话框"	,L"字符串列表"	,L"字体目录",
    L"字体"		,L"快捷键"	,L"非格式化资源"	,L"消息列表"	,L"鼠标指针组"	,L"000D"		,L"图标组"		,L"000F",
    L"版本信息"
};


void CSrc::ShowInfo()
{
    //这里用ID关联资源之间的关系，来显示层与层之间的关系
    int ID1=0;
    m_srcTreecrl.ModifyStyle(NULL,TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT);
    PeMisicInfo miscinfo=ReturnMiscInfo();
    PIMAGE_NT_HEADERS32 pNT32 = (PIMAGE_NT_HEADERS32)miscinfo.nt_headeras;
    // 1.2 获取数据目录表
    PIMAGE_DATA_DIRECTORY pDir = (PIMAGE_DATA_DIRECTORY)pNT32->OptionalHeader.DataDirectory;
    // 1.3 获取资源表的数据目录
    PIMAGE_DATA_DIRECTORY pDataDir = pDir+IMAGE_DIRECTORY_ENTRY_RESOURCE;
    // 1.4 获取资源表
    PIMAGE_RESOURCE_DIRECTORY pResource1 = (PIMAGE_RESOURCE_DIRECTORY)RVA2Memaddr(pDataDir->VirtualAddress, miscinfo.Dumpaddr, pNT32);
    // 2. 循环遍历资源表
    // 2.1 第一层目录遍历
    DWORD dwCount1 = pResource1->NumberOfIdEntries+pResource1->NumberOfNamedEntries;
    for ( DWORD i=0; i<dwCount1; i++ )
    {
        SRCSTRUCT mystc={0};
        ID1++;
        mystc.ID=ID1;
        LPCWCH* outputchar=new LPCWCH;
        PIMAGE_RESOURCE_DIRECTORY_ENTRY pDirEntry1 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)pResource1+sizeof(IMAGE_RESOURCE_DIRECTORY));
        if ( pDirEntry1[i].NameIsString )
        {
            PIMAGE_RESOURCE_DIR_STRING_U pString = (PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)pResource1+pDirEntry1[i].NameOffset);
            mystc.str.Format(L"Type:%ls",pString->NameString);
            Level1.push_back(mystc);
        } 
        else
        {
            if ( pDirEntry1[i].Name>0x10 )
            {
                mystc.str.Format(L"%04X",pDirEntry1[i].Name);
                Level1.push_back(mystc);
            }

            else
            {
                mystc.str.Format(L"%ls",szResourceType[pDirEntry1[i].Name] );
                Level1.push_back(mystc);
            }

        }
        if ( pDirEntry1[i].DataIsDirectory )
        {
            int secid=0;
            // 2.2 第二层目录的遍历
            PIMAGE_RESOURCE_DIRECTORY pResource2 = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)pResource1+pDirEntry1[i].OffsetToDirectory);
            DWORD dwCount2 = pResource2->NumberOfIdEntries+pResource2->NumberOfNamedEntries;
            for ( DWORD j=0; j<dwCount2; j++ )
            {

                SRCSTRUCT mystc2={0};
                mystc2.ID=ID1;
                //第二级的id
                secid++;
                mystc2.secid=secid;
                PIMAGE_RESOURCE_DIRECTORY_ENTRY pDirEntry2 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)pResource2+sizeof(IMAGE_RESOURCE_DIRECTORY));
                if ( pDirEntry2[j].NameIsString )
                {
                    LPWSTR szBuffer[30];
                    PIMAGE_RESOURCE_DIR_STRING_U pString = (PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)pResource2+pDirEntry2[j].NameOffset);
                    mystc2.str.Format(L"ID:%ls",pString->NameString);
                    Level2.push_back(mystc2);

                } 
                else
                {
                    mystc2.str.Format(L"ID:%X",pDirEntry2[j].Name);
                    Level2.push_back(mystc2);

                }
                if ( pDirEntry2[j].DataIsDirectory )
                {
                   DWORD subId=0;
                    // 2.3 第三层目录的遍历
                    PIMAGE_RESOURCE_DIRECTORY pResource3 = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)pResource1+pDirEntry2[j].OffsetToDirectory);
                    DWORD dwCount3 = pResource3->NumberOfIdEntries+pResource3->NumberOfNamedEntries;
                    for ( DWORD k=0; k< dwCount3; k++ )
                    {
                        SRCSTRUCT mystc3={0};
                        mystc3.secid=secid;
                        mystc3.ID=ID1;
                        subId++;
                        mystc3.subID=subId;
                        PIMAGE_RESOURCE_DIRECTORY_ENTRY pDirEntry3 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)pResource3+sizeof(IMAGE_RESOURCE_DIRECTORY));
                        PIMAGE_RESOURCE_DATA_ENTRY pData = (PIMAGE_RESOURCE_DATA_ENTRY)((DWORD)pResource1+pDirEntry3[k].OffsetToData);
                        mystc3.str.Format(L"Lng:%04X,RVA:0x%p Size:%04X Page:0x%p",pDirEntry3[k].Name,pData->OffsetToData, pData->Size, pData->CodePage);
                        Level3.push_back(mystc3); 
                    }
                } 
                else
                {
                    // ....
                }
           

            }
        } 
        else
        {
            // ......
        }
    }
RealShowInfo();
 }


void CSrc::RealShowInfo()
{
    //循环插入
    //对内存的分配不是很清楚
    //特别是new的使用
    HTREEITEM *myitem=new HTREEITEM[Level1.size()];
    HTREEITEM *myitem1=new HTREEITEM[Level2.size()];
    for(int a=0;a<Level1.size();a++)
    {
        myitem[a] = m_srcTreecrl.InsertItem((LPCTSTR)Level1[a].str,NULL,NULL,0,NULL);
        m_hLevel1item.push_back(myitem[a]);
    } 
    for(int a=0;a<Level1.size();a++)
    {
        for(int i=0;i<Level2.size();i++)
        {
            int sum=0;
            if(Level1[a].ID==Level2[i].ID)
            {
                myitem1[i]=m_srcTreecrl.InsertItem((LPCTSTR)Level2[i].str,NULL,NULL,myitem[a],NULL);
                m_hLevel2item.push_back(myitem1[i] );
                sum++;
            }
          m_secidnums.Format(_T("%d"),sum);
        }
    }
    delete[] myitem;
    delete[] myitem1;
}


DWORD RVA2Memaddr( DWORD dwRVA, PVOID lpImage, PIMAGE_NT_HEADERS32 pNT32 )
{
    PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNT32);
    for ( DWORD i=0; i<=pNT32->FileHeader.NumberOfSections; i++ )
    {
        DWORD dwMemAddr=0;

        if ( dwRVA < pSection[i].VirtualAddress )
        {
            DWORD dwR_Offset = dwRVA - pSection[i-1].VirtualAddress;
            dwMemAddr   =
                (DWORD)lpImage
                + dwR_Offset
                + pSection[i-1].PointerToRawData;
            return dwMemAddr;

        }
        else  if(dwRVA>= pSection[pNT32->FileHeader.NumberOfSections-1].VirtualAddress)
        {
            DWORD dwR_Offset = dwRVA - pSection[pNT32->FileHeader.NumberOfSections-1].VirtualAddress;
            dwMemAddr   =
                (DWORD)lpImage
                + dwR_Offset
                + pSection[pNT32->FileHeader.NumberOfSections-1].PointerToRawData;
            return dwMemAddr;
        }

    }

    return 0;
}



void CSrc::OnBnClickedButton5()
{
    // TODO: 在此添加控件通知处理程序代码
}


void CSrc::OnSelchangingTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    TVITEMW LocalView1=pNMTreeView->itemOld;
    TVITEMW LocalView=pNMTreeView->itemNew;
    HTREEITEM local_hitem=LocalView.hItem;
     
    for(int j=0;j<m_hLevel1item.size();j++)
    {

        if(local_hitem==m_hLevel1item[j])
        {
            CString mystirng=m_srcTreecrl.GetItemText(local_hitem);
            m_secidnums=mystirng;
        }
    }
  for (int i=0;i<m_hLevel2item.size();i++)
  {
      int a;
      if (local_hitem==m_hLevel2item[i])
      {
         a=i;
         m_Rva=Level3[a].str;
      }

  }
  m_rootIdnums=CString("35");
  UpdateData(FALSE);
  *pResult = 0;
}



void CSrc::OnItemchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
    NMTVITEMCHANGE *pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
    *pResult = 0;
}
