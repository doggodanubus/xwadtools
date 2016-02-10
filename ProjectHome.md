This is an updated release of Udo Monk's xwadtools package.<br>
<p>
xwadtools hasn't been maintained since 2001, and was getting difficult to compile on modern systems. Also, about a third of the tools were broken on x86_64 systems (wouldn't compile, or would compile but wouldn't run, or in some cases, would run and produce incorrect results).<br>
<p>
I've taken it upon myself to update xwadtools, and will be maintaining it while my attention span lasts. Any questions, comments, or especially patches should be sent to B. Watson (yalhcru@gmail.com).<br>
<p>
New features:<br>
<p>
- All of André Majorel's patches have been integrated, plus a few from Gentoo, Debian, and/or FreeBSD.<br>
<p>
- All the tools now compile and run correctly on:<br>
<blockquote>x86 and x86_64 Linux<br>
x86 and x86_64 FreeBSD<br>
Windows x86 (with mingw-w64 cross compiler; not tried native build)<br>
<p>
- New tools:<br>
midi3mus, open source replacement for midi2mus<br>
wadwhich, determines which game a random .wad file is for<br>
wanconvgame, attempts to convert levels from one game to another<br>
wadconvgfx, make a PWAD for one game, containing graphics from another<br>
spitwad, really an old tool by John Carmack, newly added to xwadtools<br>
<p>
- Enhancements and fixes for many existing tools. See the ChangeLog for full details.<br>
<p>
- DOS, SCO OpenServer, UnixWare ports no longer maintained. Whether or not this is a feature is debatable. If you need xwadtools for these platforms, use Udo's 20010615 release.<br>
<p>
Planned features:<br>
<p>
- Major code cleanups. Should improve portability.<br>
<p>
- NetBSD, OpenBSD support. Also maybe Mac OS X.<br>
<p>
- Will rewrite xew with a less horrid toolkit. Probably GTK+.<br>