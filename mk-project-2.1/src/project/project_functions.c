#include "./project_functions.h"

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

static bool entry_has_value(const gchar *entry_content, const gchar *value) ;

static gint cmp(const gchar *p1, const gchar *p2) ;

static GList *fill_listbox_with_g_list(GList *g_list, GtkWidget *listbox) ;

static void fill_entry(GtkWidget *entry, const gchar *string) ;

static gchar *get_entry_value(GtkWidget *entry) ;

static void sphinx_cmdline_insert(GString *string, const gchar *val) ;

static void foreach_sphinx_extension(gpointer data, GString *user_data) ;

void on_realize_widget(GtkWidget *widget, gpointer   user_data) {

 GdkWindow *gdk_window = gtk_widget_get_window(widget) ;

  if (gdk_window != NULL) {

    if (gdk_window_get_events(gdk_window) != GDK_FOCUS_CHANGE_MASK) {

      gdk_window_set_events(gdk_window, GDK_FOCUS_CHANGE_MASK) ;

    }

  }

 return ;

}

void get_spinbutton_value_indentation(GtkSpinButton *spinbutton, int *user_data) {

  *user_data = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton)) ;

  return ;

}

void get_scale_value_compression_level(GtkRange *range, int *user_data) {

  *user_data = gtk_range_get_value(GTK_RANGE(range)) ;

  return ;
}

void get_checkbutton_value(GtkToggleButton *togglebutton, bool *user_data) {

  /** Get many differents checkbutton values **/

  *user_data = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)) ;

  return ;
}

void get_sphinx_extension(GtkWidget *container) {

  int c = 0 ;

  GtkListBoxRow *row = NULL ; ;

  while ((row=gtk_list_box_get_row_at_index(GTK_LIST_BOX(container), c)) != NULL) {

    GtkWidget *toggle_button = gtk_bin_get_child(GTK_BIN(row)) ;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button))) {

      gchar *value = g_strdup_printf("--ext-%s", gtk_button_get_label(GTK_BUTTON(toggle_button))) ;

      g_ptr_array_add(project->sphinx_options->extension, value) ;

    }

    ++c ;

  }

  return ;

}


void get_combo_value(GtkComboBox *widget, gchar *user_data) {

  /** Get many differents combo configurations values **/

  gchar *combo_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget)) ;

  if (combo_text == NULL) {

    return ;
  }

  SEC_FREE(user_data) ;

  user_data = g_strdup(combo_text) ;

  SEC_FREE(combo_text) ;

  return ;

}

gboolean get_entry_value_project_version_string(GtkWidget *widget, GdkEvent  *event, char *user_data) {

  const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(widget)) ;

  if (entry_text == NULL) {

    return FALSE ;

  }

  SEC_FREE(user_data) ;

  user_data = g_strdup(entry_text) ;

  return FALSE ;

}

void insert_data(gpointer data, gpointer widget) {

  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widget), NULL, g_path_get_basename(g_app_info_get_executable(data))) ;

  g_object_unref(data) ;

}

char *have_app_application(const char *application) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gchar **env_list = g_get_environ() ;

  gchar *path_env_variable = (gchar *) g_environ_getenv(env_list, "PATH")  ;

  char *dir = NULL ;

  while ((dir=strtok(path_env_variable, ":")) != NULL) {

    gchar *filepath = g_strdup_printf("%s/%s",dir,application) ;

    if (g_file_test(filepath, G_FILE_TEST_EXISTS)) {

      g_strfreev(env_list) ;

      return filepath ;
    }

    g_free(filepath) ;

    path_env_variable = NULL ;

  }

  g_strfreev(env_list) ;

  return NULL ;

}



void update_compiler(GList *children, Project *project) {

  // FIXME: we use the value of project->language instead of cur_project->language
  //        because of bug in getting the language but it don't mind.

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  while ( (children != NULL) && (children->data != NULL) ) {

    if ( ! g_strcmp0( gtk_widget_get_name(children->data), "compiler_entry")) {

      if (! g_strcmp0(project->language, "C++")) {
        gtk_entry_set_text(GTK_ENTRY(children->data), "c++") ;

        gtk_widget_set_tooltip_text(children->data, _("c++ is your default C++ compiler") ) ;
      }
      else if (! g_strcmp0(project->language, "C")) {
        gtk_entry_set_text(GTK_ENTRY(children->data), "cc") ;

        gtk_widget_set_tooltip_text(children->data, _("cc is your default C compiler") ) ;
      }

    }

    if (children->next != NULL) {

      children = children->next ;
    }
    else {

      break ;
    }

  }

  g_list_free(children) ;

  return ;

}



void update_c_project(GList *children, Project *project) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  while ( (children != NULL) && (children->data != NULL) ) {

    if (! g_strcmp0(gtk_widget_get_name(children->data), "main_file")) {

      if (! g_strcmp0(project->language, "C")) {
        gtk_entry_set_text(GTK_ENTRY(children->data), "main.c") ;

        SEC_FREE(project->main_file) ;

        project->main_file = g_strdup_printf("%s", "main.c") ;

      }
      else if (! g_strcmp0(project->language, "C++")) {
        gtk_entry_set_text(GTK_ENTRY(children->data), "main.cpp") ;

        SEC_FREE(project->main_file) ;

        project->main_file = g_strdup_printf("%s", "main.cpp") ;

      }
    }
    else if ( g_strcmp0( gtk_widget_get_name(children->data), "ext_src") == 0) {

      gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(children->data)) ;

      if (! g_strcmp0(project->language, "C")) {
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".c") ;
      }
      else if (g_strcmp0(project->language, "C++") == 0) {
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".cpp") ;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".CPP") ;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".c++") ;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".C") ;
      }


      if (! g_strcmp0(project->language, "C")) {

        gtk_combo_box_set_active(GTK_COMBO_BOX(children->data), 0) ;
      }
      else if (g_strcmp0(project->language, "C++") == 0) {

        char *ext_src = NULL ;

        if ( (ext_src = strrchr(project->main_file, '.')) != NULL) {

          if (! g_strcmp0(ext_src, ".cpp")) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(children->data), 0) ;
          }
          else if (! g_strcmp0(ext_src, ".CPP")) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(children->data), 1) ;
          }
          else if (! g_strcmp0(ext_src, ".c++")) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(children->data), 2) ;
          }
          else if (! g_strcmp0(ext_src, ".C")) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(children->data), 3) ;
          }
       }
       else {
         gtk_combo_box_set_active(GTK_COMBO_BOX(children->data), 0) ;
       }

     }


    }
    else if ( g_strcmp0( gtk_widget_get_name(children->data), "ext_hdr") == 0)  {

      gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(children->data)) ;

      if (! g_strcmp0(project->language, "C")) {
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".h") ;
      }
      else if (! g_strcmp0(project->language, "C++")) {
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".h") ;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".hh") ;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".H") ;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".hp") ;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".hxx") ;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".hpp") ;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".HPP") ;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".h++") ;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(children->data), NULL, ".tcc") ;
      }

      gtk_combo_box_set_active(GTK_COMBO_BOX(children->data), 0) ;

    }

    if (children->next != NULL) {

      children = children->next ;
    }
    else {

      break ;
    }

  }

  g_list_free(children) ;

  return ;

}



