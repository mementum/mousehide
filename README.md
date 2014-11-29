mousehide
=========
This is an old 2009 project originally hosted on
Google Code and which got permissionless
binary distributed several times via Internet
forums.

The only change is the update to the premake4.lua
to bring it up to date and make it compatible with
the mingw-w64 toolchain used in Cygwin.

It served me as an example on how to once again
create a dll with the mingw(w64) toolchain to get
started with another small project.

It's probably of no use today, since I sincerely
doubt anyone is still using Alt-Dvb today, which
in spite of 1 or 2 unsolved bugs was by far the
best ever application to watch satellite TV using
a PC.

Original Description
====================
For me and a couple of friends, Alt-Dvb 2.2 will only
hide the mouse in Fullscreen mode ... "once". This
means that simply touching the table where the mouse
is quietly sitting may bring the mouse cursor back online
and this time it will remain visible in the middle of the
screen forever unless you move from the sofa to place the
mouse cursor off-screen.

This little MDAPI compatible plug-in will actually place
the mouse cursor offscreen after an inactivity period when
Alt-Dvb 2.2 runs in fullscreen mode