## Process this file with automake to produce Makefile.in

uidir = $(datadir)/gkiu/ui
ui_DATA = \
	uilogin.glade\
	logo.png \
	icon.png

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(GKIU_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gkiu

gkiu_SOURCES = \
	main.c\
	uilogin.c \
	uilogin.h \
	config.c \
	config.h \
	i18n.h \
	keyring.h \
	keyring.c \
	chatlog.c \
	chatlog.h

gkiu_LDFLAGS = \
	-Wl,--export-dynamic

gkiu_LDADD = @GKIU_LIBS@

EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/gkiu
