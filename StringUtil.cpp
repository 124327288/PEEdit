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
 *@brief 使用结束后，需要对指针进行delete
 */
void CStringUtil::ConvertUtf8ToUnicode( _In_ const LPCCH szUtf8,LPCWCH _Out_ &pOut) 
{ 
    // 获得字符的个数
    int nCount       = MultiByteToWideChar(CP_UTF8,0, szUtf8 ,-1, NULL,0);

    // 存储转换后得到的宽字符
    WCHAR* szUnicode = new WCHAR[nCount+1]; 
    memset(szUnicode,0, nCount*sizeof(WCHAR)+sizeof(WCHAR));

    // 转换
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
    // 获得字符的个数
    int nCount       = MultiByteToWideChar(CP_ACP,0, szGbk ,-1, NULL,0);

    // 存储转换后得到的宽字符
    WCHAR* szUnicode = new WCHAR[nCount+1]; 
    memset(szUnicode,0, nCount*sizeof(WCHAR)+sizeof(WCHAR));

    // 转换
    MultiByteToWideChar(CP_ACP,0, szGbk,-1, szUnicode, nCount);
    szUnicode[nCount] = L'\0';
    pOut = szUnicode;
}
/******************************************************************************/
/**
 *@brief 从指定位置获取字串
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
 *@brief 从缓冲区起始位置获取固定长度的字符串
 */
void CStringUtil::GetSubStringFromBufferBeg(_In_ const PTCHAR pBuf,
                                         _In_ DWORD dwLen,_Out_ CString &strOut)
{
    GetSubStringFromBuffer(pBuf,0,dwLen,strOut);
}