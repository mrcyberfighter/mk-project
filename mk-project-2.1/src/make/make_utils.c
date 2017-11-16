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

#include "make_utils.h"



static void make_new_submenu(const char *label, GtkWidget *menu) ;

static void generate_make_help_sphinx_targets(gchar *main_mk_filepath, gchar **output) ;

static void make_new_submenu(const char *label, GtkWidget *menu) {

  /** make a new submenu **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *menu_item = gtk_menu_item_new_with_label(label) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(gui->menu->make_menu), menu_item) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), menu)  ;

  gtk_widget_show_all(menu_item) ;

  return ;

}

// Boolean local global variables used as guard for menu entries.
static bool build_astyle_targets  = false ;
static bool build_indent_targets  = false ;
static bool build_bcpp_targets    = false ;

static bool build_pindent_targets = false ;

static bool build_show_targets    = false ;
static bool build_clean_targets   = false ;
static bool build_pkg_targets     = false ;

static bool build_debug_targets   = false ;
static bool build_bin_targets     = false ;
static bool build_utils_targets   = false ;

static bool build_oprofile_targets  = false ;
static bool build_valgrind_targets  = false ;

static bool build_sphinx_targets      = false ;
static bool build_sphinx_show_targets = false ;

static GtkWidget *make_submenu(GtkWidget *menu, const gchar *menu_title, bool *bool_ptr) {

  menu = gtk_menu_new() ;

  make_new_submenu(menu_title, menu) ;

  *bool_ptr = true ;

  return menu ;

}

static void make_menu_item(const char *target, const char *comment_text, const char *makefile_filepath) {

  /** Long function to build the targets menu: **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (target != NULL) {

      if (g_str_has_prefix(target, "clean")) {

        if (! build_clean_targets) {

          gui->menu->make_clean_menu = make_submenu(gui->menu->make_clean_menu, "clean", &build_clean_targets) ;

        }


        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_clean_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "pkg")) {

        if (! build_pkg_targets) {

          gui->menu->make_pkg_menu = make_submenu(gui->menu->make_pkg_menu, "package", &build_pkg_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_pkg_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "astyle")) {

        if (! build_astyle_targets) {

          gui->menu->make_astyle_menu = make_submenu(gui->menu->make_astyle_menu, "astyle", &build_astyle_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_astyle_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "indent")) {

        if (! build_indent_targets) {

          gui->menu->make_indent_menu = make_submenu(gui->menu->make_indent_menu, "indent", &build_indent_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_indent_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "bcpp")) {


        if (! build_bcpp_targets) {

          gui->menu->make_bcpp_menu = make_submenu(gui->menu->make_bcpp_menu, "bcpp", &build_bcpp_targets) ;

        }



        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bcpp_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "strace")) {


        if (! build_debug_targets) {

          gui->menu->make_debug_menu = make_submenu(gui->menu->make_debug_menu, "debug", &build_debug_targets) ;


        }


        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_debug_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "ltrace")) {


        if (! build_debug_targets) {

          gui->menu->make_debug_menu = make_submenu(gui->menu->make_debug_menu, "debug", &build_debug_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_debug_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "nm")) {

        if (! build_debug_targets) {

          gui->menu->make_debug_menu = make_submenu(gui->menu->make_debug_menu, "debug", &build_debug_targets) ;

        }


        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_debug_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "objdump")) {


        if (! build_debug_targets) {

          gui->menu->make_debug_menu = make_submenu(gui->menu->make_debug_menu, "debug", &build_debug_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_debug_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "ldd")) {

        if (! build_debug_targets) {

          gui->menu->make_debug_menu = make_submenu(gui->menu->make_debug_menu, "debug", &build_debug_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_debug_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "gdebug")) {


        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "ddebug")) {

        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }



        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "gdb")) {


        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "fdebug")) {


        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "pg")) {


        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "hexdump")) {


        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "info")) {

        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "strip")) {


        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "gprof")) {

        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "assembly-att")) {

        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }


        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "assembly-intel")) {

        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "assembly-power")) {

        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "preproc")) {

        if (! build_bin_targets) {

          gui->menu->make_bin_menu = make_submenu(gui->menu->make_bin_menu, "bin", &build_bin_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_bin_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "search-pattern")) {

        if (! build_utils_targets) {

          gui->menu->make_utils_menu = make_submenu(gui->menu->make_utils_menu, "utils", &build_utils_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_utils_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "replace-in-file")) {

        if (! build_utils_targets) {

          gui->menu->make_utils_menu = make_submenu(gui->menu->make_utils_menu, "utils", &build_utils_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_utils_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "replace-all")) {


        if (! build_utils_targets) {

          gui->menu->make_utils_menu = make_submenu(gui->menu->make_utils_menu, "utils", &build_utils_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_utils_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "rm-trailing-space")) {

        if (! build_utils_targets) {

          gui->menu->make_utils_menu = make_submenu(gui->menu->make_utils_menu, "utils", &build_utils_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_utils_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "prepend-license")) {


        if (! build_utils_targets) {

          gui->menu->make_utils_menu = make_submenu(gui->menu->make_utils_menu, "utils", &build_utils_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_utils_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "xgettext")) {

        if (! build_utils_targets) {

          gui->menu->make_utils_menu = make_submenu(gui->menu->make_utils_menu, "utils", &build_utils_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_utils_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "msgfmt")) {

        if (! build_utils_targets) {

          gui->menu->make_utils_menu = make_submenu(gui->menu->make_utils_menu, "utils", &build_utils_targets) ;

        }


        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_utils_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "msguniq")) {

        if (! build_utils_targets) {

          gui->menu->make_utils_menu = make_submenu(gui->menu->make_utils_menu, "utils", &build_utils_targets) ;

        }


        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_utils_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "diff")) {


        if (! build_utils_targets) {

          gui->menu->make_utils_menu = make_submenu(gui->menu->make_utils_menu, "utils", &build_utils_targets) ;

        }



        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_utils_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "rst2man")) {


        if (! build_utils_targets) {

          gui->menu->make_utils_menu = make_submenu(gui->menu->make_utils_menu, "utils", &build_utils_targets) ;

        }



        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_utils_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "view-man")) {


        if (! build_utils_targets) {

          gui->menu->make_utils_menu = make_submenu(gui->menu->make_utils_menu, "utils", &build_utils_targets) ;

        }



        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_utils_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "operf")) {

        if (! build_oprofile_targets) {

          gui->menu->make_oprofile_menu = make_submenu(gui->menu->make_oprofile_menu, "Oprofile", &build_oprofile_targets) ;
        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_oprofile_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "ocount")) {

        if (! build_oprofile_targets) {

          gui->menu->make_oprofile_menu = make_submenu(gui->menu->make_oprofile_menu, "Oprofile", &build_oprofile_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_oprofile_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "opreport")) {

        if (! build_oprofile_targets) {

          gui->menu->make_oprofile_menu = make_submenu(gui->menu->make_oprofile_menu, "Oprofile", &build_oprofile_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_oprofile_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "opannotate")) {

        if (! build_oprofile_targets) {

          gui->menu->make_oprofile_menu = make_submenu(gui->menu->make_oprofile_menu, "Oprofile", &build_oprofile_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_oprofile_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "opgprof")) {

        if (! build_oprofile_targets) {

          gui->menu->make_oprofile_menu = make_submenu(gui->menu->make_oprofile_menu, "Oprofile", &build_oprofile_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_oprofile_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "valgrind-")) {

        if (! build_valgrind_targets) {

          gui->menu->make_valgrind_menu = make_submenu(gui->menu->make_valgrind_menu, "valgrind", &build_valgrind_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_valgrind_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "sphinx-show")) {

        if (! build_sphinx_show_targets) {

          gui->menu->make_sphinx_show_menu = make_submenu(gui->menu->make_sphinx_show_menu, "sphinx show", &build_sphinx_show_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_sphinx_show_menu) ;

        return ;

      }
      else if (g_str_has_prefix(target, "sphinx-")) {

        if (! build_sphinx_targets) {

          gui->menu->make_sphinx_menu = make_submenu(gui->menu->make_sphinx_menu, "sphinx", &build_sphinx_targets) ;

        }

        setup_make_menu_item(target, comment_text, makefile_filepath, gui->menu->make_sphinx_menu) ;

        return ;

      }
      else {

        setup_make_menu_item(target, comment_text, makefile_filepath,  gui->menu->make_menu) ;

        return ;
      }

   }



   return ;

}



void get_output_make(const char *makefile_directory) {

  /** Parsing of the "$ make help" target output. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  // Make menu demonstrable.
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(gtk_smart_menu_item_get_menuitem(gui->menu->make_menubutton)), gui->menu->make_menu);


  gtk_widget_show_all(gui->menu->make_menu) ;


  while (g_main_context_pending(NULL)) {

    g_main_context_iteration(NULL, FALSE) ;

  }

  gchar *args[] = { "make", "help", NULL } ;

  gchar **envp = g_get_environ() ;

  gint exit_status ;

  gchar *standard_output ;

  GError *error = NULL ;

  // Synchron call.
  g_spawn_sync(makefile_directory,
                args,
                envp,
                G_SPAWN_SEARCH_PATH | G_SPAWN_SEARCH_PATH_FROM_ENVP | G_SPAWN_STDERR_TO_DEV_NULL,
                NULL,
                NULL,
                &standard_output,
                NULL,
                &exit_status,
                &error) ;

  if (error != NULL) {

    fprintf(stderr,"%s\n", error->message) ;

    g_clear_error(&error) ;

    return ;

  }





  gchar *makefile_filepath = g_strconcat(makefile_directory, "/", "Makefile", NULL) ;

  gchar **output = g_strsplit(standard_output, "\n", -1) ;

  int c = 0 ;



  while (output[c] != NULL) {

    // Splitting to get the target name:
    gchar **make_targets = g_strsplit(output[c], " ", 3) ;

    // Splitting to get the target comment: after the '#' sign.
    gchar **make_comment = g_strsplit(output[c], "#", 2) ;

    if (make_comment[0] != NULL) {

      if (make_comment[1] != NULL) {
        g_strstrip(make_comment[1]) ;
        make_comment[1] = g_strdelimit(make_comment[1], "\n", '\0') ;
      }
    }

    if (make_targets[0] != NULL) {

      if (make_targets[1] != NULL) {
        g_strstrip(make_targets[1]) ;
      }
    }

    if (make_targets[0] != NULL) {

      if (make_comment[0] == NULL) {

        make_menu_item(make_targets[1], NULL, makefile_filepath) ;

        while (g_main_context_pending(NULL)) {

          g_main_context_iteration(NULL, FALSE) ;

        }

      }
      else {

        make_menu_item(make_targets[1], make_comment[1], makefile_filepath) ;

        while (g_main_context_pending(NULL)) {

          g_main_context_iteration(NULL, FALSE) ;

        }

      }

      g_strfreev(make_targets) ;

      if (make_comment != NULL) {
        g_strfreev(make_comment) ;

      }

    }

    ++c ;

  }

  g_strfreev(output) ;

  g_free(standard_output) ;

  build_astyle_targets  = false ;
  build_indent_targets  = false ;
  build_bcpp_targets    = false ;

  build_pindent_targets = false ;

  build_show_targets    = false ;
  build_clean_targets   = false ;
  build_pkg_targets     = false ;

  build_debug_targets   = false ;
  build_bin_targets     = false ;
  build_utils_targets   = false ;

  build_oprofile_targets = false ;
  build_valgrind_targets = false ;

  build_sphinx_targets   = false ;
  build_sphinx_show_targets = false ;

  g_strfreev(envp) ;

  g_free(makefile_filepath) ;

  gtk_widget_show_all(gui->menu->make_menu) ;

  while (g_main_context_pending(NULL)) {

    // Process pending events...

    g_main_context_iteration(NULL, FALSE) ;

  }

  return ;


}

static void generate_make_help_sphinx_targets(gchar *main_mk_filepath, gchar **output) {
 
  /** This function adds all the sphinx building targets to the main Makefile "$ make help" ouput. **/
 
  GIOChannel *g_io_channel_mk_file = g_io_channel_new_file(main_mk_filepath,"r+", NULL);

  g_io_channel_set_encoding(g_io_channel_mk_file, NULL, NULL);

  free(main_mk_filepath) ;

  gchar *lineptr = NULL ;

  #if 0
  bool write_include = false ;
  #endif

  bool write_help_output = false ;

  GError *error = NULL ;

  while (G_IO_STATUS_NORMAL == g_io_channel_read_line(g_io_channel_mk_file, &lineptr, NULL, NULL, &error)) {

    #if 0
    if (g_str_has_prefix(lineptr, "include ./.SubMakefiles/distributing.mk")) {

      write_include = true ;

    }
    #endif
   
    if (g_str_has_prefix(lineptr, "endif # SHOW SPHINX ENDIF")) {

      write_help_output = true ;
    }
  
    #if 0
    if (write_include) {

      g_io_channel_write_chars(g_io_channel_mk_file, "\nifeq ($(USE_SPHINX),T)\ninclude ./.SubMakefiles/sphinx.mk\ninclude ./.SubMakefiles/sphinx-show.mk\nendif\n" ,-1, NULL, NULL) ;
    
      g_io_channel_flush(g_io_channel_mk_file, NULL);
    
      write_include = false ;

    }
    #endif
  
    if (write_help_output) {

      g_io_channel_write_chars(g_io_channel_mk_file, "ifeq ($(USE_SPHINX),T)\n" ,-1, NULL, NULL) ;

      int c = 1 ;

      while (output[c] != NULL) {

        if (! g_strcmp0(output[c],"")) {

          ++c ;

          continue ;
        }


        gchar **tokens = g_strsplit(output[c]," ", 4) ;

        if (tokens[2] != NULL && tokens[3] != NULL) {

          // We split the lines so that wecan use the tokens as targets:
          // tokens[2] for buiding targets names
          // tokens[3] for building targets tooltips.

          gchar *target_string = g_strdup_printf("	@echo \"make sphinx-%s # %s\"\n", tokens[2], g_strstrip(tokens[3])) ;

          g_io_channel_write_chars(g_io_channel_mk_file, target_string ,-1, NULL, NULL) ;

        }

        g_strfreev(tokens) ;

        ++c ;


      }

      g_strfreev(output) ;

      g_io_channel_write_chars(g_io_channel_mk_file, "	@echo\n" ,-1, NULL, NULL) ;
      g_io_channel_write_chars(g_io_channel_mk_file, "endif\n" ,-1, NULL, NULL) ;
      g_io_channel_write_chars(g_io_channel_mk_file, "	@echo\n" ,-1, NULL, NULL) ;
      g_io_channel_write_chars(g_io_channel_mk_file, "	@echo \"make help         # Display all available targets.\"\n" ,-1, NULL, NULL) ;
      write_help_output = false ;

    }

    SEC_FREE(lineptr)

  }

  g_io_channel_shutdown(g_io_channel_mk_file, TRUE, NULL);

  g_io_channel_unref(g_io_channel_mk_file) ;

  return ;

}



