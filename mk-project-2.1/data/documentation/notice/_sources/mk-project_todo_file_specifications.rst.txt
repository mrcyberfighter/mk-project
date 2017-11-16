.. Copyright (c)  2016,2017  Brüggemann Eddie.
   Permission is granted to copy, distribute and/or modify this document
   under the terms of the GNU Free Documentation License, Version 1.3
   or any later version published by the Free Software Foundation;
   with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
   A copy of the license is included in the section entitled "GNU
   Free Documentation License".

=====================================================
**\*.todo** or **\*.tdo** file format specifications:
=====================================================

The \*.todo specification give you a advice structure

of how structuring an TODO file for efficiently tasks

organizing, and so don't forget ideas or things which

you may have to do in the future for the development

of projects of any professional fields where tasks

must be organized and be accomplished in an certain

order.

-------------
Markup syntax
-------------

**Syntax of a mark:** ``[UPPERCASE :Capitalize: <digits>]``

**Syntax of end mark:** ``[/UPPERCASE] # The end mark is good for reread his todo note.``

An entire **\*.todo** file entry can be represent like this:

.. code-block:: rest

  =================
  TITLE OF DOCUMENT
  =================

  [TYPE :Priority_level: <TASK_ORDER>] Title of todo entry

    Todo main text...

  [/TYPE]

  [TYPE :Priority_level: <TASK_ORDER>] One line todo entry [/TYPE]

------------
Markup Types
------------

**TYPE** (can be):

Before complete the task:
+++++++++++++++++++++++++

+ **BUG** (*A bug have to be fixed*).

+ **FIXME** (*A problem has to be fixed*).

+ **TEST** (*You have to test a feature*).

+ **CORRECT** (*Something must be corrected*).

+ **REDO** (*Something must be redone*).

+ **COMMENT** (*You must make a comment*).

+ **TODO** (*Something must be done*).

+ **IDEA** (*You get an idea for something*).



After complete the task:
++++++++++++++++++++++++

+ **BUGFIX** (*The bug is fixed*).

+ **FIXED**  (*The problem is fixed*).

+ **TESTED** (*The test is done*).

+ **CORRECTED**  (*The correction is done*).

+ **REDONE** (*The task is rewritten*).

+ **COMMENTED** (*The commenting is done*).

+ **DONE** (*The task TODO is DONE*).

+ **IDIE** (*The idea is complete (become true)*).

Summary of TYPE
+++++++++++++++

+ **BUG** or **BUGFIX**


+ **FIXME** or **FIXED**


+ **TEST** or **TESTED**


+ **CORRECT** or **CORRECTED**


+ **REDO** or **REDONE**


+ **COMMENT** or **COMMENTED**


+ **TODO** or **DONE**


+ **IDEA** or **IDIE**

--------------
Priority_level
--------------

**Priority_level** (can take following values:)

  + **High**

  + **Medium**

  + **Low**

----------
TASK_ORDER
----------

**TASK_ORDER** (can be)

1. a **2** (Maybe *3* or *4*) digits sequences for organizing.

2. a digit and a **UPPERCASE** letter with meaning:

  + By **TODO**, **TEST**, **IDEA** entries

    - **F** -> *Free time*

    - **N** -> *Normal* (When possible)

    - **U** -> *Urgent*

  + By **CORRECT**, **BUG** and **FIXME**

    - **I** -> *Info*

    - **W** -> *Warning*

    - **F** -> *Fatal*

  :note: the digit(s) are zero per default but it can take a value
         between 0-9 for very organized structures.

.. Task organizing ! <TASK_ORDER> ordering specification.

:note:  This can be omit. Only **TYPE** and **Priority_level** are mandatory.

:Summary:

  The **TASK_ORDER** are written between ``<`` and ``>``.

  Can be composed either of:

  * **2** digits representing the *task priority*.

  * A digit and a special mean **UPPERCASE** letter.

  :syntax: <[0-9][0-9|[F|N|U]|[I|W|F]]>

  :example: [TODO :Medium: <0F>] Make a new icon because actual is ugly !!! [/TODO]

-------
Advices
-------

**\*.todo** files extensibility:

1. Every entry **TYPE** can be invented but must be written in **UPPERCASE**.

  :advice: use only one word. (Else use **'_'**).

  **DFY** (*Don't Forget Yourself: this make sens*),

  **DRY** (*Don't Repeat Yourself: don't be stupid*),

  **KISS** (*Keep It Simple Stupid: be concise*).

2. Priority level can be added as long as they are one Capitalize word.

3. **DIY** (*Do It Yourself*) for the **TASK_ORDER** or in order to maintain them ordered.


:Advice: Keep terminal width max 79 chars a line.

.. code-block:: rest

  The Best for the End: Think at things like timestamps,

  doing order, prerequisite for task, and so soon !!!

-------------------------------------
Syntax of **\*.todo** file(s) content
-------------------------------------

You can use the ``ReST`` or ``Markdown`` syntax for the content between or inside the marks.

For Titles
++++++++++

.. code-block:: rest

  ==============
  My first Title
  ==============

  ***************
  My second title
  ***************

  ##############
  My third title
  ##############

  +++++++++++++++
  My fourth title
  +++++++++++++++

  ::::::::::::::
  My fifth title
  ::::::::::::::

  --------------
  My sixth title
  --------------

  ~~~~~~~~~~~~~~~~
  My seventh title
  ~~~~~~~~~~~~~~~~

For text decorations:
+++++++++++++++++++++

.. code-block:: rest

  **bold**

  *italic*

  _underline_

  ``inline literals``

  --strike-trough--

  ^^over-line^^
 
For Lists:
++++++++++

.. code-block:: rest

  + List item 1

    - Sub list item 1

    - Sub list item 2

  + List item 2

    1. First numbered list item.

    2. Second numbered list item.

    3. Third numbered list item.

  + List item 3

    Definition list title

      Definition list text
         
For keywords values pairing:
++++++++++++++++++++++++++++

.. code-block:: rest

  :author: foo bar

  :license: fdl 

  :version: 1.0.0


For links:
++++++++++

.. code-block:: rest

  `Link text <http://www.domain.com/folder/file.html>`

For footnotes:
++++++++++++++

.. code-block:: rest

  [*] my footnote text

For comments:
+++++++++++++

.. code-block:: rest

  # My comment line

For code text:
++++++++++++++

.. code-block:: rest

  [:LANGUAGE:]

    Indented text is code !

Per example for C code:

.. code-block:: rest

  [:C:]

    const char *var = "value" ;

--------------------------------------------------------
End word of specifications of the \*.todo file(s) format
--------------------------------------------------------

Do what you must with this specifications and take it like an TODO file

structuring advice, but this document was establish to define the

specifications of a clean TODO file.

--------------------------
Example of a \*.todo file:
--------------------------

An example from a real \*.todo file from one of my projects.

.. code-block:: rest

  IT-EDIT TODO:
  +++++++++++++

  [IDEA :Low:] Advertisement for it-edit:

    it-edit provide so many schemes (more than the underlying library per default) because per example the

    emacs scheme support italic for the ReST or Markdown language which the kate scheme doesn't support.

    But I think the kate scheme is more adapt, with his settings, for program source code writing in terms of syntax coloration.
 
    And the emacs theme is better to use for ReST per example, because of better syntax coloration of italic.
 
    So better get 2 schemes, which you can easily switch, than missing a feature.

  [/IDEA]

  Editor
  ======

  [IDEA :High:] Make the text-completion configurable.

    1. The text completion is one per file.

    2. The text-completion is one for all files (**not easy**).

  [/IDEA]

  [TODO :High:] Make the regex replacement become true. (See GLib regex) [/TODO]

  [IDEA :Medium:] What about enable/disable spell-check ? [/IDEA]

  Schemes
  -------

  [BUG :High:]

  They is a highlight problem with the search all highlight with emacs schemes.

  [/BUG]


  [IDEA :low: <0F>]

  Think of schemes pairs like:

    + kate && emacs (bg white)

    + cobalt && turbo (bg blue)

    + tango && classic (Are settings defendant).

    + vsdark && oblivion (bg maroon).

    + slate && solarized-dark. (bg turquoise)

    + build && solarized-light (bg light yellow).

    + matrix (standalone).

  [/IDEA]

  Terminals
  =========

  [IDEA :Medium:] Maybe a (main  start) settings individually for every different terminals and/or a main (main  start) settings configuration. [/IDEA]

  [TODO :Medium:] Open a file into an editor tab with a terminal pattern [/TODO]

  Files
  =====

  [TODO :Medium:] Add a ChangeLog entry !

    The clipboard from the terminals has been upgraded from severals functionalities.

  [/TODO]


-------
License
-------

.. code-block:: text

  Copyright (c)  2016,2017  Brüggemann Eddie.

  Permission is granted to copy, distribute and/or modify this document

  under the terms of the GNU Free Documentation License, Version 1.3

  or any later version published by the Free Software Foundation;

  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.

  A copy of the license is included in the section entitled "GNU

  Free Documentation License".
