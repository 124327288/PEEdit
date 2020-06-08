
// PEEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEEdit.h"
#include "PEEditDlg.h"
#include "afxdialogex.h"
#include "PELoad.h"
#include"Src.h"
#include<vector>
#include "HexEdit.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDialog* g_dlg[5];
CPELoad MyPeLoad;
CPeHeader myheader;
CSectionBlock mysection;
CImportDir myimport;
CExportDir myexport;
CSrc mysrc;
CDataDirectory mydatadir;



// 用于应用程序“关于”菜单项的 CAboutDlg my对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPEEditDlg 对话框



CPEEditDlg::CPEEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPEEditDlg::IDD, pParent)
    , m_szPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPEEditDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB2, m_tabCrl);
    DDX_Text(pDX, IDC_EDIT1, m_szPath);
}

BEGIN_MESSAGE_MAP(CPEEditDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CPEEditDlg::OnTcnSelchangeTab2)
    ON_BN_CLICKED(IDC_BUTTON1, &CPEEditDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CPEEditDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON4, &CPEEditDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CPEEditDlg 消息处理程序

BOOL CPEEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);	
    // 设置小图标
    m_tabCrl.InsertItem(0,L"PE文件头");
    m_tabCrl.InsertItem(1,L"数据目录表");
    m_tabCrl.InsertItem(3,L"区块表");
    m_tabCrl.InsertItem(4,L"输入表");
    m_tabCrl.InsertItem(5,L"输出表");
    m_tabCrl.SetCurSel(0);
    CRect rc; 
   //不能将diadlg的类对象放在这个
    myheader.Create(IDD_DIA1,GetDlgItem(IDC_TAB2));
    mydata.Create(IDD_DIA2,GetDlgItem(IDC_TAB2));
    mySecetion.Create(IDD_DIA3,GetDlgItem(IDC_TAB2));
    myimport.Create(IDD_DIA4,GetDlgItem(IDC_TAB2));
    myexport.Create(IDD_DIA5,GetDlgItem(IDC_TAB2));

    m_tabCrl.GetClientRect(rc);
    rc.top+=30;
    rc.bottom-=5;
    rc.left+=5;
    rc.right-=5;



    g_dlg[0]=&myheader;
    g_dlg[1]=&mydata;
    g_dlg[2]=&mySecetion;
    g_dlg[3]=&myimport;
    g_dlg[4]=&myexport;
    g_dlg[0]->MoveWindow(&rc);
    g_dlg[1]->MoveWindow(&rc);
    g_dlg[2]->MoveWindow(&rc);
    g_dlg[3]->MoveWindow(&rc);
    g_dlg[4]->MoveWindow(&rc);


    m_TabIndex=0;//保存当前选项卡指针

    g_dlg[0]->ShowWindow(SW_SHOW);
    g_dlg[1]->ShowWindow(SW_HIDE);
    g_dlg[2]->ShowWindow(SW_HIDE);
    g_dlg[3]->ShowWindow(SW_HIDE);
    g_dlg[4]->ShowWindow(SW_HIDE);
    mysrc.Create(IDD_SRC);



	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPEEditDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPEEditDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPEEditDlg::OnQueryDragIcon()
{	
    return static_cast<HCURSOR>(m_hIcon);
}

int time1=0;
 vector<PIMAGE_SECTION_HEADER> Vec_SectionInfo;
 void CPEEditDlg::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{

    
    // TODO: 在此添加控件通知处理程序代码


    g_dlg[m_TabIndex]->ShowWindow(SW_HIDE);
    m_TabIndex =m_tabCrl.GetCurSel();
   
    time1++;
    if(time1==1)
    {

    mySecetion.InitContrlBar();
    myimport.InitImportBar();
    myimport.InitDllBar();
    myexport.InitImportBar();
    
    time1++;
    }
    if(m_TabIndex==1)
    {

       mydata.ShowDataDirectoryInfo();

    }
    if (m_TabIndex==2)
    {
        Vec_SectionInfo=mySecetion.ShowSectionInfo();
    }

    if(m_TabIndex==3)
    {
       
       vector<PIMAGE_SECTION_HEADER> Vec_SectionInfo1=mySecetion.GetSectionInfo1();
        myimport.ShowModuleInfo(Vec_SectionInfo1);
    }
    if(m_TabIndex==4)
    {
        myexport.GetExportInfo();
    }
    g_dlg[m_TabIndex]->ShowWindow(SW_SHOW);
    *pResult = 0;
 }


 void CPEEditDlg::OnBnClickedButton1()
 {
     // TODO: 在此添加控件通知处理程序代码

     CString strFile;
     CFileDialog dlgfile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.exe)|*.exe|(*.dll)|*.dll|All Files (*.*)|*.*||"), NULL);
     if(dlgfile.DoModal())
     {
         strFile=dlgfile.GetPathName();

     }
    MyPeLoad.LoadPEFile(strFile);
    myheader.GetMiscInfo();
    myheader.ContainInfo();
    m_szPath=strFile;
    UpdateData(FALSE);
    return ;
 }

//返回pe文件地址
 LPCTSTR CPEEditDlg::GetPePath()
 {
     return m_szPath;
 }

 void CPEEditDlg::OnBnClickedButton2()
 {
     // TODO: 在此添加控件通知处理程序代码
     mysrc.ShowInfo();
     mysrc.ShowWindow(SW_SHOW);
    
 }

 void CPEEditDlg::OnBnClickedButton4()
 { 
     HE_SETTINGS s;
     // TODO: 在此添加控件通知处理程序代码
     ZeroMemory(&s,sizeof(HE_SETTINGS));
     s.dwMask       = HE_SET_PARENTWINDOW|HE_SET_INPUTFILE |HE_SET_RESTOREWINDOWPOSITION;
     PeMisicInfo  localMisc= ReturnMiscInfo();
     CStringUtil mystirng;
     LPCCH lpout[100]={0};
     mystirng.ConvertUnicodeToUtf8((LPWCH)localMisc.lpPath,*lpout);
     char buffer[100]={0};
     strcpy_s(buffer,100,*lpout);
     s.szFilePath=buffer;
     if (!HESpecifySettings(&s))
     {
         return  ;
     }
     	HEEnterWindowLoop();
 }

 