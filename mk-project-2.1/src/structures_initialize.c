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

#include "structures_initialize.h"

void set_default_terminal_settings(void) {


  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  get_main_configuration() ;

  return ;

}


void free_cur_project_settings(void) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  SEC_FREE(cur_project->language)

  SEC_FREE(cur_project->prgname)

  SEC_FREE(cur_project->version_string)

  SEC_FREE(cur_project->license)

  SEC_FREE(cur_project->project_folderpath)


  /** Compiler settings: **/

  SEC_FREE(cur_project->compiler)

  SEC_FREE(cur_project->warnings)

  SEC_FREE(cur_project->cflags)

  SEC_FREE(cur_project->cppflags)

  SEC_FREE(cur_project->ldflags)

  SEC_FREE(cur_project->ldlibs)


  /** Files informations: **/

  SEC_FREE(cur_project->main_file)

  SEC_FREE(cur_project->ext_src)

  SEC_FREE(cur_project->ext_hdr)

  cur_project->program_library = false ;


  /** Disassembling informations: **/

  SEC_FREE(cur_project->nm_options)

  SEC_FREE(cur_project->gdb_options)

  SEC_FREE(cur_project->strace_options)

  SEC_FREE(cur_project->ltrace_options)

  SEC_FREE(cur_project->objdump_options)

  SEC_FREE(cur_project->ldd_options)

  SEC_FREE(cur_project->gprof_options)

  /** Oprofile informations: **/

  SEC_FREE(cur_project->operf_options) ;

  SEC_FREE(cur_project->ocount_options) ;

  SEC_FREE(cur_project->opreport_options) ;

  SEC_FREE(cur_project->opannotate_options) ;

  SEC_FREE(cur_project->opgprof_options) ;

  /** valgrind informations: **/

  SEC_FREE(cur_project->valgrind_memcheck)

  SEC_FREE(cur_project->valgrind_cachegrind)

  SEC_FREE(cur_project->valgrind_callgrind)

  SEC_FREE(cur_project->valgrind_helgrind)

  /** C/C++ Code formatter settings: **/

  cur_project->use_indent = true ;

  SEC_FREE(cur_project->indent_options)

  cur_project->use_astyle = true ;

  SEC_FREE(cur_project->astyle_options)

  cur_project->use_bcpp = true ;

  cur_project->indentation_width = 2 ;

  cur_project->use_tabs = false ;



  /** About informations: **/

  SEC_FREE(cur_project->author_s)

  SEC_FREE(cur_project->mail_address)

  SEC_FREE(cur_project->program_url)

  SEC_FREE(cur_project->copyright_string)


  /** Other informations: **/

  SEC_FREE(cur_project->editor)

  SEC_FREE(cur_project->make_options)

  SEC_FREE(cur_project->bash_location)

  cur_project->compression_level = 3 ;


  /** Licensing: **/

  SEC_FREE(cur_project->licensing_boilerplate)

  /** *.desktop file **/

  SEC_FREE(cur_project->desktop_file_boilerplate)

  cur_project->use_licensing_dkb_format     = false ;
  cur_project->use_licensing_epub_format    = false ;
  cur_project->use_licensing_pdf_format     = false ;
  cur_project->use_licensing_html_format    = false ;
  cur_project->use_licensing_latex_format   = false ;
  cur_project->use_licensing_texinfo_format = false ;
  cur_project->use_licensing_text_format    = true  ;

  #if 0 // NOT NEEDED !
  if (cur_project->sphinx_options->extension != NULL) {

    fprintf(stderr,"into cur_project->sphinx_options->extension !\n") ;

    gpointer ptr = g_ptr_array_free(cur_project->sphinx_options->extension, TRUE) ;

    g_free(ptr) ;

    cur_project->sphinx_options->extension = NULL ;

  }


  SEC_FREE(cur_project->sphinx_options->project)
  SEC_FREE(cur_project->sphinx_options->author)
  SEC_FREE(cur_project->sphinx_options->language)
  SEC_FREE(cur_project->sphinx_options->version)
  SEC_FREE(cur_project->sphinx_options->release)

  cur_project->sphinx_options->epub = false ;

  SEC_FREE(cur_project->sphinx_options)
  #endif


  return ;

}

