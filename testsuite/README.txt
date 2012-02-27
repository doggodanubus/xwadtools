"make test" or "sh runtests.sh" runs all the tests. Do this after the
binaries are built. Run "make" in the top-level xwadtools directory;
it's not necessary to "make install".

Right now, this needs a UNIX-ey environment. Should work on Linux,
FreeBSD, Windows + Cygwin (or Msys). I plan to support running the tests
in a native windows environment (cmd.exe and no UNIX stuff), but it's
low-priority right now.

This uses the FreeDoom IWAD. If you don't have it, get it here:
http://www.nongnu.org/freedoom/

You want freedoom-0.7, direct link:
http://download.savannah.gnu.org/releases/freedoom/freedoom-iwad/freedoom-iwad-0.7.zip

(link subject to change without notice, use the main site if it 404s).

Extract the zip file and copy the included doom2.wad to the testsuite/
directory as freedoom.wad.

