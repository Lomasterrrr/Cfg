#
# C Shell with process control; VM/UNIX VAX Makefile
# Bill Joy UC Berkeley; Jim Kulp IIASA, Austria
#
# With an input editor, command completion, etc. and ported to all sorts of
# things; Paul Placeway, CIS Dept., Ohio State University
#
SHELL=/bin/sh
ENVCMD=/usr/bin/env
VERSION=6.24.00
BUILD=tcsh$(EXEEXT)
INSTALL=/usr/bin/install -c
INSTALL_DATA=${INSTALL} -m 644
INSTALL_PROGRAM=${INSTALL}
MKDIR_P?=$(INSTALL) -d

srcdir=.

################################################################
## CFLAGS.  For various -D things, see config.h
################################################################
#
# These are the default suffixes from .c to .o and -c to get there
# but to use the global optimizer on the mips boxes, see below
#
SUF=o
CF=-c

CPPFLAGS=-I. -I$(srcdir)

LFLAGS=
# hpux lint
#LFLAGS= -Zn10000

# This is set by autoconf:
CFLAGS = -g -O2
# debug:
#CFLAGS= -g
# production:
#CFLAGS= -O
# Broken optimizers....
#CFLAGS=

#CFLAGS= -g -pg -DPROF
#CFLAGS= -O -pg -DPROF

# gcc 1.00-1.37
#CFLAGS= -O -finline-functions -fstrength-reduce

# gcc 1.37-1.40
#CFLAGS= -O -fcombine-regs -finline-functions -fstrength-reduce
# add -msoft-float for 68881 machines.

# gcc 2.0
# On the sparc, don't use -O2; it breaks setjmp() and vfork()
#CFLAGS= -O

# gcc-2.1+
#CFLAGS= -O2

# lucid c on suns
#CFLAGS= -O5

# gcc 2.1 on linux
#CFLAGS= -O6 -fomit-frame-pointer

# HP/UX 8.0, 9.0
#CFLAGS= +O3 -Aa

# Ultrix 4.2a
#CFLAGS= -O -Olimit 2000

# Intel Paragon OSF/1 with PGI compilers
#CFLAGS= -O -Mnodebug -Mnoperfmon

# DEC Alpha OSF/1
## Normal Optimization
#CFLAGS= -O2 -Olimit 2000
## Full Optimization - may not work
#CFLAGS= -O3 -Olimit 2000
#CF=-j
#SUF=u
#.SUFFIXES: .u

# for silicon graphics (and other mips compilers) -- use the
# global optimizer! (-O3).
# On SGI 4.0+ you need to add -D__STDC__ too.
#CFLAGS= -O3
## Ultrix 4.2a
#CFLAGS= -O3 -Olimit 2000
#CF=-j
#SUF=u
#.SUFFIXES: .u 				## Ultrix and gnu-make need that

# mips systems
# CFLAGS= -O -systype bsd43 -Wf,-XNd5000 -Wf,-XNp6000 -Olimit 2000

# for at&t machines
#CFLAGS= -O -Ksd

# Stardent Titan
#CFLAGS = -O -43

# Stardent Stellar or sunos4 /bin/cc or Solaris2.1 /opt/SUNWspro/bin/cc
#CFLAGS = -O4

# Intergraph clipper CLIX 3.1
#CFLAGS= -w -O2

# Dnix 5.3
#CFLAGS = -O -X7

# Pyramid OS/x
#CFLAGS = -OG

# Multiflow (5M binary... if you choose -O5!)
#CFLAGS = -O5 -sb_trace 0

# DDE Supermax Unix SYSV Rel III.
# CFLAGS= -O3

# SINIX RMx00
#CFLAGS= -O# -D_POSIX_SOURCE# -kansi

# Apollo's with cc [apollo builtins don't work with gcc]
# and apollo should not define __STDC__ if it does not have
# the standard header files. RT's (aos4.3) need that too;
# you might want to skip the -O on the rt's... Not very wise.
# AIX/ESA needs -D_IBMESA on command line (this may disappear by GA)
#DFLAGS=-U__STDC__
#DFLAGS=-D_IBMESA
# On aix2.2.1 we need more compiler space.
#DFLAGS=-Nd4000 -Nn3000
# AU/X 2.0 needs a flag for POSIX (read the config file)
#DFLAGS=-Zp
# Tektronix 4300 running UTek 4.0 (BSD 4.2) needs:
#DFLAGS = -DUTek -DBSD
# VMS_POSIX needs:
#DFLAGS=-D_VMS_POSIX
# Multiflow and PCC compilers don't like void typedefs.
# You may also need -U__STDC__ if you use pcc (i.e. ibmrt aos4.3).
#DFLAGS=-DMULTIFLOW
#DFLAGS=-DPCC
# DELL SVR4
#DFLAGS=-DDELL
#DFLAGS=
#DFLAGS=-D_PATH_TCSHELL='"${DESTBIN}/tcsh"'
## The following is set by autoconf.
DFLAGS = -D_PATH_TCSHELL='"${bindir}/tcsh"'  

