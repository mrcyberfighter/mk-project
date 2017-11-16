A C/C++ project with mk-project
===============================

Introduction
------------

The **source** are separated from the dependencies (*Icons*, *Configuration files*, *...*)

Because the dependencies go at distributing into a special folder.

.. code:: make

    $(pkgdatadir)

Expanded to:

``/usr/share/project-name``

``/usr/local/share/project-name``

According the prefix settings (``/usr`` or ``/usr/local`` or anything you want).

--------------

They are and you can create as many as you want in the folder:

``./share/project-name``

--------------

The **source** are separated from the documentation files (*info*, *man*, *html*, ...)...

Because the doc files go, at distributing, into a special folders:

.. code:: make

    $(mandir)

    $(infodir)

    $(docdir)

Source
------

The **source** are compiled into **object files** and then linked to an executable located at ``./bin`` for the sake of a proper compilation.

Headers files
~~~~~~~~~~~~~

Following headers files wil be generated:

-  ``./source/headers/defines.h``

They are some predefined constant and macros but you can add and remove as many as you want.

You can include this file where you want.

--------------

-  ``./source/headers/includes.h``

Contains the included headers.

You can include this file where you want.

--------------

-  ``./source/global_vars.h``

The global variable are proper declared in this file.

You can include this file where global variables were needed.

You must declare the global variables with **extern**.

.. code:: c

    extern const char *name ;

source files
~~~~~~~~~~~~

Following source file are generated:

-  ``./source/main.c``

But you can add as many source files as you want (add them to the make **$(SRC_FILES)** variable).

--------------

-  ``./source/global_vars.c``

The global variables are define in this file and this one will be compiled separately.

You can define as many global variables as you want, the compilation will success.

You must define the global variables without **extern**.

.. code:: c

    const char *name = "mk-project" ;

Adding source files.
^^^^^^^^^^^^^^^^^^^^

Normally you must make a header file for every **source** (*.c*) file.

In the **header** (*.h*) file you must declare the functions as **extern**.

.. code:: c

    extern void print_it(const char *string) ;

So you can use the header file everywhere you want.

--------------

And define them without **extern** in the **source** (*.c*) file.

.. code:: c

    void print_it(const char *string) {

      /** Do work... **/

      return ;

    }

As long as you add the source files path in the **$(SRC\_FILES)** variable.

And the header file path to the **$(HDR\_FILES)** variable.

Everthing will be are right...

The prefix setting.
-------------------

When you build a project with **mk-project** you can work on it locally,
without installing it.

But by distributing the project, **mk-project** provide you a simple
mechanism based on a prefix definition:

By developement
~~~~~~~~~~~~~~~

By developement the prefix it is set to: ``"../"`` so that you can work
locally on your project.

By releasing
~~~~~~~~~~~~

By distributing your project you can simply change the prefix so that
you have to change nothing else that the location of the files.

With adding a preprocessor definition onto the compile commandline:

.. code:: make

      $(COMPILER) -DPREFIX="/usr" ...
   
      or
   
      $(COMPILER) -DPREFIX="/usr/local" ...

And:

Simply copy your **mk-project** project local ``./share`` folder to ``/usr/share/`` or ``/usr/local/share``

and the documentation into the according folder ``$(mandir)``, ``$(docdir)`` or ``${infodir)``.
