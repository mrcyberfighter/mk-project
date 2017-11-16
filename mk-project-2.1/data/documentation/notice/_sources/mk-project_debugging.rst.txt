.. Copyright (c)  2016,2017  Brüggemann Eddie.
   Permission is granted to copy, distribute and/or modify this document
   under the terms of the GNU Free Documentation License, Version 1.3
   or any later version published by the Free Software Foundation;
   with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
   A copy of the license is included in the section entitled "GNU
   Free Documentation License".

.. _mk-project-debugging:

=====================================================================
:program:`mk-project` code investigating, debugging and disassembling
=====================================================================

.. sectionauthor:: Brüggemann Eddie <mailto:mrcyberfighter@gmail.com>

++++++++++++
Introduction
++++++++++++

You want to investigate in deep your binary cause of it bugs or simply per curiosity.

:program:`mk-project` provide a lot of targets which will make your investigation easier.

++++++++++++++++++++++++
The ``make info`` target
++++++++++++++++++++++++

The ``make info`` target display simple informations about your program.

Using the :program:`file`, :program:`size`, :command:`ls -s -h` utilities.

---------------------------
The :program:`file` utility
---------------------------

The :program:`file` utility print out the details about any file-type.

So if an executable file is given, the :program:`file` utility will display informations about it.

---------------------------
The :program:`size` utility
---------------------------

The :program:`size` utility print out the byte length of the main binary components:

``.text``, ``.data`` and ``.bss``.

+++++++++++++++++++++++
The ``make gdb`` target
+++++++++++++++++++++++

At first you can use the famous ``GNU/Debugger`` :program:`gdb` for investigating your program,

by simply launching the target ``make gdb``.

This will launch :program:`gdb` in the **./bin** folder where your binary is located

with your program as argument.

.. note:: Given options to :program:`gdb`:

  For given supplementary options to gdb, which will be passed to :program:`gdb` at every target call, edit the :makevar:`GDB_OPTS` variable.

  Else if you want to change the options for a unique call of :program:`gdb`, by using the target.

  Simply set the wanted options into the :makevar:`GDB_OPTS` variable on the command line:

  .. code-block:: bash

    $ make gdb GDB_OPTS="--option value"

+++++++++++++++++++++++
The ``make ldd`` target
+++++++++++++++++++++++

The :program:`ldd` utility show the complete list of dynamic libraries which your program will try to load (i.e. *The load time dependencies*).

.. note:: Given options to :program:`ldd`:

  For given supplementary options to :program:`ldd`, which will be passed to :program:`ldd` at every target call, edit the :makevar:`LDD_OPTS` variable.

  Else if you want to change the options for a unique call of :program:`ldd`, by using the target.

  Simply set the wanted options into the :makevar:`LDD_OPTS` variable on the command line:

  .. code-block:: bash

    $ make ldd LDD_OPTS="--option value"

.. warning:: Limitations of ldd:

  * :program:`ldd` cannot identify the libraries dynamically loaded at runtime using :func:`dlopen`.

  .. code-block:: text

    Be aware, however, that in some circumstances, some version of ldd may attempt to obtain the dependencies informations
    by directly executing the program. Thus, you should never employ ldd on untrusted executables,
    since this may result in the execution of arbitrary code.

  A safer alternative when dealing with untrusted executables is following:

  .. code-block:: bash

    $ objdump -p /path/to/binary | grep NEEDED

    # The same result result can be achieve using the readelf utility.

    $ readelf -d /path/to/binary | grep NEEDED

++++++++++++++++++++++
The ``make nm`` target
++++++++++++++++++++++

The :program:`nm` utility is used to list the symbols of a binary or object file(s).

It can also find the indicated symbol type.


.. note:: Given options to :program:`nm`:

  For given supplementary options to :program:`nm`, which will be passed to :program:`nm` at every target call, edit the :makevar:`NM_OPTS` variable.

  Else if you want to change the options for a unique call of :program:`nm`, by using the target.

  Simply set the wanted options into the :makevar:`NM_OPTS` variable on the command line:

  .. code-block:: bash

    $ make nm NM_OPTS="--option value"

:note: You can give the :makevar:`$(OBJECT)` :program:`make` variable as argument to :program:`nm` instead of the binary.

.. note::

  If the binary contains some **C++** code, the symbols are printed by default in mangled form.

Usage examples:

.. code-block:: bash

  $ nm /path/to/prg

  # List all symbols of prg (a binary or object file(s)).

  $ nm -D /path/to/prg

  # List only the symbols contains into the dynamic section(s) (exported or visible).

  $ nm -C /path/to/prg

  # List symbols in demangled form.

  $ nm -D --no-demangle /path/to/prg

  # List symbols in not demangled form.

  $ nm -u /path/to/prg

  # List undefined symbols.

Look at `The 20 best nm commands <http://www.thegeekstuff.com/2012/03/linux-nm-command>`_

+++++++++++++++++++++++++++
The ``make objdump`` target
+++++++++++++++++++++++++++

:program:`objdump` is one of the most versatile utility program, so it can support about 50 others binary formats other than the ELF format.

.. note:: Given options to :program:`objdump`:

  For given supplementary options to :program:`objdump`, which will be passed to :program:`objdump` at every target call, edit the :makevar:`OBJDUMP_OPTS` variable.

  Else if you want to change the options for a unique call of :program:`objdump`, by using the target.

  Simply set the wanted options into the :makevar:`OBJDUMP_OPTS` variable on the command line:

  .. code-block:: bash

    $ make objdump OBJDUMP_OPTS="--option value"


