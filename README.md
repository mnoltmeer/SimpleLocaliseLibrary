# SimpleLocaliseLibrary
![31_Banner_Proudly_Powered_By_CBuilder_450x150-1475104](https://user-images.githubusercontent.com/33027745/120885678-cdc61380-c5f2-11eb-9603-71658ad1abdd.png)

https://www.embarcadero.com/products/cbuilder

Supporting multiple languages in your application is a good idea. But what if during the development phase you do not yet know the complete list of languages that your application will support? Or perhaps the localisation of your application will be created by enthusiasts? The basis for the modification of the text portion of the user interface is better to lay on the stage of development. And this library will help with this.

How it works:

1. Create XML-file with structure like:

<LocalisationFile>
	<Record id = 'id_1'>first record</Record>
	<Record id = 'id_2'>second record</Record>
</LocalisationFile>

2. Mark all text elements which need to localise as $<id>, where <id> is string (with no spaces).

3. Link Localisation.dll to app and use these functions:

int __stdcall LoadLocaleFile(const wchar_t *xml_file) - to load localisation xml-file.

wchar_t* __stdcall Localise(const wchar_t *mark) - to get localised text.

Localise() geting mark (like $1) and searching for it in record list. If it found, function returns record that assigned to mark. If an error occurs, the function will return NULL. The detailed error text can be obtained by calling the function const wchar_t* __stdcall GetError().
	
To further simplify the work with the library, the project contains a module with a static class TLocalisation. This class contains all the necessary methods for working with the localization library. Just include this file in your project and add the localisation library to its directory. After that, you can use the following class methods in your code:

static HINSTANCE LoadLib(const String &dll_path) - loads the library.
static int FreeLib() - frees library.
static int OpenLocaleFile(const String &path) - opens a localisation file and creates a set of localised text records.
static wchar_t *LocaliseText(const String &mark) - returns localised text.
