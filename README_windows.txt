This is the README.txt for the Windows binary release of xwadtools-bkw.

Inside the zip file, you'll find a bin directory containing the
executables, and a doc directory with documentation, including HTML
versions of the UNIX man pages.

These executables are provided as-is. They haven't been thoroughly
tested. They were built with a mingw-w64 cross-compiler, running on
Linux and targetting win32 (meaning these are 32-bit exes, not 64-bit).
No extra DLLs are required (this is the main reason for using mingw
rather than cygwin).

Probably you want to put the bin directory in your PATH, and set
DOOMWADDIR in the environment to something like 'C:\DOOM' (or wherever
you store your IWAD files).

The wadconvgame and mergewad tools are Perl scripts, which may or may
not run correctly if you have Perl installed.

tkwadcad is a Tcl/Tk application, which probably isn't worth trying to
get running on Windows (there are many better Doom level editors for
Windows, such as Doom Builder 2).

wadconvgfx is a shell script, which might work OK with bash.exe from
msys or cygwin.

The xew tool isn't built for Windows (it's obsolete even on UNIX, slade3
is a better choice).

If you have trouble reading the documentation, try using something besides
Notepad (some of the text files might be lacking carriage returns).
