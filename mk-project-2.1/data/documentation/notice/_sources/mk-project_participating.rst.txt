.. Copyright (c)  2016,2017  Brüggemann Eddie.
   Permission is granted to copy, distribute and/or modify this document
   under the terms of the GNU Free Documentation License, Version 1.3
   or any later version published by the Free Software Foundation;
   with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
   A copy of the license is included in the section entitled "GNU
   Free Documentation License".

.. _mk-project-participating:

==========================================
:program:`mk-project` contributing advices
==========================================

.. sectionauthor:: Brüggemann Eddie <mailto:mrcyberfighter@gmail.com>

--------------
mk-project zen
--------------

  mk-project zen is simple:

  .. code-block:: text

        The minimum work for the user.

        The maximum configuration possiblities.

        + Minimum informations asking to the user, maximum deduced.

        + Maximum possibilities, with a minimum informations and binaries.

        Bring the maximum with the minimum.

        ! No package is obligatory except the coreutils
          and them needed by the programming language.

---------------
How contibute ?
---------------

  Write a project for a programming language which isn't done, or enhance one.

  Write some useful :program:`make` targets for any purpose you want.

  Write :program:`make` targets forn your well know documentation generators, for :program:`mk-project`.

  Every help is welcome, thanks.

~~~~~~~~~~~~~~~~~~~~~~~~~~
For writing a new project:
~~~~~~~~~~~~~~~~~~~~~~~~~~

  1. Simply fork the project.

  2. Make a folder named ``lang_mk-project`` (per example:
     perl_mk-project).

  3. Put your stuff inside this folder.

  4. And ask for merging.

  After your submission your project will be a mimimum tested and they is no matter of refusement only enhancement.

