/** ***********************************************************************************
  *                                                                                   *
  * mk-project a tool to ease the development process                                 *
  * and a good bridge for the distributing process.                                   *
  *                                                                                   *
  * Copyright (C) 2016,1017 Brüggemann Eddie                                          *
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

#include "xml_writer.h"

#include "xml_utils.h"

static void update_xml(xmlNodePtr node, Project *project) ;

void xml_writer(const char *filename, Project *new_project) {

  if (realpath(filename, NULL) != NULL) {

    /** File does not exist !!! **/
    return ;
  }

  xmlDocPtr xml_doc_ptr = NULL ;

  xmlKeepBlanksDefault(0) ;

  xml_doc_ptr = xmlNewDoc(BAD_CAST "1.0") ;

  xmlNodePtr root_node = NULL ;

  if ((root_node = xmlDocGetRootElement(xml_doc_ptr)) == NULL) {

   root_node = create_root_node(xml_doc_ptr, "mk-project") ;

  }

  const char *comment_text = "This file is used as standalone file for mk-project projects.\n"
                             "This file is used to keep track of user settings of a mk-project project.\n"
                             "For usage of reformatting users settings in future use.\nOr getting the user settings." ;

  xmlNodePtr start_comment_node = add_new_doc_comment(xml_doc_ptr, root_node, comment_text) ;

  char *main_info_nodes_name[] = { "PRG_LANG", "PRGNAME", "VERSION", "LICENSE", NULL } ;

  char *main_info_nodes_content[] = { new_project->language, new_project->prgname, new_project->version_string, new_project->license, NULL } ;

  int c=0 ;

  while (main_info_nodes_name[c] != NULL) {

    add_new_node(root_node,  main_info_nodes_name[c], main_info_nodes_content[c]) ;

    ++c ;

  }

  add_new_node(root_node, "FOLDERPATH", new_project->project_folderpath) ;

  xmlNodePtr C_node_ptr = NULL ;

  xmlNodePtr debugging_node = NULL ;

  xmlNodePtr code_fmt_node = NULL ;




  C_node_ptr = add_new_node(root_node, "COMPILE", NULL) ;

  add_new_node(C_node_ptr, "COMPILER", new_project->compiler)  ;
  add_new_node(C_node_ptr, "WARNS",    new_project->warnings)  ;
  add_new_node(C_node_ptr, "CFLAGS",   new_project->cflags)    ;
  add_new_node(C_node_ptr, "CPPFLAGS", new_project->cppflags)  ;
  add_new_node(C_node_ptr, "LDFLAGS",  new_project->ldflags)    ;
  add_new_node(C_node_ptr, "LDLIBS",   new_project->ldlibs)    ;

  add_new_node(C_node_ptr, "MAIN_FILENAME", new_project->main_file) ;

  add_new_node(C_node_ptr, "EXT_SRC", new_project->ext_src) ;
  add_new_node(C_node_ptr, "EXT_HDR", new_project->ext_hdr) ;

  add_new_node(C_node_ptr, "USE_PRG_LIB", (new_project->program_library) ? "T" : "F") ;

  debugging_node = add_new_node(root_node, "DEBUGGING", NULL) ;

  add_new_node(debugging_node, "NM_OPTS", new_project->nm_options) ;
  add_new_node(debugging_node, "STRACE_OPTS", new_project->strace_options) ;
  add_new_node(debugging_node, "LTRACE_OPTS", new_project->ltrace_options) ;
  add_new_node(debugging_node, "OBJDUMP_OPTS", new_project->objdump_options) ;
  add_new_node(debugging_node, "LDD_OPTS", new_project->ldd_options) ;
  add_new_node(debugging_node, "GPROF_OPTS", new_project->gprof_options) ;
  add_new_node(debugging_node, "GDB_OPTS", new_project->gdb_options) ;

  code_fmt_node = add_new_node(root_node, "CODE_FMT", NULL) ;

  set_property(code_fmt_node, "USE_INDENT", (new_project->use_indent) ? "T" : "F") ;

  add_new_node(code_fmt_node, "INDENT_OPTS", new_project->indent_options) ;

  set_property(code_fmt_node, "USE_ASTYLE", (new_project->use_astyle) ? "T" : "F") ;

  add_new_node(code_fmt_node, "ASTYLE_OPTS", new_project->astyle_options) ;

  set_property(code_fmt_node, "USE_BCPP", (new_project->use_bcpp) ? "T" : "F") ;

  set_property(code_fmt_node, "USE_TABS", (new_project->use_tabs) ? "T" : "F") ;

  gchar *buffer = g_strdup_printf("%d", new_project->indentation_width)  ;

  set_property(code_fmt_node, "INDENTATION", buffer ) ;

  g_free(buffer) ;

  xmlNodePtr doc_node = add_new_node(root_node, "DOC", NULL) ;

  set_property(doc_node, "USE_SPHINX", (new_project->use_sphinx) ? "T" : "F") ;
 
 
  #if 0
  xmlNodePtr valgrind_node = add_new_node(root_node, "VALGRIND", NULL) ;

  add_new_node(valgrind_node, "valgrind-memcheck",   new_project->valgrind_memcheck) ;
  add_new_node(valgrind_node, "valgrind-cachegrind", new_project->valgrind_cachegrind) ;
  add_new_node(valgrind_node, "valgrind-callgrind",  new_project->valgrind_callgrind) ;
  add_new_node(valgrind_node, "valgrind-helgrind",   new_project->valgrind_helgrind) ;
  #endif
 
 
  xmlNodePtr about_node = add_new_node(root_node, "ABOUT", NULL) ;

  add_new_node(about_node, "AUTHOR",         new_project->author_s) ;
  add_new_node(about_node, "MAIL",           new_project->mail_address) ;
  add_new_node(about_node, "PRGURL",         new_project->program_url) ;
  add_new_node(about_node, "COPYRIGHT_STR",  new_project->copyright_string) ;

  xmlNodePtr others_node = add_new_node(root_node, "OTHER", NULL) ;

  add_new_node(others_node, "EDITOR", new_project->editor) ;
  add_new_node(others_node, "MAKE_OPTS", new_project->make_options) ;
  add_new_node(others_node, "BASH", new_project->bash_location) ;

  buffer = g_strdup_printf("%d", new_project->compression_level) ;

  add_new_node(others_node, "COMPRESSION", buffer) ;

  g_free(buffer) ;

  xmlNodePtr licensing_node = add_new_node(root_node, "LICENSING", new_project->licensing_boilerplate) ;

  if (licensing_node != NULL) {

    set_property(licensing_node, "USE_DBK", (new_project->use_licensing_dkb_format) ? "T" : "F") ;
    set_property(licensing_node, "USE_EPUB", (new_project->use_licensing_epub_format) ? "T" : "F") ;
    set_property(licensing_node, "USE_PDF", (new_project->use_licensing_pdf_format) ? "T" : "F") ;
    set_property(licensing_node, "USE_HTML", (new_project->use_licensing_html_format) ? "T" : "F") ;
    set_property(licensing_node, "USE_LATEX", (new_project->use_licensing_latex_format) ? "T" : "F") ;
    set_property(licensing_node, "USE_TEXINFO", (new_project->use_licensing_texinfo_format) ? "T" : "F") ;
    set_property(licensing_node, "USE_TEXT", (new_project->use_licensing_text_format) ? "T" : "F") ;

  }

  xmlNodePtr desktop_node = add_new_node(root_node, "DESKTOP", new_project->desktop_file_boilerplate) ;

  #ifdef DEBUG
  xmlDocFormatDump(stdout, xml_doc_ptr, 1) ;
  #endif

  if (filename != NULL) {

    set_compression(xml_doc_ptr, 3) ;

    xmlSaveFormatFileEnc(filename, xml_doc_ptr, "UTF-8", 1) ;

  }


  xmlFreeNode(start_comment_node) ;

  xmlFreeNode(desktop_node) ;
  xmlFreeNode(others_node)  ;
  #if 0
  xmlFreeNode(valgrind_node)  ;
  #endif
  xmlFreeNode(about_node)  ;
  xmlFreeNode(doc_node)  ;
  xmlFreeNode(code_fmt_node) ;
  xmlFreeNode(debugging_node) ;
  xmlFreeNode(C_node_ptr) ;

  return ;

}