void init_project_settings(void) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif
 
  /** Main informations: **/

  project->language = g_strdup("C") ;

  project->prgname = g_strdup("") ;

  project->version_string = g_strdup("") ;

  project->license = g_strdup("gpl") ;

  project->project_folderpath = g_strdup("Select the project folder") ;


  /** Compiler settings: **/

  project->compiler = g_strdup("cc") ;

  project->warnings = g_strdup("") ;

  project->cflags = g_strdup("") ;

  project->cppflags = g_strdup("") ;

  project->ldflags = g_strdup("") ;

  project->ldlibs = g_strdup("") ;


  /** Files informations: **/

  project->main_file = g_strdup("") ;

  project->ext_src = g_strdup("") ;

  project->ext_hdr = g_strdup(".h") ;

  project->program_library = false ;


  /** Debugging informations: **/

  project->nm_options = g_strdup("") ;

  project->gdb_options = g_strdup("") ;

  project->strace_options = g_strdup("") ;

  project->ltrace_options = g_strdup("") ;

  project->objdump_options = g_strdup("-D") ;

  project->ldd_options = g_strdup("") ;

  project->gprof_options = g_strdup("") ;

  /** Oprofile informations: **/

  project->operf_options = g_strdup("") ;

  project->ocount_options = g_strdup("") ;

  project->opreport_options = g_strdup("") ;

  project->opannotate_options = g_strdup("--assembly") ;

  project->opgprof_options = g_strdup("") ;

  /** valgrind informations: **/

  project->valgrind_memcheck = g_strdup("") ;

  project->valgrind_cachegrind = g_strdup("") ;

  project->valgrind_callgrind = g_strdup("") ;

  project->valgrind_helgrind = g_strdup("") ;

  /** C/C++ Code formatter settings: **/

  project->use_indent = true ;

  project->indent_options = g_strdup("") ;

  project->use_astyle = true ;

  project->astyle_options = g_strdup("") ;

  project->use_bcpp = true ;

  project->indentation_width = 2 ;

  project->use_tabs = false ;

  project->use_sphinx = false ;

  project->use_rst2man = true ;

  /** About informations: **/

  project->author_s = g_strdup("") ;

  project->mail_address = g_strdup("") ;

  project->program_url = g_strdup("") ;

  project->copyright_string = g_strdup("") ;



  /** Other informations: **/

  project->editor = NULL ;

  project->make_options =  g_strdup_printf("%s", "--no-print-directory # -j 2") ;

  project->bash_location = NULL ;

  project->compression_level = 3 ;


  /** Licensing: **/

  gchar *contents ;

  gsize length ;

  GError *error = NULL ;

  g_file_get_contents(PATH_TO_LICENSING_GPL, &contents, &length, &error) ;

  if (error != NULL) {

    display_message_dialog(_("Error open file"), _("Cannot open licensing boilerplate."), GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    project->licensing_boilerplate = g_strdup("") ;

  }
  else {

    project->licensing_boilerplate = g_strdup_printf("%s", contents) ;
    g_free(contents) ;

  }

  /** *.desktop file **/

  length = -1 ;

  error = NULL ;

  g_file_get_contents(PATH_TO_DESKTOP_TEMPLATE, &contents, &length, &error) ;

  SEC_FREE(project->desktop_file_boilerplate)

  if (error != NULL)  {

    display_message_dialog(_("Error open file"), _("Cannot open desktop boilerplate."), GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    project->desktop_file_boilerplate = g_strdup("") ;

  }
  else {

    project->desktop_file_boilerplate = g_strdup_printf("%s", contents) ;

    g_free(contents) ;

  }

  project->use_licensing_dkb_format     = false ;
  project->use_licensing_epub_format    = false ;
  project->use_licensing_pdf_format     = false ;
  project->use_licensing_html_format    = false ;
  project->use_licensing_latex_format   = false ;
  project->use_licensing_texinfo_format = false ;
  project->use_licensing_text_format    = true  ;

  project->sphinx_options = g_malloc(sizeof(Sphinx_Options)) ;

  project->sphinx_options->extension = NULL ;

  project->sphinx_options->project = g_strdup("") ;
  project->sphinx_options->author = g_strdup("") ;
  project->sphinx_options->language = g_strdup("") ;
  project->sphinx_options->version = g_strdup("") ;
  project->sphinx_options->release = g_strdup("") ;
  project->sphinx_options->epub = false ;

  project->use_sphinx = false ;

  project->use_rst2man = true ;

  return ;

}



void free_project_settings(void) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  SEC_FREE(project->language)

  SEC_FREE(project->prgname)

  SEC_FREE(project->version_string)

  SEC_FREE(project->license)

  SEC_FREE(project->project_folderpath)

  /** Compiler settings: **/

  SEC_FREE(project->compiler)

  SEC_FREE(project->warnings)

  SEC_FREE(project->cflags)

  SEC_FREE(project->cppflags)

  SEC_FREE(project->ldflags)

  SEC_FREE(project->ldlibs)

  /** Files informations: **/

  SEC_FREE(project->main_file)

  SEC_FREE(project->ext_src)

  SEC_FREE(project->ext_hdr)

  /** Debugging informations: **/

  SEC_FREE(project->nm_options)

  SEC_FREE(project->gdb_options)

  SEC_FREE(project->strace_options)

  SEC_FREE(project->ldd_options)

  SEC_FREE(project->ltrace_options)

  SEC_FREE(project->objdump_options)

  SEC_FREE(project->gprof_options)

  /** Oprofile informations: **/

  SEC_FREE(project->operf_options) ;

  SEC_FREE(project->ocount_options) ;

  SEC_FREE(project->opreport_options) ;

  SEC_FREE(project->opannotate_options) ;

  SEC_FREE(project->opgprof_options) ;
 
  /** valgrind informations: **/

  SEC_FREE(project->valgrind_memcheck) ;

  SEC_FREE(project->valgrind_cachegrind) ;

  SEC_FREE(project->valgrind_callgrind) ;

  SEC_FREE(project->valgrind_helgrind) ;
 
  /** C/C++ Code formatter settings: **/

  SEC_FREE(project->indent_options)

  SEC_FREE(project->astyle_options)

  /** About informations: **/

  SEC_FREE(project->author_s)

  SEC_FREE(project->mail_address)

  SEC_FREE(project->program_url)

  SEC_FREE(project->copyright_string)

  /** Other informations: **/

  SEC_FREE(project->editor)

  SEC_FREE(project->make_options)

  SEC_FREE(project->bash_location)

  /** Licensing: **/

  SEC_FREE(project->licensing_boilerplate)

  /** *.desktop file **/

  SEC_FREE(project->desktop_file_boilerplate)


  if (project->sphinx_options->extension != NULL) {

    gpointer ptr = g_ptr_array_free(project->sphinx_options->extension, TRUE) ;

    g_free(ptr) ;

    project->sphinx_options->extension = NULL ;

  }

  SEC_FREE(project->sphinx_options->project)
  SEC_FREE(project->sphinx_options->author)
  SEC_FREE(project->sphinx_options->language)
  SEC_FREE(project->sphinx_options->version)
  SEC_FREE(project->sphinx_options->release)

  project->sphinx_options->epub = false ;

  project->use_sphinx = false ;

  SEC_FREE(project->sphinx_options)

  project->use_rst2man = true ;

  return ;

}


