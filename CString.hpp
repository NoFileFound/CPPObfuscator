#ifndef H_CSTRING
#define H_CSTRING
#include<windows.h>

namespace CPPObfuscator
{
	class CString
	{
		public:
			VOID ReplacePotentialKeyWords(
				CONST WCHAR*
			);

			WCHAR* GenMacroKeyword(
				CONST WCHAR*, 
				CONST WCHAR*
			);

			WCHAR* GenRandomNumber(

			);

		private:
			CONST WCHAR* msg = L"Obfuscated by Flow22";
	};
}

#endif // H_CSTRING