################################################################
## LDFLAGS.  Define something here if you need to
################################################################
## This is set by autoconf:
LDFLAGS= 
## The simplest, suitable for all.
#LDFLAGS=
## Stripped. Takes less space on disk.
#LDFLAGS= -s
## Pure executable.  Spares paging over the network for machines with
## local swap but external /usr/local/bin .
#LDFLAGS= -s -n
## Without dynamic linking. (SunOS/cc)
#LDFLAGS= -s -n -Bstatic
## Without dynamic linking. (SunOS/gcc)
#LDFLAGS= -s -n -static
## Stripped, shared text (Unicos)
#LDFLAGS= -Wl,-s,-n
## Link statically. (linux)
#LDFLAGS= -s -static
## Impure executable (linux)
#LDFLAGS= -s -N

################################################################
## SBINLDFLAGS.  Flags to build a tcsh suitable for installation in
##		 in /sbin under Solaris with gcc. See the "tcsh.sbin"
##		 target.
################################################################
SBINLDFLAGS=-Wl,-R/etc/lib,-I/etc/lib/ld.so.1,-ldl,-Bstatic

################################################################
## LIBES.  Pick one, or roll your own.
################################################################
## This is set by autoconf.
LIBES= -ltinfo -lcrypt 
## BSD style things
#LIBES= -ltermcap
## SunOS, HP-UX, pyramid
#LIBES= -ltermcap
## Linux
#LIBES= -ltermcap
## Linux with PW_SHADOW
#LIBES= -ltermcap -lshadow
## Tek XD88/10 (UTekV) with PW_SHADOW
#LIBES= -ltermcap -lsec
## Motorola MPC (sysV88) with PW_SHADOW
#LIBES= -ltermcap -lsec
## Mach
#LIBES= -ltermcap -lcs
## DEC osf1 on the alpha
#LIBES= -ltermcap -lbsd
## Intel paragon
#LIBES= -ltermcap -lbsd
## Clipper intergraph
#LIBES= -ltermcap -lbsd
## Sequent's Dynix
#LIBES= -ltermcap -lseq
## Ultrix with Enhanced Security
#LIBES= -ltermcap -lauth
## Xenix 386 style things
#LIBES= -ltermcap -ldir -lx
## masscomp RTU6.0
#LIBES= -ltermcap -lndir -lsocket -ljobs
## AIX on the rt
#LIBES= -lcurses
## TitanOS on the stellar
#LIBES= -lcurses
## SysV4 w/o BSDTIMES or Solaris 2
#LIBES= -ltermlib -lsocket -lnsl
## SysV3 w/o networking
#LIBES= -lcurses
## SysV3 with networking
#LIBES= -lcurses -lnet
## SysV2 w/o networking & dirlib
#LIBES= -lcurses -ldir
## SysV2 with networking & dirlib
#LIBES= -lcurses -ldir -lnet
## AIX on the IBM 370 or rs6000 or ps2
#LIBES= -lcurses -lbsd
## ETA10
#LIBES= -lcurses -lbsd
## Irix3.1 on the SGI-IRIS4D
#LIBES= -lcurses -lbsd
## Irix3.3 on the SGI-IRIS4D w/o yp
#LIBES= -lcurses -lbsd -lc_s
## Irix3.3 on the SGI-IRIS4D with yp
#LIBES= -lcurses -lsun -lbsd -lc_s
## Amdahl UTS 2.1
#LIBES= -lcurses -lsocket -lbsd
## Intel's hypercube.
#LIBES= -lcurses -lsocket
## ns32000 based Opus.
#LIBES= -lcurses -lsocket
## ISC 2.2 without networking
#LIBES= -lcurses -lcposix
## ISC 2.2 with networking
#LIBES= -lcposix -lc_s -lcurses -linet
## ISC 2.0.2 without networking
#LIBES= -lcurses -lsec -lc_s
## ISC 2.0.2 with networking
#LIBES= -lcurses -linet -lsec -lc_s
## SCO SysVR3.2v2.0
#LIBES= -lcurses -lintl -lcrypt
## SCO+ODT1.1
#LIBES= -lcurses -lintl -lsocket -lcrypt
## A/UX 2.0
#LIBES= -lposix -ltermcap
## A/UX 3.0
#LIBES= -lposix -ltermcap -lc_s
## att3b1 cc w/o shared lib & dirlib
#LIBES= -ldirent -lcurses
## att3b1 gcc with shared lib & dirlib
#LIBES= -shlib -ldirent -lcurses
## SysV4 with BSDTIMES
#LIBES= -ltermlib -lsocket -lnsl -lc /usr/ucblib/libucb.a
## Stardent Vistra
#LIBES= -lcurses -lnsl -lsocket -lc /usr/ucblib/libucb.a
## emx under OS/2
#LIBES= -ltermc
## Minix, VMS_POSIX
#LIBES=
## Multiflow
#LIBES= -ltermcap -lcrypt
## NetBSD
#LIBES= -ltermcap -lcrypt
## DDE Supermax
#LIBES= -lcurses

