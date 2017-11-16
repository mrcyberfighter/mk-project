========================================
Building a :program:`mk-project` project
========================================

.. sectionauthor:: Brüggemann Eddie <mailto:mrcyberfighter@gmail.com>

.. Copyright (c)  2016,2017  Brüggemann Eddie.
   Permission is granted to copy, distribute and/or modify this document
   under the terms of the GNU Free Documentation License, Version 1.3
   or any later version published by the Free Software Foundation;
   with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
   A copy of the license is included in the section entitled "GNU
   Free Documentation License".

++++++++
Starting
++++++++

At first some basic informations will be required:

+ The programming language from the project.

  + **C**

  Or

  + **C++**

+ The project name which will become the program name

  the binary name.

+ The **program version** which, if empty will be arbitrary set to the value ``0.0``.

+ The folder where to generate the project.

  :warning: The folder must be empty (Advice: create it with the folder-chooser at the same time as the project).

+ The license of your project.

  + GPL

  + AGPL

  + LGPL

  + FDL

  + Apache 2.0 License

  + Clear BSD

  + Free BSD

  + Other


:note: The license files will be copied into the project folder according to your choice of format(s).

* docbook

* epub

* pdf

* latex

* html

* texinfo

* text

+++++++++++++++++++++++++++++++
**C**/**C++** Compiler settings
+++++++++++++++++++++++++++++++

For every entry except the "Compiler entry" you get an aside button which

will permit you to add the *most common settings* **easily**.

+ **Compiler:**

  You can choose a compiler to use, which default to ``cc`` for a **C** project and ``c++`` for **C++**.

  But you can set clang per example or the compiler you want.

  :warning: The exactness of your entry will be checked by compiling a minimal program.

+ **Warnings:**

  You can set the warnings to use.

  .. note::

    The aside button will permit you to insert as warnings the following most common warnings settings:

    + ``-Wall`` (*All warning: sea the documentation of your compiler to see which are enabled*).

    + ``-Wextra`` (*Extra warning: sea the documentation of your compiler to see which are enabled*).

    + ``-Wpedantic`` (*ISO conform: most extension are permitted. sea the documentation of your compiler to see which are enabled*).

    + ``-w`` (*No output warnings*).

    + ``-Werror`` (*A warning is consider as an error*).

  :warning: The field is empty per default.

+ **CFLAGS:**

  You can set the argument to give to the compiler (like -g, -O2,...).

  .. note::

    The aside button provide few flags adding:

    + ``-g``

    + ``-O[0123gsf]``

    + ``-std=``

    + ``-pedantic``

+ **CPPFLAGS:**

  Preprocessor instruction to pass onto the compile command line.

  .. note::

    The aside button permit you to define a definition with a value or without.

+ **LDFLAGS:**

  Dynamic Linker Flags.

  .. note::

    The aside button will permit you to choose the :program:`pkg-config`

    you want to add to your project.

    By listing all the :program:`pkg-config` available on your system.

  :warning: By hand editing, if you use :program:`pkg-config`, use the back-ticks syntax:


  Else this will not work because of the make syntax.

+ **LDLIBS:**

  Dynamic Linker library libraries: per example ``-lm``.

  .. note::

    The aside button will permit you to add the linker of your choice.

    By listing all linker flags available on your system.

+++++
Files
+++++

Here you must set the extension you will use for the source and header files.

Especially for the **C++** language:

+ Source files:

  + *.cpp*

  + *.CPP*

  + *.c++*

  + *.C*

  :warning: **This is very important** because of the compilation automation which will **not work** with the **wrong extension**.

+ Header files:

  + *.h*

  + *.hh*

  + *.H*

  + *.hp*

  + *.hxx*

  + *.hpp*

  + *.HPP*

  + *.h++*

  + *.tcc*

:note: For the **C** language this default to *.c* and *.h*.

+++++++++++++
Disassembling
+++++++++++++

Here you can give the default options to pass to the debugging tools:

+ :program:`nm` options.

+ :program:`gdb` options.

+ :program:`strace` options.

+ :program:`ltrace` options.

+ :program:`objdump` options.

+ :program:`ldd` options.

+ :program:`gprof` options.

:note: For further informations sea the :ref:`mk-project code investigating, debugging and disassembling page <mk-project-debugging>`.

+++++++++
Profiling
+++++++++

-------------------
:program:`Oprofile`
-------------------

:program:`mk-project` use **Oprofile** version >= 1.0 for profiling you code.

You can set the following default options:

+ :program:`operf` options.

+ :program:`ocount` options.

+ :program:`opreport` options.

+ :program:`opannotate` options.

+ :program:`opgprof` options.

-------------------
:program:`Valgrind`
-------------------

:program:`mk-project` provides 4 :program:`valgrind` targets per default:

.. code-block:: bash

  make valgrind-memcheck   # Launch the valgrind memcheck tool on your binary.

  make valgrind-cachegrind # Launch the valgrind cachegrind tool on your binary.

  make valgrind-callgrind  # Launch the valgrind callgrind tool on your binary.

  make valgrind-helgrind   # Launch the valgrind helgrind tool on your binary.

For this :program:`valgrind` targets you can set the options.

:note: You can define more :program:`valgrind` targets by :ref:`editing the template <mk-project-hackme>`.

You can give options to apply to valgrind by setting the environment variable :envvar:`VALGRIND_OPTS`.

**Or** by passing it like this:

.. code-block:: bash

  $ make valgrind-memcheck VALGRIND_MEMCHECK_OPTS=--option=value

  $ make valgrind-cachegrind VALGRIND_CACHEGRIND_OPTS=--option=value

  $ make valgrind-callgrind VALGRIND_CALLGRIND_OPTS=--option=value

  $ make valgrind-helgrind VALGRIND_HELGRIND_OPTS=--option=value

+++++++++++++++++++++++++++++
**C**/**C++** code formatters
+++++++++++++++++++++++++++++

