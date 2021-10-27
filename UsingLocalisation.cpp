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

#pragma hdrstop

#include "UsingLocalisation.h"
//---------------------------------------------------------------------------
LOADLOCALEFILE LoadLocaleFile;
LOCALISE Localise;
GETERROR GetError;

HINSTANCE LoadLocaliseLibrary(const wchar_t *dll_path)
{
  HINSTANCE dllhandle;

  try
	 {
	   dllhandle = LoadLibrary(dll_path);

	   if (dllhandle)
		 {
		   LoadLocaleFile = (LOADLOCALEFILE) GetProcAddress(dllhandle, "LoadLocaleFile");
		   Localise = (LOCALISE) GetProcAddress(dllhandle, "Localise");
		   GetError = (GETERROR) GetProcAddress(dllhandle, "GetError");

		   if (!LoadLocaleFile || !Localise || !GetError)
			 {
			   FreeLocaliseLibrary(dllhandle);
               dllhandle = NULL;
			 }
		 }
	 }
  catch (Exception &e)
	 {
	   dllhandle = NULL;
	 }

  return dllhandle;
}
//---------------------------------------------------------------------------

int FreeLocaliseLibrary(HINSTANCE handle)
{
  int result = 0;

  try
	 {
	   FreeLibrary(handle);
	   result = 1;
	 }
  catch (Exception &e)
	 {
	   result = 0;
	 }

  return result;
}
//---------------------------------------------------------------------------

HINSTANCE TLocalisation::LoadLib(const String &dll_path)
{
  DllHandle = LoadLocaliseLibrary(dll_path.c_str());
  return DllHandle;
}
//---------------------------------------------------------------------------

int TLocalisation::FreeLib()
{
  return FreeLocaliseLibrary(DllHandle);
}
//---------------------------------------------------------------------------

int TLocalisation::OpenLocaleFile(const String &path)
{
  if (DllHandle)
	return LoadLocaleFile(path.c_str());
  else
    return 0;
}
//---------------------------------------------------------------------------

String TLocalisation::LocaliseText(const String &mark)
{
  if (DllHandle)
	return String(Localise(mark.c_str()));
  else
	return NULL;
}
//---------------------------------------------------------------------------

const wchar_t *TLocalisation::GetLastError()
{
  if (DllHandle)
	return GetError();
  else
    return NULL;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
