//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TDemoForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListBox *LocaleFileList;
	TImage *Avatar;
	TLabel *LbName;
	TImage *TextBubble;
	TLabel *LbSay;
	TButton *BtAnswer1;
	TButton *BtAnswer2;
	TButton *BtAnswer3;
	TLabel *LbChoice;
	void __fastcall LocaleFileListClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDemoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDemoForm *DemoForm;
//---------------------------------------------------------------------------
#endif
