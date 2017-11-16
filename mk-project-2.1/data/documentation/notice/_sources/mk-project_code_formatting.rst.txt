.. Copyright (c)  2016,2017  Brüggemann Eddie.
   Permission is granted to copy, distribute and/or modify this document
   under the terms of the GNU Free Documentation License, Version 1.3
   or any later version published by the Free Software Foundation;
   with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
   A copy of the license is included in the section entitled "GNU
   Free Documentation License".

.. _code-formatters:

++++++++++++++++++++++++++++++
**mk-project** code formatters
++++++++++++++++++++++++++++++

.. sectionauthor:: Brüggemann Eddie <mailto:mrcyberfighter@gmail.com>

------------
Introduction
------------

**mk-project** provide severals utilities with many predefined targets for formatting your source code.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
For **C** or **C++** source code:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* :program:`indent`

* :program:`astyle`

* :program:`bcpp`

----------------------------
Using the ``indent`` utility
----------------------------

**mk-project** provide following predefined indent styles:

.. code-block:: bash

  make indent-kr    # Format all source files in the kr style.
  make indent-gnu   # Format all source files in the gnu style.
  make indent-linux # Format all source files in the linux style.
  make indent-orig  # Format all source files in the original style.
  make indent-user  # Format all source files in the user defined style.

  make indent-clean # Remove all formatted files with suffix.

:note: The ``indent-user`` target use the given options during the project configuration for formatting your source code.

.. note::

  By launching any code formatting target **mk-project** will output a copy of all your source files suffixed with the corresponding target name:

  Per example by using the ``indent-kr`` target a file named :file:`main.c` will ouput as :file:`main-kr.c`.

  For overwriting your source files really you must set the :program:`make` variable :makevar:`OVERWRITE` on the value **T**.

  .. code-block:: bash

    $ make indent-kr OVERWRITE=T

----------------------------
Using the ``astyle`` utility
----------------------------

**mk-project** provide following predefined indent styles:

.. code-block:: bash

  make astyle-ansi          # Format all source files in the ansi style.
  make astyle-java          # Format all source files in the java style.
  make astyle-kr            # Format all source files in the kr style.
  make astyle-stroustrup    # Format all source files in the stroustrup style.
  make astyle-whitesmith    # Format all source files in the whitesmith style.
  make astyle-banner        # Format all source files in the banner style.
  make astyle-gnu           # Format all source files in the gnu style.
  make astyle-linux         # Format all source files in the linux style.
  make astyle-horstmann     # Format all source files in the horstmann style.
  make astyle-lisp          # Format all source files in the lisp style.
  make astyle-pico          # Format all source files in the pico style.
  make astyle-python        # Format all source files in the python style.
  make astyle-user          # Format all source files in the user defined style.

  make astyle-clean         # Remove all formatted files with suffix.



:note: The ``astyle-user`` target use the given options during the project configuration for formatting your source code.

.. note::

  By launching any code formatting target **mk-project** will output a copy of all your source files suffixed with the corresponding target name:

  Per example by using the ``astyle-kr`` target a file named :file:`main.c` will ouput as :file:`main-kr.c`.

  For overwriting your source files really you must set the :program:`make` variable :makevar:`OVERWRITE` on the value **T**.

  .. code-block:: bash

    $ make astyle-kr OVERWRITE=T
