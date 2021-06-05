/*!
Copyright 2019-2020 Maxim Noltmeer (m.noltmeer@gmail.com)

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
//---------------------------------------------------------------------------
*/

#include <vcl.h>
#include <windows.h>
#include <string>
#include <vector>

#pragma hdrstop
#pragma argsused

#include <Xml.adomxmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.Win.msxmldom.hpp>
#include "..\..\work-functions\Logs.h"

struct LocaleRecord
{
  int ID;
  wchar_t *Record;

  LocaleRecord(int id, int rec_len, const wchar_t *rec)
  {
	ID = id;
	Record = new wchar_t[rec_len + 1];
    wcscpy(Record, rec);
  }
};
//-------------------------------------------------------------------------

std::vector<LocaleRecord> vecRecords;

void ClearRecords()
{
  try
	 {
	   for (int i = 0; i < vecRecords.size(); i++)
		  {
	   		delete[] vecRecords[i].Record;
		  }

  	   vecRecords.clear();
	 }
  catch (Exception &e)
	 {
	   SaveLog("exceptions.log", "Localisation::ClearRecords: " + e.ToString());
	 }
}
//-------------------------------------------------------------------------

int XMLImport(const wchar_t *xml_file)
{
  int res;
  TXMLDocument *ixml = new TXMLDocument(Application);

  try
	{
	  ixml->DOMVendor = GetDOMVendor("MSXML");
	  ixml->FileName = xml_file;
	  ixml->Active = true;
	  ixml->Encoding = "UTF-8";
	  ixml->Options = ixml->Options << doNodeAutoIndent;

	  _di_IXMLNode LocalizationFile = ixml->DocumentElement;
	  _di_IXMLNode Record;

      try
		 {
		   ClearRecords();

		   String text;

		   for (int i = 0; i < LocalizationFile->ChildNodes->Count; i++)
			  {
				Record = LocalizationFile->ChildNodes->Nodes[i];
				vecRecords.push_back(LocaleRecord(int(Record->GetAttribute("id")),
												  Record->Text.Length(),
												  Record->Text.c_str()));
			  }

		   int cnt = vecRecords.size();
		 }
	  catch (Exception &e)
		 {
		   SaveLog("exceptions.log", "Localisation::XMLImport: " + e.ToString());
		   res = 0;
		 }

	  res = 1;
	}
  __finally {delete ixml;}

  return res;
}
//---------------------------------------------------------------------------

wchar_t *FindRecord(int id)
{
  wchar_t *res = NULL;

  if (id < 0)
    return NULL;

  try
	 {
	   for (int i = 0; i < vecRecords.size(); i++)
		  {
			if (vecRecords[i].ID == id)
			  {
				res = vecRecords[i].Record;
                break;
              }
		  }
	 }
  catch (Exception &e)
	 {
	   SaveLog("exceptions.log", "Localisation::FindRecord: " + e.ToString());
	   res = NULL;
	 }

  return res;
}
//-------------------------------------------------------------------------

int MarkToID(const wchar_t *mark)
{
  int res;

  try
	 {
	   String str = mark;
	   str.Delete(1, 1);

	   if (str != "")
	   	 res = str.ToInt();
	 }
  catch (Exception &e)
	 {
	   SaveLog("exceptions.log", "Localisation::MarkToID: " + e.ToString());
	   res = -1;
	 }

  return res;
}
//-------------------------------------------------------------------------

extern "C"
{
__declspec(dllexport) int __stdcall LoadLocaleFile(const wchar_t *xml_file)
{
  if (FileExists(xml_file))
	return XMLImport(xml_file);
  else
  	return 0;
}
//-------------------------------------------------------------------------

__declspec(dllexport) wchar_t* __stdcall Localise(const wchar_t *mark)
{
  return FindRecord(MarkToID(mark));
}
//-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
  if (reason == 0)
  	ClearRecords();

  return 1;
}