################################################################
## EXTRAFLAGS and EXTRALIBS
################################################################
# Compiling for AFS with kerberos authentication
#AFSLIBDIR = /usr/afsws/lib
#AFSDEF = -DAFS -I/usr/afsws/include
#AFS33LIB = -laudit
#
#Solaris and HPUX require the BSD libraries with AFS.
#We use -lc to use only what we require.
# Solaris
#AFSAUXLIB = -lsocket -lnsl -lc -lucb
# HPUX   
#AFSAUXLIB = -lc -lBSD
#
#AFSLIB = -L$(AFSLIBDIR) -L$(AFSLIBDIR)/afs -lkauth -lprot -lubik\
#         -lauth -lrxkad -lsys -ldes -lrx -llwp -lcom_err\
#         $(AFSLIBDIR)/afs/util.a $(AFS33LIB) $(AFSAUXLIB)
#

EXTRAFLAGS =  $(AFSDEF)
EXTRALIBS =  $(AFSLIB) 

# The difficult choice of a c-compiler...
# First, you should try your own c-compiler. 
# Gcc -traditional is also a safe choice. 
# If you think that you have good include files try gcc -Wall...
# If you want to take out -traditional, make sure that your sys/ioctl.h
# is fixed correctly, otherwise you'll be stopped for tty input, or you
# will lose the editor and job control.

# This is for setting your C preprocessor value.
# This is set by autoconf.
CPP = gcc -E
# The -B tells gcc to use /bin/ld. This is to avoid using the gnu ld, which
# on the suns does not know how to make dynamically linked binaries.
# This is set by autoconf.
CC = gcc
#CC= gcc -Wall -Wmissing-prototypes -Wstrict-prototypes -Wpointer-arith -Werror -Wmissing-declarations -Wredundant-decls -Wnested-externs -Wsign-compare -Wcast-qual -Wreturn-type -Wswitch -Wshadow -Wwrite-strings -Wextra -Wcast-qual -Wwrite-strings -Wold-style-definition -Wuninitialized -Wpointer-sign
# -Wconversion -Wformat=2 -ansi -pedantic
#CC=	gcc -Wall -pipe -B/bin/
# Generate code for Intel 486 (linux)
#CC=	gcc -m486 -pipe -Wall
# BSDI2.1 w/ shared libraries
#CC=	shlicc
#CC=	cc
#CC=	occ
#CC=	acc
#CC=	pcc
#CC=	hc -w
# For VMS/POSIX
#CC=	c89
# For suns, w/o gcc and SVR4
#CC=	/bin/cc
# FPS 500 (+FPX) with Sun C compiler
#CC=	/usr/lib/sun.compile/cc
# Solaris 2.1
#CC=	/opt/SUNWspro/bin/cc
# Alliant fx2800
#CC=	scc
# for NEC SX-4
#CC=	cc	-h0,ansi,novector,float0
#CC=	lcc	-wa 
CC_FOR_GETHOST = $(CC)
ED=	ed
AS=	as
RM=	rm
CXREF=	/usr/ucb/cxref
VGRIND=	csh /usr/ucb/vgrind
CTAGS=	/usr/ucb/ctags
#XSTR= /usr/ucb/xstr
SCCS=	/usr/local/sccs
# Make the multi-max run fast.
PARALLEL=12
# Use Sequent's parallel make
#P=&
P=
prefix=/usr/local
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
datarootdir=${prefix}/share
mandir=${datarootdir}/man
MANSECT=1
DESTBIN=${DESTDIR}${bindir}
DESTMAN=${DESTDIR}${mandir}/man${MANSECT}
# A/UX
# DESTMAN=${DESTDIR}/catman/man${MANSECT}
# Stardent Vistra (SysVR4)
# DESTMAN=${DESTDIR}/usr/share/man/man${MANSECT}
# Amiga unix (SysVR4)
# DESTMAN=/usr/catman/1l
EXEEXT=
FTPAREA=/usr/spool/ftp

