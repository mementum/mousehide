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

#include "mousehide.hpp"
#include "mdextern.hpp"

HANDLE g_hThread = NULL;
ThreadParams_t g_threadParams;

void
On_Start( HINSTANCE MDInstance, HWND MDWnd, BOOL Log_Set, int DLL_ID, char *My_Hot_Key, char *Api_Version, int *Keep_me_running)
{
  *My_Hot_Key = '\0';
  *Keep_me_running = 0;

  g_threadParams.m_winHandleDvbApp = MDWnd;

  g_threadParams.m_handleFinishEvent = 
    CreateEvent(
		NULL,             // default security attributes
		FALSE,            // auto-reset event
		FALSE,            // false = start non-signaled
		NULL              // name
		);

  DWORD l_dwThreadId;
  g_hThread =
    CreateThread( 
		 NULL,                     // default security attributes
		 0,                        // use default stack size  
		 LoopEntryPoint,           // thread function name
		 (LPVOID)&g_threadParams,  // argument to thread function 
		 0,                        // use default creation flags 
		 &l_dwThreadId             // returns the thread identifier 
		 );   
}

void
On_Exit( HINSTANCE MDInstance, HWND MDWnd, BOOL Log_Set)
{
  SetEvent( g_threadParams.m_handleFinishEvent);

  DWORD l_retval = WaitForSingleObject( g_hThread, 5000);

  // Unless we were signaled by the thread object, we "should" terminate the thread
  if( l_retval != WAIT_OBJECT_0)
    TerminateThread( g_hThread, 0);

  CloseHandle( g_hThread);
  CloseHandle( g_threadParams.m_handleFinishEvent);
}

void
On_Send_Dll_ID_Name( char *Name)
{
  strcpy( Name, "MouseHide");
}

void
On_Menu_Select( unsigned int MenuID)
{
}

void
On_Channel_Change( struct TProgramm82 CurrentProgramm)
{
}

void
On_Hot_Key( void)
{
}

void
On_Rec_Play( int Mode)
{
}

void
On_Osd_Key( unsigned char Key)
{
}

void
On_Filter_Close( unsigned int FilterOffset)
{
}

int
On_Key_Down( UINT nChar, UINT nRepCnt, UINT nFlags)
{
  return 0;
}