void update_licensing(GList *children, Project *project) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if (children == NULL) {

    return ;
  }

  while ( (children != NULL) && (children->data != NULL) ) {

    if (! g_strcmp0(gtk_widget_get_name(children->data), "licensing_textview")) {

      GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(children->data)) ;

      if (project->licensing_boilerplate != NULL ) {

        GtkTextIter start_iter, end_iter ;

        gtk_text_buffer_get_start_iter(buffer, &start_iter) ;

        if (! gtk_text_iter_is_start(&start_iter)) {

          return ;
        }

        gtk_text_buffer_get_end_iter(buffer, &end_iter) ;

        if (! gtk_text_iter_is_end(&end_iter)) {

          return ;
        }

        gchar *buffer_content = gtk_text_buffer_get_text(buffer, &start_iter, &end_iter, FALSE) ;

        if ( g_strcmp0(buffer_content, project->licensing_boilerplate) == 0) {
          g_free(buffer_content) ;
          return ;
        }
        else {
          g_free(buffer_content) ;
          gtk_text_buffer_set_text(buffer, project->licensing_boilerplate, -1) ;
        }

      }

    }

    if (children->next != NULL) {

      children = children->next ;
    }
    else {

      break ;
    }

  }

  g_list_free(children) ;

  return ;

}


void get_compiler_datas(GList *children, Project *project) {

  while (children != NULL) {

    if (! g_strcmp0(gtk_widget_get_name(children->data), "cflags")) {

      SEC_FREE(project->cflags) ;

      project->cflags = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "warnings")) {

      SEC_FREE(project->warnings) ;

      project->warnings = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "cppflags") ) {

      SEC_FREE(project->cppflags) ;

      project->cppflags = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "ldflags")) {

      SEC_FREE(project->ldflags) ;

      project->ldflags = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "ldlibs")) {

      SEC_FREE(project->ldlibs) ;

      project->ldlibs = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0( gtk_widget_get_name(children->data), "compiler_entry")) {

      SEC_FREE(project->compiler) ;

      project->compiler = get_entry_value(children->data) ;
    }

    if (children->next != NULL) {

      children = children->next ;
    }
    else {

      break ;
    }

  }

  g_list_free(children) ;

  return ;

}




void get_disassembling_opts(GList *children, Project *project) {

  while (children != NULL) {

    if (! g_strcmp0(gtk_widget_get_name(children->data), "nm_options")) {

      SEC_FREE(project->nm_options) ;

      project->nm_options = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "strace_options")) {

      SEC_FREE(project->strace_options) ;

      project->strace_options = g_strdup_printf("%s", gtk_entry_get_text(GTK_ENTRY(children->data)) ) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "ltrace_options")) {

      SEC_FREE(project->ltrace_options) ;

      project->ltrace_options = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "objdump_options")) {

      if (! g_strcmp0(project->objdump_options, "-D")) {

        SEC_FREE(project->objdump_options) ;

        project->objdump_options = get_entry_value(children->data) ;

      }

    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "ldd_options")) {

      SEC_FREE(project->ldd_options) ;

      project->ldd_options = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "gprof_options")) {

      SEC_FREE(project->gprof_options) ;

      project->gprof_options = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "gdb_options")) {

      SEC_FREE(project->gdb_options) ;

      project->gdb_options = get_entry_value(children->data) ;
    }

    if (children->next != NULL) {

      children = children->next ;
    }
    else {

      break ;
    }

  }

  g_list_free(children) ;

  return ;

}

void get_oprofile_opts(GList *children, Project *project) {

  while (children != NULL) {

    if (! g_strcmp0(gtk_widget_get_name(children->data), "operf_options")) {

      SEC_FREE(project->operf_options) ;

      project->operf_options = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "ocount_options")) {

      SEC_FREE(project->ocount_options) ;

      project->ocount_options = g_strdup_printf("%s", gtk_entry_get_text(GTK_ENTRY(children->data)) ) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "opreport_options")) {

      SEC_FREE(project->opreport_options) ;

      project->opreport_options = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "opannotate_options")) {

      if (! g_strcmp0(project->opannotate_options, "--assembly")) {

        SEC_FREE(project->opannotate_options) ;

        project->opannotate_options = get_entry_value(children->data) ;

      }

    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "opgprof_options")) {

      SEC_FREE(project->opgprof_options) ;

      project->opgprof_options = get_entry_value(children->data) ;
    }

    if (children->next != NULL) {

      children = children->next ;
    }
    else {

      break ;
    }

  }

  g_list_free(children) ;

  return ;

}

void get_valgrind_opts(GList *children, Project *project) {

  while (children != NULL) {

    if (! g_strcmp0(gtk_widget_get_name(children->data), "memcheck_options")) {

      SEC_FREE(project->valgrind_memcheck) ;

      project->valgrind_memcheck = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "cachegrind_options")) {

      SEC_FREE(project->valgrind_cachegrind) ;

      project->valgrind_cachegrind = g_strdup_printf("%s", gtk_entry_get_text(GTK_ENTRY(children->data)) ) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "callgrind_options")) {

      SEC_FREE(project->valgrind_callgrind) ;

      project->valgrind_callgrind = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "helgrind_options")) {

        SEC_FREE(project->valgrind_helgrind) ;

        project->valgrind_helgrind = get_entry_value(children->data) ;

    }

    if (children->next != NULL) {

      children = children->next ;
    }
    else {

      break ;
    }

  }

  g_list_free(children) ;

  return ;

}

void get_code_fmt_opts(GList *children, Project *project) {

  while (children != NULL) {

    if (! g_strcmp0(gtk_widget_get_name(children->data), "indent_options")) {

      SEC_FREE(project->indent_options) ;

      project->indent_options = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "astyle_options")) {

      SEC_FREE(project->astyle_options) ;

      project->astyle_options = get_entry_value(children->data) ;
    }

    if (children->next != NULL) {

      children = children->next ;
    }
    else {

      break ;
    }

  }

  g_list_free(children) ;

  return ;

}


void get_about_infos(GList *children, Project *project) {

  while (children != NULL) {

    if (! g_strcmp0(gtk_widget_get_name(children->data), "author_s")) {

      SEC_FREE(project->author_s) ;

      project->author_s = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "mail_address")) {

      SEC_FREE(project->mail_address) ;

      project->mail_address = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "program_url")) {

      SEC_FREE(project->program_url) ;

      project->program_url = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "copyright_string")) {

      SEC_FREE(project->copyright_string) ;

      project->copyright_string = get_entry_value(children->data) ;
    }

    if (children->next != NULL) {

      children = children->next ;
    }
    else {

      break ;
    }

  }

  return ;

}



void get_other_infos(GList *children, Project *project) {

  while (children != NULL) {

    if (! g_strcmp0(gtk_widget_get_name(children->data), "make_options")) {

      SEC_FREE(project->make_options) ;

      project->make_options = get_entry_value(children->data) ;
    }
    else if (! g_strcmp0(gtk_widget_get_name(children->data), "bash_location")) {

      SEC_FREE(project->bash_location) ;

      project->bash_location = get_entry_value(children->data) ;
    }

    if (children->next != NULL) {

      children = children->next ;
    }
    else {

      break ;
    }

  }

  g_list_free(children) ;

  return ;

}


void get_licensing_boilerplate(GList *content, Project *project) {

  while (content != NULL) {

    if (g_strcmp0(gtk_widget_get_name(content->data), "licensing_textview") == 0) {

      GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(content->data)) ;

      GtkTextIter start_iter, end_iter ;

      gtk_text_buffer_get_start_iter(buffer, &start_iter) ;

      gtk_text_buffer_get_end_iter(buffer, &end_iter) ;

      SEC_FREE(project->licensing_boilerplate) ;

      gchar *buffer_content = gtk_text_buffer_get_text(buffer, &start_iter, &end_iter, FALSE) ;

      project->licensing_boilerplate = g_strdup(buffer_content) ;

      g_free(buffer_content) ;

      break ;

    }



    if (content->next != NULL) {

      content = content->next ;
    }
    else {

      break ;
    }

  }

  g_list_free(content) ;

  return ;

}