Here you can choose the code formatter(s) you want to use.

+ You can set the options to give to :program:`indent` and to :program:`astyle` for the ``indent-user`` and ``astyle-user`` target if you know this tools.

  :note: But :program:`mk-project` provides a lot of pre-configurated :program:`astyle`, :program:`indent`, :program:`bcpp` targets.

|

+ You can set the ``indentation width`` to use and wether to use tabulation or not during the formatting process.

:note: For further information sea the page: :ref:`mk-project code formatters <code-formatters>`

+++++++++++++
Documentation
+++++++++++++

1. Simply choose to use :ref:`sphinx or not <mk-project-documentation>`.

2. Set the options according to your sphinx version.

3. *Enable*/*Disable* the wanted sphinx extensions.

:sphinx: This will generate a ``Makefile`` and :program:`sphinx` specific targets.

--------
man-page
--------

The man page generating is separated from the documentation because they normally

does not contains the same,

so :program:`mk-project` provides through the :program:`rst2man` tool an option

to build (using the :abbr:`ReST (ReStructured Text)` syntax) and view a man page.

++++++++++++++++++
About informations
++++++++++++++++++

Here you can set some informations about your program.

+ Author(s).

+ Mail address.

+ Program URL.

+ Copyright string.

:note: All this informations will generate some constant definition into the ``./headers/defines.${EXT_HDR}`` file.

+++++++++++++++++++
Others Informations
+++++++++++++++++++

+ Make options: the options to pass to :program:`make` at every call.

+ The bash location (auto-detect).

+ Compression level for the ``pkg-\*`` targets, with which you can build an archive from your project.

+++++++++
Licensing
+++++++++

You can edit a source code files header according to the chosen license.

And add it to every source file with the target:

:makevar:`make prepend-license`.

+++++++++++++++
\*.desktop file
+++++++++++++++

You can build a desktop file with this boilerplate.

++++++++++++++++++++++
Archiving your project
++++++++++++++++++++++

:program:`mk-project` provides many compressed archiving targets:

+ :program:`zip` archive.

+ :program:`tar` archive compressed with :program:`lzma`, :program:`xz`, :program:`gz`, :program:`bz`.

+ :program:`rar` archive.

If the wanted archive program is installed at your site. What is not oblige. 

:note: :program:`mk-project` provides through his :abbr:`G.U.I (Graphical User Interface)` a: :guilabel:`Project --> extract and load` menu item.

+++++++
Summary
+++++++

Last step to complete the generation of your project.

Enjoy the easiness of working with :program:`mk-project` the :abbr:`T.D.E Terminal Development Environment`.

-----------------------
Exporting your settings
-----------------------

You can exporting your settings as a :program:`mk-project` profile.

To load it by the next project because typing all this options can be painful.

You will get the most wanted settings setted like ``nm_options`` per example,

but not all like the program name.

:warning: The file extension will arbitrary set to ``*.mkpp``.