~~~~~~~~
Makefile
~~~~~~~~

  You can take the included makefiles (``./.SubMakefiles/*.mk``)

  To put it into your project, this is highly recommanded, **don't reinvent the wheel**.

  We want targets for:

  -  Executing the source.

  -  debugging the source.

  -  profiling the source.

  -  And what you want else...

~~~~~~~~~
Scripting
~~~~~~~~~

  We script into **bash** or **python** (the script must be compatible with **python2** and **python3**).

  Or if your project is about a scripting language you can use this language.

  :warning: Think to modify the script ``prepend_license.py`` to adapt the comment sign from your language

  .. code-block:: text

    It's easy even if you don't know python or

    in the worse case i will do this for you.

  Scripts are set into the ``./.scripts`` folder.

~~~~~~~~
Becoming
~~~~~~~~

  If you create a **Makefile** project you become a **coauthor** of :program:`mk-project`

  If you enhance a project you become a **contributor** of :program:`mk-project`

  So if you submit a project for your well know language(s),

  you will take first the benefit to get a **Project done** for **your programming language**.

  And the proudness to contribute to :program:`mk-project`

  :note: I will ensure the updating of the GUI at every new project adding.

~~~~~
NOTES
~~~~~

  If you write the Makefile for your language, think at writing a minimal example project who writes

  ``hello world welcome to mk-project``

  on ``stdout``.

  You can enhance your project with everything you want like the debugging definition in the C/C++ language,

  and write entire module(s) for the project purpose.

--------
Makefile
--------

~~~~~~~~
BINARIES
~~~~~~~~

  -  Verify the presence of the binary using the function
     **BINARY_EXIST**.

  -  **UPPERCASE** the binary variable name for no confusion.

     .. code-block:: make


         BINARY = ${call BINARY_EXIST, binary}

  -  test if binary installed with:

     .. code-block:: make


           # Compare the ${BINARY} variable with an empty string.
           ifneq (${BINARY}, )
           # do work...
           endif

  :note: Binaries test are in file ``./.SubMakefiles/binary_checks.mk``

~~~~~~~~~
VARIABLES
~~~~~~~~~

  -  Make the same for configuration:

     -  use **T** for **TRUE**

     -  use **F** for **FALSE**

     .. code-block:: make


           # No comment on following line and remove trailing spaces.
           OVERWRITE = T

           # Compare the ${OVERWRITE} variable with T (don't insert  a space).
           ifeq (${OVERWRITE},T)
           # Do work...
           else
           # Do work...
           endif

     The configuration options set or select by the user must be at the
     top of the Makefile,

     with a default value.

     And you must inform me about in the goal to update the GUI properly.

  -  Use the assigments operators cleverly:

    .. code-block:: make


         # define var     value  # Value definition (used for multiline).
         # define var =   value  # indirect. (the value change at the next assignment for the final variable value.)
         # define var :=  value  # direct.   (the value doesn't change at the next assignment for the final variable value.)
         # define var ::= value  # retro and inter compatibility with other make tools.
         # define var +=  value  # increment assignment operator.
         # define var ?=  value  # shell expansion operator.

  -  Use the increment operator ( **+=** ) cleverly so that the user can
     define the variable on the command-line.

    .. code-block:: make


         USE_TABS += -t

    Or **not**:

    .. code-block:: make


         override MY_VAR = value

      #

  :note: Take care by inserting comments some settings doesn't support comments on the same line as the variable.

~~~~~
Files
~~~~~

  You can verify if a file exist or if it's generated by using the function **FILE_EXIST**

  .. code-block:: make

    MY_FILE = ${call FILE_EXIST, /path/to/my_file.ext}

  It will return **T** (TRUE) or **F** (FALSE) if the file exist or not.

~~~~~~~~~~~~~~~~~~
FILES and FILEPATH
~~~~~~~~~~~~~~~~~~

  -  First define all path relativ, included Makefiles are at the same position as the main Makefile.

  -  Define a variable for the **FILEPATH** and for the **FILE**.

     .. code-block:: make


           MY_FILEPATH = ./filepath/...

           MY_FILE = ${MY_FILEPATH}/my_file.txt

     We construct the filepath relativ to the main Makefile: (./Makefile)

  :note: Filepath are defined in file ``./.SubMakefiles/path.mk``

  -  You can (not obligatory) put the extension in a variable, if this
     make sens.

     .. code-block:: make


           EXT_TYPE = .type

           MY_FILE = ${MY_FILEPATH}/${FILE}${EXT_TYPE}

  -  You can use the make function **FILE_EXIST** to verify the presence
     of a file.

     .. code-block:: make


           MY_FILE = ${call FILE_EXIST, my_file}

  :note: The included Makefiles are correctly named and end in the extension \*.mk so that an editor can reconize them.

  :note: The included Makefiles are set in the SubMakefiles folder.

~~~~~~~~~
LIBRARIES
~~~~~~~~~

  Today most of the libraries use the program :program:`pkg-config` which you can use to auto-detect the

  presence of a library.

  By using the **PKG_CONFIG_EXIST** function.

  .. code-block:: make

    HAS_LIB_PC =  ${call PKG_CONFIG_EXIST, thelibpc}

  It will return **T** (TRUE) or **F** (FALSE) in relationship of the presence of a \*.pc file for ``thelibpc``.  





~~~~~~~
TARGETS
~~~~~~~

  If you need to compose some targets names from more than a word, separate them by:

  -  A **'-'** (*minus*) if it's a **user-target**.

  -  A **'_'** (*underscore*) if it's an **intern_target**.

     Which can be put together with others intern targets to form a **user-target**.

  :note: Don't forget the ``.PHONY:`` definition if the target has no depdending targets.

~~~~~~~
ADVICES
~~~~~~~

  **IMPORTANT:** make doesn't support trailing spaces, so strip them.

  You can use the following command

  .. code-block:: bash


        $ sed -i 's/[[:space:]]$//' filepath

---------------
code formatters
---------------


  We can make usages of following utilities, for code formatting in severals languages:

~~~
 C
~~~

  + :program:`indent` (checked).

  + :program:`astyle` (checked).

  + :program:`bcpp` (checked).

  + :program:`uncrustify` (not check, help me !).

~~~~~
 C++
~~~~~

  + :program:`indent` (checked).

  + :program:`astyle` (checked).

  + :program:`bcpp` (checked).

  + :program:`uncrustify` (not check, help me !).


:note: Must check if we can use this scripts by the :program:`universalindentgui` authors or the tools author(s).

~~~~
HTML
~~~~

  + :program:`tidy` (not checked).

~~~
CSS
~~~

  + :program:`csstidy` (not checked).

~~~~~~~~~
Javascipt
~~~~~~~~~

  + :program:`JsDecoder.js` (not checked).

:note: Must check if we can use this scripts by the :program:`universalindentgui` authors or the tools author(s).

~~~~
Perl
~~~~

  + :program:`perltidy` (not checked).

~~~
PHP
~~~

  + :program:`phpStylist.php` (not checked).

:note: Must check if we can use this scripts by the :program:`universalindentgui` authors or the tools author(s).

~~~~
Ruby
~~~~

  + :program:`rbeautify.rb` (not checked).

  + :program:`ruby_formatter.rb` (not checked).

:note: Must check if we can use this scripts by the :program:`universalindentgui` authors or the tools author(s).

~~~
XML
~~~

  + :program:`xmlindent` (not checked).

~~~~~~~~~~~~~~~~~~~~~~
Using a code formatter
~~~~~~~~~~~~~~~~~~~~~~

  The usage of a code formatter must be user defined controlled so that:

  1. We ask the user if he wants to use it.

  2. We make his usage conditionnaly in the corresponding Makefile: ``./.SubMakefiles/code_formatter.mk``.

    By using a variable named :makevar:`USE_(TOOL NAME UPPERCASE)` given the value:

    * **T** for ``true`` or

    * **F** for ``false``.

    According the user settings.