BUILD_CATALOGS = yes

ASSRCS=	sh.c sh.dir.c sh.dol.c sh.err.c sh.exec.c sh.char.c \
	sh.exp.c sh.file.c sh.func.c sh.glob.c sh.hist.c sh.init.c \
	sh.lex.c sh.misc.c sh.parse.c sh.print.c sh.proc.c sh.sem.c \
	sh.set.c sh.time.c sh.char.h sh.dir.h sh.proc.h sh.h \
	tw.color.c
PSSRCS= sh.decls.h glob.c glob.h dotlock.c dotlock.h mi.termios.c mi.wait.h mi.varargs.h ma.setp.c \
	vms.termcap.c
SHSRCS= ${ASSRCS} ${PSSRCS}
SHOBJS=	sh.${SUF} sh.dir.${SUF} sh.dol.${SUF} sh.err.${SUF} sh.exec.${SUF} \
	sh.char.${SUF} sh.exp.${SUF} sh.file.${SUF} sh.func.${SUF} \
	sh.glob.${SUF} sh.hist.${SUF} sh.init.${SUF} sh.lex.${SUF} \
	sh.misc.${SUF} sh.parse.${SUF} sh.print.${SUF} sh.proc.${SUF} \
	sh.sem.${SUF} sh.set.${SUF} sh.time.${SUF} glob.${SUF} dotlock.${SUF} \
	mi.termios.${SUF} ma.setp.${SUF} vms.termcap.${SUF}

TWSRCS= tw.decls.h tw.h tw.help.c tw.init.c tw.parse.c tw.spell.c \
	tw.comp.c tw.color.c
TWOBJS=	tw.help.${SUF} tw.init.${SUF} tw.parse.${SUF} tw.spell.${SUF} \
	tw.comp.${SUF} tw.color.${SUF}

EDSRCS= ed.chared.c ed.decls.h ed.defns.c ed.h ed.init.c ed.inputl.c \
	ed.refresh.c ed.screen.c ed.xmap.c ed.term.c ed.term.h
EDOBJS=	ed.chared.${SUF} ed.refresh.${SUF} ed.screen.${SUF} ed.init.${SUF} \
	ed.inputl.${SUF} ed.defns.${SUF} ed.xmap.${SUF} ed.term.${SUF}

TCSRCS= tc.alloc.c tc.bind.c tc.const.c tc.decls.h tc.disc.c \
	tc.func.c tc.nls.c tc.os.c tc.os.h tc.printf.c tc.prompt.c \
	tc.sched.c tc.sig.c tc.sig.h tc.str.c sh.types.h tc.vers.c tc.wait.h \
	tc.who.c tc.h
TCOBJS=	tc.alloc.${SUF} tc.bind.${SUF} tc.const.${SUF} tc.defs.${SUF} \
	tc.disc.${SUF} tc.func.${SUF} tc.nls.${SUF} tc.os.${SUF} tc.printf.${SUF} \
	tc.prompt.${SUF} tc.sched.${SUF} tc.sig.${SUF} tc.str.${SUF} \
	tc.vers.${SUF} tc.who.${SUF} 

PVSRCS= Makefile.std Makefile.vms Makefile.in Makefile.win32
AVSRCS= BUILDING Fixes MAKEDIFFS MAKESHAR NewThings README.md FAQ \
	WishList config_f.h eight-bit.me glob.3 patchlevel.h \
	pathnames.h tcsh.man Ported src.desc Imakefile imake.config \
	complete.tcsh vmsreadme.txt termcap.vms snames.h host.defs \
	gethost.c tcsh.man2html configure.ac configure config.h.in \
	tests/testsuite.at aclocal.m4 dot.login dot.tcshrc
TESTFILES= tests/aliases.at tests/arguments.at tests/commands.at \
	tests/expr.at tests/lexical.at tests/mb-eucjp.at \
	tests/mb-utf8.at tests/noexec.at tests/parenthesis.at tests/syntax.at \
	tests/subst.at tests/variables.at tests/sh.dol.at

VHSRCS=${PVSRCS} ${AVSRCS}

