//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <iostream>
#include <stdio.h>



using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------



__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
   //Chargement de la DLL
g_dasusbdll = LoadLibrary(L"DasHard2006.dll");
//Verification du chargement

if (g_dasusbdll)
{
   DasUsbCommand = (DASHARDCOMMAND)::GetProcAddress((HMODULE)g_dasusbdll, "DasUsbCommand");
}

//Initialisation de la DLL
interface_open =DasUsbCommand(DHC_INIT,0, NULL);
//On affiche la version de la DLL qui est retourn�e par DasUSBCommand DHC INIT
LinkLabel1->Caption = interface_open;
//On ouvre la liaison avec l'interface USB -1 si on ne trouve pas le port USB
//retourn DHC-OK = 1 si USB connect�
interface_open = DasUsbCommand(DHC_OPEN,0,0);
LinkLabel1->Caption = interface_open;
//Envoi D'une Trame DMX
//pour test je force USB meme si pas branch�
//interface_open = 1;
if (interface_open>0)
{
	// Param�tre : Commande DHC_DMXOUT, Taille Block 512 , Trame dmxbloc Pointeur
	// dmxBlock[512] est d�clar� en global dans le .h
	// Mais il faut creer la trame

	int i;

	for(i=0 ; i<DMX_MAXCHANNEL + 1; i++)
	{
		dmxBlock[i]=0;
	}
	// Voir la documentation sur une trame DMX pour remplir les bon champs
	// Pour un flux DMX il y a 1 secence de bit pour d�marer la trame
	// puis en s�rie sont envoy� un ensemble d'octet qui correspond aux
	// adresse du mat�riel.
	// exemple si la lumi�re est sur le canal 12, alors l'octet dmxBlock[12] contient
	// un ensemble de 8 bits repr�sentant les informations � envoyer � la lumi�re : intensit� couleur ect
	// le dmxBlock[0] est le Le start-code il est souvent positionner � 0 c'est un code sur 255 possibilit� qui indique la nature du message qui suit
	// ATtention une lumi�re peut avoir plusieur cannaux
	// exemple une led 3 couleurs aura 3 cannaux pour rouge vert bleu
	// donc la deuxieme lampe devra etre configur� sur un canal 4
	DasUsbCommand(DHC_DMXOUT, DMX_MAXCHANNEL, dmxBlock);
}
}




//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    DasUsbCommand(DHC_CLOSE, 0, 0);
    DasUsbCommand(DHC_EXIT, 0, NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
	dmxBlock[0]=TrackBar1->Position;
	DasUsbCommand(DHC_DMXOUT, DMX_MAXCHANNEL, dmxBlock);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
    dmxBlock[1]=TrackBar2->Position;
	DasUsbCommand(DHC_DMXOUT, DMX_MAXCHANNEL, dmxBlock);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar3Change(TObject *Sender)
{
    dmxBlock[2]=TrackBar3->Position;
	DasUsbCommand(DHC_DMXOUT, DMX_MAXCHANNEL, dmxBlock);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar4Change(TObject *Sender)
{
	int i;

	for(i=0 ; i<DMX_MAXCHANNEL + 1; i++)
	{
		dmxBlock[i]=0;
	}
	DasUsbCommand(DHC_DMXOUT, DMX_MAXCHANNEL, dmxBlock);
}
//---------------------------------------------------------------------------