void get_desktop_file_boilerplate(GList *content, Project *project) {

  while (content != NULL) {

    if (! g_strcmp0(gtk_widget_get_name(content->data), "desktop_file_textview")) {

      GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(content->data)) ;

      GtkTextIter start_iter, end_iter ;

      gtk_text_buffer_get_start_iter(buffer, &start_iter) ;

      gtk_text_buffer_get_end_iter(buffer, &end_iter) ;

      SEC_FREE(project->desktop_file_boilerplate) ;

      gchar *buffer_content = gtk_text_buffer_get_text(buffer, &start_iter, &end_iter, FALSE) ;

      project->desktop_file_boilerplate = g_strdup(buffer_content) ;

      g_free(buffer_content) ;

      break ;

    }



    if (content->next != NULL) {

      content = content->next ;
    }
    else {

      break ;
    }

  }

  g_list_free(content) ;

  return ;

}



static bool entry_has_value(const gchar *entry_content, const gchar *value) {

  gchar *has_value = g_strrstr(entry_content, value) ;

   if (has_value == NULL) {

     return false ;

   }

   return true ;

}

static gint cmp(const gchar *p1, const gchar *p2) {

  return g_strcmp0(p1,p2) ;
}


GList* get_pkg_config_list(void) {

  gchar *argv[] = {"pkg-config", "--list-all", NULL } ;

  gchar **envp = g_get_environ() ;

  gchar *standard_output ;

  GError *error = NULL ;

  g_spawn_sync(NULL, argv, envp, G_SPAWN_SEARCH_PATH | G_SPAWN_STDERR_TO_DEV_NULL, NULL,NULL,&standard_output, NULL, NULL, &error);

  if (error != NULL) {

    fprintf(stderr,"%s\n", error->message) ;

    g_error_free(error) ;

    return NULL ;

  }



  gchar **pkg_config_strv = g_strsplit(standard_output, "\n", -1);

  GList *g_list_pkg_config = NULL ;

  int c = 0 ;

  while (pkg_config_strv[c] != NULL) {

    int cc = 0 ;

    while (pkg_config_strv[c][cc] != ' ') {

      ++cc ;
    }

    pkg_config_strv[c][cc] = '\0' ;

    //g_list_pkg_config = g_list_insert_sorted_with_data(g_list_pkg_config, g_strdup(pkg_config_strv[c]), (GCompareDataFunc) cmp, NULL) ;
    g_list_pkg_config = g_list_prepend(g_list_pkg_config, g_strdup(pkg_config_strv[c])) ;

    pkg_config_strv[c][cc] = ' ' ;

    ++c ;

  }

  g_list_pkg_config = g_list_sort(g_list_pkg_config, (GCompareFunc) cmp) ;

  g_free(standard_output) ;

  g_strfreev(pkg_config_strv) ;


  return g_list_first(g_list_pkg_config) ;

}

GList* get_linkage_list(void) {

  gchar *argv[] = {"ldconfig", "-p", NULL } ;

  gchar **envp = g_get_environ() ;

  gchar *standard_output ;

  GError *error = NULL ;

  g_spawn_sync(NULL, argv, envp, G_SPAWN_SEARCH_PATH | G_SPAWN_STDERR_TO_DEV_NULL, NULL,NULL,&standard_output, NULL, NULL, &error);

  if (error != NULL) {

    fprintf(stderr,"%s\n", error->message) ;

    g_error_free(error) ;

    return NULL ;

  }



  gchar **linkage_strv = g_strsplit(standard_output, "\n", -1);

  GList *g_list_linkage = NULL ;

  int c = 0 ;

  while (linkage_strv[c] != NULL) {


    g_strchug(linkage_strv[c]) ;

    if (g_str_has_prefix(linkage_strv[c],"lib")) {

      int cc = 2 ;

      while (linkage_strv[c][cc] != '.') {

        ++cc ;
      }

      linkage_strv[c][cc] = '\0' ;

      gchar *test = g_strdup(linkage_strv[c]+(sizeof(gchar)*3)) ;

      if (g_list_find_custom(g_list_linkage, test, (GCompareFunc) cmp) == NULL) {

        g_list_linkage = g_list_prepend(g_list_linkage, test) ;

      }
      else {

        g_free(test) ;
      }

      linkage_strv[c][cc] = '.' ;

    }

    ++c ;

  }

  g_list_linkage = g_list_sort(g_list_linkage, (GCompareFunc) cmp) ;

  g_free(standard_output) ;

  g_strfreev(linkage_strv) ;

  return g_list_first(g_list_linkage) ;

}

GtkWidget *create_button(const gchar *filepath, const gchar *tooltip_text) {

  return gtk_smart_icon_button_new_with_tooltip(filepath, tooltip_text)  ;

}

GtkWidget *create_checkbox(const gchar *text, const gchar *tooltip_text, const gboolean checked) {

  GtkWidget *checkbutton = gtk_check_button_new_with_label(text) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), checked) ;

  gtk_widget_set_tooltip_text(checkbutton, tooltip_text) ;

  return checkbutton ;

}

