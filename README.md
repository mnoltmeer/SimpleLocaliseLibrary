# SimpleLocaliseLibrary
![31_Banner_Proudly_Powered_By_CBuilder_450x150-1475104](https://user-images.githubusercontent.com/33027745/120885678-cdc61380-c5f2-11eb-9603-71658ad1abdd.png)

https://www.embarcadero.com/products/cbuilder

Supporting multiple languages in your application is a good idea. But what if during the development phase you do not yet know the complete list of languages that your application will support? Or perhaps the localisation of your application will be created by enthusiasts? The basis for the modification of the text portion of the user interface is better to lay on the stage of development. And this library will help with this.

How it works:

1. Create XML-file with structure like:

```xml
<LocalisationFile>
	<Record id = 'id_1'>first record</Record>
	<Record id = 'id_2'>second record</Record>
</LocalisationFile>
```

2. Mark all text elements which need to localise as $[id], where [id] is string (with no spaces).

3. Link Localisation.dll to app and use these functions:
	
```int __stdcall LoadLocaleFile(const wchar_t *xml_file)``` - to load localisation xml-file.

```wchar_t* __stdcall Localise(const wchar_t *mark)``` - to get localised text.

Localise() function geting mark (like $1) and searching for it in record list. If it found, function returns record that assigned to mark. If an error occurs, the function will return NULL. The detailed error text can be obtained by calling the function const wchar_t* __stdcall GetError().
	
To further simplify the work with the library, the project contains a module with a static class TLocalisation. This class contains all the necessary methods for working with the localisation library. Just include this file in your project and add the localisation library to its directory. After that, you can use the following class methods in your code:
	
```c++
static HINSTANCE LoadLib(const String &dll_path) - loads library.
static int FreeLib() - frees library.
static int OpenLocaleFile(const String &path) - opens a localisation file and creates a set of localised text records.
static wchar_t *LocaliseText(const String &mark) - returns localised text.
static const wchar_t *GetLastError() - returns last error.
```
	
Let's see how it works. Add some lines of code.	

```c++
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
```

Place the library and localisation files in the application directory.

![image](https://user-images.githubusercontent.com/33027745/120896680-4052e580-c62b-11eb-9f13-679b0a1182ad.png)
	
And this is how our application changes in real time:

By default:
	
![image](https://user-images.githubusercontent.com/33027745/120898017-ceca6580-c631-11eb-9244-3ba2e21ba088.png)
	
And after choosing one of the localisation files: 

![image](https://user-images.githubusercontent.com/33027745/120896451-4dbba000-c62a-11eb-9fe5-2863f32c44f6.png)
![image](https://user-images.githubusercontent.com/33027745/120896400-046b5080-c62a-11eb-9904-1f9a40629f00.png)
![image](https://user-images.githubusercontent.com/33027745/120896405-09300480-c62a-11eb-966b-c23cead9f1f7.png)


