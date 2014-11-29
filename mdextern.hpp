/*
  MouseHide for AltDvb 2.2 in FullScreen Mode

  Copyright (C) 2009 Daniel Rodriksson

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*
  This modules implements the entry points and structures for an MD-API plug-in
  so that the application will execute inside ALT-Dvb as another MD-API plug-in
 */

#ifndef _MDEXTERN_HPP_
#define _MDEXTERN_HPP_

#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#include <windows.h>

/* Common parts not dependent on MD8.0/8.2+ version */

#define MDAPI_GET_TRANSPONDER        0x01020000
#define MDAPI_SET_TRANSPONDER        0x01020001

#define MDAPI_GET_PROGRAMM           0x01020010
#define MDAPI_SET_PROGRAMM           0x01020011
#define MDAPI_RESCAN_PROGRAMM        0x01020012
#define MDAPI_SAVE_PROGRAMM          0x01020013
#define MDAPI_GET_PROGRAMM_NUMMER    0x01020014
#define MDAPI_SET_PROGRAMM_NUMMER    0x01020015

#define MDAPI_START_FILTER           0x01020020
#define MDAPI_STOP_FILTER            0x01020021

#define MDAPI_SCAN_CURRENT_TP        0x01020030
#define MDAPI_SCAN_CURRENT_CAT       0x01020031

#define MDAPI_START_OSD              0x01020040
#define MDAPI_OSD_DRAWBLOCK          0x01020041
#define MDAPI_OSD_SETFONT            0x01020042
#define MDAPI_OSD_TEXT               0x01020043
#define MDAPI_SEND_OSD_KEY           0x01020044
#define MDAPI_STOP_OSD               0x01020049

#define MDAPI_DVB_COMMAND            0x01020060

typedef struct TPIDFilters {
  char FilterName[ 5];
  unsigned char FilterId;
  unsigned short PID;
} TPIDFilters;

typedef enum {
  RECPLAY_PLAY = 1,
  RECPLAY_RECORD = 2,
  RECPLAY_STOP = 3
} RECPLAY_t;

struct TTransponder {
  int ttk;
  int power;
  int diseqc;
  unsigned int freq;
  int volt;
  int qam;
  unsigned int srate;
  int fec;
  int sync;                     /* sync from decoder */
  int afc;                      /* frequency offset in Hz */
  unsigned short agc;           /* gain */
  unsigned short nest;          /* noise estimation */
  unsigned int vber;            /* viterbi bit error rate */
  unsigned short ts_id;
  unsigned int sig;               
  unsigned int err;               
};

struct TProgrammNummer {
  int RealNummer;
  int VirtNummer;
};

struct TTPCat {
  unsigned char TAG;
  unsigned char DesLen;
  unsigned short CA_ID;
  unsigned short EMM;
  unsigned short BufferLen;
  unsigned char Buffer[ 64];
};

#define TPSIZE 256

struct TOSD_START {
  int DLL_Id;
  unsigned char BitTiefe;
  int x1;
  int y1;
  int x2;
  int y2;
  BOOL Input;
};

struct TOSD_DRAW {
  unsigned short x;
  unsigned short y;
  unsigned short Sizex;
  unsigned short Sizey;
  unsigned short Color;
};

struct TOSD_SETFONT {
  unsigned short Typ;
  unsigned short Fg_Color;
  unsigned short Bg_Color;
};

struct TOSD_SETEXT {
  unsigned short x;
  unsigned short y;
  char Zeile[ 128];
};

struct TSTART_FILTER {
  unsigned short DLL_ID;
  unsigned short Filter_ID;
  unsigned short Pid;
  unsigned char Name[ 32];
  DWORD Irq_Call_Adresse;
  int Running_ID;
};

struct TDVB_COMMAND{
  unsigned short Cmd_laenge;
  unsigned short Cmd_Buffer[ 32];
};

#ifndef MDEXTERN80_H
#define MDEXTERN80_H

/* Part specific for MD before 8.2 */

typedef struct TCA_System80 {
  unsigned short CA_Typ;
  unsigned short ECM;
  unsigned short EMM;
} TCA_System80;

