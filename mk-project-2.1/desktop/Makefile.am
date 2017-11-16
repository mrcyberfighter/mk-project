# Copyright (c)  2016,2017  Brüggemann Eddie.
# Permission is granted to copy, distribute and/or modify this document
# under the terms of the GNU Free Documentation License, Version 1.3
# or any later version published by the Free Software Foundation;
# with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
# A copy of the license is included in the section entitled "GNU
# Free Documentation License".

desktopdir  = $(DESTDIR)$(prefix)/share/applications

DESKTOP_NAME = mk.project.mrcyberfighter.desktop

desktop:
	- if `test ! -d "$(desktopdir)"` ; then $(MKDIR_P) "$(desktopdir)" ; fi
	@echo "[Desktop Entry]" > $(desktopdir)/$(DESKTOP_NAME)
	@echo "Name=mk-project" >> $(desktopdir)/$(DESKTOP_NAME)
	@echo "GenericName=make-project" >> $(desktopdir)/$(DESKTOP_NAME)
	@echo "Comment=A tool to ease the development process and a good bridge for the distributing process." >> $(desktopdir)/$(DESKTOP_NAME)
	@echo "Exec=mk-project %u" >> $(desktopdir)/$(DESKTOP_NAME)
	@echo "Icon=$(pkgdatadir)/icons/mk-project_icon.png" >> $(desktopdir)/$(DESKTOP_NAME)
	@echo "Terminal=false" >> $(desktopdir)/$(DESKTOP_NAME)
	@echo "X-MultipleArgs=false" >> $(desktopdir)/$(DESKTOP_NAME)
	@echo "StartupNotify=true" >> $(desktopdir)/$(DESKTOP_NAME)
	@echo "Type=Application" >> $(desktopdir)/$(DESKTOP_NAME)
	@echo "MimeType=application/x-extension-mkp;"  >> $(desktopdir)/$(DESKTOP_NAME)
	@echo "Keywords=Development;Programming;Terminal;TDE;make;"  >> $(desktopdir)/$(DESKTOP_NAME)
	@echo "Categories=Development;IDE;GTK;"  >> $(desktopdir)/$(DESKTOP_NAME)
	echo "desktop file generated at: $(desktopdir)/$(DESKTOP_NAME)"

update-desktop:
if HAVE_XDG_UTILS
	$(XDG_ICON_RESSOURCE) install --context mimetypes --size 16 "$(DESTDIR)$(pkgdatadir)/icons/set/16x16/mk-project_icon.png" "application-x-extension-mkp"
	$(XDG_ICON_RESSOURCE) install --context mimetypes --size 22 "$(DESTDIR)$(pkgdatadir)/icons/set/22x22/mk-project_icon.png" "application-x-extension-mkp"
	- $(XDG_ICON_RESSOURCE) install --context mimetypes --size 24 "$(DESTDIR)$(pkgdatadir)/icons/set/24x24/mk-project_icon.png" "application-x-extension-mkp"
	$(XDG_ICON_RESSOURCE) install --context mimetypes --size 32 "$(DESTDIR)$(pkgdatadir)/icons/set/32x32/mk-project_icon.png" "application-x-extension-mkp"
	- $(XDG_ICON_RESSOURCE) install --context mimetypes --size 36 "$(DESTDIR)$(pkgdatadir)/icons/set/36x36/mk-project_icon.png" "application-x-extension-mkp"
	- $(XDG_ICON_RESSOURCE) install --context mimetypes --size 42 "$(DESTDIR)$(pkgdatadir)/icons/set/42x42/mk-project_icon.png" "application-x-extension-mkp"
	- $(XDG_ICON_RESSOURCE) install --context mimetypes --size 48 "$(DESTDIR)$(pkgdatadir)/icons/set/48x48/mk-project_icon.png" "application-x-extension-mkp"
	$(XDG_ICON_RESSOURCE) install --context mimetypes --size 64 "$(DESTDIR)$(pkgdatadir)/icons/set/64x64/mk-project_icon.png" "application-x-extension-mkp"
	- $(XDG_ICON_RESSOURCE) install --context mimetypes --size 72 "$(DESTDIR)$(pkgdatadir)/icons/set/72x72/mk-project_icon.png" "application-x-extension-mkp"
	- $(XDG_ICON_RESSOURCE) install --context mimetypes --size 96 "$(DESTDIR)$(pkgdatadir)/icons/set/96x96/mk-project_icon.png" "application-x-extension-mkp"
	$(XDG_ICON_RESSOURCE) install --context mimetypes --size 128 "$(DESTDIR)$(pkgdatadir)/icons/set/128x128/mk-project_icon.png" "application-x-extension-mkp"
	- $(XDG_ICON_RESSOURCE) install --context mimetypes --size 192 "$(DESTDIR)$(pkgdatadir)/icons/set/192x192/mk-project_icon.png" "application-x-extension-mkp"
	- $(XDG_ICON_RESSOURCE) install --context mimetypes --size 256 "$(DESTDIR)$(pkgdatadir)/icons/set/256x256/mk-project_icon.png" "application-x-extension-mkp"
	- $(XDG_ICON_RESSOURCE) install --context mimetypes --size 512 "$(DESTDIR)$(pkgdatadir)/icons/set/512x512/mk-project_icon.png" "application-x-extension-mkp"
	$(XDG_ICON_RESSOURCE) install --context apps --size 16 "$(DESTDIR)$(pkgdatadir)/icons/set/16x16/mk-project_icon.png" "mk-project"
	$(XDG_ICON_RESSOURCE) install --context apps --size 22 "$(DESTDIR)$(pkgdatadir)/icons/set/22x22/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) install --context apps --size 24 "$(DESTDIR)$(pkgdatadir)/icons/set/24x24/mk-project_icon.png" "mk-project"
	$(XDG_ICON_RESSOURCE) install --context apps --size 32 "$(DESTDIR)$(pkgdatadir)/icons/set/32x32/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) install --context apps --size 36 "$(DESTDIR)$(pkgdatadir)/icons/set/36x36/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) install --context apps --size 42 "$(DESTDIR)$(pkgdatadir)/icons/set/42x42/mk-project_icon.png" "mk-project"
	$(XDG_ICON_RESSOURCE) install --context apps --size 48 "$(DESTDIR)$(pkgdatadir)/icons/set/48x48/mk-project_icon.png" "mk-project"
	$(XDG_ICON_RESSOURCE) install --context apps --size 64 "$(DESTDIR)$(pkgdatadir)/icons/set/64x64/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) install --context apps --size 72 "$(DESTDIR)$(pkgdatadir)/icons/set/72x72/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) install --context apps --size 96 "$(DESTDIR)$(pkgdatadir)/icons/set/96x96/mk-project_icon.png" "mk-project"
	$(XDG_ICON_RESSOURCE) install --context apps --size 128 "$(DESTDIR)$(pkgdatadir)/icons/set/128x128/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) install --context apps --size 192 "$(DESTDIR)$(pkgdatadir)/icons/set/192x192/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) install --context apps --size 256 "$(DESTDIR)$(pkgdatadir)/icons/set/256x256/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) install --context apps --size 512 "$(DESTDIR)$(pkgdatadir)/icons/set/512x512/mk-project_icon.png" "mk-project"
	$(XDG_ICON_RESSOURCE) forceupdate --mode system
	$(XDG_DESKTOP_MENU) forceupdate --mode system
	- $(XDG_DESKTOP_MENU) install --novendor --mode system "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	- $(XDG_DESKTOP_MENU) forceupdate --mode system
