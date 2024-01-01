#include "CFile.hpp"
using namespace CPPObfuscator;

BOOL FileManager::CheckFileExist(
    CONST WCHAR* filePath
)
{
    DWORD fileAttributes = GetFileAttributes(filePath);
    return (fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

BOOL FileManager::FormatFileName(
    WCHAR* filePath,
    WCHAR** newFilePath
)
{
    SIZE_T newSize = wcslen(filePath) + wcslen(ob_extension) + 1;
    *newFilePath = (WCHAR*)malloc(newSize * sizeof(WCHAR));

    if (*newFilePath != NULL) {
        wcscpy_s(*newFilePath, newSize, filePath);
        wcscat_s(*newFilePath, newSize, ob_extension);
        return TRUE;
    }
    return FALSE;
}

PVOID FileManager::ReadFileContent(
    CONST WCHAR* filePath, 
    PULONGLONG bufferSize
)
{
    HANDLE hFile;
    PVOID buffer;
    LARGE_INTEGER internalFileSize;
    DWORD bytesRead;
    BOOL readFileStatus;

    hFile = CreateFile(
        filePath,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    if (!GetFileSizeEx(hFile, &internalFileSize)) {
        CloseHandle(hFile);
        return NULL;
    }

    *bufferSize = (ULONGLONG)internalFileSize.QuadPart;
    buffer = HeapAlloc(GetProcessHeap(), 0, (SIZE_T)* bufferSize);

    if (buffer == NULL) {
        CloseHandle(hFile);
        return NULL;
    }

    readFileStatus = ReadFile(
        hFile, 
        buffer, 
        (DWORD)*bufferSize, 
        &bytesRead, 
        NULL
    );

    CloseHandle(hFile);
    if (!readFileStatus)
    {
        HeapFree(GetProcessHeap(), 0, buffer);
        return NULL;
    }
	return buffer;
}

BOOL FileManager::WriteToFile(
    CONST WCHAR* filePath,
    PVOID buffer, 
    DWORD bufferSize
)
{
    if (CheckFileExist(filePath))
    {
        WCHAR* newFileName{};
        if (FormatFileName((WCHAR*)filePath, &newFileName))
        {
            return WriteToFile(newFileName, buffer, bufferSize);
        }
        return FALSE;
    }
    else
    {
        HANDLE hFile;
        BOOL status;

        hFile = CreateFile(
            filePath,
            GENERIC_WRITE,
            0,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        if (hFile == INVALID_HANDLE_VALUE)
        {
            return FALSE;
        }

        DWORD bytesWritten;
        status = WriteFile(hFile, buffer, bufferSize, &bytesWritten, NULL);
        if (!status)
            CloseHandle(hFile);

        return status;
    }
}