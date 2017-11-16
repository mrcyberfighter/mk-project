/** ***********************************************************************************
  *                                                                                   *
  * mk-project a tool to ease the development process                                 *
  * and a good bridge for the distributing process.                                   *
  *                                                                                   *
  * Copyright (C) 2016,2017 Brüggemann Eddie                                          *
  *                                                                                   *
  * This file is part of mk-project.                                                  *
  * mk-project is free software: you can redistribute it and/or modify                *
  * it under the terms of the GNU General Public License as published by              *
  * the Free Software Foundation, either version 3 of the License, or                 *
  * (at your option) any later version.                                               *
  *                                                                                   *
  * mk-project is distributed in the hope that it will be useful,                     *
  * but WITHOUT ANY WARRANTY; without even the implied warranty of                    *
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                      *
  * GNU General Public License for more details.                                      *
  *                                                                                   *
  * You should have received a copy of the GNU General Public License                 *
  * along with mk-project. If not, see <http://www.gnu.org/licenses/>                 *
  *                                                                                   *
  *************************************************************************************/

#ifndef MK_PROJECT_PROJECT_STRUCTURE_HH
#define MK_PROJECT_PROJECT_STRUCTURE_HH

#include "../includes.h"

typedef struct {

  GPtrArray *extension ;

  gchar *project ;

  gchar *author ;

  gchar *language ;

  gchar *version ;

  gchar *release ;

  bool  epub ;

} Sphinx_Options ;

typedef struct {



  /** Main informations: **/

  gchar *language ;

  gchar *prgname  ;

  gchar *version_string ;

  gchar *license ;

  gchar *project_folderpath ;

  /** Compiler settings: **/

  gchar *compiler ;

  gchar *warnings ;

  gchar *cflags ;

  gchar *cppflags ;

  gchar *ldflags ;

  gchar *ldlibs ;

  /** Files informations: **/

  gchar *main_file ;

  gchar *ext_src ;

  gchar *ext_hdr ;

  /** Debugging informations: **/

  gchar *nm_options ;

  #if 0
  /** Not portable ! *//
  gchar *readelf_options ;
  #endif

  gchar *gdb_options ;

  gchar *strace_options ;

  gchar *ltrace_options ;

  gchar *objdump_options ;

  gchar *ldd_options ;

  gchar *gprof_options ;

  // Oprofile options:
  gchar *operf_options ;

  gchar *ocount_options ;

  gchar *opreport_options ;

  gchar *opannotate_options ;

  gchar *opgprof_options ;

  // valgrind options:
  gchar *valgrind_memcheck ;

  gchar *valgrind_cachegrind ;

  gchar *valgrind_callgrind ;

  gchar *valgrind_helgrind ;

  /** C/C++ Code formatter settings: **/

  gchar *indent_options ;

  gchar *astyle_options ;

  /** Python project. **/

  //gchar *python_interpreter ;

  /** Documenation generators settings: **/

  //gchar *markdown_dialect ;

  gchar *sphinx_language ;

  /** About informations: **/

  gchar *author_s ;

  gchar *mail_address ;

  gchar *program_url ;

  gchar *copyright_string ;

  /** Other informations: **/

  gchar *editor ;

  gchar *make_options ;

  gchar *bash_location ;

  /** Licensing: **/

  gchar *licensing_boilerplate ;

  /** *.desktop file **/

  gchar *desktop_file_boilerplate ;


  Sphinx_Options *sphinx_options ;

  int indentation_width ;

  uint8_t compression_level ;

  bool program_library ;

  bool use_astyle ;

  bool use_tabs ;

  bool use_indent ;

  bool use_bcpp ;

  bool use_licensing_dkb_format ;
  bool use_licensing_epub_format ;
  bool use_licensing_pdf_format ;
  bool use_licensing_html_format ;
  bool use_licensing_latex_format ;
  bool use_licensing_texinfo_format ;
  bool use_licensing_text_format ;

  bool use_sphinx ;
 
  bool use_rst2man ;
 

} Project ;

#endif
