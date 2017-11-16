# Copyright (c)  2016,2017  Brüggemann Eddie.
# Permission is granted to copy, distribute and/or modify this document
# under the terms of the GNU Free Documentation License, Version 1.3
# or any later version published by the Free Software Foundation;
# with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
# A copy of the license is included in the section entitled "GNU
# Free Documentation License".

# This will build an entry into the /Applications folder of MacOSX.

if PLATFORM_DARWIN
install-data-hook:
	- if `test ! -d "../MACOSX/mk-project_app/Contents/MacOS"` ; then $(MKDIR_P) "../MACOSX/mk-project_app/Contents/MacOS" ; fi
	- $(CP) $(DESTDIR)$(bindir)/mk-project ../MACOSX/mk-project_app/Contents/MacOS
	- $(CP) -R ../MACOSX/mk-project_app /Applications/mk-project.app

uninstall-hook:
	- $(RM) -rf /Applications/mk-project.app

endif


