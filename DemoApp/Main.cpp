//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "..\UsingLocalisation.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDemoForm *DemoForm;
//---------------------------------------------------------------------------
__fastcall TDemoForm::TDemoForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TDemoForm::LocaleFileListClick(TObject *Sender)
{
  if (LocaleFileList->ItemIndex == 0)
	{
	  //restoring default values (just for example)
	  LbName->Caption = "$name";
	  LbSay->Caption = "$wiz_say";
	  LbChoice->Caption = "$choice";
	  BtAnswer1->Caption = "$answer1";
	  BtAnswer2->Caption = "$answer2";
	  BtAnswer3->Caption = "$answer3";
	}
  else
	{
	  TLocalisation::LoadLib("Localisation.dll"); //loading library

	  String file = LocaleFileList->Items->Strings[LocaleFileList->ItemIndex] + ".xml";

	  if (!TLocalisation::OpenLocaleFile(file)) //reading file
		ShowMessage("Can't load file " + file);
	  else
		{
		  //localising UI controls
		  LbName->Caption = TLocalisation::LocaliseText("$name");
		  LbSay->Caption = TLocalisation::LocaliseText("$wiz_say");
		  LbChoice->Caption = TLocalisation::LocaliseText("$choice");
		  BtAnswer1->Caption = TLocalisation::LocaliseText("$answer1");
		  BtAnswer2->Caption = TLocalisation::LocaliseText("$answer2");
		  BtAnswer3->Caption = TLocalisation::LocaliseText("$answer3");
		}

	  TLocalisation::FreeLib();
	}
}
//---------------------------------------------------------------------------