void generate_sphinx_targets(const gchar *sphinx_makefile_directory_path, gchar *main_mk_filepath) {

  gchar *sphinx_makefilepath = g_strconcat(sphinx_makefile_directory_path, "/", "Makefile", NULL) ;

  GMainContext *thread_main_context = g_main_context_ref_thread_default() ;

  while (! g_file_test(sphinx_makefilepath, G_FILE_TEST_EXISTS)) {

    // Wait until the Makefile is created.

    g_main_context_iteration(thread_main_context, FALSE) ;

  }

  gchar *argv[] = { "make", NULL} ;

  gchar **envp = g_get_environ() ;

  gint exit_status = -1 ;

  gchar *standard_output ;

  GError *error = NULL ;

  g_spawn_sync(sphinx_makefile_directory_path, argv, envp, G_SPAWN_SEARCH_PATH | G_SPAWN_SEARCH_PATH_FROM_ENVP | G_SPAWN_STDERR_TO_DEV_NULL,
                (GSpawnChildSetupFunc) sync,
                NULL,
                &standard_output,
                NULL,
                &exit_status,
                &error) ;

  g_spawn_check_exit_status(exit_status,&error);

  if (error != NULL) {

    fprintf(stderr,"error getting sphinx targets: %s\n", error->message) ;

    g_clear_error(&error) ;

    return ;
  }

  // We split the output in lines.
  gchar **output = g_strsplit(standard_output, "\n", -1) ;

  char *buf = g_malloc(sizeof(char)*26*4) ;

  time_t now = time(NULL) ;

  ctime_r(&now, buf);

  int c = 1 ;

  gchar *sphinx_mk_filepath = g_strconcat(project->project_folderpath, "/.SubMakefiles/sphinx.mk", NULL) ;

  FILE *fp =g_fopen(sphinx_mk_filepath, "w");
 
  gchar *header = g_strdup_printf("# Makefile generated by the program: mk-project.\n# File generate the: %s\n# Providing all possible sphinx specific targets.\n", buf) ;

  free(buf) ;

  fwrite(header, sizeof(gchar), strlen(header), fp) ;

  free(header) ;

  while (output[c] != NULL) {



    if (! g_strcmp0(output[c],"")) {

      ++c ;

      continue ;
    }


    gchar **tokens = g_strsplit(output[c]," ", 4) ;

    if (tokens[2] != NULL) {

      // We split the lines so that wecan use the tokens as targets:
      // tokens[1] for buiding targets names
      // tokens[2] for building targets tooltips.

      gchar *target_string = g_strdup_printf(".PHONY: sphinx-%s\nsphinx-%s:\n""	cd ./doc ; $(MAKE) %s\n\n", tokens[2], tokens[2], tokens[2]) ;

      fwrite(target_string, sizeof(gchar), strlen(target_string), fp) ;

    }

    g_strfreev(tokens) ;

    ++c ;


  }

  fflush(fp) ;

  fclose(fp) ;

  generate_make_help_sphinx_targets(main_mk_filepath, output) ;

  g_main_context_unref(thread_main_context) ;

  return ;

}

