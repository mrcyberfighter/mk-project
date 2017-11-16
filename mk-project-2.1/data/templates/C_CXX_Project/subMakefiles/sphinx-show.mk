# No license prefixing, you are free to use the license you want.
#
#

ifeq ($(USE_SPHINX),T)

.PHONY: sphinx-show-texi sphinx-show-man sphinx-show-info

SPHINX_TEXI_FILE = $(PRGNAME).tex

SPHINX_MAN_FILE = $(PRGNAME).1

sphinx-show-texi:
		cd ./doc/build/texinfo ; $(XDG_OPEN) $(SPHINX_TEXI_FILE)

sphinx-show-man:
	cd ./doc/build/man ; $(MAN) -l $(SPHINX_MAN_FILE)

sphinx-show-info:
	cd ./doc/build/texinfo ; $(INFO) -f $(SPHINX_INFO_FILE)

.PHONY: sphinx-show-pdf sphinx-show-latexpdf sphinx-show-latexpdfja

SPHINX_LATEX_PDF_FILE = $(PRGNAME).pdf
sphinx-show-pdf:
		cd doc/build/latex ; $(PDF) $(SPHINX_LATEX_PDF_FILE)

sphinx-showlatexpdf:
		cd doc/build/latex ; $(PDF) $(SPHINX_LATEX_PDF_FILE)

sphinx-show-latexpdfja:
	cd doc/build/latex ; $(PDF) $(SPHINX_LATEX_PDF_FILE)

.PHONY: sphinx-show-html sphinx-show-dirhtml sphinx-show-texinfo

SPHINX_HTML_FILE = index.html

sphinx-show-html:
	cd doc/build/html ; $(BROWSER) $(SPHINX_HTML_FILE)

SPHINX_DIRHTML_FILE = index.html

sphinx-show-dirhtml:
	cd doc/build/dirhtml ; $(BROWSER) $(SPHINX_DIRHTML_FILE)

SPHINX_TEXINFO_FILE = $(PRGNAME).texi

sphinx-show-texinfo:
	cd ./doc/build/texinfo ; $(XDG_OPEN) $(SPHINX_TEXINFO_FILE)

.PHONY: sphinx-show-xml sphinx-show-pseudoxml sphinx-show-plain sphinx-show-pickle sphinx-show-json

SPHINX_XML_FILE = index.html

sphinx-show-xml:
	cd ./doc/build/xml ; $(BROWSER) $(SPHINX_XML_FILE)

SPHINX_PSEUDOXML_FILE = index.pseudoxml

sphinx-show-pseudoxml:
	cd ./doc/build/pseudoxml ; $(BROWSER) $(SPHINX_PSEUDOXML_FILE)

SPHINX_PLAIN_FILE = index.txt

sphinx-show-plain:
	cd ./doc/build/text ; $(XDG_OPEN) $(SPHINX_PLAIN_FILE)

SPHINX_PICKLE_FILE = index.fpickle

sphinx-show-pickle:
	cd ./doc/build∕pickle ; $(XDG_OPEN) $(SPHINX_PICKLE_FILE)


SPHINX_JSON_FILE = index.fjson

sphinx-show-json:
	$(XDG_OPEN) $(SPHINX_JSON_FILE)

.PHONY: sphinx-show-helphtml sphinx-show-qthelp sphinx-show-devhelp

SPHINX_HELPHTML_FILE = index.html

sphinx-show-helphtml:
	cd ./doc/build/htmlhelp ; $(BROWSER) $(SPHINX_HELPHTML_FILE)

SPHINX_QTHELP_FILE = index.html

sphinx-show-qthelp:
	cd ./doc/build/qthelp ; $(BROWSER) $(SPHINX_QTHELP_FILE)

SPHINX_DEVHELP_FILE = index.html

sphinx-show-devhelp:
	cd ./doc/build/devhelp ; $(BROWSER) $(SPHINX_DEVHELP_FILE)

.PHONY: sphinx-show-epub

SPHINX_EPUB_FILE = $(PRGNAME).epub

sphinx-show-epub:
	cd ./doc/build/epub ; $(EPUB) $(SPHINX_EPUB_FILE)

endif