else
if HAVE_DESTOP_FILE_UTILS
	- $(DESKTOP_FILE_INSTALL) --rebuild-mime-info-cache "$(desktopdir)/$(DESKTOP_NAME)"
endif
endif



        
unupdate-desktop:
if HAVE_XDG_UTILS
	$(XDG_ICON_RESSOURCE) uninstall --context apps --size 16 "$(DESTDIR)$(pkgdatadir)/icons/set/16x16/mk-project_icon.png" "mk-project"
	$(XDG_ICON_RESSOURCE) uninstall --context apps --size 22 "$(DESTDIR)$(pkgdatadir)/icons/set/22x22/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) uninstall --context apps --size 24 "$(DESTDIR)$(pkgdatadir)/icons/set/24x24/mk-project_icon.png" "mk-project"
	$(XDG_ICON_RESSOURCE) uninstall --context apps --size 32 "$(DESTDIR)$(pkgdatadir)/icons/set/32x32/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) uninstall --context apps --size 36 "$(DESTDIR)$(pkgdatadir)/icons/set/36x36/mk-project_icon.png" "mk-project"
	$(XDG_ICON_RESSOURCE) uninstall --context apps --size 48 "$(DESTDIR)$(pkgdatadir)/icons/set/48x48/mk-project_icon.png" "mk-project"
	$(XDG_ICON_RESSOURCE) uninstall --context apps --size 64 "$(DESTDIR)$(pkgdatadir)/icons/set/64x64/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) uninstall --context apps --size 72 "$(DESTDIR)$(pkgdatadir)/icons/set/72x72/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) uninstall --context apps --size 96 "$(DESTDIR)$(pkgdatadir)/icons/set/96x96/mk-project_icon.png" "mk-project"
	$(XDG_ICON_RESSOURCE) uninstall --context apps --size 128 "$(DESTDIR)$(pkgdatadir)/icons/set/128x128/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) uninstall --context apps --size 192 "$(DESTDIR)$(pkgdatadir)/icons/set/192x192/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) uninstall --context apps --size 256 "$(DESTDIR)$(pkgdatadir)/icons/set/256x256/mk-project_icon.png" "mk-project"
	- $(XDG_ICON_RESSOURCE) uninstall --context apps --size 512 "$(DESTDIR)$(pkgdatadir)/icons/set/512x512/mk-project_icon.png" "mk-project"
	$(XDG_ICON_RESSOURCE) forceupdate --mode system
	$(XDG_DESKTOP_MENU) forceupdate --mode system
else
if HAVE_DESTOP_FILE_UTILS
	- $(UPDATE_DESKTOP_DATABASE) "$(desktopdir)/$(DESKTOP_NAME)"
endif
endif

install-data-hook:
	- $(MAKE) desktop
	- $(MAKE) update-desktop
	$(CHMOD) -R a+rx "$(DESTDIR)$(pkgdatadir)"
	if `test ! -d "$(DESTDIR)$(pkgdatadir)/configuration"` ; then $(MKDIR_P) "$(DESTDIR)$(pkgdatadir)/configuration" ; fi
	$(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/configuration"
	$(MV) "$(DESTDIR)$(pkgdatadir)/Makefile.mk" "$(DESTDIR)$(pkgdatadir)/Makefile"
	$(MKDIR_P) "$(DESTDIR)$(pkgdatadir)/bin"
	$(MKDIR_P) "$(DESTDIR)$(pkgdatadir)/dist"
	$(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/src"
	$(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/bin"
	$(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/dist"

uninstall-hook:
	- $(MAKE) unupdate-desktop
	- $(RM) -f $(desktopdir)/$(DESKTOP_NAME)
	- $(RM) -R -f "$(DESTDIR)$(pkgdatadir)"
	- $(RM) -R -f "$(DESTDIR)$(docdir)"
