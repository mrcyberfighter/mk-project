.. Copyright (c)  2016,2017  Brüggemann Eddie.
   Permission is granted to copy, distribute and/or modify this document
   under the terms of the GNU Free Documentation License, Version 1.3
   or any later version published by the Free Software Foundation;
   with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
   A copy of the license is included in the section entitled "GNU
   Free Documentation License".


.. _mk-project-documentation:

+++++++++++++++++++++++++++++++++++
:program:`mk-project` documentation
+++++++++++++++++++++++++++++++++++

.. sectionauthor:: Brüggemann Eddie <mailto:mrcyberfighter@gmail.com>

------------
Introduction
------------

:program:`mk-project` currently support only one single documentation generator: :program:`sphinx`.

sphinx was first design to generate official python documentation but time has past and :program:`sphinx`

has become very popular at first by the python community.

Without any particular extension (like autodoc) :program:`sphinx` is based on the `R.e.S.T Re Structured Text <http://docutils.sourceforge.net/docs/user/rst/quickref.html>`_ language but `Mardown <http://markdown-syntax.html>`_ can be used through modifying the :file:`conf.py` file.

The Rest language is an easy markup language as like markdown but it is standardized (Markdown not) and can be extented what sphinx does.

:note: Some `R.e.S.T Re Structured Text <http://docutils.sourceforge.net/docs/user/rst/quickref.html>`_ extension permit to build **C** andf **C++** documentation without using any extension.

----------------------
You are a sphinx user:
----------------------

So everything is are right.

------------------------
You aren't a sphinx user
------------------------

Let me convince you to adopt sphinx by learning the easy markup `R.e.S.T Re Structured Text <http://docutils.sourceforge.net/docs/user/rst/quickref.html>`_ or `Markdown <http://markdown-syntax.html>`_  language.

For generating documentation in many formats, :program:`mk-project` generate make targets from the make output according which sphinx extension are installed on your system.

Per exemple currently on my system.

.. code-block:: bash

  make sphinx-html # to make standalone HTML files

  make sphinx-dirhtml # to make HTML files named index.html in directories

  make sphinx-singlehtml # to make a single large HTML file

  make sphinx-pickle # to make pickle files

  make sphinx-json # to make JSON files

  make sphinx-htmlhelp # to make HTML files and an HTML help project

  make sphinx-qthelp # to make HTML files and a qthelp project

  make sphinx-applehelp # to make an Apple Help Book

  make sphinx-devhelp # to make HTML files and a Devhelp project

  make sphinx-epub # to make an epub

  make sphinx-epub3 # to make an epub3

  make sphinx-latex # to make LaTeX files, you can set PAPER=a4 or PAPER=letter

  make sphinx-latexpdf # to make LaTeX files and run them through pdflatex

  make sphinx-latexpdfja # to make LaTeX files and run them through platex/dvipdfmx

  make sphinx-lualatexpdf # to make LaTeX files and run them through lualatex

  make sphinx-xelatexpdf # to make LaTeX files and run them through xelatex

  make sphinx-text # to make text files

  make sphinx-man # to make manual pages

  make sphinx-texinfo # to make Texinfo files

  make sphinx-info # to make Texinfo files and run them through makeinfo

  make sphinx-gettext # to make PO message catalogs

  make sphinx-changes # to make an overview of all changed/added/deprecated items

  make sphinx-xml # to make Docutils-native XML files

  make sphinx-pseudoxml # to make pseudoxml-XML files for display purposes

  make sphinx-linkcheck # to check all external links for integrity

  make sphinx-doctest # to run all doctests embedded in the documentation (if enabled)

  make sphinx-coverage # to run coverage check of the documentation (if enabled)

.. # Output on my mk-project :program:`make` ``help`` target.

+ Many themes are available.

+ Many contrib packages are available for extending sphinx in many ways.

+ The :abbr:`rdt (Read The Doc)` theme provide a web service, format the output in his theme and provide the documentation downloadable in many format.

---------------------------------------------
:program:`mk-project` documentation visualize
---------------------------------------------

