#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "include/DasHard.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#define DMX_MAXCHANNEL 512
#include <Windows.h>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published: // Composants g�r�s par l'EDI
	TButton *Button1;
	TLabel *LinkLabel1;
	TButton *Button2;
	TTrackBar *TrackBar1;
	TTrackBar *TrackBar2;
	TTrackBar *TrackBar3;
	TTrackBar *TrackBar4;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall TrackBar2Change(TObject *Sender);
	void __fastcall TrackBar3Change(TObject *Sender);
	void __fastcall TrackBar4Change(TObject *Sender);

private: // D�clarations utilisateur
	HINSTANCE  g_dasusbdll; //variable qui va initialiser la librairie
public: // D�clarations utilisateur
	__fastcall TForm1(TComponent* Owner);
	typedef int (*DASHARDCOMMAND)(int, int, unsigned char*);
	DASHARDCOMMAND DasUsbCommand ;
	int interface_open;
	unsigned char dmxBlock[512];
	void __fastcall SendTrame();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
