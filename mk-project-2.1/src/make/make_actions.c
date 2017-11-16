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

#include "make_actions.h"

static GError *errors = NULL ;

static gchar *lineptr = NULL;

static char *get_variable_value(const char *in_text, const char *variable) ;

void strip_variable(gchar *string) {

  if (string != NULL) {

    g_strstrip(string) ;

    #ifdef DEBUG
    fprintf(stdout,"Get %s -> %s\n", "make opts", string) ;
    #endif
  }

  return ;

}


static char *check_variable_value(gchar *string, const gchar *lineptr, const char *pattern) {

  if (string == NULL) {

    string = get_variable_value(lineptr, pattern) ;

  }

  return string ;

}

void get_main_makefile_values(const char *makefile_filepath) {

  /** Parse main Makefile and set values according to what is find **/

  #ifdef DEBUG
     DEBUG_FUNC_MARK
   #endif

  // We ensure all values from the structure cur_project are equal to NULL **/
  // Then we get the values from the Makefile parsing.

  GIOChannel *gio_channel = g_io_channel_new_file(makefile_filepath, "r", &errors);

  if (errors != NULL) {

    display_message_dialog(_("Error open file !"), g_strdup(errors->message), GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_clear_error(&errors) ;

    return ;
  }

  while (G_IO_STATUS_NORMAL  == g_io_channel_read_line(gio_channel, &lineptr, NULL, NULL, NULL)) {

    /** @NOTE: It's very ugly to query for different REGEX every line so I test the variables for @NULL.
      *         If you get a better idea for limiting the calls thanks to tell me it.
    **/

    if (cur_project->language == NULL) {

      cur_project->language=check_variable_value(cur_project->language, lineptr, "PRG_LANG") ;
    }

    if (cur_project->make_options == NULL) {

      cur_project->make_options=check_variable_value(cur_project->make_options, lineptr, "MAKE_OPTS") ;
    }

    if (cur_project->prgname == NULL) {

      cur_project->prgname=check_variable_value(cur_project->prgname, lineptr, "PRGNAME") ;
    }

    if (cur_project->version_string == NULL) {

      cur_project->version_string=check_variable_value(cur_project->version_string, lineptr, "VERSION") ;
    }

    if (cur_project->ext_src == NULL) {

      cur_project->ext_src=check_variable_value(cur_project->ext_src, lineptr, "EXT_SRC") ;
    }

    if (cur_project->ext_hdr == NULL) {

      cur_project->ext_hdr=check_variable_value(cur_project->ext_hdr, lineptr, "EXT_HDR") ;
    }

    if (cur_project->compiler == NULL) {

      cur_project->compiler=check_variable_value(cur_project->compiler, lineptr, "COMPILER") ;
    }

    if (cur_project->warnings == NULL) {

      cur_project->warnings=check_variable_value(cur_project->warnings, lineptr, "WARNS") ;
    }

    if (cur_project->cflags == NULL) {

      cur_project->cflags=check_variable_value(cur_project->cflags, lineptr, "CFLAGS") ;
    }

    if (cur_project->cppflags == NULL) {

      cur_project->cppflags=check_variable_value(cur_project->cppflags, lineptr, "CPPFLAGS") ;
    }

    if (cur_project->ldflags == NULL) {

      cur_project->ldflags=check_variable_value(cur_project->ldflags, lineptr, "LDFLAGS") ;
    }

    if (cur_project->ldlibs == NULL) {

      cur_project->ldlibs=check_variable_value(cur_project->ldlibs, lineptr, "LDLIBS") ;
    }

    if (cur_project->nm_options == NULL) {

      cur_project->nm_options=check_variable_value(cur_project->nm_options, lineptr, "NM_OPTS") ;
    }

    if (cur_project->gdb_options == NULL) {

      cur_project->gdb_options=check_variable_value(cur_project->gdb_options, lineptr, "GDB_OPTS") ;
    }

    if (cur_project->strace_options == NULL) {

      cur_project->strace_options=check_variable_value(cur_project->strace_options, lineptr, "STRACE_OPTS") ;
    }

    if (cur_project->ltrace_options == NULL) {

      cur_project->ltrace_options=check_variable_value(cur_project->ltrace_options, lineptr, "LTRACE_OPTS") ;
    }

    if (cur_project->objdump_options == NULL) {

      cur_project->objdump_options=check_variable_value(cur_project->objdump_options, lineptr, "OBJDUMP_OPTS") ;
     
    }

    if (cur_project->ldd_options == NULL) {

      cur_project->ldd_options=check_variable_value(cur_project->ldd_options, lineptr, "LDD_OPTS") ;
    }

    if (cur_project->gprof_options == NULL) {

      cur_project->gprof_options=check_variable_value(cur_project->gprof_options, lineptr, "GPROF_OPTS") ;
    }

    if (cur_project->operf_options == NULL) {

      cur_project->operf_options=check_variable_value(cur_project->operf_options, lineptr, "OPERF_OPTS") ;
    }

    if (cur_project->ocount_options == NULL) {

      cur_project->ocount_options=check_variable_value(cur_project->ocount_options, lineptr, "OCOUNT_OPTS") ;
    }

    if (cur_project->opreport_options == NULL) {

      cur_project->opreport_options=check_variable_value(cur_project->opreport_options, lineptr, "OPREPORT_OPTS") ;
    }

    if (cur_project->opannotate_options == NULL) {

      cur_project->opannotate_options=check_variable_value(cur_project->opannotate_options, lineptr, "OPANNOTATE_OPTS") ;
    }

    if (cur_project->opgprof_options == NULL) {

      cur_project->opgprof_options=check_variable_value(cur_project->opgprof_options, lineptr, "OPGPROF_OPTS") ;
    }
 
    if (cur_project->valgrind_memcheck == NULL) {

      cur_project->valgrind_memcheck=check_variable_value(cur_project->valgrind_memcheck, lineptr, "VALGRIND_MEMCHECK_OPTS") ;
    }
 
    if (cur_project->valgrind_cachegrind == NULL) {

      cur_project->valgrind_cachegrind=check_variable_value(cur_project->valgrind_cachegrind, lineptr, "VALGRIND_CACHEGRIND_OPTS") ;
    }
 
    if (cur_project->valgrind_callgrind == NULL) {

      cur_project->valgrind_callgrind=check_variable_value(cur_project->valgrind_callgrind, lineptr, "VALGRIND_CALLGRIND_OPTS") ;
    }
 
    if (cur_project->valgrind_helgrind == NULL) {

      cur_project->valgrind_helgrind=check_variable_value(cur_project->valgrind_helgrind, lineptr, "VALGRIND_HELGRIND_OPTS") ;
    }
 
    SEC_FREE(lineptr) ;

  }

  // End of file reading...

  g_io_channel_shutdown(gio_channel, FALSE, &errors) ;

  g_io_channel_unref(gio_channel) ;

  if (errors != NULL) {

    display_message_dialog(_("Error closing file !"), errors->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_clear_error(&errors) ;

  }

  // The g_strstrip(...) calls remove leading and traing spaces.

  strip_variable(cur_project->make_options) ;
  strip_variable(cur_project->language) ;
  strip_variable(cur_project->prgname) ;
  strip_variable(cur_project->version_string) ;
  strip_variable(cur_project->ext_src) ;
  strip_variable(cur_project->ext_hdr) ;
  strip_variable(cur_project->warnings) ;

  if (cur_project->compiler != NULL) {

    g_strstrip(cur_project->compiler) ;

    if (! g_strcmp0(cur_project->compiler, "$(CC)")) {

      free(cur_project->compiler) ; cur_project->compiler = g_strdup("cc") ;

    }
    else if (! g_strcmp0(cur_project->compiler, "$(CXX)")) {

      free(cur_project->compiler) ; cur_project->compiler = g_strdup("c++") ;

    }

    #ifdef DEBUG
    fprintf(stdout,"Get %s -> %s\n", "compiler", cur_project->compiler) ;
    #endif
  }

  strip_variable(cur_project->cflags) ;
  strip_variable(cur_project->cppflags) ;
  strip_variable(cur_project->ldflags) ;
  strip_variable(cur_project->ldlibs) ;
  strip_variable(cur_project->gdb_options) ;
  strip_variable(cur_project->ltrace_options) ;
  strip_variable(cur_project->objdump_options) ;
  strip_variable(cur_project->ldd_options) ;
  strip_variable(cur_project->gprof_options) ;
  strip_variable(cur_project->strace_options) ;
  strip_variable(cur_project->nm_options) ;
  strip_variable(cur_project->operf_options) ;
  strip_variable(cur_project->ocount_options) ;
  strip_variable(cur_project->opreport_options) ;
  strip_variable(cur_project->opannotate_options) ;
  strip_variable(cur_project->opgprof_options) ;
  strip_variable(cur_project->valgrind_memcheck) ;
  strip_variable(cur_project->valgrind_cachegrind) ;
  strip_variable(cur_project->valgrind_callgrind) ;
  strip_variable(cur_project->valgrind_helgrind) ;


  return ;

}

void set_boolean_flag(bool *value, const gchar *string) {

  *value = (g_strcmp0(string, "T") == 0)   ? true : (g_strcmp0(string, "F") == 0) ? false : true ;

  return ;

}


void get_code_fmt_makefile_values(const char *makefile_filepath) {

  /** Parse ./.subMakefiles/code_formatter.mk file and set values according to what is find **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  // Temporary string variables:
  char *use_indent = NULL ;

  char *use_astyle = NULL ;

  char *use_bcpp = NULL ;

  char *use_pindent = NULL ;

  char *indentation_width = NULL ;

  char *use_tabs = NULL ;

  /** TODO: use g_io_readline... **/

  GIOChannel *gio_channel = g_io_channel_new_file(makefile_filepath, "r", &errors);

  if (errors != NULL) {

    display_message_dialog(_("Error open file !"), g_strdup(errors->message), GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_clear_error(&errors) ;

    return ;
  }

  while (G_IO_STATUS_NORMAL  == g_io_channel_read_line(gio_channel, &lineptr, NULL, NULL, NULL)) {

    cur_project->indent_options=check_variable_value(cur_project->indent_options, lineptr, "INDENT_OPTS") ;

    cur_project->astyle_options=check_variable_value(cur_project->astyle_options, lineptr, "ASTYLE_OPTS") ;

    use_indent=check_variable_value(use_indent, lineptr, "USE_INDENT") ;

    use_astyle=check_variable_value(use_astyle, lineptr, "USE_ASTYLE") ;

    use_bcpp=check_variable_value(use_bcpp, lineptr, "USE_BCPP") ;

    use_pindent=check_variable_value(use_pindent, lineptr, "USE_PINDENT") ;

    indentation_width=check_variable_value(indentation_width, lineptr, "INDENTATION") ;

    use_tabs=check_variable_value(use_tabs, lineptr, "USE_TABS") ;

    SEC_FREE(lineptr) ;

  }

  g_io_channel_shutdown(gio_channel, FALSE, &errors) ;

  g_io_channel_unref(gio_channel) ;

  if (errors != NULL) {

    display_message_dialog(_("Error closing file !"), errors->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_clear_error(&errors) ;

  }


  strip_variable(cur_project->indent_options) ;
  strip_variable(cur_project->astyle_options) ;

  if (use_indent != NULL) {

    g_strstrip(use_indent) ;

    set_boolean_flag(&cur_project->use_indent, use_indent) ;

    g_free(use_indent) ;

    #ifdef DEBUG
    fprintf(stdout,"Get %s -> %d\n", "use_indent", cur_project->use_indent) ;
    #endif
  }

  if (use_astyle != NULL) {

    g_strstrip(use_astyle) ;

    set_boolean_flag(&cur_project->use_astyle, use_astyle) ;

    g_free(use_astyle) ;

    #ifdef DEBUG
    fprintf(stdout,"Get %s -> %d\n", "use_astyle", cur_project->use_astyle) ;
    #endif
  }

  if (use_bcpp != NULL) {

    g_strstrip(use_bcpp) ;

    set_boolean_flag(&cur_project->use_bcpp, use_bcpp) ;

    g_free(use_bcpp) ;

    #ifdef DEBUG
    fprintf(stdout,"Get %s -> %d\n", "use_bcpp", cur_project->use_bcpp) ;
    #endif

  }

  if (use_tabs != NULL) {

    g_strstrip(use_tabs) ;

    set_boolean_flag(&cur_project->use_tabs, use_tabs) ;

    g_free(use_tabs) ;

    #ifdef DEBUG
    fprintf(stdout,"Get %s -> %d\n", "use_tabs", cur_project->use_tabs) ;
    #endif
  }

  if (indentation_width != NULL) {

    g_strstrip(indentation_width) ;

    cur_project->indentation_width = (int) g_strtod(indentation_width, NULL) ;

    g_free(indentation_width) ;

    #ifdef DEBUG
    fprintf(stdout,"Get %s -> %d\n", "cur_project->indentation_width", cur_project->indentation_width) ;
    #endif


  }

  return ;

}



void get_dist_makefile_values(const char *makefile_filepath) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  // Temporary string variables:
  char *compression = NULL ;

  // We ensure all values from the structure cur_project are equal to NULL **/
  // Then we get the values from the Makefile parsing.

  GIOChannel *gio_channel = g_io_channel_new_file(makefile_filepath, "r", &errors);

  if (errors != NULL) {

    display_message_dialog(_("Error open file !"), g_strdup(errors->message), GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_clear_error(&errors) ;

    return ;
  }

  while (G_IO_STATUS_NORMAL  == g_io_channel_read_line(gio_channel, &lineptr, NULL, NULL, NULL)) {

    compression=check_variable_value(compression, lineptr, "COMPRESSION") ;

    SEC_FREE(lineptr)

  }

  g_io_channel_shutdown(gio_channel, FALSE, &errors) ;

  g_io_channel_unref(gio_channel) ;

  if (errors != NULL) {

    display_message_dialog(_("Error closing file !"), errors->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_clear_error(&errors) ;

  }


  // End of file reading...
  //
  // The g_strstrip(...) call remove leading and traing spaces.
  //


  if (compression != NULL) {

    g_strstrip(compression) ;

    #ifdef DEBUG
    fprintf(stdout,"Get %s -> %s\n", "compression", compression) ;
    #endif

    cur_project->compression_level = (uint8_t) g_strtod(compression, NULL) ;

    g_free(compression) ;

    #ifdef DEBUG
    fprintf(stdout,"Get %s -> %d\n", "compression level", cur_project->compression_level) ;
    #endif

  }

  return ;

}

void set_dist_makefile_values(const char *filepath) {

  /** Set the ./.subMakefiles/distributing.mk values with a GRegex replacement **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  gchar *compression = g_strdup_printf("COMPRESSION = %d", cur_project->compression_level) ;

  const char *replacements[] = { "^[ ]{0,}COMPRESSION[ ]{0,}=.*", compression, NULL } ;

  replace_into_file(filepath, replacements) ;

  g_free(compression) ;

  return ;

}



void set_code_fmt_makefile_values(const char *filepath) {

  /** Set the ./.subMakefiles/code_formatter.mk values with a GRegex replacement **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  gchar *indent_options = g_strdup_printf("INDENT_OPTS = %s", cur_project->indent_options) ;

  gchar *astyle_options = g_strdup_printf("ASTYLE_OPTS = %s", cur_project->astyle_options) ;

  gchar *use_indent = g_strdup_printf("USE_INDENT = %s", (cur_project->use_indent) ? "T" : "F") ;

  gchar *use_astyle = g_strdup_printf("USE_ASTYLE = %s", (cur_project->use_astyle) ? "T" : "F") ;

  gchar *use_bcpp = g_strdup_printf("USE_BCPP = %s", (cur_project->use_bcpp) ? "T" : "F") ;

  gchar *use_tabs = g_strdup_printf("USE_TABS = %s", (cur_project->use_tabs) ? "T" : "F") ;

  // We no more support python, so pindent doen't make sense.
  //gchar *use_pindent = g_strdup_printf("USE_PINDENT = %s", (cur_project->use_pindent) ? "T" : "F") ;

  gchar *indentation_width = g_strdup_printf("INDENTATION = %d", cur_project->indentation_width) ;

  const char *replacements[] =
                                { "^[ ]{0,}INDENT_OPTS[ ]{0,}=.*", indent_options,
                                  "^[ ]{0,}ASTYLE_OPTS[ ]{0,}=.*", astyle_options,
                                  "^[ ]{0,}USE_INDENT[ ]{0,}=.*", use_indent,
                                  "^[ ]{0,}USE_ASTYLE[ ]{0,}=.*", use_astyle,
                                  "^[ ]{0,}USE_BCPP[ ]{0,}=.*", use_bcpp,
                                  //"^[ ]{0,}USE_PINDENT[ ]{0,}=.*", use_pindent,
                                  "^[ ]{0,}USE_TABS[ ]{0,}=.*", use_tabs,
                                  "^[ ]{0,}INDENTATION[ ]{0,}=.*", indentation_width,
                                  NULL
                                } ;

  replace_into_file(filepath, replacements) ;

  g_free(indent_options) ;

  g_free(astyle_options) ;

  g_free(use_indent) ;

  g_free(use_astyle) ;

  g_free(use_bcpp) ;

  //g_free(use_pindent) ;

  g_free(use_tabs) ;

  g_free(indentation_width) ;


  return ;

}


void set_main_makefile_values(const char *filepath) {

  /** Set the main Makefile values with a GRegex replacement **/

  #ifdef DEBUG
     DEBUG_FUNC_MARK
  #endif

  gchar *make_opts = g_strdup_printf("MAKE_OPTS = %s", cur_project->make_options) ;

  gchar *compiler = g_strdup_printf("COMPILER = %s", (! g_strcmp0(cur_project->compiler, "cc")) ? "$(CC)" : (! g_strcmp0(cur_project->compiler, "c++")) ? "$(CXX)" : cur_project->compiler ) ;

  gchar *warns = g_strdup_printf("WARNS = %s", cur_project->warnings) ;

  gchar *cflags = g_strdup_printf("CFLAGS = %s", cur_project->cflags) ;

  gchar *cppflags = g_strdup_printf("CPPFLAGS = %s", cur_project->cppflags) ;

  gchar *ldflags = g_strdup_printf("LDFLAGS = %s", cur_project->ldflags) ;

  gchar *ldlibs = g_strdup_printf("LDFLAGS = %s", cur_project->ldlibs) ;

  gchar *nm_options = g_strdup_printf("NM_OPTS = %s", cur_project->nm_options) ;

  gchar *gdb_options = g_strdup_printf("GDB_OPTS = %s", cur_project->gdb_options) ;

  gchar *strace_options = g_strdup_printf("STRACE_OPTS = %s", cur_project->strace_options) ;

  gchar *ltrace_options = g_strdup_printf("LTRACE_OPTS = %s", cur_project->ltrace_options) ;

  gchar *objdump_options = g_strdup_printf("OBJDUMP_OPTS = %s", cur_project->objdump_options) ;

  gchar *ldd_options = g_strdup_printf("LDD_OPTS = %s", cur_project->ldd_options) ;

  gchar *gprof_options = g_strdup_printf("GPROF_OPTS = %s", cur_project->gprof_options) ;
 
  gchar *valgrind_memcheck = g_strdup_printf("VALGRIND_MEMCHECK_OPTS = %s", cur_project->valgrind_memcheck) ;
  gchar *valgrind_cachegrind = g_strdup_printf("VALGRIND_CACHEGRIND_OPTS = %s", cur_project->valgrind_cachegrind) ;
  gchar *valgrind_callgrind = g_strdup_printf("VALGRIND_CALLGRIND_OPTS = %s", cur_project->valgrind_callgrind) ;
  gchar *valgrind_helgrind = g_strdup_printf("VALGRIND_HELGRIND_OPTS = %s", cur_project->valgrind_helgrind) ;
 
  const char *replacements[] =
                          { "^[ ]{0,}MAKE_OPTS[ ]{0,}=.*", make_opts,
                            "^[ ]{0,}COMPILER[ ]{0,}=.*", compiler,
                            "^[ ]{0,}WARNS[ ]{0,}=.*", warns,
                            "^[ ]{0,}CFLAGS[ ]{0,}=.*", cflags,
                            "^[ ]{0,}CPPFLAGS[ ]{0,}=.*", cppflags,
                            "^[ ]{0,}LDFLAGS[ ]{0,}=.*", ldflags,
                            "^[ ]{0,}LDLIBS[ ]{0,}=.*", ldlibs,
                            "^[ ]{0,}NM_OPTS[ ]{0,}=.*", nm_options,
                            "^[ ]{0,}GDB_OPTS[ ]{0,}=.*", gdb_options,
                            "^[ ]{0,}STRACE_OPTS[ ]{0,}=.*", strace_options,
                            "^[ ]{0,}LTRACE_OPTS[ ]{0,}=.*", ltrace_options,
                            "^[ ]{0,}OBJDUMP_OPTS[ ]{0,}=.*", objdump_options,
                            "^[ ]{0,}LDD_OPTS[ ]{0,}=.*", ldd_options,
                            "^[ ]{0,}GPROF_OPTS[ ]{0,}=.*", gprof_options,
                            "^[ ]{0,}VALGRIND_MEMCHECK_OPTS[ ]{0,}=.*", valgrind_memcheck,
                            "^[ ]{0,}VALGRIND_CACHEGRIND_OPTS[ ]{0,}=.*", valgrind_cachegrind,
                            "^[ ]{0,}VALGRIND_CALLGRIND_OPTS[ ]{0,}=.*", valgrind_callgrind,
                            "^[ ]{0,}VALGRIND_HELGRIND_OPTS[ ]{0,}=.*", valgrind_helgrind,
                            NULL

                             } ;


  replace_into_file(filepath, replacements) ;

  g_free(make_opts) ;

  g_free(compiler) ;

  g_free(warns) ;

  g_free(cflags) ;

  g_free(cppflags) ;

  g_free(ldflags) ;

  g_free(ldlibs) ;

  g_free(nm_options) ;

  g_free(gdb_options) ;

  g_free(strace_options) ;

  g_free(objdump_options) ;

  g_free(ldd_options) ;

  g_free(gprof_options) ;
 
  g_free(valgrind_memcheck) ;
 
  g_free(valgrind_cachegrind) ;
 
  g_free(valgrind_callgrind) ;
 
  g_free(valgrind_helgrind) ;
 
  return ;

}

void replace_into_file(const char *filepath, const char *pattern_replacement[]) {

  /** Function() to replace a @make variables values in terms of pairs:
    *
    *  1. pattern for detecting the variable, (If the pattern isn't found it is skipped.).
    *
    *  2. new variable definition.
    *
    **************************************************************************************/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  gchar *tmp_filepath = NULL ;

  gint fd = g_file_open_tmp("mk_parsing_tmp_file_XXXXXX.mk", &tmp_filepath, &errors);

  g_close(fd, NULL) ;

  FILE *out_fp = g_fopen(tmp_filepath, "w");

  gchar *lineptr = NULL ;

  GIOChannel *gio_channel = g_io_channel_new_file(filepath, "r", &errors);

  if (errors != NULL) {

    display_message_dialog(_("Error open file !"), errors->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_clear_error(&errors) ;

    return ;
  }

  while (G_IO_STATUS_NORMAL  == g_io_channel_read_line(gio_channel, &lineptr, NULL, NULL, NULL)) {

    gchar *text_replaced = NULL ;

    int c = 0 ;

    bool must_continue = false ;

    while ( (pattern_replacement[c] != NULL) && (pattern_replacement[c+1] != NULL) ) {

      if ( (text_replaced = exec_replacement((const char *) pattern_replacement[c], lineptr, (const char *) pattern_replacement[c+1])) != NULL) {

        fwrite(text_replaced, sizeof(char), strlen(text_replaced), out_fp) ;

        g_free(text_replaced) ;

        SEC_FREE(lineptr)

        must_continue = true ;

        break ;

      }

      c += 2 ;

    }

    if (must_continue) {

      continue ;

    }

    fwrite(lineptr, sizeof(char), strlen(lineptr), out_fp) ;

    SEC_FREE(lineptr)

  }

  g_io_channel_shutdown(gio_channel, FALSE, &errors) ;

  g_io_channel_unref(gio_channel) ;

  if (errors != NULL) {

    display_message_dialog(_("Error closing file !"), errors->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_clear_error(&errors) ;

  }


  fflush(out_fp)  ;

  fclose(out_fp)  ;

  copy_file(tmp_filepath, filepath) ;

  g_remove(tmp_filepath) ;

  return ;

}

void insert_new_file_in_makefile(const char *mk_filepath, const char *variable, const char *extension, const char *filepath_to_append) {

  /** Function() to add a new file to the mk-project @make variable @SRC_FILES,
    *
    *  to extend it in the way we copy the entire file by reading it line per line
    *
    *  and detecting some patterns for locating the @F@cking @SRC_FILES variable,
    *
    *  then simply add the new file to the stream and copy the rest.
    *
    *  @NOTE: We take cares also as you should of the indentation width by the multiline.
    *
  **/

  #ifdef DEBUG
     DEBUG_FUNC_MARK
  #endif

  if (filepath_to_append == NULL) {

    /** "No filepath to append **/

    return ;
  }


  const char *filepath_to_threath = mk_filepath ;

  FILE *in_fp = g_fopen(filepath_to_threath, "r") ;

  gchar *tmp_filepath = g_strconcat(g_get_tmp_dir(), "/", "mk_parsing_tmp_file.mk", NULL) ;

  if ( g_file_test(tmp_filepath, G_FILE_TEST_EXISTS) ) {

    g_remove(tmp_filepath) ;

  }

  FILE *out_fp = g_fopen(tmp_filepath, "w") ;


  GError *error = NULL ;

  /** First file pattern **/

  gchar *pattern_src_files = g_strdup_printf("[ ]{0,}%s[ ]{0,}=.*", variable) ;

  GRegex *regex_first_file = g_regex_new( (const gchar *) pattern_src_files, // Pattern
                                          G_REGEX_CASELESS | G_REGEX_EXTENDED | G_REGEX_DOTALL | G_REGEX_NEWLINE_ANYCRLF, // GRegexCompileFlags
                                          0, //GRegexMatchFlags match_options,
                                          &error);

  g_free(pattern_src_files) ;

  #ifdef DEBUG
  if (error != NULL) {

    fprintf(stdout,"error: %s\n", error->message) ;

    g_error_free(error) ;

    error = NULL ;

  }
  #endif

  /** Following files pattern (ending with a '\\' for multilines defintion.) **/

  gchar *pattern_files = g_strdup_printf("^.*\\%s.* \\ .*$", extension) ;

  GRegex *regex_files = g_regex_new( (const gchar *) pattern_files, // Pattern
                                    G_REGEX_CASELESS | G_REGEX_EXTENDED | G_REGEX_DOTALL | G_REGEX_NEWLINE_ANYCRLF, // GRegexCompileFlags
                                    0, //GRegexMatchFlags match_options,
                                    &error);


  g_free(pattern_files) ;

  #ifdef DEBUG
  if (error != NULL) {

    fprintf(stdout,"error: %s\n", error->message) ;

    g_error_free(error) ;

    error = NULL ;

  }
  #endif

  /** Last file pattern for adding new file after. **/

  gchar *pattern_last_file = g_strdup_printf("^.*\\%s.*$", extension) ;

  GRegex *regex_last_file = g_regex_new( (const gchar *) pattern_last_file, // Pattern
                                    G_REGEX_CASELESS | G_REGEX_EXTENDED | G_REGEX_DOTALL | G_REGEX_NEWLINE_ANYCRLF, // GRegexCompileFlags
                                    0, //GRegexMatchFlags match_options,
                                    &error);


  g_free(pattern_last_file) ;

  #ifdef DEBUG
  if (error != NULL) {

    fprintf(stdout,"error: %s\n", error->message) ;

    g_error_free(error) ;

    error = NULL ;

  }
  #endif


  /** We read the entire file line after line using the getline() function. **/

  static bool find_SRC_FILES = false ;

  static bool found_SRC_FILES = false ;

  gchar *lineptr = NULL ;

  GIOChannel *gio_channel = g_io_channel_new_file(filepath_to_threath, "r", &errors);

  if (errors != NULL) {

    display_message_dialog(_("Error open file !"), errors->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_clear_error(&errors) ;

    return ;
  }

  while (G_IO_STATUS_NORMAL  == g_io_channel_read_line(gio_channel, &lineptr, NULL, NULL, NULL)) {

    if (found_SRC_FILES) {

     /** All Files found: Here we continue to copy file... **/

     fwrite(lineptr, sizeof(gchar), strlen(lineptr), out_fp) ;

     SEC_FREE(lineptr)

     continue ;

    }



    if (find_SRC_FILES) {

      /** The first file was found but it remains some files. **/

      GMatchInfo *match_info ;

      if (g_regex_match(regex_files, lineptr, 0, &match_info)) {

        /** A file was found and they are a least one more... **/

        #ifdef DEBUG
        fprintf(stderr, "%s Regex find a file...\n", __func__) ;
        #endif

        gchar *value = NULL ;

        if (g_match_info_matches(match_info)) {

          value = g_match_info_fetch(match_info, 0) ;

          #ifdef DEBUG
          g_print ("SRC_FILES: %s\n", value);
          #endif

          g_match_info_next(match_info, NULL);

        }


        if (match_info != NULL) {
          g_match_info_free(match_info);
        }

        fwrite(lineptr, sizeof(gchar), strlen(lineptr), out_fp) ;

        free(value) ;

        SEC_FREE(lineptr)


        continue ;

      }
      else if (g_regex_match(regex_last_file, lineptr, 0, &match_info)) {

        /** The last file is found so we concluded. **/

        gchar *value = NULL ;

        #ifdef DEBUG
        fprintf(stdout,"%s Find last source file.\n", __func__) ;
        #endif

        if (g_match_info_matches(match_info)) {

          value = g_match_info_fetch(match_info, 0) ;

          #ifdef DEBUG
          g_print ("SRC_FILES: %s\n", value);
          #endif

          g_match_info_next(match_info, NULL);

        }

        if (match_info != NULL) {
          g_match_info_free(match_info);
        }


        find_SRC_FILES = false ;  /** No more entry in searching more files. **/

        found_SRC_FILES = true ;  /** Go to copy the rest content of the file. **/


        /** TODO: Add the new file here. **/

        // Old-stylewise add new filepath.
        bool first_letter = false ;

        uint16_t spaces_counter = 0 ;

        for (uint16_t c=0 ; value[c] != '\0' ; ++c) {

          if (! first_letter) {

            if (value[c] == ' ') {

              spaces_counter++ ;
            }
            else {

              first_letter = true ;
            }

          }

          if (value[c] == '\n') {

            value[c] = ' ' ;
          }

        }

        char *spaces = g_strnfill ( (gsize) spaces_counter, ' ') ;

        char *new_entry = g_strdup_printf("%s\\ \n%s%s\n", value, spaces, filepath_to_append) ;

        fwrite(new_entry, sizeof(gchar), strlen(new_entry), out_fp) ;



        fflush(out_fp) ;

        g_free(spaces) ;

        g_free(new_entry) ;

        SEC_FREE(lineptr)

        continue ;


      }

    }

    GMatchInfo *match_info ;

    if (g_regex_match(regex_first_file, lineptr, 0, &match_info)) {

      /** The first file was found ! **/

      gchar *value = NULL ;

      find_SRC_FILES = true ;

      #ifdef DEBUG
      fprintf(stdout,"%s Find first source file !\n", __func__) ;
      #endif

      if (g_match_info_matches(match_info)) {

        value = g_match_info_fetch(match_info, 0) ;

        #ifdef DEBUG
        g_print ("SRC_FILES: %s\n", value);
        #endif

        g_match_info_next(match_info, NULL);

      }

      bool find_backslash = false ;

      for (uint16_t c = 0 ; value[c] != '\0' ; ++c) {

        /** Check if contains a backslash **/

        if (value[c] == '\\') {

          find_backslash = true ;

          #ifdef DEBUG
          fprintf(stdout,"%s Backslash found in first file !!!\nso we continue investigating for files...\n\n", __func__) ;
          #endif

          break ;
        }

      }

      if (! find_backslash) {

        #ifdef DEBUG
        fprintf(stderr,"Not found backslash\n") ;
        #endif

        /** They are no others lines to check **/

        /** TODO: Add the new file here. **/

        size_t spaces_counter = strlen("SRC_FILES = ") ;

        #ifdef DEBUG
        fprintf(stderr,"%s number of spaces: %zu\n", __func__, spaces_counter) ;
        #endif

        for (uint16_t c=0 ; value[c] != '\0' ; ++c) {

          if (value[c] == '\n') {

            value[c] = ' ' ;
          }

        }

        char *spaces = g_strnfill ( (gsize) spaces_counter, ' ') ;

        if (spaces == NULL) {

          #ifdef DEBUG
          fprintf(stderr, "Failed to set the spaces before filename\n") ;
          #endif
        }



        char *new_entry = g_strdup_printf("%s\\ \n%s%s\n", value, spaces, filepath_to_append) ;

        fwrite(new_entry, sizeof(char), strlen(new_entry), out_fp) ;


        fflush(out_fp) ;

        g_free(spaces) ;

        g_free(new_entry) ;

        found_SRC_FILES = true ;
      }
      else {

        /** Some others lines remains **/

        fwrite(value, sizeof(char), strlen(value), out_fp) ;

        find_SRC_FILES = true ;

      }



      g_match_info_free(match_info);

      g_regex_unref(regex_first_file);

      SEC_FREE(lineptr)


      continue ;

    }

    fwrite(lineptr, sizeof(char), strlen(lineptr), out_fp) ;

    SEC_FREE(lineptr)

  }

  g_io_channel_shutdown(gio_channel, TRUE, NULL) ;

  g_io_channel_unref(gio_channel) ;



  g_regex_unref(regex_files) ;

  g_regex_unref(regex_last_file) ;



  fclose(in_fp)   ;

  fflush(out_fp)  ;

  fclose(out_fp)  ;


  copy_file(tmp_filepath, mk_filepath) ;

  find_SRC_FILES = false ;

  found_SRC_FILES = false ;

  return ;

}


static char *get_variable_value(const char *in_text, const char *variable) {

  /** Construct the pattern for getting variable value **/

  #ifdef DEBUG
     DEBUG_FUNC_MARK
  #endif

  GError *error = NULL ;

  gchar *pattern = g_strdup_printf("^[ ]{0,}%s[ ]{0,}=(.*)", variable) ;

  GRegex *regex = g_regex_new( (const gchar *) pattern, // Pattern
                               G_REGEX_CASELESS | G_REGEX_EXTENDED | G_REGEX_OPTIMIZE, // GRegexCompileFlags
                               0, //GRegexMatchFlags match_options,
                               &error);

  g_free(pattern) ;

  if (error != NULL) {

    fprintf(stderr,"error: %s\n", error->message) ;

    g_error_free(error) ;

    error = NULL ;

  }


  GMatchInfo *match_info = NULL ;

  if (g_regex_match(regex, in_text, 0, &match_info)) {

    gchar *value = NULL ;

    if (g_match_info_matches(match_info)) {

      value = g_match_info_fetch(match_info, 1) ;

      #ifdef DEBUG
      g_print("Value found: %s\n", value);
      #endif

      g_match_info_next(match_info, NULL);

    }



    g_match_info_free(match_info);

    g_regex_unref(regex);

    if (value != NULL) {

      return value ;

    }

  }

  g_regex_unref(regex);

  return NULL ;

}

char *exec_replacement(const char *pattern, const char *in_text, const char *replacement) {

  /** Replace one @make variable in the stream. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  GError *error = NULL ;

  GRegex *regex = g_regex_new( (const gchar *) pattern, // Pattern
                               G_REGEX_CASELESS | G_REGEX_EXTENDED | G_REGEX_NEWLINE_ANYCRLF, // GRegexCompileFlags
                               0, //GRegexMatchFlags match_options,
                               &error);

  if (error != NULL) {

    fprintf(stderr,"error: %s\n", error->message) ;

    g_error_free(error) ;

    error = NULL ;

  }

  GMatchInfo *match_info = NULL ;

  if (g_regex_match(regex, in_text, 0, &match_info)) {

    gchar *new_text = g_regex_replace(regex, in_text, strlen(in_text),
                                      0,
                                      (const gchar *) replacement,
                                      0, &error) ;

    if (error != NULL) {

      fprintf(stderr,"error: %s\n", error->message) ;

      g_error_free(error) ;

      error = NULL ;

    }

    #ifdef DEBUG
    fprintf(stdout,"replacement done:\n%s\n", new_text) ;
    #endif


    #ifdef DEBUG
    while (g_match_info_matches (match_info)) {
      gchar *word = g_match_info_fetch(match_info, 0);
      g_print ("Found: %s\n", word);
      g_free (word);
      g_match_info_next (match_info, NULL);
    }
    #endif

    g_match_info_free(match_info);
    g_regex_unref(regex);

    return new_text ;

  }

  g_regex_unref(regex);

  return NULL ;

}

