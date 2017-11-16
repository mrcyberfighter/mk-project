.. Copyright (c)  2016,2017  Brüggemann Eddie.
   Permission is granted to copy, distribute and/or modify this document
   under the terms of the GNU Free Documentation License, Version 1.3
   or any later version published by the Free Software Foundation;
   with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
   A copy of the license is included in the section entitled "GNU
   Free Documentation License".

=====================
:program:`mk-project`
=====================

:author: Brüggemann Eddie <mrcyberfighter@gmail.com>

:program: mk-project

:version: |version|

:language: C

:release: |today|

.. sectionauthor:: Brüggemann Eddie <mailto:mrcyberfighter@gmail.com>

Presentation
------------

:program:`mk-project` is a **C** and **C++** project builder, with a nice :abbr:`G.U.I (Graphical User Interface)`, which generate at first a big, big do it all, ``Makefile``.

So that you can create a project and keep the tree of your project, which reflect the UNIX file system tree.

:note: :program:`mk-project` does not claim to replace the auto-tools but it is build on the top in the spirit of development instead of distributing.

|

In addition :program:`vim` or others :abbr:`T.U.I (Terminal User Interface)` editors users,

can use the entire program by editing their source files into the :menuselection:`Terminals --> Edit terminal` which is a notebook, you can adding as many terminals you want.

|

Else :program:`mk-project` is a tool done to *ease the development process* of **C** or **C++** programs and a good bridge for the distributing process. Especially with the **autotools**.

:program:`mk-project` is a :abbr:`T.D.E (Terminal Development Environment)` (**T**\erminal **D**\evelopement **E**\nvironment):

  an **utility** used for the **development** of **programs** with many functionalities !

:program:`mk-project` is based on the :program:`make` tool which on his turn, use severals utilities, for providing many features

and so many useful :program:`make` targets.

Callable through a terminal, in preference (or through the :abbr:`G.U.I (Graphical User Interface)` from :program:`mk-project`: :menuselection:`targets --> *`).

|

:program:`mk-project` is an ``Environment`` in the terms of his wide field of ``targets`` which aren't statically at all.

But **dynamically** *configurable*, *changeable* and *self-build-able* and so that the grass becomes greener...

The ``targets`` are short string easy to remember and so you can make work

* your computer, through the terminals

* and mostly your head through **remembering**, **configuring**, **modifying** and **creating** ``targets``.

And not become an :abbr:`I.D.E` (**I**\ntegrated **D**\evelopment **E**\nvironment)  **zombie** thrashing his head and knows !

But a proud well informed programmer which knows exactly how his system and environment works which can easily automate the task using the :program:`make` syntax.

.. _mk-project-hackme:

Hackme
------

You can **edit** the ``Makefile`` by hand at your convenience, of course **!**

.. note::

    But I think It's better for some :ref:`generic targets to include <set_make_help>` them directly

    into the template file(s) you will find at :makevar:`$(pkgdatadir)`: :file:`/usr(/local/share/mk-project/templates/*`

    So that you get it every time you generate a new project.

    :warning: If you do this: you must take care of escaping the '%' with a '%' character : "%%".

    But think to notify the :ref:`developers <developers-contributors>`,

    to inform them about your add-on(s) if you think it's reliable and usable for others.


.. To set where it's the best to fit in.

.. You will surely ask you the question: Of what is made and what make :program:`mk-project` for me.

.. The answers is simply ``all is make in Makefiles``, which will make you *the development easier*.


What provide :program:`mk-project`
----------------------------------

.. note::

  At the time i write this documentation :program:`mk-project` support:

  the **C** and **C++** programming language.

  *"I invite all the community to work together to take in charge more languages..."*

  .. TODO: make a file of the written one.

  :file: :ref:`see this document for participating (You can become from the simple contributor to the entire coauthor). <mk-project-participating>`

+ :program:`mk-project` provide at first a solid base for building a work,

  through a big Makefile, which can be edited manually in respect of the following few conventions:

