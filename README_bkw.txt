This is an updated release of Udo Monk's xwadtools package.

xwadtools hasn't been maintained since 2001, and was getting difficult to
compile on modern systems. Also, about a third of the tools were broken
on x86_64 systems (wouldn't compile, or would compile but wouldn't run,
or in some cases, would run and produce incorrect results).

I've taken it upon myself to update xwadtools, and will be maintaining
it while my attention span lasts. Any questions, comments, or especially
patches should be sent to B. Watson <yalhcru@gmail.com>.

New features:

- All of Andre Amajorel's patches have been integrated, plus a few
  from Gentoo, Debian, and/or FreeBSD.

- All the tools now compile and run correctly on:
  x86 and x86_64 Linux
  x86 and x86_64 FreeBSD
  Windows x86 (with mingw-w64 cross compiler; not tried native build)

- New tools:
  - midi3mus, open source replacement for midi2mus
  - wadwhich, determines which game a random .wad file is for
  - wanconvgame, attempts to convert levels from one game to another
  - wadconvgfx, make a PWAD for one game, containing graphics from another
  - spitwad, really an old tool by John Carmack, newly added to xwadtools

- Enhancements and fixes for many existing tools. See the ChangeLog for
  full details.

- DOS, SCO OpenServer, UnixWare ports no longer maintained. Whether
  or not this is a feature is debatable. If you need xwadtools for these
  platforms, use Udo's 20010615 release.

Planned features:

- Major code cleanups. Should improve portability.

- NetBSD, OpenBSD support. Also maybe Mac OS X.

- Will rewrite xew with a less horrid toolkit. Probably GTK+.
