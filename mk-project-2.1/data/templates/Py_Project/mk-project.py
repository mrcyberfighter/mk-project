#!%s
# -*- coding: utf-8 -*-

from sys import argv, exit

import time

import gettext

# gettext support localedir
t = gettext.translation(argv[0].rstrip(".py"), localedir="./share/locale/", fallback=True, codeset="UTF-8")

try:
  # gettext support unicode format strings for python2.
  _ = t.ugettext
 
except :
  # gettext support unicode format strings for python3.
  _ = t.gettext
  
# gettext debuggging information:
#
# By development we use the localdir from the project.
# By distributing you have to set the value on "/usr/share/local/" or "/usr/local/share/locale/"
#
# print(gettext.find(argv[0].rstrip(".py"), localedir="./share/locale/", all=True))



def print_it(string) :

  print(string)



if __name__ == "__main__" :

  print_it(time.ctime())
  print_it( _("Welcome to mk-project !\n") ) # Unicode gettext string format example.
  exit(0)

