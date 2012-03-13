#
# Makefile to compile under Linux x86 or x86_64, or similar systems.
# This is the only Makefile being maintained in the -bkw branch.
#

# define for big endian machine like Sun Sparc, the x86 stuff is little endian
# solaris on sparcs:              ENDIAN = -DBIGEND
# linux/solaris on x86 systems:   ENDIAN = 
ENDIAN =

# Define the Operating System here, possible choices are:
#	-DUNIX
#	-DMSDOS (probably broken right now)
OS = -DUNIX

# no for mingw-w64, probably all mingw*
# yes for linux, bsd
HAVE_FNMATCH = yes

ifeq ($(HAVE_FNMATCH),yes)
FNM= -DHAVE_FNMATCH
endif

# Your C compiler. xwadtools-bkw branch only tested with gcc.
CC = gcc
COPTFLAGS = -O2 -fPIC
CFLAGS = '$(FNM) -g -Wall $(COPTFLAGS) $(ENDIAN) $(OS)'

# Your C++ compiler. xwadtools-bkw branch only tested with g++.
# Only reject and listacs are in C++.
CPP = g++
CPPOPTFLAGS = -O2 -fPIC
CPPFLAGS = '-g -Wall $(CPPOPTFLAGS) $(ENDIAN) $(OS)'

# Uncomment these only if you get compile/link errors that mention
# strcasecmp() and strncasecmp(). Also, please send an email
# to yalhcru@gmail.com and let me know what platform you have
# that requires these.
#CFLAGS+=-DNEED_STRCASECMP
#CPPFLAGS+=-DNEED_STRCASECMP
#CFLAGS+=-DNEED_STRNCASECMP
#CPPFLAGS+=-DNEED_STRNCASECMP

# This Makefile is for GNU make... which predefines MAKE.
# Uncomment if you're using some weird make that supports
# GNU-style conditionals, but doesn't define MAKE (I doubt
# such a beast exists...)
#MAKE = make

# Do we have and want to use the XForms library? This only affects
# whether xew is built, as it's the only thing that uses XForms.
XFORMS = no

# Your installation directories. PREFIX gets baked into some of the
# binaries, don't change it between "make" and "make install".
# Use DESTDIR instead.
DESTDIR=
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
SHAREDIR = $(PREFIX)/share/games/xwadtools
MANDIR = $(PREFIX)/share/man
MAN6DIR = $(MANDIR)/man6
DOCDIR = $(PREFIX)/share/doc/xwadtools

# install man pages gzipped or plain?
GZIP_MAN=yes

ifeq ($(GZIP_MAN),yes)
INSTALL_MAN=./install_man_gz $(DESTDIR)$(MAN6DIR)
else
INSTALL_MAN=cp
endif

# Do we have a bsd/gnu style install command?
HAVE_INSTALL=yes

# install binaries stripped? Only matters if HAVE_INSTALL=yes.
# if HAVE_INSTALL != yes, they're never stripped.
STRIP_BINS=yes
ifeq ($(STRIP_BINS),yes)
STRIP_OPT=-s
else
STRIP_OPT=
endif

ifeq ($(HAVE_INSTALL),yes)
INSTALL_BIN=install -m0755 $(STRIP_OPT)
else
INSTALL_BIN=cp
endif

# variables for slackware target
ARCH=i486
VERSION=20120222bkw
BUILD=1
TAG=_bkw
PKGTYPE=tgz
TMP=/tmp
OUTPUT=$(TMP)
PKG=$(TMP)/package-xwadtools

#-----------------------------------------------------------------------------

### cruft starts here
# your local include files and libs, like for xforms
# leave these directories empty for solaris
# the definition of LINCDIR = -I/usr/include will NOT work with gcc
# please specify the full option for example -I/usr/local/include
LINCDIR = -I/usr/local/include
LLIBDIR = -L/usr/local/lib

# If XFORMS is uncommented set up correct X11 path
#
# X11 include directory and X11 directory
# For older solaris systems (< solaris 2.6) this is 
# XINCDIR = -I/usr/openwin/include
# XLIBDIR = -L/usr/openwin/lib
# Since solaris 2.6 X11 is also in /usr/lib and /usr/include.
# Both directories should be 
# buildin defaults for the compiler and there should be no need
# to define the dirs here
# XINCDIR = -I/usr/include
# XLIBDIR = -L/usr/lib
# Indeed the solaris gnu compiler will NOT compile if -I/usr/include
# is defined together with -I/usr/ucbinclude
#
# Solaris < 2.6: use this:
# XINCDIR = -I/usr/openwin/include
# XLIBDIR = -I/usr/openwin/lib
# Solaris >= 2.6: do not define XINCDIR and XLIBDIR
# For linux use the X11R6 directory
XINCDIR = -I/usr/X11R6/include
XLIBDIR = -L/usr/X11R6/lib

