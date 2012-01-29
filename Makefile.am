## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po
GKIU_LIBS = -lgdbm

gkiudocdir = ${prefix}/doc/gkiu
gkiudoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(gkiudoc_DATA) \
	$(INTLTOOL_FILES)\
	logo.png

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(gkiudocdir)