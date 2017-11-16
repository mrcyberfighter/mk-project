.. Copyright (c)  2016,2017  Brüggemann Eddie.
   Permission is granted to copy, distribute and/or modify this document
   under the terms of the GNU Free Documentation License, Version 1.3
   or any later version published by the Free Software Foundation;
   with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
   A copy of the license is included in the section entitled "GNU
   Free Documentation License".

====================
About **mk-project**
====================

:author: Eddie Brüggemann <mrcyberfighter@gmail.com>

:documenter: Eddie Brüggemann <mrcyberfighter@gmail.com>

.. sectionauthor:: Brüggemann Eddie <mailto:mrcyberfighter@gmail.com>

A word from the author
++++++++++++++++++++++

I must recognize to write a program which **generates** and **parse** *severals files* is **painfull** in the **C** *programming language*.

But I hope *that the community will adopt this usefull tool...*

.. Which I will use starting every new project with,

.. because I use a :abbr:`I.T.E (Integrated Terminals Editor)` editor named `it-edit <http://www.open-source-projects.net/IT-Edit/IT-Edit_presentation.html>`_,

.. so I have a terminal on my sidebar (with another otherwere) and I now the *targets* (I'm not an :abbr:`I.D.E (Integrated Development Environment)` **zombie**).

I dislike :abbr:`I.D.E (Integrated Development Environment)`'s because their advantages is their weak point:

  They let you make forget everything once you have configurate their interface.

  Even how to build your program (i.e. The command line to build your program, you know it ?).

*I use the commandline everyday* and by doing a **good compromise** between **automating task** and doesn't forget **how the command works**.

Is issue **mk-project**...

The adding of the ``Edit terminals`` is suppose for :program:`ed`, :program:`vi`, :program:`emacs`, etc users.

And the :abbr:`G.U.I (Graphical User Interface)` :program:`make` targets launching can be extend :ref:`like explain in the presentation <futur-of-mk-project>`.

**Finally**: I hope you will join us to make **mk-project** support more and more programming languages.

:note: I have put all my *savoir-faire* in this project for you and the entire community.

Dependencies
++++++++++++

Libraries
---------

+ ``libgtk-3-dev``

+ ``libvte-2.91-dev``

+ ``libxml2-dev``

Main program
------------

+ The :program:`make` program.

+ ``coreutils``

Documentation
-------------

+ ``python(3)-sphinx``

+ ``python(3)-docutils``

Debugging
---------

+ ``binutils``

+ ``libc-bin``

+ ``findutils``

+ ``file``

+ ``size``

+ ``hexdump``

:note: Only required if you make usage of them, else the corresponding target won't be available.

Code formatters
---------------

+ ``indent``

+ ``astyle``

+ ``bcpp``

:note: Only required if you make usage of them, else the corresponding target won't be available.

Internationalisation
--------------------

+ ``gettext``

:note: Only required if you make usage of them, else the corresponding target won't be available.


Documentation Source
--------------------

+ ``GNU Make manual`` (A very good manual from the GNU manuals serie).

:authors: Stallman, McGrath, Smith.

+ ``C/C++ Compiling`` (A very good book about libraries and machine code investigation).

:author: Milan Stevanovic.

+  ``Writing efficient C code``.

:author: Jonas Skeppstedt (author of the compiler :ref:`ISO Certicated and Validated <iso-conform-compiler-list>` :program:`lmpcc`).

.. _iso-conform-compiler-list:

ISO (ISO/IEC 9899:19999, C language) conform compiler list
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

+ EDG C/C++ 3.0.1, december 2002.

+ lmpcc C99 Compiler for Linux / PowerPC 1.3, july 2003.

+ Sun studio 9, May 2004.

+ IBM VAC 6.0.0.8, October 2004.

:note: No :program:`gcc` neither :program:`clang` are certified to be fully compliant with it.

THANKS
------

  + Dennis M Ritchie, for UNIX and C.

  + Richard Stallman, for gcc and the F.S.F movement.

  + Ken Tompson, for UNIX.

  + Linus Tornvalds, for Linux and git.

  + And to every worker for a better world...

Author final word:
------------------

I use :program:`mk-project` since the version **1.0** (spring *2016*) for my programs.

Accompanier with my `terminals integrated editor it-edit <http://www.open-source-projects.net/it-edit/it-edit>`_,

where I type my targets instead of using vim or any other :abbr:`T.U.I Terminal User Interface`.

I must confess that I do not use all the targets provided by mk-project.

My most used targets are:

.. code-block:: bash

  $ make

  $ make -B

  $ make exec

  $ make fdebug

  $ make gdb

  $ make search-pattern argv="pattern"

  ...