.. note::

  + Configuration settings are set through the string:

    + **F** For false (disable option).

    + **T** for true (enable option).

  + Some few others variables:

    The variable :makevar:`$(SRC_FILES)` is build from the variable :makevar:`$(SRC_DIR)` which value is always: ``./src``.

      This mean if you want to add files manually (*if you doesn't use the GUI for this task*) to your Makefile,

      do it properly by using the :makevar:`$(SRC_DIR)` variable:

      .. code-block:: bash

        SRC_DIR   = ./src

        SRC_FILES = ${SRC_DIR}/my_file${EXT_SRC} \
                    ${SRC_DIR}/subfolder/my_file${EXT_SRC}

      So you will add file(s) relative to the ``./src`` directory where source file(s) have to reside.

      :note: Otherwise simply use the :abbr:`G.U.I (Graphical User Interface)` for adding file(s) :menuselection:`Project -> Add file(s) to project`.  

+ A building system for your source files.

+ Many tools for machine code investigation:

  From the simple **-g** option setting by a ``GNU-Compiler`` for debbuging with ``gdb``, through **disassemble** the *machine code* files and *executable tracing*, to **profiling** the entire work.

+ For the documentation :program:`mk-project` support :ref:`the sphinx documentation generator <mk-project-documentation>`.

  The :program:`sphinx` documentation ``targets`` support many output formats:

  .. to update

  + **info** files.

  + **man** (manual pages).

  + **HTML**, single **HTML**, and **texi HTML** documentation.

  + **PDF** and **LATEXPDF** files.

  + **XML** files.

  + **LATEX** files.

  + **EPUB** files.

  **And many more** through :program:`sphinx` like: **qthelp**, **applehelp**, **xml**, **json** or **devhelp** per example.


:program:`mk-project` provide a simple :abbr:`G.U.I (Graphical User Interface)` composing of terminals and a menu-bar.

At first you can use the menu items to perform some actions like:

  + Generate a new project: :menuselection:`Project -> New Project`.

    Then you have to configure your project answering some basics questions like:

    * Programming language.

    * Program name

    * Project folder (in which the new project will be generate).

    And some others according to your settings.

  Once the new project is generated you can access to the make targets either through the :program:`mk-project` :abbr:`G.U.I (Graphical User Interface)` menu-bar (*simple click on the wanted target to execute it !*).

  Or from the terminal of :program:`mk-project` or any else terminal at the condition to be in the :file:`Makefile` current folder.

  :note: Simply type :command:`$ make help` to get the list of available targets.

.. _set_make_help:

  .. warning::

    If you add some user-targets, to the :file:`Makefile(s)`, think at adding them to the :command:`$ make help` output.

    So that mk-project can auto-detect your target and list it to add it as menu item to the make targets.

    If you add a bash comment on the same line it will be displayed as tool-tip by overfly the menu items.

    :warning: Simply think to limit your entry at terminal maximal size: 79 characters.

So :program:`mk-project` provide another terminals ordered in tabs which you can add, remove, and configuring.

For purpose of terminals editor users like :program:`vi`, :program:`ed`, :program:`emacs` which can be easily launch an instance their favorite ``terminal editor`` in every tab all that continuing using the :program:`mk-project` *interface*.

Finally you can switch between the single :menuselection:`terminals -> make terminal`   (which should stay in the :file:`Makefile` current folder) and the :menuselection:`terminals -> edit terminals` terminals using the menu radio items.

How :program:`mk-project` works
-------------------------------

:note: The answers is simply ``all is make in Makefiles``, which will make you *the development easier*.

.. Talk about the defines.h and includes.h files and the separated build system when is a good location for talking about it.
.. I think of making a doc page per project.

:program:`mk-project` doesn't claim to replace an **IDE** or others **building tools** but only give you an alternative

which ``you can entirely adapt`` to your requirement.

.. note::

  For being **true** the :program:`make` tool implementation and the way it make you the life easier

  without forgetting your ``TTY Knows`` has impress me so that

  I couldn't develop a good project without it

  or in others words:

  .. code-block:: text

    If the make tool have never exist I would invent it...

.. _developers-contributors:

Author(s)
---------

:Developer: `Brüggemann Eddie <mailto:mrcyberfighter@gmail>`_

:Documenter: `Brüggemann Eddie <mailto:mrcyberfighter@gmail>`_

Contributor(s)
--------------

**Become one !!!**

.. Thanks from everybody using and get interest into mk-project !

.. _futur-of-mk-project:

The future of :program:`mk-project`
-----------------------------------

:program:`mk-project`: ``mic-on`` !!!
+++++++++++++++++++++++++++++++++++++

.. note::

  The idea is to sit in front of the interface of :program:`mk-project` (``microphone on`` **!**),

  writing the *source code* from your last creation:

  And to say ``execute: make exec``, or the target you want...

  The **program** could **react** by *analyzing your voice entry* and **executing the target** !!!

  So that the build is **automate** by (*simple*) **voice recognition**.

  So you can write your **program** with your hands

    and

  **build it** with by emitting a *simple order* so that the *program execute the corresponding target*,

  if recognize...

  **What do you think about it ?**

  :note: We could enhance :program:`mk-project` in the way of Speech recognition...

