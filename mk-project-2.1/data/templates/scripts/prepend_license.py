#!/usr/bin/python
# -*- coding: utf-8 -*-

from sys import exit

from os import walk

from os.path import isdir, isfile

import argparse

# Parse the given argument and display usage if not valid.
parser = argparse.ArgumentParser(prog="prepend_license.py", description='Prepend license boilerplate to all files recursively from the given folder.')

parser.add_argument('-d', '--dir', type=str, dest="DIR", help='Folder to prepend license recursively.', required=True)
parser.add_argument('-f', '--file', type=str, dest="FILE", help='Boilerplate file.', required=True)
parser.add_argument('-l', '--lang', type=str, dest="LANG", help='Programming language.', required=True)

args = parser.parse_args()


if not isdir(args.DIR) :
  parser.print_help()
  print("\n")
  print("%s is not a valid directory !" % args.DIR) ;
  exit(1) ;

if not isfile(args.FILE) :
  parser.print_help()
  print("\n")
  print("%s is not a valid filepath !" % args.FILE) ;
  exit(1) ;

if (args.LANG.lower() == "c") or (args.LANG.lower() == "c++") :

  global start_comment, comment, end_comment

  start_comment = "/**" ;

  comment = "*" ;

  end_comment = "*/" ;

def prepend_license(filepath, biolerplate) :

  src_file=open(filepath, 'r') ;

  src_file_content = src_file.read() ;

  boilerplate = open(biolerplate, 'r') ;

  boilerplate_list = boilerplate.readlines() ;

  res_list = []

  i=0

  if ( (args.LANG.lower() == "c") or (args.LANG.lower() == "c++") ) :
    # If language C or C++ add multilines comment start.
    res_list.append("/**\n") ;

  max_count = 0
  
  while (i < len(boilerplate_list)) :
  
    # Iterate on boilerplate file content and prepend a comment sign before every line.
  
    if (len(boilerplate_list[i]) > max_count) :
      # Compute maximum length of a line.
      max_count = len(boilerplate_list[i])

    v = " " + comment + " " + boilerplate_list[i]

    res_list.append(v) ;

    i += 1

  if (args.LANG.lower() == "c" or args.LANG.lower() == "c++") :
    # If language C or C++ add multilines end comment.
    res_list.append("\n"+" "+((max_count-2) * "*")+end_comment+"\n") ;
    res_list.append("\n") ;
   
  else :
 
    res_list.append("\n") ;

  # prepend list content to file.
  end_file = open(filepath, "w") ;
  end_file.writelines(res_list) ;
  end_file.write(src_file_content) ;




a=walk(args.DIR)

for x, y, z in a :

  for values in z :

    # str(x)+'/'+values
    # Prepend license to all files find in directory.
    prepend_license(str(x)+'/'+values, args.FILE) ;
  