void select_warnings(GtkWidget *widget, GtkWidget *entry) {

  GtkWidget *warnings_dialog = gtk_dialog_new_with_buttons( _("Add project WARNINGS"),
                                                             GTK_WINDOW(gui->window),
                                                            GTK_DIALOG_MODAL
                                                            | GTK_DIALOG_DESTROY_WITH_PARENT
                                                            | GTK_DIALOG_USE_HEADER_BAR,
                                                            _("Add"),
                                                            GTK_RESPONSE_APPLY,
                                                            _("Cancel"),
                                                            GTK_RESPONSE_CANCEL,
                                                            NULL);

 gtk_container_set_border_width(GTK_CONTAINER(warnings_dialog), BOX_SPACING/2) ;
                      
 GtkWidget *warnings_listbox = gtk_list_box_new() ;

 gtk_container_set_border_width(GTK_CONTAINER(warnings_listbox), BOX_SPACING);

 g_object_set(G_OBJECT(warnings_listbox), "selection-mode", GTK_SELECTION_NONE, NULL) ;

 gtk_list_box_unselect_all(GTK_LIST_BOX(warnings_listbox)) ;

 GtkWidget *wall_checkbutton = create_checkbox("Wall", _("This enables all the warnings about constructions that some users\n"
                                                                               "consider questionable, and that are easy to avoid (or modify to\n"
                                                                               "prevent the warning), even in conjunction with macros. This also\n"
                                                                               "enables some language-specific warnings described in C++ Dialect\n"
                                                                               "Options and Objective-C and Objective-C++ Dialect Options."), TRUE) ;

 gtk_list_box_insert(GTK_LIST_BOX(warnings_listbox), wall_checkbutton, 0)  ;

 GtkWidget *wextra_checkbutton = create_checkbox("Wextra", _("This enables some extra warning flags that are not enabled by -Wall."), TRUE) ;
                                         
 gtk_list_box_insert(GTK_LIST_BOX(warnings_listbox), wextra_checkbutton, 1)  ;

 GtkWidget *wpedantic_checkbutton = create_checkbox("Wpedantic", _("Not strict ISO C and ISO C++ (In relationship with -std).\n"
                                                                                    "reject all programs that use forbidden extensions,\n"
                                                                                    "but some extensions are permitted !\n\n"
                                                                                    "Usually:\n"
                                                                                    "-Wpedantic does not cause warning messages for use of the alternate\n"
                                                                                    "keywords whose names begin and end with __. Pedantic warnings are\n"
                                                                                    "also disabled in the expression that follows \"__extension__\".\n\n"
                                                                                    "Look at the maunual from your compiler for further informations."), FALSE) ;

 gtk_list_box_insert(GTK_LIST_BOX(warnings_listbox), wpedantic_checkbutton, 2)  ;

 GtkWidget *w_checkbutton = create_checkbox("w", _("Inhibit all warning messages."), FALSE) ;

 gtk_list_box_insert(GTK_LIST_BOX(warnings_listbox),  w_checkbutton, 3)  ;

 GtkWidget *werror_checkbutton = create_checkbox("Werror", _("Make all warnings into errors."), FALSE) ;

 gtk_list_box_insert(GTK_LIST_BOX(warnings_listbox), werror_checkbutton, 4)  ;

 GtkWidget *vbox = gtk_dialog_get_content_area(GTK_DIALOG(warnings_dialog)) ;

 gtk_box_set_spacing(GTK_BOX(vbox), BOX_SPACING) ;

 gtk_box_pack_start(GTK_BOX(vbox), warnings_listbox, FALSE, FALSE, 0) ;

 gtk_widget_show_all(warnings_dialog) ;
                                              
 gint ret = gtk_dialog_run(GTK_DIALOG(warnings_dialog)) ;                                             

 if (ret == GTK_RESPONSE_APPLY) {

   gchar *before_entry_content =  (gchar *) gtk_entry_get_text(GTK_ENTRY(entry)) ;

   bool has_wall = entry_has_value(before_entry_content, "-Wall") ;
   bool has_wextra = entry_has_value(before_entry_content, "-Wextra") ;
   bool has_wpedantic = entry_has_value(before_entry_content, "-Wpedantic") ;
   bool has_w = entry_has_value(before_entry_content, "-w") ;
   bool has_werror = entry_has_value(before_entry_content, "-Werror") ;

   gchar *new_warnings = g_strdup_printf("%s %s %s %s %s",
                  (! has_wall && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wall_checkbutton))) ? "-Wall" : "",
                  (! has_wextra && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wextra_checkbutton))) ? "-Wextra" : "",
                  (! has_wpedantic && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wpedantic_checkbutton))) ? "-Wpedantic" : "",
                  (! has_w && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w_checkbutton))) ? "-w" : "",
                  (! has_werror && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(werror_checkbutton)))  ? "-Werror" : "") ;

   gchar *new_entry_content = g_strdup_printf("%s %s", before_entry_content, new_warnings) ;

   gtk_entry_set_text(GTK_ENTRY(entry), g_strstrip(new_entry_content)) ;

   g_free(new_entry_content) ;

   g_free(new_warnings) ;

 }

 gtk_widget_destroy(warnings_dialog) ;

 return ;

}






void select_flags(GtkWidget *widget, GtkWidget *entry) {

  GtkWidget *flags_dialog = gtk_dialog_new_with_buttons( _("Add project FLAGS"),
                                                             GTK_WINDOW(gui->window),
                                                            GTK_DIALOG_MODAL
                                                            | GTK_DIALOG_DESTROY_WITH_PARENT
                                                            | GTK_DIALOG_USE_HEADER_BAR,
                                                            _("Add"),
                                                            GTK_RESPONSE_APPLY,
                                                            _("Cancel"),
                                                            GTK_RESPONSE_CANCEL,
                                                            NULL);

 gtk_container_set_border_width(GTK_CONTAINER(flags_dialog), BOX_SPACING/2) ;
                      
 GtkWidget *flags_listbox = gtk_list_box_new() ;

 g_object_set(G_OBJECT(flags_listbox), "selection-mode", GTK_SELECTION_NONE, NULL) ;

 gtk_list_box_unselect_all(GTK_LIST_BOX(flags_listbox)) ;

 GtkWidget *flags_gdwarf_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

 GtkWidget *flags_g_checbutton = create_checkbox("-g", _("To tell GCC to emit extra information for use by a debugger."), TRUE) ;

 gtk_box_pack_start(GTK_BOX(flags_gdwarf_hbox), flags_g_checbutton, FALSE, FALSE, 0) ;

 gtk_box_set_spacing(GTK_BOX(flags_gdwarf_hbox), BOX_SPACING) ;

 gtk_list_box_insert(GTK_LIST_BOX(flags_listbox), flags_gdwarf_hbox, 0)  ;


 GtkWidget *flags_standart_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

 GtkWidget *flags_standart_checkbutton = gtk_check_button_new_with_label("-std") ;

 gtk_widget_set_tooltip_text(flags_standart_checkbutton, _("Set the standart type.")) ;

 GtkWidget *flags_standart_entry = gtk_entry_new() ;

  if (g_strcmp0(project->language, "C") == 0) {

    gtk_entry_set_placeholder_text(GTK_ENTRY(flags_standart_entry), "c99") ;

  }
  else if (g_strcmp0(project->language, "C++") == 0) {

    gtk_entry_set_placeholder_text(GTK_ENTRY(flags_standart_entry), "c++11") ;

  }

 gtk_box_pack_start(GTK_BOX(flags_standart_hbox), flags_standart_checkbutton,   FALSE,  FALSE, 0) ;
 gtk_box_pack_start(GTK_BOX(flags_standart_hbox), flags_standart_entry,         TRUE,   TRUE, 0) ;

 gtk_box_set_spacing(GTK_BOX(flags_standart_hbox), BOX_SPACING) ;

 gtk_list_box_insert(GTK_LIST_BOX(flags_listbox), flags_standart_hbox, 1)  ;


 GtkWidget *flags_optimisation_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

 GtkWidget *flags_optimisation_checkbutton = create_checkbox("-O  ", _("Set the optimisation level or type"), TRUE) ;

 GtkWidget *flags_optimisation_combo_box = gtk_combo_box_text_new() ;

 gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(flags_optimisation_combo_box), NULL, "0") ;
 gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(flags_optimisation_combo_box), NULL, "1") ;
 gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(flags_optimisation_combo_box), NULL, "2") ;
 gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(flags_optimisation_combo_box), NULL, "3") ;
 gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(flags_optimisation_combo_box), NULL, "g") ;
 gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(flags_optimisation_combo_box), NULL, "s") ;
 gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(flags_optimisation_combo_box), NULL, "fast") ;

 gtk_combo_box_set_active(GTK_COMBO_BOX(flags_optimisation_combo_box), 2) ;

 gtk_box_pack_start(GTK_BOX(flags_optimisation_hbox), flags_optimisation_checkbutton,   FALSE,  FALSE,  0) ;
 gtk_box_pack_start(GTK_BOX(flags_optimisation_hbox), flags_optimisation_combo_box,     TRUE,   TRUE,   0) ;

 gtk_box_set_spacing(GTK_BOX(flags_optimisation_hbox), BOX_SPACING) ;

 gtk_list_box_insert(GTK_LIST_BOX(flags_listbox), flags_optimisation_hbox, 2)  ;
                                              

 GtkWidget *flags_pedantic_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

 GtkWidget *flags_pedantic_checkbutton = create_checkbox("pedantic", _("Strict ISO C and ISO C++ (In relationship with -std).\n"
                                                                       "reject all programs that use forbidden extensions,\n"
                                                                       "and some other programs that do not follow ISO C and ISO C++."),TRUE) ;

 gtk_box_pack_start(GTK_BOX(flags_pedantic_hbox), flags_pedantic_checkbutton, FALSE, FALSE, 0) ;

 gtk_box_set_spacing(GTK_BOX(flags_pedantic_hbox), BOX_SPACING) ;


 gtk_list_box_insert(GTK_LIST_BOX(flags_listbox), flags_pedantic_hbox, 3)  ;



                                  

 GtkWidget *vbox = gtk_dialog_get_content_area(GTK_DIALOG(flags_dialog)) ;

 gtk_box_pack_start(GTK_BOX(vbox), flags_listbox, FALSE, FALSE, 0) ;



 gtk_widget_show_all(flags_dialog) ;
                                              
 gint ret = gtk_dialog_run(GTK_DIALOG(flags_dialog)) ;                                             

 if (ret == GTK_RESPONSE_APPLY) {

   const gchar *entry_content = gtk_entry_get_text(GTK_ENTRY(entry)) ;

   gchar *std_string = NULL ;

   gboolean std_bool = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(flags_standart_checkbutton)) ;

   if ( std_bool ) {

     const gchar *std_entry = gtk_entry_get_text(GTK_ENTRY(flags_standart_entry)) ;

     if (g_strcmp0(std_entry,"") != 0) {


      std_string = g_strdup_printf("-std=%s",std_entry) ;

     }
     else {

       std_bool = false ;
     }


   }

   const gchar *flags_optimisation = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(flags_optimisation_combo_box)) ;

   bool optimisation_bool = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(flags_optimisation_checkbutton)) ;

   gchar *optimisation_level = g_strdup_printf("%s%s", optimisation_bool ? "-O" : "",  optimisation_bool ? flags_optimisation : "") ;

   gchar *new_entry_content = g_strdup_printf("%s %s %s %s %s",
                                              entry_content,
                                              ((std_bool) && (! entry_has_value(entry_content, "-std="))) ? std_string : "",
                                              (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(flags_g_checbutton))
                                              && (! entry_has_value(entry_content, "-g")) != 0) ? "-g" : "",
                                              ((optimisation_bool) && (! entry_has_value(entry_content,"-O"))) ? optimisation_level : "",
                                              (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(flags_pedantic_checkbutton)) && (! entry_has_value(entry_content, "-pedantic"))) ? "-pedantic" : "") ;



   g_free(optimisation_level) ;

   gtk_entry_set_text(GTK_ENTRY(entry), g_strstrip(new_entry_content)) ;

   g_free(new_entry_content) ;

 }

 gtk_widget_destroy(flags_dialog) ;

 return ;

}                         