# the X11 library. This should be -lX11 for all systems
X11LIB = -lX11

# need socket library to link X11 apps?
SOLIB =

# 20120215 bkw: the curses options only affect "ew" (the non-GUI version
# on xew). Right now, ew will build, but gives a garbled useless display,
# so there's no point in bothering with it until it's fixed.

# Uncomment the next line to use curses.
# USE_CURSES = curses

# Uncomment the next line to use ncurses.
# USE_NCURSES = ncurses

# If USE_CURSES or USE_NCURSES is uncommented, specify the locations for 
# curses
#
# where to find curses and/or ncurses
#CSINCDIR =
#CSLIBDIR =

# These 2 only used for xew:
CCOPT = '$(LINCDIR) $(XINCDIR) $(CSINCDIR)'
LIBOPT = '$(LLIBDIR) $(XLIBDIR) $(CSLIBDIR) $(X11LIB) $(SOLIB)'

### cruft ends here

all:
	cd lib; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd mkwad; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd lswad; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd mktran; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd wadps; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd wadwhat; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd qmus2mid; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd wadtxls; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd bsp; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd idbsp; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd wadlc; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd wadldc; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd wadgc; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd wadext; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd wadtex; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd wadflat; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd wadsprit; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd wadpat; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd wadcat; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd idmultigen; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd raw2ppm; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd raw2sfx; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd reject; $(MAKE) CPP=$(CPP) CPPFLAGS=$(CPPFLAGS)
	cd warm; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd slige; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS) LIBDIR=$(SHAREDIR)
	cd pal2c; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd mkxppal; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd mkgipal; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd mkpopal; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd mkqmap; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd dmpsmu/source; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd swantbls; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd acc; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS) LIBDIR=$(SHAREDIR)
ifeq ($(XFORMS),yes)
	cd xew; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS) CCOPT=$(CCOPT) LIBOPT=$(LIBOPT) $(USE_NCURSES) $(USE_CURSES) xforms
endif
ifeq ($(CROSS),1)
	cd deutex; cp Makefile.cross Makefile && $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
else
	cd deutex; ./configure && $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
endif
	cd listacs; $(MAKE) CPP=$(CPP) CPPFLAGS=$(CPPFLAGS)
	cd dm2au; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
ifneq ($(CROSS),1)
	cd trigcalc; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
endif
	cd midi3mus; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd spitwad; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)
	cd doom2to64; $(MAKE) CC=$(CC) CFLAGS=$(CFLAGS)

