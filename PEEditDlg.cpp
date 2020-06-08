
// PEEditDlg.cpp : ʵ���ļ�
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



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg my�Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CPEEditDlg �Ի���



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


// CPEEditDlg ��Ϣ�������

BOOL CPEEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);	
    // ����Сͼ��
    m_tabCrl.InsertItem(0,L"PE�ļ�ͷ");
    m_tabCrl.InsertItem(1,L"����Ŀ¼��");
    m_tabCrl.InsertItem(3,L"�����");
    m_tabCrl.InsertItem(4,L"�����");
    m_tabCrl.InsertItem(5,L"�����");
    m_tabCrl.SetCurSel(0);
    CRect rc; 
   //���ܽ�diadlg�������������
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


    m_TabIndex=0;//���浱ǰѡ�ָ��

    g_dlg[0]->ShowWindow(SW_SHOW);
    g_dlg[1]->ShowWindow(SW_HIDE);
    g_dlg[2]->ShowWindow(SW_HIDE);
    g_dlg[3]->ShowWindow(SW_HIDE);
    g_dlg[4]->ShowWindow(SW_HIDE);
    mysrc.Create(IDD_SRC);



	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPEEditDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPEEditDlg::OnQueryDragIcon()
{	
    return static_cast<HCURSOR>(m_hIcon);
}

int time1=0;
 vector<PIMAGE_SECTION_HEADER> Vec_SectionInfo;
 void CPEEditDlg::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{

    
    // TODO: �ڴ���ӿؼ�֪ͨ����������


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
     // TODO: �ڴ���ӿؼ�֪ͨ����������

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

//����pe�ļ���ַ
 LPCTSTR CPEEditDlg::GetPePath()
 {
     return m_szPath;
 }

 void CPEEditDlg::OnBnClickedButton2()
 {
     // TODO: �ڴ���ӿؼ�֪ͨ����������
     mysrc.ShowInfo();
     mysrc.ShowWindow(SW_SHOW);
    
 }

 void CPEEditDlg::OnBnClickedButton4()
 { 
     HE_SETTINGS s;
     // TODO: �ڴ���ӿؼ�֪ͨ����������
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

 