static void cppflags_tooltip(GtkWidget *widget) {

  switch (gtk_combo_box_get_active(GTK_COMBO_BOX(widget))) {

    case 1 :

      gtk_widget_set_tooltip_text(widget, "If you define this macro, then the functionality from the POSIX.1\n"
                                          "standard (IEEE Standard 1003.1) is available, as well as all of the\n"
                                          "ISO C facilities.\n\n"
                                          "The state of '_POSIX_SOURCE' is irrelevant if you define the macro\n"
                                          "'_POSIX_C_SOURCE' to a positive integer.") ;
      break ;

    case 2 :

      gtk_widget_set_tooltip_text(widget, "Define this macro to a positive integer to control which POSIX\n"
                                          "functionality is made available.  The greater the value of this\n"
                                          "macro, the more functionality is made available.\n\n"
                                          "If you define this macro to a value greater than or equal to '1',\n"
                                          "then the functionality from the 1990 edition of the POSIX.1\n"
                                          "standard (IEEE Standard 1003.1-1990) is made available.\n\n"
                                          "If you define this macro to a value greater than or equal to '2',\n"
                                          "then the functionality from the 1992 edition of the POSIX.2\n"
                                          "standard (IEEE Standard 1003.2-1992) is made available.\n\n"
                                          "If you define this macro to a value greater than or equal to\n"
                                          "'199309L', then the functionality from the 1993 edition of the\n"
                                          "POSIX.1b standard (IEEE Standard 1003.1b-1993) is made available.\n\n"
                                          "Greater values for '_POSIX_C_SOURCE' will enable future extensions.\n"
                                          "The POSIX standards process will define these values as necessary,\n"
                                          "and the GNU C Library should support them some time after they\n"
                                          "become standardized.  The 1996 edition of POSIX.1 (ISO/IEC 9945-1:\n"
                                          "1996) states that if you define '_POSIX_C_SOURCE' to a value\n"
                                          "greater than or equal to '199506L', then the functionality from the\n"
                                          "1996 edition is made available.") ;
      
    break ;

  case 3 :

    gtk_widget_set_tooltip_text(widget, "If you define this macro, functionality derived from 4.3 BSD Unix\n"
                                        "is included as well as the ISO C, POSIX.1, and POSIX.2 material.") ;
    
    break ;

  case 6 :

    gtk_widget_set_tooltip_text(widget, "If you define this macro, functionality derived from SVID is\n"
                                        "included as well as the ISO C, POSIX.1, POSIX.2, and X/Open\n"
                                        "material.") ;
    
    break ;

  case 7 :

    gtk_widget_set_tooltip_text(widget, "If you define this macro, functionality described in the X/Open\n"
                                        "Portability Guide is included.  This is a superset of the POSIX.1\n"
                                        "and POSIX.2 functionality and in fact '_POSIX_SOURCE' and\n"
                                        "'_POSIX_C_SOURCE' are automatically defined.\n\n"
                                        "As the unification of all Unices, functionality only available in\n"
                                        "BSD and SVID is also included.\n\n"
                                        "If the macro '_XOPEN_SOURCE_EXTENDED' is also defined, even more\n"
                                        "functionality is available.  The extra functions will make all\n"
                                        "functions available which are necessary for the X/Open Unix brand.\n\n"
                                        "If the macro '_XOPEN_SOURCE' has the value 500 this includes all\n"
                                        "functionality described so far plus some new definitions from the\n"
                                        "Single Unix Specification, version 2.") ;
    
    break ;
     
  case 8 :

    gtk_widget_set_tooltip_text(widget, "If you define this macro, functionality described in the X/Open\n"
                                        "Portability Guide is included.  This is a superset of the POSIX.1\n"
                                        "and POSIX.2 functionality and in fact '_POSIX_SOURCE' and\n"
                                        "'_POSIX_C_SOURCE' are automatically defined.\n\n"
                                        "As the unification of all Unices, functionality only available in\n"
                                        "BSD and SVID is also included.\n\n"
                                        "If the macro '_XOPEN_SOURCE_EXTENDED' is also defined, even more\n"
                                        "functionality is available.  The extra functions will make all\n"
                                        "functions available which are necessary for the X/Open Unix brand.\n\n"
                                        "If the macro '_XOPEN_SOURCE' has the value 500 this includes all\n"
                                        "functionality described so far plus some new definitions from the\n"
                                        "Single Unix Specification, version 2.") ;
    
    break ;

  case 9 :

    gtk_widget_set_tooltip_text(widget, "If this macro is defined some extra functions are available which\n"
                                        "rectify a few shortcomings in all previous standards.\n"
                                        "Specifically, the functions 'fseeko' and 'ftello' are available.\n"
                                        "Without these functions the difference between the ISO C interface\n"
                                        "('fseek', 'ftell') and the low-level POSIX interface ('lseek')\n"
                                        "would lead to problems.\n\n"
                                        "This macro was introduced as part of the Large File Support\n"
                                        "extension (LFS).") ;
    
    break ;

  case 10 :

    gtk_widget_set_tooltip_text(widget, "If you define this macro an additional set of functions is made\n"
                                        "available which enables 32 bit systems to use files of sizes beyond\n"
                                        "the usual limit of 2GB. This interface is not available if the\n"
                                        "system does not support files that large.  On systems where the\n"
                                        "natural file size limit is greater than 2GB (i.e., on 64 bit\n"
                                        "systems) the new functions are identical to the replaced functions.\n\n"
                                        "The new functionality is made available by a new set of types and\n"
                                        "functions which replace the existing ones.  The names of these new\n"
                                        "objects contain '64' to indicate the intention, e.g., 'off_t' vs.\n"
                                        "'off64_t' and 'fseeko' vs.  'fseeko64'.\n\n"
                                        "This macro was introduced as part of the Large File Support\n"
                                        "extension (LFS). It is a transition interface for the period when 64 bit\n"
                                        "offsets are not generally used (see '_FILE_OFFSET_BITS').") ;
    
    break ;

  case 11 :

    gtk_widget_set_tooltip_text(widget, "This macro determines which file system interface shall be used,\n"
                                        "one replacing the other.  Whereas '_LARGEFILE64_SOURCE' makes the 64 bit\n"
                                        "interface available as an additional interface, '_FILE_OFFSET_BITS'\n"
                                        "allows the 64 bit interface to replace the old interface.\n\n"
                                        "If '_FILE_OFFSET_BITS' is undefined, or if it is defined to the\n"
                                        "value '32', nothing changes.  The 32 bit interface is used and\n"
                                        "types like 'off_t' have a size of 32 bits on 32 bit systems.\n\n"
                                        "If the macro is defined to the value '64', the large file interface\n"
                                        "replaces the old interface.  I.e., the functions are not made\n"
                                        "available under different names (as they are with\n"
                                        "'_LARGEFILE64_SOURCE').  Instead the old function names now\n"
                                        "reference the new functions, e.g., a call to 'fseeko' now indeed\n"
                                        "calls 'fseeko64'.\n\n"
                                        "This macro should only be selected if the system provides\n"
                                        "mechanisms for handling large files.  On 64 bit systems this macro\n"
                                        "has no effect since the '*64' functions are identical to the normal\n"
                                        "functions.\n\n"
                                        "This macro was introduced as part of the Large File Support\n"
                                        "extension (LFS).") ;
    
    break ;

  case 12 :

    gtk_widget_set_tooltip_text(widget, "Until the revised ISO C standard is widely adopted the new features\n"
                                        "are not automatically enabled.  The GNU C Library nevertheless has\n"
                                        "a complete implementation of the new standard and to enable the new\n"
                                        "features the macro '_ISOC99_SOURCE' should be defined.") ;
    
    break ;

  case 13 :

    gtk_widget_set_tooltip_text(widget, "If you define this macro, most features are included apart from\n"
                                        "X/Open, LFS and GNU extensions; the effect is similar to defining\n"
                                        "'_POSIX_C_SOURCE' to '200809L' and '_POSIX_SOURCE', '_SVID_SOURCE',\n"
                                        "and '_BSD_SOURCE' to 1.  Defining this macro, on its own and\n"
                                        "without using compiler options such as '-ansi' or '-std=c99', has\n"
                                        "the same effect as not defining any feature test macros; defining\n"
                                        "it together with other feature test macros, or when options such as\n"
                                        "'-ansi' are used, enables those features even when the other\n"
                                        "options would otherwise cause them to be disabled.") ;
    
    break ;

  case 14 :

    gtk_widget_set_tooltip_text(widget, "If you define one of these macros, reentrant versions of several\n"
                                        "functions get declared.  Some of the functions are specified in\n"
                                        "POSIX.1c but many others are only available on a few other systems\n"
                                        "or are unique to the GNU C Library.  The problem is the delay in\n"
                                        "the standardization of the thread safe C library interface.\n\n"
                                        "Unlike on some other systems, no special version of the C library\n"
                                        "must be used for linking. There is only one version but while\n"
                                        "compiling this it must have been specified to compile as thread\n"
                                        "safe.") ;

    break ;
    
    case 15 :

      gtk_widget_set_tooltip_text(widget, "If you define one of these macros, reentrant versions of several\n"
                                          "functions get declared.  Some of the functions are specified in\n"
                                          "POSIX.1c but many others are only available on a few other systems\n"
                                          "or are unique to the GNU C Library.  The problem is the delay in\n"
                                          "the standardization of the thread safe C library interface.\n\n"
                                          "Unlike on some other systems, no special version of the C library\n"
                                          "must be used for linking. There is only one version but while\n"
                                          "compiling this it must have been specified to compile as thread\n"
                                          "safe.") ;

      break ;

    default :

      gtk_widget_set_tooltip_text(widget, "We recommend you use '_GNU_SOURCE' in new programs.  If you don't\n"
                                          "specify the '-ansi' option to GCC, or other conformance options such as\n"
                                          "'-std=c99', and don't define any of these macros explicitly, the effect\n"
                                          "is the same as defining '_DEFAULT_SOURCE' to 1.") ;

      break ;    

                                                                                                                                                                                                                                                                                                                                                                   

  }

  return ;

}

