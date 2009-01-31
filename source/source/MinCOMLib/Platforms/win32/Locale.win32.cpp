#include "Common/Common.h"

#include "Locale.win32.h"

namespace MinCOM
{

	std::wstring LocaleWin32::A2W(const std::string& str)
	{
		// Calculate a number of characters.
		int wideCharacters = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		// Allocate memory to keep converted string.
		std::wstring wstr(wideCharacters + 1, L'\x0');
		// Convert multi byte string to wide.
		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &(*wstr.begin()), wideCharacters);
		return wstr;
	}

}
