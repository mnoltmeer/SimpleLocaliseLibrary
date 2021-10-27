/*!
Copyright 2019-2021 Maxim Noltmeer (m.noltmeer@gmail.com)

This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------

#ifndef UsingLocalisationH
#define UsingLocalisationH

#include <System.Classes.hpp>
#include <windows.h>
//---------------------------------------------------------------------------
typedef int (__stdcall *LOADLOCALEFILE)(const wchar_t *xml_file);
typedef wchar_t* (__stdcall *LOCALISE)(const wchar_t *mark);
typedef const wchar_t* (__stdcall *GETERROR)();

HINSTANCE LoadLocaliseLibrary(const wchar_t *dll_path);
int FreeLocaliseLibrary(HINSTANCE handle);

static HINSTANCE DllHandle;

class TLocalisation
{
  public:
	static HINSTANCE LoadLib(const String &dll_path);
	static int FreeLib();
	static int OpenLocaleFile(const String &path);
	static String LocaliseText(const String &mark);
    static const wchar_t *GetLastError();
};
//---------------------------------------------------------------------------
#endif