void add_cppflags(GtkWidget *widget, GtkWidget *entry) {

  GtkWidget *cppflags_dialog = gtk_dialog_new_with_buttons(_("Project CPPFLAGS"),
                                                    GTK_WINDOW(gui->window),
                                                    GTK_DIALOG_MODAL
                                                    | GTK_DIALOG_DESTROY_WITH_PARENT
                                                    | GTK_DIALOG_USE_HEADER_BAR,
                                                    _("Add"),
                                                    GTK_RESPONSE_APPLY,
                                                    _("Cancel"),
                                                    GTK_RESPONSE_CANCEL,
                                                    NULL);


   gtk_container_set_border_width(GTK_CONTAINER(cppflags_dialog), 16) ;

   GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

   gtk_box_set_spacing(GTK_BOX(hbox), 16) ;

   GtkWidget *label  = gtk_label_new(" -D ") ;

   GtkWidget *combo_text = gtk_combo_box_text_new_with_entry() ;

   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "__STRICT_ANSI__") ;
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_POSIX_SOURCE") ;
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_POSIX_C_SOURCE") ;
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_BSD_SOURCE") ;
  
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_ISOC99_SOURCE") ;
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_ISOC11_SOURCE") ;
  
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_SVID_SOURCE") ;
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_XOPEN_SOURCE") ;
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_XOPEN_SOURCE_EXTENDED") ;

   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_LARGEFILE_SOURCE") ;
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_LARGEFILE64_SOURCE") ;
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_FILE_OFFSET_BITS") ;
  

   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_DEFAULT_SOURCE") ;
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_ATFILE_SOURCE") ;
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_GNU_SOURCE") ;
   
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_REENTRANT") ;
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_THREAD_SAFE") ;
   gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_text), NULL, "_FORTIFY_SOURCE") ;
  
   gtk_widget_set_size_request(combo_text, 256, -1) ;

   g_signal_connect(G_OBJECT(combo_text), "changed", G_CALLBACK(cppflags_tooltip), NULL) ;

   GtkWidget *label_eq = gtk_label_new(" = ") ;

   GtkWidget *cppflags_entry = gtk_entry_new() ;

   gtk_box_pack_start(GTK_BOX(hbox), label,           FALSE, FALSE, 0) ;
   gtk_box_pack_start(GTK_BOX(hbox), combo_text,      TRUE, TRUE, 0) ;
   gtk_box_pack_start(GTK_BOX(hbox), label_eq,        FALSE, FALSE, 0) ;
   gtk_box_pack_start(GTK_BOX(hbox), cppflags_entry,  FALSE, FALSE, 0) ;

   GtkWidget *vbox = gtk_dialog_get_content_area(GTK_DIALOG(cppflags_dialog)) ;

   gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0) ;

   gtk_widget_show_all(cppflags_dialog) ;

   gint ret = gtk_dialog_run(GTK_DIALOG(cppflags_dialog)) ;

   if (ret == GTK_RESPONSE_APPLY) {

      gchar *cppflag = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_text)) ;

      const gchar *cppflag_value = gtk_entry_get_text(GTK_ENTRY(cppflags_entry)) ;

      const gchar *entry_content = gtk_entry_get_text(GTK_ENTRY(entry)) ;

      gchar *new_entry_content = NULL ;

      if (cppflag != NULL && g_strcmp0(cppflag_value,"") != 0) {

        new_entry_content = g_strdup_printf("%s -D%s=%s", entry_content, cppflag, cppflag_value) ;
      }
      else if (cppflag != NULL && g_strcmp0(cppflag_value,"") == 0) {

        new_entry_content = g_strdup_printf("%s -D%s", entry_content, cppflag) ;
      }

      g_free(cppflag) ;

      gtk_entry_set_text(GTK_ENTRY(entry), g_strstrip(new_entry_content)) ;

      g_free(new_entry_content) ;

   }

   gtk_widget_destroy(cppflags_dialog) ;

   return ;

}