CONFSRCS=config/* 

ALLSRCS=  ${SHSRCS} ${TWSRCS} ${EDSRCS} ${TCSRCS} ${VHSRCS}
DISTSRCS= ${PSSRCS} ${TWSRCS} ${EDSRCS} ${TCSRCS} ${AVSRCS} $(TESTFILES)

OBJS= ${SHOBJS} ${TWOBJS} ${EDOBJS} ${TCOBJS}

all: ${BUILD} catalogs

tcsh$(EXEEXT):$(P) ${OBJS} 
	rm -f tcsh$(EXEEXT) core
	${CC} -o tcsh$(EXEEXT) ${LDFLAGS} ${CFLAGS} ${CPPFLAGS} ${OBJS} ${LIBES} ${EXTRALIBS}

tcsh.sbin:$(P) ${OBJS} 
	rm -f tcsh.sbin core
	${CC} -o tcsh.sbin ${SBINLDFLAGS} ${LDFLAGS} ${CFLAGS} ${CPPFLAGS} ${OBJS} ${LIBES} ${EXTRALIBS}

# Purify
pure:$(P) ${OBJS} 
	rm -f tcsh$(EXEEXT) core
	purify `echo ${CC} | sed -e s,-B/bin/,,` -o tcsh$(EXEEXT) ${LDFLAGS} ${CFLAGS} ${CPPFLAGS} ${OBJS} ${LIBES} ${EXTRALIBS}
# OS/2
#tcsh.exe: tcsh
#	emxbind tcsh

gethost:  gethost.c sh.err.h tc.const.h sh.h
	rm -f gethost
	${CC_FOR_GETHOST} -o gethost ${CPPFLAGS} ${CFLAGS} ${LDFLAGS} $(srcdir)/gethost.c

tc.defs.c:	gethost host.defs
	@rm -f $@.tmp
	@echo "/* Do not edit this file, make creates it */" > $@.tmp
	./gethost $(srcdir)/host.defs >> $@.tmp
	@if [ -f $@ ] && cmp -s $@.tmp $@; then echo $@ unchanged.; rm -f $@.tmp; else mv -f $@.tmp $@; echo $@ recreated.; fi

tcsh.ps: tcsh.man
	rm -f tcsh.ps
	-ptroff -t -man $(srcdir)/tcsh.man > tcsh.ps

.c.${SUF}:
	${CC} ${CF} ${CFLAGS} ${CPPFLAGS} ${DFLAGS} ${EXTRAFLAGS} $<

.SUFFIXES: .s .i

.c.i:
	${CC} -E ${CFLAGS} ${CPPFLAGS} ${DFLAGS} ${EXTRAFLAGS} $< | cat -s > $@

.c.s:
	${CC} -S ${CFLAGS} ${CPPFLAGS} ${DFLAGS} ${EXTRAFLAGS} $<

# _VMS_POSIX #module addition
#.c.${SUF}:
#	@(echo '#module '`echo $< | sed -e 's/\./_/g'`; cat $<) > $*..c
#	@echo ${CC} ${CF} ${CFLAGS} ${CPPFLAGS} ${DFLAGS} ${EXTRAFLAGS} $*.c
#	@${CC} ${CF} ${CFLAGS} ${CPPFLAGS} ${DFLAGS} ${EXTRAFLAGS} $*..c
#	@mv $*..o $*.o
#	@rm -f $*..c


# Don't do any special massaging of C files for sharing of strings!!
# it causes weird segmentation faults on some systems.
#.c.o:
#	${CPP} ${CFLAGS} ${CPPFLAGS} $*.c | ${XSTR} -c -
#	${CC} ${CF} ${CFLAGS} ${CPPFLAGS} x.c 
#	mv -f x.o $*.o
#	rm -f x.c

#ed.init.o: ed.init.c
#	${CPP} ${CFLAGS} ${CPPFLAGS} $*.c | ${XSTR} -c -
#	${CC} -R ${CF} ${CFLAGS} ${CPPFLAGS} x.c 
#	mv -f x.o $*.o
#	rm -f x.c

#strings.o: strings
#	${XSTR}
#	${CC} -c -R xs.c
#	mv -f xs.o strings.o
#	rm -f xs.c

##.DEFAULT:
##	${SCCS} get $<

##.DEFAULT:
##	co $<

ed.defns.h: ed.defns.c
	@rm -f $@.tmp
	@echo '/* Do not edit this file, make creates it. */' > $@.tmp
	@echo '#ifndef _h_ed_defns' >> $@.tmp
	@echo '#define _h_ed_defns' >> $@.tmp
	grep '[FV]_' $(srcdir)/ed.defns.c | grep '^#define' >> $@.tmp
	@echo '#endif /* _h_ed_defns */' >> $@.tmp
	@if [ -f $@ ] && cmp -s $@.tmp $@; then echo $@ unchanged.; rm -f $@.tmp; else mv -f $@.tmp $@; echo $@ recreated.; fi