void init_cur_project_settings(void) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  cur_project->language = NULL ;

  cur_project->prgname = NULL ;

  cur_project->version_string = NULL ;

  cur_project->license = NULL ;

  cur_project->project_folderpath = NULL ;

  /** Compiler settings: **/

  cur_project->compiler = NULL ;

  cur_project->warnings = NULL ;

  cur_project->cflags = NULL ;

  cur_project->cppflags = NULL ;

  cur_project->ldflags = NULL ;

  cur_project->ldlibs = NULL ;

  /** Files informations: **/

  cur_project->main_file = NULL ;

  cur_project->ext_src = NULL ;

  cur_project->ext_hdr = NULL ;

  /** Debugging informations: **/

  cur_project->nm_options = NULL ;

  cur_project->gdb_options = NULL ;

  cur_project->strace_options = NULL ;

  cur_project->ltrace_options = NULL ;

  cur_project->objdump_options = NULL ;

  cur_project->ldd_options = NULL ;

  cur_project->gprof_options = NULL ;

  /** Oprofile informations: **/

  cur_project->operf_options = NULL ;

  cur_project->ocount_options = NULL ;

  cur_project->opreport_options = NULL ;

  cur_project->opannotate_options = NULL ;

  cur_project->opgprof_options = NULL ;

  /** valgrind informations: **/

  cur_project->valgrind_memcheck = NULL ;

  cur_project->valgrind_cachegrind = NULL ;

  cur_project->valgrind_callgrind = NULL ;

  cur_project->valgrind_helgrind = NULL ;

  /** C/C++ Code formatter settings: **/

  cur_project->use_indent = true ;

  cur_project->indent_options = NULL ;

  cur_project->use_astyle = true ;

  cur_project->astyle_options = NULL ;

  cur_project->use_bcpp = true ;

  cur_project->indentation_width = 2 ;

  cur_project->use_tabs = false ;

  /** About informations: **/

  cur_project->author_s = NULL ;

  cur_project->mail_address = NULL ;

  cur_project->program_url = NULL ;

  cur_project->copyright_string = NULL ;

  /** Other informations: **/

  cur_project->editor = NULL ;

  cur_project->make_options = NULL ;

  cur_project->bash_location = NULL ;

  cur_project->compression_level = 3 ;

  /** Licensing: **/

  cur_project->licensing_boilerplate = NULL ;

  /** *.desktop file **/

  cur_project->desktop_file_boilerplate = NULL ;

  cur_project->use_licensing_dkb_format     = false ;
  cur_project->use_licensing_epub_format    = false ;
  cur_project->use_licensing_pdf_format     = false ;
  cur_project->use_licensing_html_format    = false ;
  cur_project->use_licensing_latex_format   = false ;
  cur_project->use_licensing_texinfo_format = false ;
  cur_project->use_licensing_text_format    = true  ;

  cur_project->sphinx_options = g_malloc(sizeof(Sphinx_Options)) ;

  cur_project->sphinx_options->extension = NULL ;

  cur_project->sphinx_options->project = g_strdup("") ;
  cur_project->sphinx_options->author = g_strdup("") ;
  cur_project->sphinx_options->language = g_strdup("") ;
  cur_project->sphinx_options->version = g_strdup("") ;
  cur_project->sphinx_options->release = g_strdup("") ;
  cur_project->sphinx_options->epub = false ;

  cur_project->use_sphinx = false ;

  cur_project->use_rst2man = true ;

  return ;


}
