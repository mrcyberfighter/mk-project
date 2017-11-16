# No license prefixing, you are free to use the license you want.

########## [START] directory variables [START] #################################

prefix = /usr/local

exec_prefix = $(prefix)

bindir  = $(prefix)/bin

sbindir = $(prefix)/sbin

libexecdir = $(exec_prefix)/libexec

datarootdir = $(prefix)/share

datadir     = $(datarootdir)

sysconfdir = $(prefix)/etc

sharedstatedir = $(prefix)/com

localstatedir = $(prefix)/var

includedir   = $(prefix)/include

oldincludedir = /usr/include

docdir = $(datarootdir)/doc/$(PRGNAME)

infodir = $(datarootdir)/info

htmldir = $(docdir)

dvidir = $(docdir)

pdfdir = $(docdir)

psdir = $(docdir)

libdir  = $(exec_prefix)/lib

lispdir =$(datarootdir)/emacs/site-lisp

localedir = $(datarootdir)/locale

mandir  = $(datarootdir)/man

man1dir = $(mandir)/man1

man2dir = $(mandir)/man2

man3dir = $(mandir)/man3

man4dir = $(mandir)/man4

man5dir = $(mandir)/man5

man6dir = $(mandir)/man6

man7dir = $(mandir)/man7

man7dir = $(mandir)/man8

man9dir = $(mandir)/man9


################################################################################

pkgdatadir      = $(datarootdir)/$(PRGNAME)

pkgincludedir   = $(includedir)/$(PRGNAME)

pkglibdir       = $(libdir)/$(PRGNAME)

pkglibexecdir   = $(libexecdir)/$(PRGNAME)

################################################################################

srcdir  = .

################################################################################

TMP_DIR   = /tmp

LOCALE_DIR = ./share/locale

GETTEXT_BKUP_DIR = ./gettext_backup

DESKTOP_DIR = /usr/share/applications

################################################################################

PREPEND_LICENSE_SCRIPT = ./.scripts/prepend_license.py

################################################################################

BOILERPLATE_PATH = ./.licensing/licensing.tmpl

############# [Start] temporary docbook file [START] ###########################

TMP_DBK_FILE = $(TMP_DIR)/mk-project_doc.dbk

################################################################################

############# [START] Documenation informations [START] ########################

DOC_DIR    = ./doc

SPHINX_OUTPUT_DIR = $(DOC_DIR)/build

RST_DIR    = $(DOC_DIR)/rst

MD_DIR     = $(DOC_DIR)/md

INFO_DIR   = $(DOC_DIR)/info

PDF_DIR    = $(DOC_DIR)/pdf

HTML_DIR   = $(DOC_DIR)/html

HTML5_DIR  = $(DOC_DIR)/html5

TEXT_DIR   = $(DOC_DIR)/text

MAN_DIR    = $(DOC_DIR)/man

ODT_DIR    = $(DOC_DIR)/odt

XML_DIR    = $(DOC_DIR)/xml

LATEX_DIR  = $(DOC_DIR)/latex

EPUB_DIR   = $(DOC_DIR)/epub

ASCIIDOC_DIR  = $(DOC_DIR)/asciidoc

#################### [START] Textinfo files [START] ################################

ifeq ($(USE_SPHINX),T)

SPHINX_TEXI_FILE = $(SPHINX_OUTPUT_DIR)/texinfo/$(PRGNAME).texi

SPHINX_MAN_FILE = $(SPHINX_OUTPUT_DIR)/man/$(PRGNAME).1

SPHINX_INFO_FILE = $(SPHINX_OUTPUT_DIR)/texinfo/$(PRGNAME).info

SPHINX_LATEX_FILE = $(SPHINX_OUTPUT_DIR)/latex/$(PRGNAME).tex

SPHINX_LATEX_PDF_FILE = $(SPHINX_OUTPUT_DIR)/latexpdf/$(PRGNAME).pdf

SPHINX_LATEXPDFJA_FILE = $(SPHINX_OUTPUT_DIR)/latexpdfja/$(PRGNAME).pdf

SPHINX_HTML_FILE = $(SPHINX_OUTPUT_DIR)/html/index.pdf

SPHINX_DIRHTML_FILE = $(SPHINX_OUTPUT_DIR)/dirhtml/index.pdf

SPHINX_SINGLEHTML_FILE = $(SPHINX_OUTPUT_DIR)/singlehtml/index.pdf

SPHINX_TEXINFO_FILE = $(SPHINX_OUTPUT_DIR)/texinfo/$(PRGNAME).texinfo

SPHINX_XML_FILE = $(SPHINX_OUTPUT_DIR)/xml/$(PRGNAME).xml

SPHINX_PSEUDOXML_FILE = $(SPHINX_OUTPUT_DIR)/pseudoxml/$(PRGNAME).xml

SPHINX_PLAIN_FILE = $(SPHINX_OUTPUT_DIR)/text/$(PRGNAME).txt

SPHINX_PICKLE_FILE = $(SPHINX_OUTPUT_DIR)/pickle/index.fpickle

SPHINX_JSON_FILE = $(SPHINX_OUTPUT_DIR)/json/index.json

SPHINX_HELPHTML_FILE = $(SPHINX_OUTPUT_DIR)/htmlhelp/index.html

SPHINX_QTHELP_FILE = $(SPHINX_OUTPUT_DIR)/qthelp/index.html

SPHINX_DEVHELP_FILE = $(SPHINX_OUTPUT_DIR)/devhelp/index.html

SPHINX_EPUB_FILE = $(SPHINX_OUTPUT_DIR)/epub/$(PRGNAME).epub

endif

################################################################################


