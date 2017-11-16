# Copyright (c)  2016,2017  Brüggemann Eddie.
# Permission is granted to copy, distribute and/or modify this document
# under the terms of the GNU Free Documentation License, Version 1.3
# or any later version published by the Free Software Foundation;
# with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
# A copy of the license is included in the section entitled "GNU
# Free Documentation License".

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = mk-project

mk_project_SOURCES =  ./main.c \
                      ./global_vars.c \
                      ./structures_initialize.c \
                      ./cmdline/cmdline.c \
                      ./configuration/configuration_dialog.c \
                      ./configuration/configuration_storing.c \
                      ./GUI/gui_callback.c \
                      ./GUI/message_dialog.c \
                      ./GUI/setup_gui.c \
                      ./make/make_actions.c \
                      ./make/make_menu.c \
                      ./make/make_utils.c \
                      ./project/fmt_files.c \
                      ./project/load_project.c \
                      ./project/new_project.c \
                      ./project/project_functions.c \
                      ./project/reconf_project.c \
                      ./project/project.c \
                      ./terminals/terminals.c \
                      ./terminals/terminals_callback.c \
                      ./xml_utils/xml_getter.c \
                      ./xml_utils/xml_utils.c \
                      ./xml_utils/xml_writer.c \
                      ./terminals/GtkMkTerm.c \
                      ./GUI/GtkSmartMenuItem.c \
                      ./terminals/GtkMkTermTab.c \
                      ./GUI/GtkSmartIconButton.c
             

EXTRA_DIST = ./*.h \
             ./headers/*.h \
             ./headers/structures/*.h \
             ./cmdline/*.h \
             ./configuration/*.h \
             ./GUI/*.h \
             ./make/*.h \
             ./project/*.h \
             ./terminals/*.h \
             ./xml_utils/*.h



mk_project_CPPFLAGS = -DPREFIX=\"$(DESTDIR)$(prefix)\"

WARNS=-Wno-missing-field-initializers -Wno-unused-parameter -Wno-deprecated-declarations

if PLATFORM_DARWIN

mk_project_CFLAGS = $(WARNS) $(GTK_CFLAGS) $(VTE_CFLAGS)  $(XML_CFLAGS) $(GTK_MAC_INTEGRATION_CFLAGS)

mk_project_LDADD = $(GTK_LIBS) $(VTE_LIBS) $(XML_LIBS) $(GTK_MAC_INTEGRATION_LIBS)

else

mk_project_CFLAGS =  $(WARNS) $(GTK_CFLAGS) $(VTE_CFLAGS) $(XML_CPPFLAGS)

mk_project_LDADD = $(GTK_LIBS) $(VTE_LIBS) $(XML_LIBS)       

endif

install-exec-hook:
	if `test ! -d "$(DESTDIR)$(pkgdatadir)/hashing"` ; then $(MKDIR_P) "$(DESTDIR)$(pkgdatadir)/hashing" ; fi
if HAVE_MD5
	echo `$(MD5SUM) $(DESTDIR)$(bindir)/$(PACKAGE)` > "$(DESTDIR)$(pkgdatadir)/hashing/$(PACKAGE).md5"
endif
if HAVE_SHA1
	echo `$(SHA1SUM) $(DESTDIR)$(bindir)/$(PACKAGE)` > "$(DESTDIR)$(pkgdatadir)/hashing/$(PACKAGE).sha1"
endif
if HAVE_SHA256
	echo `$(SHA256SUM) $(DESTDIR)$(bindir)/$(PACKAGE)` > "$(DESTDIR)$(pkgdatadir)/hashing/$(PACKAGE).sha256"
endif
if HAVE_SHA512
	echo `$(SHA512SUM) $(DESTDIR)$(bindir)/$(PACKAGE)` > "$(DESTDIR)$(pkgdatadir)/hashing/$(PACKAGE).sha512"
endif