typedef struct TProgramm80
{
  char Name[ 30];
  char Anbieter[ 30];
  char Land[ 30];
  unsigned long freq;
  unsigned char Typ;
  unsigned char volt;              
  unsigned char afc;
  unsigned char diseqc;            
  unsigned int srate;         
  unsigned char qam;               
  unsigned char fec;   
  unsigned char norm;
  unsigned short tp_id;        
  unsigned short Video_pid;        
  unsigned short Audio_pid;
  unsigned short TeleText_pid;          
  unsigned short PMT_pid;
  unsigned short PCR_pid;
  unsigned short ECM_PID;
  unsigned short SID_pid;
  unsigned short AC3_pid;
  unsigned char TVType; 
  unsigned char ServiceTyp;
  unsigned char CA_ID;
  unsigned short Temp_Audio;
  unsigned short Filteranzahl;
  struct TPIDFilters Filters[ 12];
  unsigned short CA_Anzahl;
  struct TCA_System80 CA_System[ 6];
  char CA_Land[ 5];
  unsigned char Merker;
  unsigned short Link_TP;
  unsigned short Link_SID;
  unsigned char Dynamisch;

  char Extern_Buffer[ 16];
} TProgramm80;

struct TTPCatio80 {
  int TPCatAnzahl;
  struct TTPCat TPCat[ 8];
};

#endif

#ifndef MDEXTERN82_H
#define MDEXTERN82_H

/* Part specific for MD8.2+ */

#define MDAPI_GET_VERSION            0x01020100
#define MAX_CA_SYSTEMS 32
#define MAX_PID_IDS 32

struct TCA_System82 {
  unsigned short CA_Typ;
  unsigned short ECM;
  unsigned short EMM;
  unsigned int Provider_Id;   // Neu -> Viaccess und Seca Provider in der Kanalliste
};

typedef struct TProgramm82
{
  char Name[ 30];
  char Anbieter[ 30];
  char Land[ 30];
  unsigned long freq;
  unsigned char Typ;
  unsigned char volt;              
  unsigned char afc;
  unsigned char diseqc;            
  unsigned int srate;         
  unsigned char qam;               
  unsigned char fec;   
  unsigned char norm;
  unsigned short tp_id;        
  unsigned short Video_pid;        
  unsigned short Audio_pid;
  unsigned short TeleText_pid;                     // Teletext PID
  unsigned short PMT_pid;
  unsigned short PCR_pid;
  unsigned short ECM_PID;
  unsigned short SID_pid;
  unsigned short AC3_pid;
  unsigned char TVType;                            //  == 00 PAL ; 11 == NTSC    
  unsigned char ServiceTyp;
  unsigned char CA_ID;
  unsigned short Temp_Audio;
  unsigned short Filteranzahl;
  struct TPIDFilters Filters[ MAX_PID_IDS];        // Vergrößert auf 32 Einträge
  unsigned short CA_Anzahl;
  struct TCA_System82 CA_System[ MAX_CA_SYSTEMS];  // Vergrößert auf 32 Einträge  ( Neues PMT-Parsing ) 
  char CA_Land[ 5];
  unsigned char Merker;
  unsigned short Link_TP;
  unsigned short Link_SID;
  unsigned char Dynamisch;
  char Extern_Buffer[ 16];
} TProgramm82;

struct TTPCatio82 {
  int TPCatAnzahl;
  struct TTPCat TPCat[ 32];
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

void
On_Start( HINSTANCE MDInstance, HWND MDWnd, BOOL Log_Set, int DLL_ID, char *My_Hot_Key, char *Api_Version, int *Keep_me_running);

void
On_Exit( HINSTANCE MDInstance, HWND MDWnd, BOOL Log_Set);

void
On_Send_Dll_ID_Name( char *Name);

void
On_Menu_Select( unsigned int MenuID);

void
On_Channel_Change( struct TProgramm82 CurrentProgramm);

void
On_Hot_Key( void);

void
On_Rec_Play( int Mode);

void
On_Osd_Key( unsigned char Key);

void
On_Filter_Close( unsigned int FilterOffset);

int
On_Key_Down( UINT nChar, UINT nRepCnt, UINT nFlags);

#ifdef __cplusplus
}
#endif

#endif

