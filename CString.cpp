#include "CString.hpp"
using namespace CPPObfuscator;

VOID CString::ReplacePotentialKeyWords(
    CONST WCHAR* filePath
)
{

}

WCHAR* CString::GenMacroKeyword(
    CONST WCHAR* keyword, 
    CONST WCHAR* number
)
{
    DWORD length = wcslen(L"#define ") + wcslen(keyword) + wcslen(number) + 1;
    WCHAR* res = (WCHAR*)malloc(length * sizeof(WCHAR));

    if (res != NULL) {
        wcscpy(res, L"#define ");
        wcscat(res, keyword);
        wcscat(res, L" ");
        wcscat(res, number);
        wcscat(res, L"\n");
    }
    return res;
}

WCHAR* CString::GenRandomNumber(

)
{
    SYSTEMTIME st;
    DWORD len;
    WCHAR* num;

    GetSystemTime(&st);
    srand(st.wMilliseconds);
    len = rand() % 11 + 5;
    num = (WCHAR*)malloc((len + 1) * sizeof(WCHAR));

    if (num != NULL) {
        for (DWORD i = 0; i < len; ++i) {
            num[i] = L'0' + rand() % 10;
        }
        num[len] = L'\0';
    }
    return num;
}