#include "stdafx.h"
#include "StringUtil.h"


CStringUtil::CStringUtil(void)
{
}


CStringUtil::~CStringUtil(void)
{
}

/******************************************************************************/
/**
 *@brief ʹ�ý�������Ҫ��ָ�����delete
 */
void CStringUtil::ConvertUtf8ToUnicode( _In_ const LPCCH szUtf8,LPCWCH _Out_ &pOut) 
{ 
    // ����ַ��ĸ���
    int nCount       = MultiByteToWideChar(CP_UTF8,0, szUtf8 ,-1, NULL,0);

    // �洢ת����õ��Ŀ��ַ�
    WCHAR* szUnicode = new WCHAR[nCount+1]; 
    memset(szUnicode,0, nCount*sizeof(WCHAR)+sizeof(WCHAR));

    // ת��
    MultiByteToWideChar(CP_UTF8,0, szUtf8,-1, szUnicode, nCount);
    szUnicode[nCount] = L'\0';
    pOut = szUnicode;
}

/******************************************************************************/
void CStringUtil::ConvertUnicodeToUtf8(_In_ const LPWCH pUnicode, _Out_ LPCCH &pOut)
{
    int nCount = ::WideCharToMultiByte(CP_UTF8, NULL,pUnicode, wcslen(pUnicode), NULL, 0, NULL, NULL);

    CHAR* szUtf8 = new char[nCount+1];
    memset(szUtf8,0, nCount*sizeof(CHAR)+sizeof(CHAR));
    ::WideCharToMultiByte(CP_UTF8, NULL, pUnicode, wcslen(pUnicode), szUtf8, nCount, NULL, NULL);
    szUtf8[nCount] = '\0';

    pOut = szUtf8;
}

/******************************************************************************/
void CStringUtil::ConvertGbkToUnicode( _In_ const LPCCH szGbk,LPCWCH _Out_ &pOut)
{
    // ����ַ��ĸ���
    int nCount       = MultiByteToWideChar(CP_ACP,0, szGbk ,-1, NULL,0);

    // �洢ת����õ��Ŀ��ַ�
    WCHAR* szUnicode = new WCHAR[nCount+1]; 
    memset(szUnicode,0, nCount*sizeof(WCHAR)+sizeof(WCHAR));

    // ת��
    MultiByteToWideChar(CP_ACP,0, szGbk,-1, szUnicode, nCount);
    szUnicode[nCount] = L'\0';
    pOut = szUnicode;
}
/******************************************************************************/
/**
 *@brief ��ָ��λ�û�ȡ�ִ�
 */
void CStringUtil::GetSubStringFromBuffer(_In_ const PTCHAR pBuf,_In_ DWORD dwPos,
                                         _In_ DWORD dwLen,_Out_ CString &strOut)
{
    PTCHAR pTemp = new TCHAR[dwLen+1];

#ifdef _UNICODE
    wcsncpy_s(pTemp,dwLen+1,pBuf+dwPos,dwLen);
#else
    strncpy_s(pTemp,dwLen+1,pBuf+dwPos,dwLen);
#endif // _UNICODE

    strOut = pTemp;
    delete[] pTemp;
}
/******************************************************************************/
/**
 *@brief �ӻ�������ʼλ�û�ȡ�̶����ȵ��ַ���
 */
void CStringUtil::GetSubStringFromBufferBeg(_In_ const PTCHAR pBuf,
                                         _In_ DWORD dwLen,_Out_ CString &strOut)
{
    GetSubStringFromBuffer(pBuf,0,dwLen,strOut);
}