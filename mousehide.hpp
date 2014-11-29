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

#ifndef __MOUSEHIDE_HPP__
#define __MOUSEHIDE_HPP__

#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#include <windows.h>

DWORD
WINAPI
LoopEntryPoint( LPVOID lpParam);

bool
rectWidthGreaterOrEqualThan( RECT &p_rect1, RECT &p_rect2);

bool
rectHeightGreaterOrEqualThan( RECT &p_rect1, RECT &p_rect2);

bool
rectIsTopLeftFromRect( RECT &p_rect1, RECT &p_rect2);

bool
IsWindowFullScreenInMonitorRect( HWND p_winHandle, RECT &p_monitorRect);

struct ThreadParams_t
{
  HANDLE m_handleFinishEvent;
  HWND m_winHandleDvbApp;
};

#endif
