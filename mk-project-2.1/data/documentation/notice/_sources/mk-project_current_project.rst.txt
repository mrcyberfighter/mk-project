.. Copyright (c)  2016,2017  Brüggemann Eddie.
   Permission is granted to copy, distribute and/or modify this document
   under the terms of the GNU Free Documentation License, Version 1.3
   or any later version published by the Free Software Foundation;
   with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
   A copy of the license is included in the section entitled "GNU
   Free Documentation License".

====================================================
Working on an existing :program:`mk-project` project
====================================================

.. sectionauthor:: Brüggemann Eddie <mailto:mrcyberfighter@gmail.com>

-------------------------------------
Open an :program:`mk-project` project
-------------------------------------

For opening an existing project you can make use of the :file:`*.mkp` file from your project.

+ Either by calling :program:`mk-project` with the :file:`*.mkp` file given as argument:

  .. code-block:: bash

    $ mk-project /path/to/project_folder/prgname.mkp

  Or open the project within :program:`mk-project`'s :abbr:`G.U.I (Graphical User Interface)` (:menuselection:`Projects --> Load project`).

+ By using your file manager:

  Simply click on the :file:`*.mkp` file in the project folder

  **or**

  Opening the :file:`*.mkp` file with your file manager using the ``open with`` option.

  To open the :program:`mk-project` :abbr:`G.U.I (Graphical User Interface)` and loading the entire project.

+ Using the :program:`mk-project` :abbr:`G.U.I (Graphical User Interface)`:

  Use the menu item :menuselection:`Projects --> Load project` and choose the :file:`*.mkp` of interest.

  To load the entire project in the :program:`mk-project` :abbr:`G.U.I (Graphical User Interface)`

All targets will be available according to your settings.

.. note::

  Else you can simply use a terminal to use the :program:`mk-project` projects:

  simply type ``make help`` in the project folder to sea the available targets.

---------------------------------
Reconfiguring an existing project
---------------------------------

Open the :program:`mk-project` :abbr:`G.U.I (Graphical User Interface)` and use the menu item :menuselection:`Projects -> Reconfigure project`

to open the project reconfiguring project interface.

Here you can:

+ **Change** some settings of your project.

+ **Enable** or **disable** some features.

+ **Edit** the Licensing boilerplate to prepend it to all source and header files if you want to do so.

+ **Edit** the desktop file boilerplate.

----------------------------
Adding files to your project
----------------------------

Open an existing project and then use the menu item :menuselection:`Projects -> Add file(s) to project`.

Then select the file(s) you want to add to your project.

.. note:: Take care of the checkbutton in the file chooser !

  + You can choose to add the corresponding *header* file to your project.

    :note: If the header file doesn't exist it will be create.


.. warning:: The file(s) must be in the ``./src`` folder or subfolders from it !

  Take care to organize your project properly so that all source files still in the ``./src`` folder from your project !

  Else you can add the file(s) to your project anyway but this can break your project tree if you rename the project folder.

  :note: It's better to create sub-folders from the ``./src`` folder to organize your project properly !

