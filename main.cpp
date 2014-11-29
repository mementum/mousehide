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

 AltDvb 2.2 does only hide the mouse once after going in Fullscreen mode,
 leaving the mouse on if it's moved afterwards, forcing the user to hide the
 mouse

 The application will move the pointer offscreen if AltDvb is running in
 fullscreen mode

*/

#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#include <windows.h>

// Entry Point for a DLL

BOOL
WINAPI
DllMain( HINSTANCE p_hInstanceDLL, DWORD p_fdwReason, LPVOID p_lpvReserved)
{
  return TRUE;
}
