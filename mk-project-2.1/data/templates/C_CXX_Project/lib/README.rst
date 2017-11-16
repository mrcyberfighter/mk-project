==========
mk-project
==========

++++++++++++++++++++++++++++++++
Building a static library README
++++++++++++++++++++++++++++++++

  You have only to set all the source files (from the given extension) in this folder and type:
 
  $ make libmyprgname
 
  To build the static library.
 
  Then simply type:
 
  $ make -B
 
  To rebuild the binary with the static library.
 

:question: What to do if I want to build a tree of folders from the library source.

:answers: Fill the make variable SRC_FILES with your files listing.    