:note: You can give the :makevar:`$(OBJECT)` :program:`make` variable as argument to :program:`objdump` instead of the binary.

Usage examples:

.. code-block:: bash

  $ objdump -f /path/to/prg

  # Is used to obtain an insight into the object file(s) header.
  # The header provide plenty of informations like
  #
  # * binary type
  # * entry point (The start of the .text section)
  # * etc..

  $ objdump -h /path/to/prg

  # Is used to list the available sections from the prg.

  $ objdump -T /path/to/prg

  # List dynamic symbols only.

  # Is equivalent to running: $ nm -D /path/to/prg

  $ objdump -t /path/to/prg

  # Examines the dynamic section(s).

  $ objdump -R /path/to/prg

  # Examines the relocation section(s).

  $ objdump -S -j <section name> /path/to/prg

  # Provide the hex-dump of the values carried by the given section.

  $ objdump -p /path/to/prg

  # Display informations about the ELF binary segments.


Usage example for code disassembling using :program:`objdump`:

.. code-block:: bash

  $ objdump -d -M intel /path/to/prg

  # Used to disassemble a binary using the Intel syntax.

  $ objdump -d -S -M intel /path/to/prg

  # Like above but interspercing the original source code.

  $ objdump -d -M intel -j <section name> /path/to/prg

  # This only works if the binary is compiled with the -g (debugging) option.

++++++++++++++++++++++++++
The ``make strace`` target
++++++++++++++++++++++++++

The :program:`strace` utility tracks down the **system calls** made by the **process** as well as the **signals** received by the **process**.

.. note:: Given options to :program:`strace`:

  For given supplementary options to strace, which will be passed to :program:`strace` at every target call, edit the :makevar:`STRACE_OPTS` variable.

  Else if you want to change the options for a unique call of :program:`strace`, by using the target.

  Simply set the wanted options into the :makevar:`STRACE_OPTS` variable on the command line:

  .. code-block:: bash

    $ make strace STRACE_OPTS="--option value"


++++++++++++++++++++++++++
The ``make ltrace`` target
++++++++++++++++++++++++++

The :program:`ltrace` utility tracks down the **libraries calls** made by the **process**.

.. note:: Given options to :program:`ltrace`:

  For given supplementary options to ltrace, which will be passed to :program:`ltrace` at every target call, edit the :makevar:`LTRACE_OPTS` variable.

  Else if you want to change the options for a unique call of :program:`ltrace`, by using the target.

  Simply set the wanted options into the :makevar:`LTRACE_OPTS` variable on the command line:

  .. code-block:: bash

    $ make ltrace LTRACE_OPTS="--option value"

+++++++++++++++++++++++++
The ``make strip`` target
+++++++++++++++++++++++++

The :program:`strip` utility can be used to eliminated all the symbols not needed in the process.

.. note:: Given options to :program:`strip`:

  For given supplementary options to strip, which will be passed to :program:`strip` at every target call, edit the :makevar:`STRIP_OPTS` variable.

  Else if you want to change the options for a unique call of :program:`strip`, by using the target.

  Simply set the wanted options into the :makevar:`STRIP_OPTS` variable on the command line:

  .. code-block:: bash

    $ make strip STRIP_OPTS="--option value"

++++++++++++++++
Oprofile targets
++++++++++++++++

The program collection Oprofile is a profiling system for systems running Linux 2.6.31 and greater.

OProfile makes use of the hardware performance  counters  provided  on  Intel,  AMD,  and  other processors.

OProfile can profile a selected program or process or the whole system.

OProfile can also  be used to collect cumulative event counts at the application, process, or system level.

Begin to show at:

  .. code-block:: bash

    $ man Oprofile

    $ ophelp

:program:`ophelp` lists the available performance counter options.

If you give it a symbolic event name, it will return  the  hardware  value (e.g. "ophelp DATA_MEM_REFS").

:note: :program:`mk-project` use the version >= 1.0 of Oprofile.

And the available Oprofile programs are:

* :program:`operf`

* :program:`ocount`

* :program:`opreport`

* :program:`opannotate`

* :program:`oparchive`

* :program:`opgprof`

:program:`mk-project` provides wrapper around this programs except :program:`oparchive`.

Simply remember that operf and :program:`ocount` generate a ``profile_specification``.

And the other are done to interpret the datas.

:warning: You must run this programs as root.

++++++++++++++++
Valgrind targets
++++++++++++++++

If valgrind is present on your system :program:`mk-project` provide you 4 targets for the most common usage of valgrind:

.. code-block:: bash

  make valgrind-memcheck   # Launch the valgrind memcheck tool on your binary.

  make valgrind-cachegrind # Launch the valgrind cachegrind tool on your binary.

  make valgrind-callgrind  # Launch the valgrind callgrind tool on your binary.

  make valgrind-helgrind   # Launch the valgrind helgrind tool on your binary.

For every target you can set at creating the project or changing at reconfiguring your project the wanted options.

.. note::

  Fell free :ref:`to edit the template to set your prefered options in hard coded <mk-project-hackme>`.

  Or set the environment variable :envvar:`$VALGRIND_OPTS`.


++++++++++++++++++++++
Alternative to \*_OPTS
++++++++++++++++++++++

:note: You can **export** :makevar:`*_OPTS` the corresponding variable before launching the :program:`make` target.

++++++++++++++++++++
Documentation Source
++++++++++++++++++++

+ ``GNU Make manual`` (A very good manual from the GNU manuals serie).

:authors: Stallman, McGrath, Smith.

+ ``C/C++ Compiling`` (A very good book about libraries and machine code investigation).

:author: Milan Stevanovic.

         