:program:`mk-project` permit you to visualize all the output files in different manners:

:program:`mk-project` will search severals documentation viewer programs on your installation.

.. note::

  * The :program:`make` varibale :makevar:`${BROWSER}` will link to your :program:`browser`.

  * The :program:`make` variable :makevar:`{INFO}` will link to the :program:`info` program.

  * The :program:`make` variable :makevar:`{MAN}` will link to the :program:`man` program.

  * The :program:`make` variable :makevar:`{EPUB}` will link to your :program:`epub` viewer (:program:`fbreader` or :program:`okular`) if available.

  * The :program:`make` variable :makevar:`{PDF}` will link to your :program:`pdf` viewer if available.

  :note: If :program:`mk-project` doesn't find a binary for viewing a file it will use the :program:`xdg-open` program as fallback.

.. warning::

  The ``sphinx-show-\*`` targets are set *arbitrary*

  **as best as I can**

  because their is either **no** way to know into which ``sub-folder`` the **documentation** will be **generate**

  and **nor** the **filename the documentation will have**...

  Simply **trust me** or correct it **yourself** if necessary.

---------------------------
:program:`mk-project` slots
---------------------------

Always remember that you can write some :program:`make` targets into the :program:`mk-project` Makefile.

To ease you the documentation generating process and so :ref:`extend mk-project <mk-project-hackme>`.

Per example by the first version of mk-project, it use a mix of:

* The ``pandoc`` package.

* The ``python(3)-docutils`` and the ``rst2pdf`` packages.

* The ``texinfo`` and ``texlive`` packages.

To provide ReST, Markdown and texinfo documentation generation but Only one page per output format.

**but** I used :program:`sphinx` to write the documentation of the version 1.0 of :program:`mk-project`

with some few self -builded targets like this:

.. code-block:: make

  ################################################################################

  # sphinx slot.

  .PHONY: sphinx-singlehtml sphinx-html sphinx-htmlhelp sphinx-epub sphinx-info sphinx-man

  # sphinx Makefile singlehtml target link.
  sphinx-singlehtml:
  	cd sphinx_doc ; ${MAKE} singlehtml ;

  # sphinx Makefile html target link.
  sphinx-html:
  	cd sphinx_doc ; ${MAKE} html ;

  # sphinx Makefile epub target link.
  sphinx-epub:
  	cd sphinx_doc ; ${MAKE} epub ;

  # sphinx Makefile info target link.
  sphinx-info:
  	cd sphinx_doc ; ${MAKE} info ;

  # sphinx Makefile man target link.
  sphinx-man:
  	cd sphinx_doc ; ${MAKE} man ;

  # sphinx Makefile doctest target link.
  sphinx-doctest:
  	cd sphinx_doc ; ${MAKE} doctest


  # sphinx builded files showing targets.
  .PHONY: sphinx-show-singlehtml sphinx-show-html sphinx-show-epub sphinx-show-info sphinx-show-man

  sphinx-show-singlehtml:
  	cd ./sphinx_doc/build/singlehtml ; ${BROWSER} index.html ;

  sphinx-show-html:
  	cd ./sphinx_doc/build/html ; ${BROWSER} index.html ;

  sphinx-show-epub:
  	cd ./sphinx_doc/build/epub  ; ${EPUB} *.epub ;

  sphinx-show-info:
  	cd ./sphinx_doc/build/texinfo ; ${INFO} -f *.info ;

  sphinx-show-man:
  	cd ./sphinx_doc/build/man ; ${MAN} -f ${PRGNAME}.${MAN_LEVEL} ;

  # sphinx clean target.
  sphinx-clean:
  	cd sphinx_doc ; cd build ; rm -R * ;

  ################################################################################

-----------
``rst2man``
-----------

If you get the program :program:`rst2man` installed on your system,

:program:`mk-project` will create a folder named ``rst2man`` into the project tree into

which you will find a file ``${PRGNAME}.rst`` to edit a man-page with :program:`rst2man`.

:warning: Because the man-page is often apart from the documentation.