install:
	-mkdir -p $(DESTDIR)$(SHAREDIR)
	-mkdir -p $(DESTDIR)$(BINDIR)
	-mkdir -p $(DESTDIR)$(MAN6DIR)
	-mkdir -p $(DESTDIR)$(DOCDIR)
	$(INSTALL_MAN) doc/*.6 $(DESTDIR)$(MAN6DIR)
	cp doc/COPYING doc/*.txt README HINTS CREDITS Change* $(DESTDIR)$(DOCDIR)
	cp -r examples $(DESTDIR)$(DOCDIR)
	$(INSTALL_BIN) mkwad/mkwad $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) mkwad/mkwad.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) lswad/lswad $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) lswad/lswad.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) mktran/mktran $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) mktran/mktran.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) wadps/wadps $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) wadps/wadps.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) wadwhat/wadwhat $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) wadwhat/wadwhat.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/wadwhat
	cp wadwhat/*.txt $(DESTDIR)$(DOCDIR)/wadwhat
	$(INSTALL_BIN) qmus2mid/qmus2mid $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) qmus2mid/qmus2mid.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/qmus2mid
	cp qmus2mid/README $(DESTDIR)$(DOCDIR)/qmus2mid
	$(INSTALL_BIN) wadtxls/wadtxls $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) wadtxls/wadtxls.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/wadtxls
	cp wadtxls/Changes.Log wadtxls/README wadtxls/*.sh wadtxls/*.txt $(DESTDIR)$(DOCDIR)/wadtxls
	$(INSTALL_BIN) bsp/bsp $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) bsp/bsp.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/bsp
	cp bsp/*.txt bsp/*.wad $(DESTDIR)$(DOCDIR)/bsp
	$(INSTALL_BIN) idbsp/idbsp $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) idbsp/idbsp.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) idbsp/waddwd $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) idbsp/waddwd.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/idbsp
	cp idbsp/README $(DESTDIR)$(DOCDIR)/idbsp
	$(INSTALL_BIN) wadlc/wadlc $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) wadlc/wadlc.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) wadldc/wadldc $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) wadldc/wadldc.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) wadgc/wadgc $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) wadgc/wadgc.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) wadext/wadext $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) wadext/wadext.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) wadtex/wadtex $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) wadtex/wadtex.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) wadflat/wadflat $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) wadflat/wadflat.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) wadpat/wadpat $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) wadpat/wadpat.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) wadsprit/wadsprit $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) wadsprit/wadsprit.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) wadcat/wadcat $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) wadcat/wadcat.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) idmultigen/idmultigen $(DESTDIR)$(BINDIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/idmultigen
	cp idmultigen/README idmultigen/*.txt $(DESTDIR)$(DOCDIR)/idmultigen
	$(INSTALL_BIN) raw2ppm/raw2ppm $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) raw2ppm/raw2ppm.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) raw2sfx/raw2sfx $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) raw2sfx/raw2sfx.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) reject/wreject $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) reject/wreject.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/wreject
	cp reject/*.txt $(DESTDIR)$(DOCDIR)/wreject
	$(INSTALL_BIN) warm/warm $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) warm/warm.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/warm
	cp warm/*.txt $(DESTDIR)$(DOCDIR)/warm
	$(INSTALL_BIN) slige/slige $(DESTDIR)$(BINDIR)
	cp slige/sl*.sh $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) slige/slige.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/slige
	cp slige/*.txt $(DESTDIR)$(DOCDIR)/slige
	mkdir -p $(DESTDIR)$(SHAREDIR)/slige
	cp slige/*.cfg $(DESTDIR)$(SHAREDIR)/slige
	$(INSTALL_BIN) pal2c/pal2c $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) pal2c/pal2c.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) mkxppal/mkxppal $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) mkxppal/mkxppal.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) mkgipal/mkgipal $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) mkgipal/mkgipal.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) mkpopal/mkpopal $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) mkpopal/mkpopal.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) mkqmap/mkqmap $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) mkqmap/mkqmap.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) dmpsmu/source/dmpsmu $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) dmpsmu/dmpsmu.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) dmpsmu/source/dmpsmap $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) dmpsmu/dmpsmap.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/dmpsmu
	cp dmpsmu/Changes.Log dmpsmu/README dmpsmu/dmpsmu26.txt dmpsmu/*.sh $(DESTDIR)$(DOCDIR)/dmpsmu
	$(INSTALL_BIN) swantbls/swantbls $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) swantbls/swantbls.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/swantbls
	cp swantbls/defswani.dat $(DESTDIR)$(DOCDIR)/swantbls
	$(INSTALL_BIN) acc/acc $(DESTDIR)$(BINDIR)/acc-raven
	$(INSTALL_MAN) acc/acc-raven.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/acc
	cp acc/README.TXT $(DESTDIR)$(DOCDIR)/acc/readme.txt
	cp acc/LICENSE.TXT $(DESTDIR)$(DOCDIR)/acc/license.txt
	-mkdir -p $(DESTDIR)$(SHAREDIR)/acc/hexen
	cp acc/common.acs $(DESTDIR)$(SHAREDIR)/acc/hexen
	cp acc/defs.acs $(DESTDIR)$(SHAREDIR)/acc/hexen
	cp acc/specials.acs $(DESTDIR)$(SHAREDIR)/acc/hexen
ifeq ($(XFORMS),yes)
	$(INSTALL_BIN) xew/*ew $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) xew/xew.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/xew
	cp xew/README xew/*.txt xew/*.ini xew/xew_logo.xpm $(DESTDIR)$(DOCDIR)/xew
endif
	$(INSTALL_BIN) deutex/deutex $(DESTDIR)$(BINDIR)
	$(INSTALL_BIN) deutex/deusf $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) deutex/deutex.6 $(DESTDIR)$(MAN6DIR)
ifeq ($(GZIP_MAN),yes)
	ln -s deutex.6.gz $(DESTDIR)$(MAN6DIR)/deusf.6.gz
else
	ln -s deutex.6 $(DESTDIR)$(MAN6DIR)/deusf.6
endif
	mkdir -p $(DESTDIR)$(DOCDIR)/deutex
	cp deutex/C* deutex/L* deutex/R* deutex/T* deutex/V* deutex/*.txt deutex/docsrc/hackers_guide.html $(DESTDIR)$(DOCDIR)/deutex
	$(INSTALL_BIN) listacs/listacs $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) listacs/listacs.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) dm2au/dm2au $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) dm2au/dm2au.6 $(DESTDIR)$(MAN6DIR)
	mkdir -p $(DESTDIR)$(DOCDIR)/dm2au
	cp dm2au/README $(DESTDIR)$(DOCDIR)/dm2au
	$(INSTALL_BIN) trigcalc/trigcalc $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) trigcalc/trigcalc.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) midi3mus/midi3mus $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) midi3mus/midi3mus.6 $(DESTDIR)$(MAN6DIR)
	$(INSTALL_BIN) spitwad/spitwad $(DESTDIR)$(BINDIR)
	$(INSTALL_MAN) spitwad/spitwad.6 $(DESTDIR)$(MAN6DIR)
	cp mergewad/mergewad.pl $(DESTDIR)$(BINDIR)/mergewad
	chmod 0755 $(DESTDIR)$(BINDIR)/mergewad
	mkdir -p $(DESTDIR)$(DOCDIR)/mergewad
	cp mergewad/mergewad.txt $(DESTDIR)$(DOCDIR)/mergewad
	sed "s,_SHAREDIR_,$(SHAREDIR),g" tkwadcad/tkwadcad > $(DESTDIR)$(BINDIR)/tkwadcad
	chmod 0755 $(DESTDIR)$(BINDIR)/tkwadcad
	sed "s,_SHAREDIR_,$(SHAREDIR),g" tkwadcad/tkwadcad-extract-iwads > $(DESTDIR)$(BINDIR)/tkwadcad-extract-iwads
	chmod 0755 $(DESTDIR)$(BINDIR)/tkwadcad-extract-iwads
	mkdir -p $(DESTDIR)$(SHAREDIR)/tkwadcad
	cp -r tkwadcad/doom tkwadcad/doom2 tkwadcad/hexen tkwadcad/lib tkwadcad/scripts tkwadcad/*.lst $(DESTDIR)$(SHAREDIR)/tkwadcad
	sed "s,_SHAREDIR_,$(SHAREDIR),g" tkwadcad/tkwadcad.6 > $(DESTDIR)$(MAN6DIR)/tkwadcad.6
	sed "s,_SHAREDIR_,$(SHAREDIR),g" tkwadcad/tkwadcad-extract-iwads.6 > $(DESTDIR)$(MAN6DIR)/tkwadcad-extract-iwads.6
	mkdir -p $(DESTDIR)$(DOCDIR)/tkwadcad
	cp tkwadcad/INSTALL tkwadcad/README tkwadcad/manual/tkwadcad.ps $(DESTDIR)$(DOCDIR)/tkwadcad
	cp wadwhich/wadwhich $(DESTDIR)$(BINDIR)
	chmod 0755 $(DESTDIR)$(BINDIR)/wadwhich
	$(INSTALL_MAN) wadwhich/wadwhich.6 $(DESTDIR)$(MAN6DIR)
	sed "s,_SHAREDIR_,$(SHAREDIR),g" wadconvgame/wadconvgame > $(DESTDIR)$(BINDIR)/wadconvgame
	chmod 0755 $(DESTDIR)$(BINDIR)/wadconvgame
	mkdir -p $(DESTDIR)$(SHAREDIR)/wadconvgame
	cp wadconvgame/*.wcgmap $(DESTDIR)$(SHAREDIR)/wadconvgame
	sed "s,_SHAREDIR_,$(SHAREDIR),g" wadconvgfx/wadconvgfx > $(DESTDIR)$(BINDIR)/wadconvgfx
	chmod 0755 $(DESTDIR)$(BINDIR)/wadconvgfx
	sed "s,_SHAREDIR_,$(SHAREDIR),g" wadconvgame/wadconvgame.6 > $(DESTDIR)$(MAN6DIR)/wadconvgame.6
	sed "s,_SHAREDIR_,$(SHAREDIR),g" wadconvgfx/wadconvgfx.6 > $(DESTDIR)$(MAN6DIR)/wadconvgfx.6
ifeq ($(GZIP_MAN),yes)
	gzip $(DESTDIR)$(MAN6DIR)/wadconvgame.6 $(DESTDIR)$(MAN6DIR)/wadconvgfx.6 \
	$(DESTDIR)$(MAN6DIR)/tkwadcad.6 $(DESTDIR)$(MAN6DIR)/tkwadcad-extract-iwads.6
endif

clean:
	cd lib; $(MAKE) clean
	cd mkwad; $(MAKE) clean
	cd lswad; $(MAKE) clean
	cd mktran; $(MAKE) clean
	cd wadps; $(MAKE) clean
	cd wadwhat; $(MAKE) clean
	cd qmus2mid; $(MAKE) clean
	cd wadtxls; $(MAKE) clean
	cd bsp; $(MAKE) clean
	cd idbsp; $(MAKE) clean
	cd wadlc; $(MAKE) clean
	cd wadldc; $(MAKE) clean
	cd wadgc; $(MAKE) clean
	cd wadext; $(MAKE) clean
	cd wadtex; $(MAKE) clean
	cd wadflat; $(MAKE) clean
	cd wadsprit; $(MAKE) clean
	cd wadpat; $(MAKE) clean
	cd wadcat; $(MAKE) clean
	cd idmultigen; $(MAKE) clean
	cd raw2ppm; $(MAKE) clean
	cd raw2sfx; $(MAKE) clean
	cd reject; $(MAKE) clean
	cd warm; $(MAKE) clean
	cd slige; $(MAKE) clean
	cd pal2c; $(MAKE) clean
	cd mkxppal; $(MAKE) clean
	cd mkgipal; $(MAKE) clean
	cd mkpopal; $(MAKE) clean
	cd mkqmap; $(MAKE) clean
	cd dmpsmu/source; $(MAKE) clean
	cd swantbls; $(MAKE) clean
	cd acc; $(MAKE) clean
	cd xew; $(MAKE) clean
	cd deutex; $(MAKE) clean || true
	cd listacs; $(MAKE) clean
	cd dm2au; $(MAKE) clean
	cd trigcalc; $(MAKE) clean
	cd midi3mus; $(MAKE) clean
	cd spitwad; $(MAKE) clean
	cd testsuite; $(MAKE) clean

crosswin: clean
	$(MAKE) PREFIX='C:\\xwadtools' CROSS=1 CC=/opt/mingw-w64-win32/bin/i686-w64-mingw32-gcc CPP=/opt/mingw-w64-win32/bin/i686-w64-mingw32-g++ AR="/opt/mingw-w64-win32/bin/i686-w64-mingw32-ar -ru" COPTFLAGS="-O2 -Wall" CPPOPTFLAGS="-O2 -Wall" HAVE_FNMATCH=no

crosszip: crosswin
	rm -rf xwadtools-win32
	$(MAKE) -i install CROSS=1 PREFIX=/ DESTDIR=$(shell pwd)/xwadtools-win32 STRIP_BINS=no GZIP_MAN=no MANDIR=/
	for i in $$( find xwadtools-win32/bin -type f |xargs file | grep PE|cut -d: -f1 ); do mv $$i $$i.exe; /opt/mingw-w64-win32/bin/i686-w64-mingw32-strip $$i.exe ; done
	mv xwadtools-win32/bin/wadconvgame xwadtools-win32/bin/wadconvgame.pl
	mv xwadtools-win32/bin/wadconvgfx xwadtools-win32/bin/wadconvgfx.sh
	mv xwadtools-win32/bin/mergewad xwadtools-win32/bin/mergewad.pl
	cp README_windows.txt xwadtools-win32/README.txt
	mkdir -p xwadtools-win32/html
	( cd xwadtools-win32/man6 ; for i in *.6; do man2html $$i|grep -v ^Content-type: |sed 's,.*localhost/cgi-bin.*,<hr>,' > ../html/$$i.html; done )
	rm -rf xwadtools-win32/man6
	( cd xwadtools-win32/ ; zip -r ../xwadtools-win32-$(VERSION).zip . )

slackware:
	rm -rf $(PKG)
	mkdir -p $(PKG)/install
	$(MAKE) clean
	$(MAKE) PREFIX=/usr COPTFLAGS="-O2 -fPIC" CPPOPTFLAGS="-O2 -fPIC"
	$(MAKE) install PREFIX=/usr DESTDIR=$(PKG) MANDIR=/usr/man DOCDIR=/usr/doc/xwadtools-$(VERSION)
	cat doc/slack-desc > $(PKG)/install/slack-desc
	cd $(PKG) && \
	/sbin/makepkg -c n -l y $(OUTPUT)/xwadtools-$(VERSION)-$(ARCH)-$(BUILD)$(TAG).$(PKGTYPE)

.PHONY: install
