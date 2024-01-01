#ifndef CFILE_H
#define CFILE_H
#include<windows.h>

namespace CPPObfuscator {

	class FileManager
	{
		public:
			BOOL CheckFileExist(
				CONST WCHAR*
			);

			BOOL FormatFileName(
				WCHAR*,
				WCHAR**
			);

			PVOID ReadFileContent(
				CONST WCHAR*, 
				PULONGLONG
			);

			BOOL WriteToFile(
				CONST WCHAR*, 
				PVOID, 
				DWORD
			);
		private:
			CONST WCHAR* ob_extension = L"_obfuscated";
	};
}

#endif // CFILE_H