sh.err.h: sh.err.c
	@rm -f $@.tmp
	@echo '/* Do not edit this file, make creates it. */' > $@.tmp
	@echo '#ifndef _h_sh_err' >> $@.tmp
	@echo '#define _h_sh_err' >> $@.tmp
	grep 'ERR_' $(srcdir)/sh.err.c | grep '^#define' >> $@.tmp
	@echo '#endif /* _h_sh_err */' >> $@.tmp
	@if [ -f $@ ] && cmp -s $@.tmp $@; then echo $@ unchanged.; rm -f $@.tmp; else mv -f $@.tmp $@; echo $@ recreated.; fi

tc.const.h: tc.const.c sh.char.h config.h config_f.h sh.types.h sh.err.h
	@rm -f $@.tmp
	@echo '/* Do not edit this file, make creates it. */' > $@.tmp
	@echo '#ifndef _h_tc_const' >> $@.tmp
	@echo '#define _h_tc_const' >> $@.tmp
	${CPP} $(CPPFLAGS) ${DFLAGS} ${EXTRAFLAGS} -D_h_tc_const\
	    $(srcdir)/tc.const.c | \
	    sed -n -e 's/^\(Char STR[a-zA-Z0-9_]*\) *\[ *\].*/extern \1[];/p' | \
	    LC_COLLATE=C sort >> $@.tmp
	@echo '#endif /* _h_tc_const */' >> $@.tmp
	@if [ -f $@ ] && cmp -s $@.tmp $@; then echo $@ unchanged.; rm -f $@.tmp; else mv -f $@.tmp $@; echo $@ recreated.; fi

