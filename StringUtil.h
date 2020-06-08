/**
 *@file    StringUtil.h
 *@date    2013-10-8  15:01
 *@author  ������
 *@version 1.0
 *@brief   �ַ���������	
 */
#pragma once
#include "afx.h"

enum CharseEnum
{
    // ����ö��ʱ����ʹ��UTF-8�� -
    UTF8,GBK
};

class CStringUtil :
    public CObject
{
    public:
    CStringUtil(void);
    ~CStringUtil(void);
public:
    static void ConvertUtf8ToUnicode( _In_ const LPCCH szUtf8,LPCWCH _Out_  &pOut);
    static void ConvertUnicodeToUtf8(_In_ const LPWCH pUnicode, _Out_ LPCCH &pOut);
    static void ConvertGbkToUnicode( _In_ const LPCCH szGbk,LPCWCH _Out_ &pOut);


    static void GetSubStringFromBuffer(_In_ const PTCHAR pBuf,_In_ DWORD dwPos,
                                      _In_ DWORD dwLen,_Out_ CString &strOut);
    static void GetSubStringFromBufferBeg(_In_ const PTCHAR pBuf,_In_ DWORD dwLen,_Out_ CString &strOut);
};