static void update_xml(xmlNodePtr node, Project *project) {

  xmlNodePtr n = NULL ;

  for (n = node ; n != NULL ; n = n->next) {

    if (! strcmp((const char *) n->name, "PRG_LANG") ) {

      replace_node_content(n, project->language) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "PRGNAME") ) {

      replace_node_content(n, project->prgname) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "COMPILER") ) {

      replace_node_content(n, project->compiler) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "WARNS") ) {

      replace_node_content(n, project->warnings) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "CFLAGS") ) {

      replace_node_content(n, project->cflags) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "CPPFLAGS") ) {

      replace_node_content(n, project->cppflags) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "LDFLAGS") ) {

      replace_node_content(n, project->ldflags) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "LDLIBS") ) {

      replace_node_content(n, project->ldlibs) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "EXT_SRC") ) {
 
      replace_node_content(n, project->ext_src) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "EXT_HDR") ) {

      replace_node_content(n, project->ext_hdr) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "NM_OPTS") ) {

      replace_node_content(n, project->nm_options) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "STRACE_OPTS") ) {

      replace_node_content(n, project->strace_options) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "LTRACE_OPTS") ) {

      replace_node_content(n, project->ltrace_options) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "OBJDUMP_OPTS") ) {

      replace_node_content(n, project->objdump_options) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "LDD_OPTS") ) {

      replace_node_content(n, project->ldd_options) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "GPROF_OPTS") ) {

      replace_node_content(n, project->gprof_options) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "GDB_OPTS") ) {

      replace_node_content(n, project->gdb_options) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "CODE_FMT") ) {

      set_property(n, "USE_INDENT", (project->use_indent) ? "T" : "F" ) ;
      set_property(n, "USE_ASTYLE", (project->use_astyle) ? "T" : "F" ) ;
      set_property(n, "USE_BCPP", (project->use_bcpp) ? "T" : "F" ) ;
      set_property(n, "USE_TABS", (project->use_tabs) ? "T" : "F" ) ;
      gchar *indentation_string = g_strdup_printf("%d", project->indentation_width)  ;
      set_property(n, "INDENTATION", indentation_string) ;
      g_free(indentation_string) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "INDENT_OPTS")) {

      replace_node_content(n, project->indent_options) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "ASTYLE_OPTS")) {

      replace_node_content(n, project->indent_options) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "EDITOR")) {

      replace_node_content(n, project->editor) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "EDITOR")) {

      replace_node_content(n, project->editor) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "MAKE_OPTS")) {

      replace_node_content(n, project->make_options) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "BASH")) {

      replace_node_content(n, project->bash_location) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "COMPRESSION")) {

      gchar *buffer = g_strdup_printf("%d", project->compression_level) ;

      replace_node_content(n, buffer) ;

      g_free(buffer) ;

      update_xml(n->children, project) ;

    }
    else if (! strcmp((const char *) n->name, "LICENSING")) {
   
      set_property(n, "USE_DBK", (project->use_licensing_dkb_format) ? "T" : "F" ) ;
      set_property(n, "USE_EPUB", (project->use_licensing_epub_format) ? "T" : "F" ) ;
      set_property(n, "USE_PDF", (project->use_licensing_pdf_format) ? "T" : "F" ) ;
      set_property(n, "USE_HTML", (project->use_licensing_html_format) ? "T" : "F" ) ;
      set_property(n, "USE_LATEX", (project->use_licensing_latex_format) ? "T" : "F" ) ;
      set_property(n, "USE_TEXINFO", (project->use_licensing_texinfo_format) ? "T" : "F" ) ;
      set_property(n, "USE_TEXT", (project->use_licensing_text_format) ? "T" : "F" ) ;

      replace_node_content(n, project->licensing_boilerplate) ;

      update_xml(n->children, project) ;
   
    }
    else if (! strcmp((const char *) n->name, "DESKTOP")) {

      replace_node_content(n, project->desktop_file_boilerplate) ;

      update_xml(n->children, project) ;
   
    }
    else {

      update_xml(n->children, project);
    }
  }

  return ;

}

void xml_updating(const char *filepath, Project *pproject) {

  xmlDocPtr xmldoc = NULL ;

  xmldoc = xmlParseFile(filepath) ;

  if (xmldoc == NULL) {

    #ifdef DEBUG
    fprintf(stderr,"Failed to acess xml file\n") ;
    #endif

    return ;
  }

  xmlNodePtr root = NULL ;

  root = xmlDocGetRootElement(xmldoc) ;

  if (root == NULL) {

    #ifdef DEBUG
    fprintf(stderr,"Cannot access root node\n") ;
    #endif

    return ;
  }

  update_xml(root, pproject) ;

  #ifdef DEBUG
  xmlDocFormatDump(stderr, xmldoc, 1) ;
  #endif

  if (filepath != NULL) {

    set_compression(xmldoc, 3) ;

    xmlSaveFormatFileEnc(filepath, xmldoc, "UTF-8", 1) ;

  }

  return ;

}