static GList *fill_listbox_with_g_list(GList *g_list, GtkWidget *listbox) {

  g_list = g_list_first(g_list) ;

  gint c = 0 ;

  while (g_list != NULL) {

    if (g_list->data != NULL) {

      if ( g_strcmp0((const gchar *) g_list->data,"")) {

        GtkWidget *checkbutton = gtk_check_button_new_with_label((const gchar *) g_list->data) ;

        gtk_list_box_insert(GTK_LIST_BOX(listbox), checkbutton, c) ;

      }

      ++c ;

    }
    else {

      break ;
    }

    if (g_list->next != NULL) {

      g_list = g_list->next ;
    }
    else {

      break ;
    }

  }

  return g_list_first(g_list) ;
}

static gchar *get_entry_value(GtkWidget *entry) {

  return g_strdup(gtk_entry_get_text(GTK_ENTRY(entry))) ;

}

static void fill_entry(GtkWidget *entry, const gchar *string) {

  const gchar *entry_content = gtk_entry_get_text(GTK_ENTRY(entry)) ;

  gchar *entry_new_content = g_strdup_printf("%s %s", (entry_content != NULL) ? entry_content : "", (string != NULL) ? string : "") ;

  gtk_entry_set_text(GTK_ENTRY(entry), entry_new_content) ;

  g_free(entry_new_content) ;

  return ;

}

void add_pkg_config_to_project(GtkWidget *button, libraries_entries *entries) {

  GtkWidget *dialog = gtk_dialog_new_with_buttons(_("Add pkg-config to project"),
                                                    GTK_WINDOW(gui->window),
                                                    GTK_DIALOG_MODAL
                                                    | GTK_DIALOG_DESTROY_WITH_PARENT
                                                    | GTK_DIALOG_USE_HEADER_BAR,
                                                    _("Add"),
                                                    GTK_RESPONSE_APPLY,
                                                    _("Cancel"),
                                                    GTK_RESPONSE_CANCEL,
                                                    NULL);





  GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL) ;

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC) ;

  #if (GTK_MINOR_VERSION >= 22)

    gtk_scrolled_window_set_max_content_height(GTK_SCROLLED_WINDOW(scrolled_window), 512) ;

    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled_window), 256+128) ;

    gtk_scrolled_window_set_max_content_width(GTK_SCROLLED_WINDOW(scrolled_window), 256+128) ;

    gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrolled_window), 256+128) ;

  #else

    gtk_widget_set_size_request(scrolled_window, 256+128, 512) ;

  #endif

  GtkWidget *pkg_config_listbox= gtk_list_box_new() ;

  g_object_set(G_OBJECT(pkg_config_listbox), "selection-mode", GTK_SELECTION_NONE, NULL) ;

  gtk_list_box_unselect_all(GTK_LIST_BOX(pkg_config_listbox)) ;

  GList *g_list_pkg_config = get_pkg_config_list() ;

  g_list_pkg_config = fill_listbox_with_g_list(g_list_pkg_config, pkg_config_listbox) ;

  gtk_container_add(GTK_CONTAINER(scrolled_window), pkg_config_listbox) ;

  GtkWidget *vbox = gtk_dialog_get_content_area(GTK_DIALOG(dialog)) ;

  gtk_box_set_spacing(GTK_BOX(vbox), BOX_SPACING) ;

  gtk_container_add(GTK_CONTAINER(vbox), scrolled_window) ;

  gtk_widget_show_all(dialog) ;

  gint ret = gtk_dialog_run(GTK_DIALOG(dialog)) ;

  if (ret == GTK_RESPONSE_APPLY) {

    int c = 0 ;

    GtkListBoxRow *row = NULL ;

    gchar *pkg_config_cflags_str  = NULL ;
    gchar *pkg_config_libs_str    = NULL ;

    while ((row=gtk_list_box_get_row_at_index(GTK_LIST_BOX(pkg_config_listbox), c)) != NULL) {

      GtkWidget *toggle_button = gtk_bin_get_child(GTK_BIN(row)) ;

      if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button))) {

          gchar *copy_cflags = g_strdup(pkg_config_cflags_str) ;

          SEC_FREE(pkg_config_cflags_str)

          if (copy_cflags == NULL) {

            pkg_config_cflags_str = g_strdup_printf("`pkg-config --cflags %s` ", gtk_button_get_label(GTK_BUTTON(toggle_button))) ;

          }
          else {

             pkg_config_cflags_str = g_strdup_printf("%s `pkg-config --cflags %s` ", copy_cflags, gtk_button_get_label(GTK_BUTTON(toggle_button))) ;

          }

          g_free(copy_cflags) ;

          gchar *copy_ldlibs = g_strdup(pkg_config_libs_str) ;

          SEC_FREE(pkg_config_libs_str)

          if (copy_ldlibs == NULL) {

            pkg_config_libs_str = g_strdup_printf("`pkg-config --libs %s`", gtk_button_get_label(GTK_BUTTON(toggle_button))) ;
          }
          else {

            pkg_config_libs_str = g_strdup_printf("%s `pkg-config --libs %s`", copy_ldlibs, gtk_button_get_label(GTK_BUTTON(toggle_button))) ;
          }

          g_free(copy_ldlibs) ;

      }

      ++c ;

    }


    fill_entry(entries->ldflags_entry, pkg_config_cflags_str) ;

    g_free(pkg_config_cflags_str) ;

    fill_entry(entries->ldlibs_entry, pkg_config_libs_str) ;

    g_free(pkg_config_libs_str) ;



  }


  g_list_free_full(g_list_pkg_config, (GDestroyNotify) free);

  gtk_widget_destroy(dialog) ;

  return ;

}