$(srcdir)/tests/package.m4: $(srcdir)/configure.ac
	{								   \
	  echo '# Signature of the current package.';			   \
	  echo 'm4_define([AT_PACKAGE_NAME],      [tcsh])';	   \
	  echo 'm4_define([AT_PACKAGE_TARNAME],   [tcsh])';   \
	  echo 'm4_define([AT_PACKAGE_VERSION],   [6.24.00])';   \
	  echo 'm4_define([AT_PACKAGE_STRING],    [tcsh 6.24.00])';	   \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [https://bugs.astron.com/])'; \
	} >$(srcdir)/tests/package.m4

$(srcdir)/tests/testsuite: $(srcdir)/tests/package.m4 $(srcdir)/tests/testsuite.at $(TESTFILES)
	autom4te --language=autotest -I $(srcdir)/tests \
		$(srcdir)/tests/testsuite.at -o $@.tmp
	mv $@.tmp $@

atconfig: config.status
	$(SHELL) ./config.status ./atconfig


csh.prof: ${OBJS} sh.prof.${SUF} mcrt0.${SUF}
	rm -f csh.prof
	ld -X mcrt0.${SUF} ${OBJS} -o csh.prof ${LIBES} -lc

sh.prof.${SUF}:
	cp sh.c sh.prof.c
	${CC} ${CF} ${CFLAGS} ${CPPFLAGS} -DPROF sh.prof.c

lint: tc.const.h ed.defns.h
	lint ${DFLAGS} ${CPPFLAGS} ${LFLAGS} sh*.c tw*.c ed*.c tc.*.c ${LIBES}

alint: tc.const.h ed.defns.h
	alint ${DFLAGS} ${CPPFLAGS} ${LFLAGS} sh*.c tw*.c ed*.c tc.*.c ${LIBES}

print:
	@pr READ_ME
	@pr makefile makefile.*
	@(size -l a.out; size *.${SUF}) | pr -h SIZES
	@${CXREF} sh*.c | pr -h XREF
	@ls -l | pr 
	@pr sh*.h [a-rt-z]*.h sh*.c alloc.c

vprint:
	@pr -l84 READ_ME TODO
	@pr -l84 makefile makefile.*
	@(size -l a.out; size *.${SUF}) | pr -l84 -h SIZES
	@${CXREF} sh*.c | pr -l84 -h XREF
	@ls -l | pr -l84
	@${CXREF} sh*.c | pr -l84 -h XREF
	@pr -l84 sh*.h [a-rt-z]*.h sh*.c alloc.c

vgrind:
	@cp /dev/null index
	@for i in *.h; do vgrind -t -h "C Shell" $$i >/crp/bill/csh/$$i.t; done
	@for i in *.c; do vgrind -t -h "C Shell" $$i >/crp/bill/csh/$$i.t; done
	@vgrind -t -x -h Index index >/crp/bill/csh/index.t

install: tcsh$(EXEEXT) install.catalogs install.man
	$(MKDIR_P) ${DESTBIN}
	$(INSTALL_PROGRAM) tcsh$(EXEEXT) ${DESTBIN}/tcsh$(EXEEXT)

install.catalogs:
	@test "x${BUILD_CATALOGS}" = "xyes" && (cd nls; ${MAKE} install DESTDIR=${DESTDIR}) || exit 0

install.man: tcsh.man
	$(MKDIR_P) ${DESTMAN}
	$(INSTALL_DATA) $(srcdir)/tcsh.man ${DESTMAN}/tcsh.${MANSECT}

# Amiga Unix
#install.man: tcsh.man
#	compress tcsh.man
#	cp tcsh.man.Z ${DESTMAN}/tcsh.Z
#	chmod 444 ${DESTMAN}/tcsh.Z

# Apple A/UX
#install.man: tcsh.man
#	-rm -f ${DESTMAN}/tcsh.${MANSECT}.Z
#	nroff -man tcsh.man | compress > ${DESTMAN}/tcsh.${MANSECT}.Z
#	chmod 444 ${DESTMAN}/tcsh.${MANSECT}.Z

clean: clean.catalogs
	${RM} -f a.out strings x.c xs.c tcsh$(EXEEXT) tcsh.a _MAKE_LOG gethost
	${RM} -f *.${SUF} *.i *.s
	${RM} -f sh.prof.c ed.defns.h tc.const.h sh.err.h tc.defs.c
	${RM} -f tcsh.*.m tcsh.*.cat

clean.catalogs:
	@test "x${BUILD_CATALOGS}" = "xyes" && (cd nls; ${MAKE} clean) || exit 0

veryclean: clean
	${RM} -f Makefile config.h config_p.h nls/Makefile
	${RM} -f config.status config.cache config.log tcsh.ps
	${RM} -f missing
	${RM} -f testsuite.log
	${RM} -rf testsuite.dir
	${RM} -rf autom4te.cache
	${RM} -f *~ #*

distclean: veryclean

cleandir: veryclean

tags:	/tmp
	${CTAGS} sh*.c

tar.Z:
	rm -f tcsh-${VERSION}.tar.Z
	rm -rf tcsh-${VERSION} 
	-mkdir tcsh-${VERSION} tcsh-${VERSION}/config tcsh-${VERSION}/tests
	cp ${ALLSRCS} tcsh-${VERSION}
	cp ${CONFSRCS} tcsh-${VERSION}/config
	tar cf - nls/Makefile nls/?*/set?* | (cd tcsh-${VERSION}; tar xpf -)
	tar cvf - tcsh-${VERSION} | compress > tcsh-${VERSION}.tar.Z
	rm -rf tcsh-${VERSION}

tar.gz:
	rm -f tcsh-${VERSION}.tar.gz
	rm -rf tcsh-${VERSION} 
	-mkdir tcsh-${VERSION} tcsh-${VERSION}/config tcsh-${VERSION}/tests
	cp ${ALLSRCS} tcsh-${VERSION}
	cp ${CONFSRCS} tcsh-${VERSION}/config
	tar cf - nls/Makefile nls/?*/set?* | (cd tcsh-${VERSION}; tar xpf -)
	tar cvf - tcsh-${VERSION} | gzip > tcsh-${VERSION}.tar.gz
	rm -rf tcsh-${VERSION}

shar:
	rm -f tcsh-*.shar
	rm -rf tcsh-${VERSION} 
	-mkdir tcsh-${VERSION} tcsh-${VERSION}/config tcsh-${VERSION}/tests
	cp ${ALLSRCS} tcsh-${VERSION}
	cp ${CONFSRCS} tcsh-${VERSION}/config
	tar cf - nls/Makefile nls/?*/set?* | (cd tcsh-${VERSION}; tar xpf -)
	MAKESHAR -v -n tcsh-${VERSION} tcsh-${VERSION} \
		 tcsh-${VERSION}/?* tcsh-${VERSION}/config/?* \
		 tcsh-${VERSION}/?*/set?*
	rm -rf tcsh-${VERSION}

catalogs:
	@test "x${BUILD_CATALOGS}" = "xyes" && (cd nls; ${MAKE} catalogs) || exit 0

tcsh-${VERSION}.tar.Z:
	rm -rf tcsh-${VERSION} 
	rm -f tcsh-${VERSION}.tar tcsh-${VERSION}.tar.Z DIFFS.[123]
	-mkdir tcsh-${VERSION} tcsh-${VERSION}/tests
	./MAKEDIFFS bsd
	mv DIFFS.1 DIFFS.2 DIFFS.3 tcsh-${VERSION}
	cp ${DISTSRCS} tcsh-${VERSION}
	-mkdir tcsh-${VERSION}/config
	cp ${CONFSRCS} tcsh-${VERSION}/config
	cp Makefile tcsh-${VERSION}/Makefile.new
	tar cf - nls/Makefile nls/?*/set?* | (cd tcsh-${VERSION}; tar xpf -)
	tar cvf - tcsh-${VERSION} | compress > tcsh-${VERSION}.tar.Z
	rm -rf tcsh-${VERSION}

tcsh.tahoe-${VERSION}.tar.Z:
	rm -rf tcsh.tahoe-${VERSION} 
	rm -f tcsh.tahoe-${VERSION}.tar tcsh.tahoe-${VERSION}.tar.Z DIFFS.[123]
	-mkdir tcsh.tahoe-${VERSION}
	./MAKEDIFFS tahoe
	mv DIFFS.1 DIFFS.2 DIFFS.3 tcsh.tahoe-${VERSION}
	cp ${DISTSRCS} tcsh.tahoe-${VERSION}
	-mkdir tcsh.tahoe-${VERSION}/config
	cp ${CONFSRCS} tcsh.tahoe-${VERSION}/config
	cp Makefile tcsh.tahoe-${VERSION}/Makefile.new
	tar cf - nls/Makefile nls/?*/set?* | (cd tcsh-${VERSION}; tar xpf -)
	tar cvf - tcsh.tahoe-${VERSION} | compress > tcsh.tahoe-${VERSION}.tar.Z
	rm -rf tcsh.tahoe-${VERSION}

tcsh.reno-${VERSION}.tar.Z:
	rm -rf tcsh.reno-${VERSION} 
	rm -f tcsh.reno-${VERSION}.tar tcsh.reno-${VERSION}.tar.Z DIFFS.[123]
	-mkdir tcsh.reno-${VERSION}
	./MAKEDIFFS reno
	mv DIFFS.1 DIFFS.2 DIFFS.3 tcsh.reno-${VERSION}
	cp ${DISTSRCS} tcsh.reno-${VERSION}
	-mkdir tcsh.reno-${VERSION}/config
	cp ${CONFSRCS} tcsh.reno-${VERSION}/config
	cp Makefile tcsh.reno-${VERSION}/Makefile.new
	tar cf - nls/Makefile nls/?*/set?* | (cd tcsh-${VERSION}; tar xpf -)
	tar cvf - tcsh.reno-${VERSION} | compress > tcsh.reno-${VERSION}.tar.Z
	rm -rf tcsh.reno-${VERSION}

ftp: tcsh-${VERSION}.tar.Z tcsh.tahoe-${VERSION}.tar.Z
	cp tcsh-${VERSION}.tar.Z tcsh.tahoe-${VERSION}.tar.Z ${FTPAREA}
	cp tcsh.man ${FTPAREA}

autoconfigure: $(srcdir)/configure $(srcdir)/config.h.in

$(srcdir)/configure: $(srcdir)/configure.ac
	cd $(srcdir) && autoconf

$(srcdir)/config.h.in: $(srcdir)/stamp-h.in
$(srcdir)/stamp-h.in: $(srcdir)/configure.ac
	cd $(srcdir) && autoheader
	@echo timestamp > $(srcdir)/stamp-h.in

check test: atconfig $(srcdir)/tests/testsuite
	$(ENVCMD) - \
		USER="$(USER)" \
		$(SHELL) $(srcdir)/tests/testsuite

#
# Dependencies
#
config.h: config_f.h

TCH=tc.h tc.const.h tc.decls.h tc.nls.h tc.os.h tc.sig.h
SHH=sh.h sh.types.h sh.char.h sh.err.h sh.dir.h sh.proc.h pathnames.h \
    sh.decls.h ${TCH}
TWH=tw.h tw.decls.h
EDH=ed.h ed.decls.h

# EDH
EDINC=sh.${SUF} sh.func.${SUF} sh.lex.${SUF} sh.print.${SUF} sh.proc.${SUF} \
      sh.set.${SUF} tc.bind.${SUF} tc.os.${SUF} tc.prompt.${SUF} \
      tc.sched.${SUF} tw.parse.${SUF} tw.color.${SUF}
${EDOBJS} ${EDINC} : ${EDH}

# SHH
${OBJS}: config.h ${SHH}

# TWH
TWINC=ed.chared.${SUF} ed.inputl.${SUF} sh.exec.${SUF} sh.func.${SUF} \
      sh.set.${SUF} tc.func.${SUF} tc.nls.${SUF} tw.color.${SUF}
${TWOBJS} ${TWINC}: ${TWH}

# glob.h
glob.${SUF} sh.glob.${SUF}: glob.h

# dotlock.h
dotlock.${SUF}: dotlock.h

# ed.defns.h
EDDINC=tc.bind.${SUF} tc.func.${SUF} tc.os.${SUF}
${EDOBJS} ${EDDINC}: ed.defns.h

# tc.defs.o
tc.defs.${SUF}:	tc.defs.c sh.h
