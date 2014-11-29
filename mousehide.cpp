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

bool
rectWidthGreaterOrEqualThan( RECT &p_rect1, RECT &p_rect2)
{
  return( p_rect1.right - p_rect1.left) >= ( p_rect2.right - p_rect2.left);
}

bool
rectHeightGreaterOrEqualThan( RECT &p_rect1, RECT &p_rect2)
{
  return( p_rect1.bottom - p_rect1.top) >= ( p_rect2.bottom - p_rect2.top);
}

bool
rectIsTopLeftFromRect( RECT &p_rect1, RECT &p_rect2)
{
  return ( p_rect1.top <= p_rect2.top) && ( p_rect1.left <= p_rect2.left);
}

bool
IsWindowFullScreenInMonitorRect( HWND p_winHandle, RECT &p_monitorRect)
{
  RECT l_winRect;
  GetWindowRect( p_winHandle, &l_winRect);

  return (
	  rectWidthGreaterOrEqualThan( l_winRect, p_monitorRect)
	  &&
	  rectHeightGreaterOrEqualThan( l_winRect, p_monitorRect)
	  &&
	  rectIsTopLeftFromRect( l_winRect, p_monitorRect)
	  );
}

DWORD
WINAPI
LoopEntryPoint( LPVOID p_lpParam )
{

  ThreadParams_t *l_threadParams = (ThreadParams_t *)p_lpParam;

  HANDLE l_handleFinishEvent = l_threadParams->m_handleFinishEvent;
  HWND l_winHandleDvbApp = l_threadParams->m_winHandleDvbApp;

  size_t l_sleepValueMs = 2000;

  HMONITOR l_monitorHandle = MonitorFromWindow( l_winHandleDvbApp, MONITOR_DEFAULTTONULL);
  if( l_monitorHandle == NULL)
    return 0;

  MONITORINFO l_monitorInfo;
  l_monitorInfo.cbSize = sizeof( l_monitorInfo);

  if( GetMonitorInfo( l_monitorHandle, &l_monitorInfo) == FALSE)
    return 0;

  while( true) {

    DWORD l_retval = WaitForSingleObject( l_handleFinishEvent, l_sleepValueMs); 

    // If the event has been signaled, break out of the loop
    if( l_retval == WAIT_OBJECT_0)
      break;

    // Else, operate on input and mouse

    LASTINPUTINFO l_lastInputInfo;
    l_lastInputInfo.cbSize = sizeof( l_lastInputInfo);
    if( GetLastInputInfo( &l_lastInputInfo) == FALSE)
      continue;

    // Check if sufficient time has elapsed to actually hide the mouse
    if( GetTickCount() < ( l_lastInputInfo.dwTime + l_sleepValueMs))
      continue;

    // Chain of window classes to find if AltDvb is in Fullscreen Mode (or Floating Window mode)
    // TFloatingVideo -> TVideoPanel -> VideoRenderer

    HWND l_winHandleAltDvb = FindWindow( "TFloatingVideo", NULL);
    if( l_winHandleAltDvb == NULL)
      continue;

    HWND l_winHandleVideoPanel = FindWindowEx( l_winHandleAltDvb, NULL, "TVideoPanel", NULL);
    if( l_winHandleVideoPanel == NULL)
      continue;

    HWND l_winHandleVideoRenderer = FindWindowEx( l_winHandleVideoPanel, NULL, "VideoRenderer", NULL);
    if( l_winHandleVideoRenderer == NULL)
      continue;

    if( IsWindowFullScreenInMonitorRect( l_winHandleVideoRenderer, l_monitorInfo.rcMonitor) == FALSE)
      continue;

    SetCursorPos( l_monitorInfo.rcMonitor.right, l_monitorInfo.rcMonitor.bottom);
  }

  return 0;
}