void add_linkage_to_project(GtkWidget *button, GtkWidget *entry) {

  GtkWidget *dialog = gtk_dialog_new_with_buttons(_("Add links to project"),
                                                    GTK_WINDOW(gui->window),
                                                    GTK_DIALOG_MODAL
                                                    | GTK_DIALOG_DESTROY_WITH_PARENT
                                                    | GTK_DIALOG_USE_HEADER_BAR,
                                                    _("Add"),
                                                    GTK_RESPONSE_APPLY,
                                                    _("Cancel"),
                                                    GTK_RESPONSE_CANCEL,
                                                    NULL);





  GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL) ;

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC) ;

  #if (GTK_MINOR_VERSION >= 22)

    gtk_scrolled_window_set_max_content_height(GTK_SCROLLED_WINDOW(scrolled_window), 512) ;

    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled_window), 256+128) ;

    gtk_scrolled_window_set_max_content_width(GTK_SCROLLED_WINDOW(scrolled_window), 256+128) ;

    gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrolled_window), 256+128) ;

  #else

    gtk_widget_set_size_request(scrolled_window, 256+128, 512) ;

  #endif

  GtkWidget *linkage_listbox= gtk_list_box_new() ;

  g_object_set(G_OBJECT(linkage_listbox), "selection-mode", GTK_SELECTION_NONE, NULL) ;

  gtk_list_box_unselect_all(GTK_LIST_BOX(linkage_listbox)) ;

  GList *g_list_linkage = get_linkage_list() ;

  g_list_linkage = fill_listbox_with_g_list(g_list_linkage, linkage_listbox) ;

  gtk_container_add(GTK_CONTAINER(scrolled_window), linkage_listbox) ;

  GtkWidget *vbox = gtk_dialog_get_content_area(GTK_DIALOG(dialog)) ;

  gtk_box_set_spacing(GTK_BOX(vbox), BOX_SPACING) ;

  gtk_container_add(GTK_CONTAINER(vbox), scrolled_window) ;

  gtk_widget_show_all(dialog) ;

  gint ret = gtk_dialog_run(GTK_DIALOG(dialog)) ;

  if (ret == GTK_RESPONSE_APPLY) {

    int c = 0 ;

    GtkListBoxRow *row = NULL ;

    gchar *linking_str  = NULL ;

    while ((row=gtk_list_box_get_row_at_index(GTK_LIST_BOX(linkage_listbox), c)) != NULL) {

      GtkWidget *toggle_button = gtk_bin_get_child(GTK_BIN(row)) ;

      if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button))) {

        gchar *copy_linking_str = g_strdup(linking_str) ;

        SEC_FREE(linking_str) ;

        if (copy_linking_str == NULL) {

          linking_str = g_strdup_printf("-l%s", gtk_button_get_label(GTK_BUTTON(toggle_button))) ;
        }
        else {

          linking_str = g_strdup_printf("%s -l%s", copy_linking_str, gtk_button_get_label(GTK_BUTTON(toggle_button))) ;

        }

        g_free(copy_linking_str) ;

      }

      ++c ;

    }

    fill_entry(entry, linking_str) ;

    g_free(linking_str) ;

  }

  g_list_free_full(g_list_linkage, (GDestroyNotify) free);

  gtk_widget_destroy(dialog) ;

  return ;

}

static void sphinx_cmdline_insert(GString *string, const gchar *val) {

  if (val != NULL) {

    g_string_append(string, " ") ;
    g_string_append(string, val) ;

  }

  return ;

}

static void foreach_sphinx_extension(gpointer data, GString *user_data) {

  if (! g_strcmp0(data,"autodoc")) {

    // We discard the --ext-autodoc, because only python use it and it make mk-project bugging if enabled.

    return ;
  }

  sphinx_cmdline_insert(user_data, data) ;

  return ;

}

void generate_sphinx_doc(gchar *main_make_filepath) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  /** Usage of sphinx as documentation generator, we process... **/

  gchar *sphinx_quickstart = have_app_application("sphinx-quickstart") ;

  if (sphinx_quickstart != NULL) {

    GString *sphinx_cmdline = g_string_new(sphinx_quickstart);

    sphinx_cmdline_insert(sphinx_cmdline, "--sep") ;


    // Required for using quiet NOT INTERACTIVE sphinx Makefile generation.

    gchar *sphinx_project = g_strdup_printf("--project %s", project->prgname) ;

    sphinx_cmdline_insert(sphinx_cmdline, sphinx_project) ;

    g_free(sphinx_project) ;



    if (g_strcmp0(project->author_s,"") == 0) {

      // --author option required for using quiet NOT INTERACTIVE sphinx Makefile generation.

      project->author_s = g_strdup(g_get_real_name()) ;

    }



    gchar *sphinx_author = g_strdup_printf("--author %s", project->author_s) ;

    sphinx_cmdline_insert(sphinx_cmdline, sphinx_author) ;

    g_free(sphinx_author) ;



    if (! g_strcmp0(project->version_string,"")) {

      // Required for using quiet NOT INTERACTIVE sphinx Makefile generation.
      project->version_string = g_strdup("1.0") ;

    }

    gchar *sphinx_version = g_strdup_printf("-v %s", project->version_string) ;

    sphinx_cmdline_insert(sphinx_cmdline, sphinx_version) ;

    g_free(sphinx_version) ;



    gchar *sphinx_language = NULL ;

    if (project->sphinx_options->language != NULL && g_strcmp0(project->sphinx_options->language,"")) {

      sphinx_language = g_strdup_printf("language=%s", project->sphinx_options->language) ;

      sphinx_cmdline_insert(sphinx_cmdline, sphinx_language) ;

      g_free(sphinx_language) ;

    }

    sphinx_cmdline_insert(sphinx_cmdline, "-q") ;
    sphinx_cmdline_insert(sphinx_cmdline, "--makefile") ;
    sphinx_cmdline_insert(sphinx_cmdline, "--no-batchfile") ;
    sphinx_cmdline_insert(sphinx_cmdline, "--no-use-make-mode") ;

    g_ptr_array_foreach(project->sphinx_options->extension, (GFunc) foreach_sphinx_extension, sphinx_cmdline) ;

    g_string_append(sphinx_cmdline, " \r") ;


    gchar *sphinx_mk_folderpath = g_strconcat(project->project_folderpath, "/", "doc", NULL) ;
    gchar *cd_to_sphinx_dir_cmd = g_strdup_printf("cd %s \r", sphinx_mk_folderpath) ;
    vte_terminal_feed_child( VTE_TERMINAL(gtk_mkterm_get_vte_terminal(gui->make_terminal)), cd_to_sphinx_dir_cmd, strlen(cd_to_sphinx_dir_cmd) ) ;
    free(cd_to_sphinx_dir_cmd) ;

    gchar *sphinx_cmdline_ptr = g_string_free(sphinx_cmdline, FALSE);
    vte_terminal_feed_child( VTE_TERMINAL(gtk_mkterm_get_vte_terminal(gui->make_terminal)), sphinx_cmdline_ptr, strlen(sphinx_cmdline_ptr) ) ;
    free(sphinx_cmdline_ptr) ;

    GMainContext *thread_main_context = g_main_context_ref_thread_default() ;

    while (g_main_context_pending(thread_main_context)) {

      g_main_context_iteration(thread_main_context, FALSE) ;

    }



    generate_sphinx_targets(sphinx_mk_folderpath, main_make_filepath) ;

    g_free(sphinx_mk_folderpath) ;

    g_main_context_unref(thread_main_context) ;
        
  }

  return ;

}

