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
//---------------------------------------------------------------------------
*/

#include <vcl.h>
#include <windows.h>
#include <string>
#include <vector>
#include <memory>

#pragma hdrstop
#pragma argsused

#include <Xml.adomxmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.Win.msxmldom.hpp>
#include "..\work-functions\Logs.h"

struct LocaleRecord
{
  wchar_t *Label;
  wchar_t *Record;

  LocaleRecord(int label_len, const wchar_t *label, int rec_len, const wchar_t *rec)
  {
	Label = new wchar_t[label_len + 1];
	wcscpy(Label, label);
	Record = new wchar_t[rec_len + 1];
	wcscpy(Record, rec);
  }
};
//-------------------------------------------------------------------------

std::vector<LocaleRecord> vecRecords;
wchar_t LastError[256];
//-------------------------------------------------------------------------

void ClearRecords()
{
  try
	 {
	   for (int i = 0; i < vecRecords.size(); i++)
		  {
			delete[] vecRecords[i].Label;
			delete[] vecRecords[i].Record;
		  }

  	   vecRecords.clear();
	 }
  catch (Exception &e)
	 {
	   e.Message = "ClearRecords: " + e.Message;

	   throw e;
	 }
}
//-------------------------------------------------------------------------

int XMLImport(const wchar_t *xml_file)
{
  int res;
  auto ixml = std::make_unique<TXMLDocument>(Application);

  try
	{
      if (!FileExists(xml_file))
    	throw Exception("Localisation file doesn't exist!");

	  ClearRecords();

	  ixml->DOMVendor = GetDOMVendor("MSXML");
	  ixml->FileName = xml_file;
	  ixml->Active = true;
	  ixml->Encoding = "UTF-8";
	  ixml->Options = ixml->Options << doNodeAutoIndent;

	  _di_IXMLNode LocalisationFile = ixml->DocumentElement;
	  _di_IXMLNode Record;

	  int node_ind;

      try
		 {
		   String text, label;

		   for (node_ind = 0; node_ind < LocalisationFile->ChildNodes->Count; node_ind++)
			  {
				Record = LocalisationFile->ChildNodes->Nodes[node_ind];

				text = Record->Text;
				label = Record->GetAttribute("id");

				vecRecords.push_back(LocaleRecord(label.Length(),
												  label.c_str(),
												  text.Length(),
												  text.c_str()));
			  }

		   int cnt = vecRecords.size();
		 }
	  catch (Exception &e)
		 {
		   res = 0;

		   e.Message = "Parsing XML at node [" + IntToStr(node_ind) + "]" + e.Message;

		   throw e;
		 }

	  res = 1;
	}
  catch (Exception &e)
	{
	  res = 0;

	  e.Message = "XMLImport: " + e.Message;

	  throw e;
	}

  return res;
}
//---------------------------------------------------------------------------

wchar_t *FindRecord(const wchar_t *label)
{
  wchar_t *res = NULL;

  if (!label)
	return NULL;

  try
	 {
	   for (int i = 0; i < vecRecords.size(); i++)
		  {
			if (wcscmp(vecRecords[i].Label, label) == 0)
			  {
				res = vecRecords[i].Record;
                break;
              }
		  }
	 }
  catch (Exception &e)
	 {
	   res = NULL;

	   e.Message = "FindRecord: " + e.Message;

	   throw e;
	 }

  return res;
}
//-------------------------------------------------------------------------

const wchar_t *GetLabelFromMark(const wchar_t *mark)
{
  const wchar_t *res;

  try
	 {
	   if (!mark)
		 throw Exception("Pointer to Mark is NULL!");

	   String str = mark;
	   str.Delete(1, 1);

	   if (str != "")
		 res = str.c_str();
	 }
  catch (Exception &e)
	 {
	   res = nullptr;

	   e.Message = "GetLabelFromMark: " + e.Message;

	   throw e;
	 }

  return res;
}
//-------------------------------------------------------------------------

extern "C"
{
__declspec(dllexport) int __stdcall LoadLocaleFile(const wchar_t *xml_file)
{
  int res;

  try
	 {
	   res = XMLImport(xml_file);
	 }
  catch (Exception &e)
	 {
	   res = 0;
	   wcscpy(LastError, e.ToString().c_str());
	 }

  return res;
}
//-------------------------------------------------------------------------

__declspec(dllexport) wchar_t* __stdcall Localise(const wchar_t *mark)
{
  wchar_t *res;

  try
	 {
	   res = FindRecord(GetLabelFromMark(mark));
	 }
  catch (Exception &e)
	 {
	   res = NULL;
	   wcscpy(LastError, e.ToString().c_str());
	 }

  return res;
}
//-------------------------------------------------------------------------

__declspec(dllexport) const wchar_t* __stdcall GetError()
{
  return LastError;
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
//-------------------------------------------------------------------------

