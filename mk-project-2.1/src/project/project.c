#include "project.h"

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

GtkWidget *new_project_assistant = NULL ;

GList *sphinx_extensions = NULL ;

gchar *sphinx_quickstart = NULL ;

/** GtkAssistant functions **/

static void configure_project_language(void) ;

/** Compiler settings configuration **/
static void configure_compiler_project(void) ;

/** C/C++ Project assistant pages **/

static void configure_c_project_main(void) ;

static void configure_disassembling_options(void) ;

static void configure_oprofile_options(void) ;

static void configure_valgrind_options(void) ;

static void configure_code_c_fmt_project(void) ;

/** Documentation settings **/

static GList *get_sphinx_extensions(void) ;

static void configure_new_doc_project(void) ;

/** About informations **/

static void configure_about_project(void) ;

/** Others informations **/

static void configure_others_info_project(void) ;

/** Licensing boilerplate **/

static void configure_licensing_project(void) ;

static void get_combo_value_licensing(GtkComboBox *widget, char *user_data) ;


/** *.Desktop file boilerplate  **/

static void configure_desktop_file_project(void) ;


/** Summary of project  **/

static void summary_of_project(void) ;



/** Compiler and Interpreter check **/

static gboolean is_compiler_focus_out(GtkWidget *widget, GdkEvent  *event, gpointer user_data) ;

static bool check_compiler(const char *compiler) ;


/** On cancel page **/

static void cancel_event(GtkAssistant *assistant, gpointer pointer) ;


/** On prepare page: before the page is shown **/

static void on_prepare_page(GtkAssistant *assistant, GtkWidget *page, gpointer user_data) ;

/** On apply page: When the user press the Next button. **/

static void on_apply_page(GtkAssistant *assistant, gpointer user_data) ;

/** On close: When finished configurating project-> **/

static void on_close_project(GtkAssistant *assistant, gpointer user_data) ;




/** Language callback **/
static void get_combo_value_language(GtkComboBox *widget, char *user_data) ;

/** End configuration of Project **/


/** C/C++ Project callbacks  **/

static void get_combo_value_c_src_ext(GtkComboBox *widget, GtkWidget *main_file_entry) ;

static void get_combo_value_c_hdr_ext(GtkComboBox *widget) ;

/** End C/C++ Project pages. **/

/** Select project folder **/
void select_folder_dialog(GtkWidget *widget, GtkWidget *page) ;

/** Export project settings as profile. **/

static void save_as_profile(GtkWidget *widget) ;

/** All projects callbacks **/

static void get_entry_value_prgname(GtkWidget *widget, GdkEvent  *event, GtkWidget *page) ;

static char *get_language(void) ;

/** Intern functions **/

static void update_summary(GList *content) ;

/** End intern functions **/

static gboolean is_compiler_focus_out(GtkWidget *widget, GdkEvent  *event, gpointer   user_data) {

  gchar *content = g_path_get_basename(gtk_entry_get_text(GTK_ENTRY(widget))) ;

  if (! g_strcmp0(project->compiler, content) ) {

    g_free(content) ;

    return FALSE ;

  }


  if ( have_app_application(content) ) {

    if (! check_compiler(content)) {

      if (g_strcmp0(project->language, "C") == 0) {

        display_message_dialog( _("Compiler not valid !"), _("The given compiler cannot compile source code.\nSo it's not a valid C compiler !\n\nAdvice: use cc."),  GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

        gtk_entry_set_text(GTK_ENTRY(widget), "cc") ;
      }
      else if (g_strcmp0(project->language, "C++") == 0) {

        display_message_dialog( _("Compiler not valid !"), _("The given compiler cannot compile source code.\nSo it's not a valid C++ compiler !\n\nAdvice: use c++."),  GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

        gtk_entry_set_text(GTK_ENTRY(widget), "c++") ;

      }

    }

  }
  else {

    display_message_dialog( _("Compiler not found !"), _("The given compiler doesn't exist in the $PATH variable"),  GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    if (g_strcmp0(project->language, "C") == 0) {
      gtk_entry_set_text(GTK_ENTRY(widget), "cc") ;
    }
    else if (g_strcmp0(project->language, "C++") == 0) {
      gtk_entry_set_text(GTK_ENTRY(widget), "c++") ;
    }
  }

  g_free(content) ;

  return FALSE ;
}

static bool check_compiler(const char *compiler) {

  FILE *fp = NULL ;

  if (g_strcmp0(project->language,"C") == 0) {

   gchar *filepath = g_strdup_printf("%s/testit.c", g_get_tmp_dir()) ;

   fp = fopen(filepath, "w") ;

   g_free(filepath) ;

  }
  else if (g_strcmp0(project->language,"C++") == 0) {

   gchar *filepath = g_strdup_printf("%s/testit.cpp", g_get_tmp_dir()) ;

   fp = fopen(filepath, "w") ;

   g_free(filepath) ;

  }

  const char *src_code = "int main(int argc, char *argv[]) {\n"
                          "  \n"
                          "  return 0 ;\n"
                          "}\n" ;

  char *pathname = NULL ;

  if (g_strcmp0(project->language,"C") == 0) {
    pathname = g_strdup_printf("%s/testit.%s",g_get_tmp_dir(), "c") ;
  }
  else if ( g_strcmp0(project->language,"C++") == 0) {
    pathname = g_strdup_printf("%s/testit.%s", g_get_tmp_dir(), "cpp") ;
  }

  fwrite(src_code, strlen(src_code), sizeof(char), fp) ;

  fflush(fp) ;

  fclose(fp) ;

  gchar *a_out_file = g_strdup_printf("%s/a.out",g_get_tmp_dir()) ;

  char *cmdline = g_strdup_printf("%s %s -o %s", compiler, pathname, a_out_file) ;



  if (system(cmdline) != 0) {

    free(cmdline) ;

    g_remove(pathname) ;

    free(pathname) ;

    return false ;
  }

  g_remove(pathname) ;

  g_remove(a_out_file) ;

  free(pathname) ;

  free(cmdline) ;

  return true ;

}



static void get_combo_value_c_src_ext(GtkComboBox *widget, GtkWidget *main_file_entry) {

  gchar *combo_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget)) ;

  if (combo_text == NULL) {

    return ;
  }

  SEC_FREE(project->ext_src) ;

  project->ext_src = g_strdup(combo_text) ;

  SEC_FREE(project->main_file) ;

  project->main_file = g_strdup_printf("%s%s", "main", project->ext_src) ;

  gtk_entry_set_text(GTK_ENTRY(main_file_entry), project->main_file) ;

  SEC_FREE(combo_text) ;

  return ;

}

static void get_combo_value_c_hdr_ext(GtkComboBox *widget) {

  gchar *combo_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget)) ;

  if (combo_text == NULL) {

    return ;
  }

  SEC_FREE(project->ext_hdr) ;

  project->ext_hdr = g_strdup(combo_text) ;

  SEC_FREE(combo_text) ;

  return ;

}


static void get_combo_value_language(GtkComboBox *widget, char *user_data) {

  gchar *combo_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget)) ;

  if (combo_text == NULL) {

    return ;

  }

  SEC_FREE(user_data) ;

  user_data = g_strdup(combo_text) ;


  return ;

}

static void get_combo_value_licensing(GtkComboBox *widget, char *user_data) {

  gchar *licensing = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget)) ;

  if (licensing == NULL) {

    return ;

  }

  SEC_FREE(project->license) ;

  project->license = g_strdup(licensing) ;

  gchar *contents ;

  gsize length ;

  GError *error = NULL ;


  SEC_FREE(project->licensing_boilerplate) ;

  if ( g_strcmp0(licensing, "gpl") == 0) {

    g_file_get_contents(PATH_TO_LICENSING_GPL, &contents, &length, &error) ;

  }
  else if ( g_strcmp0(licensing, "agpl") == 0) {

    g_file_get_contents(PATH_TO_LICENSING_AGPL, &contents, &length, &error) ;

  }
  else if ( g_strcmp0(licensing, "lgpl") == 0) {

    g_file_get_contents(PATH_TO_LICENSING_LGPL, &contents, &length, &error) ;
  }
  else if ( g_strcmp0(licensing, "fdl") == 0) {

    g_file_get_contents(PATH_TO_LICENSING_FDL, &contents, &length, &error) ;

  }
  else if ( g_strcmp0(licensing, "Apache 2.0") == 0) {

    g_file_get_contents(PATH_TO_LICENSING_APACHE_2_0, &contents, &length, &error) ;

  }
  else if ( g_strcmp0(licensing, "Clear BSD") == 0) {

    g_file_get_contents(PATH_TO_LICENSING_CLEAR_BSD, &contents, &length, &error) ;

  }
  else if ( g_strcmp0(licensing, "Free BSD") == 0) {

    g_file_get_contents(PATH_TO_LICENSING_FREE_BSD, &contents, &length, &error) ;

  }
  else if ( g_strcmp0(licensing, _("Other")) == 0) {

    contents = g_strdup("\n") ;

  }

  if (error != NULL)  {

    display_message_dialog(_("Error open file"), _("Cannot open licensing boilerplate."), GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

  }
  else {

    project->licensing_boilerplate = g_strdup(contents) ;

    g_free(contents) ;

  }

  SEC_FREE(licensing) ;

  return ;
}

static void get_entry_value_prgname(GtkWidget *widget, GdkEvent *event, GtkWidget *page) {

  SEC_FREE(project->prgname) ;

  project->prgname = g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))) ;

  if ( (g_strcmp0(project->prgname, "") != 0) && (g_strcmp0(project->project_folderpath, N_("Select the project folder") ) != 0) ) {

     gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), page, TRUE) ;
  }
  else {

    gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), page, FALSE) ;
  }


  return ;

}

static GList *get_sphinx_extensions(void) {

  gchar *sphinx_quickstart_check = NULL ;

  if ((sphinx_quickstart_check=have_app_application("sphinx-quickstart")) == NULL) {

    return NULL ;

  }

  g_free(sphinx_quickstart_check) ;

  gchar *argv[] = { "sphinx-quickstart", "--help", NULL} ;

  gchar **envp = g_get_environ() ;

  gchar *standard_output = NULL ;

  GError *error = NULL ;

  g_spawn_sync(NULL, argv, envp, G_SPAWN_SEARCH_PATH | G_SPAWN_STDERR_TO_DEV_NULL, NULL,NULL,&standard_output, NULL, NULL, &error);

  gchar **lines_ptr = g_strsplit(standard_output,"\n", -1) ;

  GList *g_list_sphinx_extensions = NULL ;

  int c=0 ;

  while (lines_ptr[c] != NULL) {

    gchar *extension = NULL ;

    if ((extension = g_strrstr(lines_ptr[c], "--ext-")) != NULL) {

      int cc = 0 ;

      while (extension[cc] != ' ') {

        ++cc ;
      }

      extension[cc]='\0' ;

      gchar *input = g_strdup(&extension[6]) ;

      if (! g_strcmp0(input,"autodoc")) {

        ++c ;

        free(input) ;

        continue ;

      }


      g_list_sphinx_extensions = g_list_append(g_list_sphinx_extensions, input ) ;

    }

    ++c ;

  }

  return g_list_first(g_list_sphinx_extensions) ;

}

static void save_as_profile(GtkWidget *widget) {

  GtkWidget *window = gtk_widget_get_toplevel(widget) ;

  GtkWidget *export_profile_file_dialog =  gtk_file_chooser_dialog_new( _("Export project as profile"), GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE,
                                                                        _("Export"), GTK_RESPONSE_OK,
                                                                        _("Cancel"), GTK_RESPONSE_CANCEL,
                                                                        NULL) ;

  GtkFileFilter *file_filter = gtk_file_filter_new();
                        
  gtk_file_filter_add_pattern(file_filter, "*.mkpp");                      
                        
  gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(export_profile_file_dialog), file_filter);                       

  gint res = gtk_dialog_run(GTK_DIALOG(export_profile_file_dialog)) ;

  if (res == GTK_RESPONSE_OK) {
  
    gchar *profile_path = NULL ;
  
    gchar *filepath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(export_profile_file_dialog)) ;

    if (filepath != NULL) {
    
      if (! g_str_has_suffix(filepath, ".mkpp")) {
      
        profile_path = g_strdup_printf("%s%s", filepath, ".mkpp") ;
    
      }

    g_free(filepath) ;

    }

    if (profile_path != NULL) {

      export_as_profile(profile_path) ;
      
      g_free(profile_path) ;

    }

  }

  gtk_widget_destroy(export_profile_file_dialog) ;

  return ;

}

static void update_summary(GList *content) {

  while (content != NULL) {

    if (! g_strcmp0( gtk_widget_get_name(content->data), "summary_of_project_label")) {

      gchar *summary_text =    g_strdup_printf( _("<big>Creating new project named:</big> <big><b>%s</b></big>.\n\n"
                                              "<big>Version:</big> <big><b>%s</b></big>\n\n<big>Using the</big> <big><b>%s</b></big> <big>language</big>.\n\n"
                                              "<big>To Install in folder:</big>\n<big><i>%s</i></big>"),

                                              project->prgname, project->version_string, project->language, project->project_folderpath) ;

      gtk_label_set_markup(GTK_LABEL(content->data), summary_text) ;

      free(summary_text) ;
    }

    if (content->next != NULL) {

      content = content->next ;
    }
    else {

      break ;
    }

  }

  return ;

}





static void on_prepare_page(GtkAssistant *assistant, GtkWidget *page, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if (page == NULL) {

    return ;
  }

  GList *children = gtk_container_get_children(GTK_CONTAINER(page)) ;

  while ( (children != NULL) && (children->data != NULL) ) {

    if (! g_strcmp0(gtk_widget_get_name(children->data) , "data_c_project")) {

      update_c_project( gtk_container_get_children(GTK_CONTAINER(children->data)), project ) ;
    }

    if (! g_strcmp0(gtk_widget_get_name(children->data), "compiler_settings_container")) {

      update_compiler( gtk_container_get_children(GTK_CONTAINER(children->data)), project ) ;
    }

    if (! g_strcmp0(gtk_widget_get_name(children->data), "licensing_hbox")) {

      GList *child_of_children = gtk_container_get_children(children->data) ;

      child_of_children = g_list_first(child_of_children) ;

      while (child_of_children != NULL) {

        if (child_of_children->data != NULL) {

          if (! g_strcmp0(gtk_widget_get_name(child_of_children->data),"licensing_viewport")) {


            update_licensing( gtk_container_get_children(GTK_CONTAINER(child_of_children->data)), project ) ;

            break ;

          }
        }

        if (child_of_children->next != NULL) {

          child_of_children = child_of_children->next ;
        }
        else {

          break ;
        }

      }

      g_list_free(child_of_children) ;

    }
    if (! g_strcmp0(gtk_widget_get_name(children->data), "sphinx")) {

      if (project->sphinx_options->extension == NULL) {

        project->sphinx_options->extension = g_ptr_array_new_with_free_func((GDestroyNotify) free);
      }
      else {

        gpointer ptr = g_ptr_array_free(project->sphinx_options->extension, TRUE) ;

        g_free(ptr) ;

        project->sphinx_options->extension = g_ptr_array_new_with_free_func((GDestroyNotify) free);

      }

    }
    if (! g_strcmp0(gtk_widget_get_name(children->data), "summary_of_project_container")) {

      update_summary( gtk_container_get_children(GTK_CONTAINER(children->data)) ) ;

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



static void on_apply_page(GtkAssistant *assistant, gpointer user_data) {

  GtkWidget *current_page = gtk_assistant_get_nth_page(assistant, gtk_assistant_get_current_page(assistant)) ;

  GList *page_content = gtk_container_get_children(GTK_CONTAINER(current_page)) ;

  while (page_content != NULL) {

    if (! g_strcmp0(gtk_widget_get_name(page_content->data),  "licensing_hbox")) {

      GList *child_of_children = gtk_container_get_children(page_content->data) ;

      child_of_children = g_list_first(child_of_children) ;

      while (child_of_children != NULL) {

        if (child_of_children->data != NULL) {

          if (! g_strcmp0(gtk_widget_get_name(child_of_children->data),"licensing_viewport")) {

            get_licensing_boilerplate( gtk_container_get_children(GTK_CONTAINER(child_of_children->data)), project ) ;

            break ;

          }
        }

        if (child_of_children->next != NULL) {

          child_of_children = child_of_children->next ;
        }
        else {

          break ;
        }

      }

      g_list_free(child_of_children) ;

    }
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data),  "desktop_file_viewport")) {

      get_desktop_file_boilerplate( gtk_container_get_children(GTK_CONTAINER(page_content->data)), project ) ;

    }

    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "compiler_settings_container")) {

      get_compiler_datas( gtk_container_get_children(GTK_CONTAINER(page_content->data)), project ) ;

    }
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "disassembling_opts")) {

      get_disassembling_opts( gtk_container_get_children(GTK_CONTAINER(page_content->data)), project ) ;

    }
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "oprofiling_opts")) {

      get_oprofile_opts( gtk_container_get_children(GTK_CONTAINER(page_content->data)), project ) ;

    }
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "valgrind_opts")) {

      get_valgrind_opts(gtk_container_get_children(GTK_CONTAINER(page_content->data)), project ) ;

    }
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "code_fmt")) {

      get_code_fmt_opts( gtk_container_get_children(GTK_CONTAINER(page_content->data)), project ) ;

    }
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "about_infos")) {

      get_about_infos( gtk_container_get_children(GTK_CONTAINER(page_content->data)), project ) ;

    }
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "others_infos")) {

      get_other_infos( gtk_container_get_children(GTK_CONTAINER(page_content->data)), project ) ;

    }
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "sphinx")) {

      GtkWidget *expander  = g_list_nth_data(gtk_container_get_children(GTK_CONTAINER(page_content->data)), 1) ;

      GtkWidget *vbox = g_list_nth_data(gtk_container_get_children(GTK_CONTAINER(expander)), 0) ;

      GtkWidget *listbox = g_list_nth_data(gtk_container_get_children(GTK_CONTAINER(vbox)), 2) ;

      get_sphinx_extension(listbox) ;

    }

    if (page_content->next != NULL) {

      page_content = page_content->next ;
    }
    else {

      break ;
    }

  }

  g_list_free(page_content) ;

  return ;

}

static void on_close_project(GtkAssistant *assistant, gpointer user_data) {

  /** New project creation launching **/

  gtk_widget_destroy(GTK_WIDGET(assistant)) ;

  create_new_project() ;

  return ;

}




void select_folder_dialog(GtkWidget *widget, GtkWidget *page) {

  GtkWidget *new_project_select_folder_dialog = gtk_file_chooser_dialog_new( _("Choose a location where to create the project.") ,
                                                                            GTK_WINDOW(gui->window),
                                                                            GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER,
                                                                            "OK",     // No gettext macro to make sure the program is in the English language.
                                                                            GTK_RESPONSE_OK,
                                                                            "Cancel", // No gettext macro to make sure the program is in the English language.
                                                                            GTK_RESPONSE_CANCEL, NULL) ;

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(new_project_select_folder_dialog), g_get_user_special_dir(G_USER_DIRECTORY_DESKTOP)) ;

  int res = gtk_dialog_run(GTK_DIALOG(new_project_select_folder_dialog)) ;

  switch (res) {

    case GTK_RESPONSE_OK : {

      gchar *folderpath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(new_project_select_folder_dialog)) ;



      if ( g_file_test(folderpath, G_FILE_TEST_EXISTS) ) {

        GError *error = NULL ;

        GDir *dir = g_dir_open(folderpath, 0, &error) ;

        if (error != NULL) {

          g_error_free(error) ;

          break ;
        }

        if (g_dir_read_name(dir) != NULL) {

          display_message_dialog(_("Directory not empty"), _("Cannot create project into directory."), GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

          gtk_window_present(GTK_WINDOW(gtk_widget_get_toplevel(new_project_assistant))) ;

          break ;
        }

      }

      SEC_FREE(project->project_folderpath) ;

      project->project_folderpath = g_strdup(folderpath) ;

      gtk_button_set_label(GTK_BUTTON(widget), g_path_get_basename(folderpath)) ;

      if (g_strcmp0(project->prgname, "") != 0) {
        gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), page, TRUE) ;
      }

      g_free(folderpath) ;

      break ;
    }

    default :

      break ;
  }

  gtk_widget_destroy(new_project_select_folder_dialog) ;

  return ;
}

static bool get_profile_file(GtkWidget *widget) {

  GtkWidget *window = gtk_widget_get_toplevel(widget) ;

  GtkWidget *file_chooser = gtk_file_chooser_dialog_new( _("Load profile file"), GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN,
                                                         _("Import"), GTK_RESPONSE_OK,
                                                         _("Cancel"), GTK_RESPONSE_CANCEL,
                                                         NULL) ;

  GtkFileFilter *file_filter = gtk_file_filter_new() ;

  gtk_file_filter_add_pattern(file_filter, "*.mkpp") ;

  gtk_file_filter_set_name(file_filter, "mk-project profile.");

  gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(file_chooser),file_filter);

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser), g_get_home_dir()) ;
                                                               
  gint res = gtk_dialog_run(GTK_DIALOG(file_chooser)) ;

  if (res == GTK_RESPONSE_OK) {

    gchar *filepath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)) ;
  
    if (filepath == NULL || (! get_a_profile(filepath))) {
  
      g_free(filepath) ;
  
      gtk_widget_destroy(file_chooser) ;
    
      return false ;
    }
  
    g_free(filepath) ;
  
    gtk_widget_destroy(file_chooser) ;
  
    return true ;

  }                                                                    

  gtk_widget_destroy(file_chooser) ;

  return false ;

}
void new_project(GtkWidget *widget) {

  free_project_settings() ;

  init_project_settings() ;

  sphinx_quickstart = have_app_application("sphinx-quickstart") ;

  if (sphinx_quickstart) {

    sphinx_extensions = get_sphinx_extensions() ;

  }
  
  /** FIXME: The assistant bug on MacOSX : the assistant becomes transparent when you click "next" for the first time.
    ******************************************************************************************************************/
  
  new_project_assistant = gtk_assistant_new() ;

  if (g_strcmp0(gtk_widget_get_name(widget), "profile") == 0) {
 
    /** Try to load a profile from file. **/
 
    if (! get_profile_file(new_project_assistant)) {
   
      /** Profile loading failed ! **/
   
      g_free(sphinx_quickstart) ;
  
      g_list_free_full(sphinx_extensions, (GDestroyNotify) free);

      sphinx_extensions = NULL ;
  
      free_project_settings() ;

      init_project_settings() ;
  
      gtk_widget_destroy(GTK_WIDGET(new_project_assistant)) ;

      new_project_assistant = NULL ;

      return ;
  
    }

  }

 

  GtkWidget *mk_project_presentation_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  #ifdef USE_IMG
  GtkWidget *mk_project_presentation_image = gtk_image_new_from_file(PATH_TO_ICON) ;
  #endif

  // Start a new project text
  GtkWidget *mk_project_presentation_label = gtk_label_new("") ;


  gtk_label_set_markup(GTK_LABEL(mk_project_presentation_label),

                                                                 _("<b>mk-project</b> generate you a <i>Makefile</i> based project,\n"
                                                                 "according to your settings...\n\n"
                                                              
                                                                 "You can <b>compile</b>, <b>launch</b>, <b>debug</b>, <b>profiling</b> and so on.\n\n"
                                                              
                                                                 "You can <b>format your source code</b> with 3 different code beautifiers !\n\n"
                                                              
                                                                 "You can <b>generate documentation</b> using sphinx, and so based on\n"
                                                                 "<i>ReST</i> or <i>Markdown</i> syntax, and many sphinx extensions.\n"
                                                                 "With many output possibilities:\n"
                                                                 "<b>singlehtml</b>, <b>html</b>, <b>pdf</b>, <b>epub</b>, <b>latex</b>, <b>info</b> and so on.\n\n"
                                                              
                                                                 "You can create an <b>archive from your project</b> !\n\n"
                                                              
                                                                 "And <b>mk-project</b> provide many others features !!!") )  ;


  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(mk_project_presentation_hbox), mk_project_presentation_image, FALSE, FALSE, MARGING) ;
  #endif
  gtk_box_pack_start(GTK_BOX(mk_project_presentation_hbox), mk_project_presentation_label, TRUE,  TRUE,  MARGING) ;

  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), mk_project_presentation_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), mk_project_presentation_hbox, GTK_ASSISTANT_PAGE_INTRO) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), mk_project_presentation_hbox, _("New project")) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), mk_project_presentation_hbox, TRUE);


  configure_project_language() ;

  configure_compiler_project() ;

  configure_c_project_main() ;

  configure_disassembling_options() ;

  configure_oprofile_options() ;

  configure_valgrind_options() ;

  // Currently only sphinx-doc supported.
  configure_new_doc_project() ;

  configure_code_c_fmt_project() ;

  configure_about_project() ;

  configure_others_info_project() ;

  configure_licensing_project() ;

  configure_desktop_file_project() ;

  summary_of_project() ;


  gtk_window_set_resizable(GTK_WINDOW(new_project_assistant),  FALSE) ;
  gtk_window_set_position(GTK_WINDOW(new_project_assistant), GTK_WIN_POS_CENTER_ALWAYS);

  g_signal_connect_after(G_OBJECT(new_project_assistant), "cancel",  G_CALLBACK(cancel_event), NULL) ;
  g_signal_connect_after(G_OBJECT(new_project_assistant), "prepare", G_CALLBACK(on_prepare_page), NULL) ;
  g_signal_connect_after(G_OBJECT(new_project_assistant), "apply",   G_CALLBACK(on_apply_page), NULL) ;
  g_signal_connect_after(G_OBJECT(new_project_assistant), "close",   G_CALLBACK(on_close_project), NULL) ;

  gtk_widget_show_all(new_project_assistant) ;

  return ;

}


static void configure_project_language(void) {

  GtkWidget *new_project_language_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *new_project_primary_infos_label_vbox   = gtk_box_new(GTK_ORIENTATION_VERTICAL,   0) ;

  GtkWidget *new_project_primary_infos_data_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL,   0) ;

  #ifdef USE_IMG
  GtkWidget *new_project_image = gtk_image_new_from_file(PATH_TO_ICON) ;
  #endif


  GtkWidget *new_project_language_label = gtk_label_new(_("Language")) ;

  GtkWidget *new_project_language_combotext =  gtk_combo_box_text_new() ;

  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(new_project_language_combotext), NULL, "C") ;
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(new_project_language_combotext), NULL, "C++") ;

  if ( g_strcmp0(project->language, "C") == 0 ) {
    gtk_combo_box_set_active(GTK_COMBO_BOX(new_project_language_combotext), 0) ;
  }
  else if ( g_strcmp0(project->language, "C++") == 0) {
    gtk_combo_box_set_active(GTK_COMBO_BOX(new_project_language_combotext), 1) ;
  }

  g_signal_connect(G_OBJECT(new_project_language_combotext), "changed", G_CALLBACK(get_combo_value_language), project->language) ;


  GtkWidget *new_project_prgname_label = gtk_label_new(_("program name")) ;

  GtkWidget *new_project_prgname_entry =  gtk_entry_new() ;

  gtk_entry_set_placeholder_text(GTK_ENTRY(new_project_prgname_entry), "prgname");

  g_signal_connect(G_OBJECT(new_project_prgname_entry), "realize", G_CALLBACK(on_realize_widget), NULL) ;

  g_signal_connect_after(G_OBJECT(new_project_prgname_entry), "focus-out-event", G_CALLBACK(get_entry_value_prgname), new_project_language_hbox) ;

  gtk_widget_set_tooltip_text(new_project_prgname_entry, _("Allowed characters: [A-Za-z0-9-:_.]\nElse the character will be replace by an underscore.") ) ;


  GtkWidget *new_project_version_label = gtk_label_new("Version") ;

  GtkWidget *new_project_version_entry =  gtk_entry_new() ;

  gtk_widget_set_name(new_project_version_entry, "version_string") ;

  gtk_entry_set_placeholder_text(GTK_ENTRY(new_project_version_entry), "1.0.0");

  g_signal_connect(G_OBJECT(new_project_version_entry), "realize", G_CALLBACK(on_realize_widget), NULL) ;

  g_signal_connect_after(G_OBJECT(new_project_version_entry), "focus-out-event", G_CALLBACK(get_entry_value_project_version_string), project->version_string) ;


  GtkWidget *new_project_license_label = gtk_label_new( _("License") ) ;

  GtkWidget *new_project_license_combo = gtk_combo_box_text_new() ;

  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(new_project_license_combo), NULL, "gpl") ;
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(new_project_license_combo), NULL, "agpl") ;
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(new_project_license_combo), NULL, "lgpl") ;
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(new_project_license_combo), NULL, "fdl") ;

  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(new_project_license_combo), NULL, "Apache 2.0") ;
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(new_project_license_combo), NULL, "Clear BSD") ;
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(new_project_license_combo), NULL, "Free BSD") ;

  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(new_project_license_combo), NULL, _("Other")) ;
  // NOTE: The user is great enough to get his wanted license file(s).


  if (g_strcmp0(project->license, "gpl") == 0) {
    gtk_combo_box_set_active(GTK_COMBO_BOX(new_project_license_combo), 0) ;
  }
  else if (g_strcmp0(project->license, "agpl") == 0) {
    gtk_combo_box_set_active(GTK_COMBO_BOX(new_project_license_combo), 1) ;
  }
  else if (g_strcmp0(project->license, "lgpl") == 0) {
    gtk_combo_box_set_active(GTK_COMBO_BOX(new_project_license_combo), 2) ;
  }
  else if (g_strcmp0(project->license, "fdl") == 0) {
    gtk_combo_box_set_active(GTK_COMBO_BOX(new_project_license_combo), 3) ;
  }
  else if (g_strcmp0(project->license, "Apache 2.0") == 0) {
    gtk_combo_box_set_active(GTK_COMBO_BOX(new_project_license_combo), 4) ;
  }
  else if (g_strcmp0(project->license, "Clear BSD") == 0) {
    gtk_combo_box_set_active(GTK_COMBO_BOX(new_project_license_combo), 5) ;
  }
  else if (g_strcmp0(project->license, "Free BSD") == 0) {
    gtk_combo_box_set_active(GTK_COMBO_BOX(new_project_license_combo), 6) ;
  }
  else {
    gtk_combo_box_set_active(GTK_COMBO_BOX(new_project_license_combo), 7) ;
  }


  g_signal_connect(G_OBJECT(new_project_license_combo), "changed", G_CALLBACK(get_combo_value_licensing), NULL) ;

  g_signal_emit_by_name(G_OBJECT(new_project_license_combo), "changed",NULL);

  // TODO: Rectify project folder choice !
  GtkWidget *new_project_folder_label = gtk_label_new(_("Project folder")) ;

  GtkWidget *new_project_folder_filebutton =  gtk_button_new_with_label( N_("Select the project folder")) ;


  g_signal_connect(G_OBJECT(new_project_folder_filebutton), "clicked", G_CALLBACK(select_folder_dialog), new_project_language_hbox) ;

  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(new_project_language_hbox), new_project_image, FALSE, FALSE, MARGING) ;
  #endif

  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_label_vbox), gtk_label_new(""),              TRUE,   TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_label_vbox), new_project_language_label,     FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_label_vbox), gtk_label_new(""),              TRUE,   TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_label_vbox), new_project_prgname_label,     FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_label_vbox), gtk_label_new(""),              TRUE,   TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_label_vbox), new_project_version_label,     FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_label_vbox), gtk_label_new(""),              TRUE,   TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_label_vbox), new_project_license_label,     FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_label_vbox), gtk_label_new(""),              TRUE,   TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_label_vbox), new_project_folder_label,       FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_label_vbox), gtk_label_new(""),              TRUE,   TRUE, 0) ;





  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_data_vbox), gtk_label_new(""),              TRUE,   TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_data_vbox), new_project_language_combotext, FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_data_vbox), gtk_label_new(""),              TRUE,   TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_data_vbox), new_project_prgname_entry,      FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_data_vbox), gtk_label_new(""),              TRUE,   TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_data_vbox), new_project_version_entry,      FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_data_vbox), gtk_label_new(""),              TRUE,   TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_data_vbox), new_project_license_combo,      FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_data_vbox), gtk_label_new(""),              TRUE,   TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_data_vbox), new_project_folder_filebutton,  FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(new_project_primary_infos_data_vbox), gtk_label_new(""),              TRUE,   TRUE, 0) ;

  gtk_box_pack_start(GTK_BOX(new_project_language_hbox), new_project_primary_infos_label_vbox,      FALSE, FALSE, MARGING) ;
  gtk_box_pack_start(GTK_BOX(new_project_language_hbox), new_project_primary_infos_data_vbox,       TRUE, TRUE,   MARGING) ;

  gtk_widget_show_all(new_project_language_hbox) ;

  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), new_project_language_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), new_project_language_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), new_project_language_hbox, _("Language")) ;



}


static void configure_compiler_project(void) {





  #ifdef USE_IMG
  GtkWidget *configure_c_project_image = gtk_image_new_from_file(PATH_TO_ICON) ;
  #endif

  GtkWidget *configure_c_project_compiler_label = gtk_label_new( _("Compiler") ) ;

  GtkWidget *configure_c_project_compiler_entry = gtk_entry_new() ;

  gtk_widget_set_size_request(configure_c_project_compiler_entry, COMPILER_ENTRY_SIZE, -1)  ;

  gtk_widget_set_name(configure_c_project_compiler_entry, "compiler_entry") ;

  gtk_entry_set_text(GTK_ENTRY(configure_c_project_compiler_entry), project->compiler) ;

  gtk_widget_set_tooltip_text(configure_c_project_compiler_entry, _("cc is your default C compiler")) ;


  g_signal_connect(G_OBJECT(configure_c_project_compiler_entry), "realize", G_CALLBACK(on_realize_widget), NULL) ;

  g_signal_connect_after(G_OBJECT(configure_c_project_compiler_entry), "focus-out-event", G_CALLBACK(is_compiler_focus_out), NULL) ;

  GtkWidget *configure_c_project_compiler_button = gtk_button_new() ;

  gtk_button_set_relief(GTK_BUTTON(configure_c_project_compiler_button), GTK_RELIEF_NONE) ;



  GtkWidget *configure_c_project_warns_label = gtk_label_new("Warnings") ;

  GtkWidget *configure_c_project_warns_entry = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_c_project_warns_entry), project->warnings) ;

  g_object_set(G_OBJECT(configure_c_project_warns_entry), "activates-default", TRUE, NULL) ;

  gtk_widget_set_size_request(configure_c_project_warns_entry, COMPILER_ENTRY_SIZE, -1)  ;

  gtk_widget_set_can_default(configure_c_project_warns_entry, TRUE) ;

  if (gtk_widget_get_can_default(configure_c_project_warns_entry) ) {

    gtk_widget_set_receives_default(configure_c_project_warns_entry, TRUE) ;

  }


  gtk_widget_set_name(configure_c_project_warns_entry, "warnings") ;

  gtk_entry_set_placeholder_text(GTK_ENTRY(configure_c_project_warns_entry), "-Wall -Wextra") ;


  GtkWidget *configure_c_project_warns_button = create_button(PATH_TO_BUTTON_ICON "/flag-red.png", _("Set the commons project WARNINGS !\nYou can set the warnings you want by editing the entry by hand.")) ;

  g_signal_connect(G_OBJECT(configure_c_project_warns_button), "clicked", G_CALLBACK(select_warnings), configure_c_project_warns_entry) ;


  GtkWidget *configure_c_project_cflags_label = gtk_label_new("CFLAGS") ;

  GtkWidget *configure_c_project_cflags_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_c_project_cflags_entry, "cflags") ;

  gtk_entry_set_text(GTK_ENTRY(configure_c_project_cflags_entry), project->cflags) ;

  gtk_entry_set_placeholder_text(GTK_ENTRY(configure_c_project_cflags_entry), "-g -O2") ;

  gtk_widget_set_size_request(configure_c_project_cflags_entry, COMPILER_ENTRY_SIZE, -1)  ;

  gtk_widget_set_tooltip_text(configure_c_project_cflags_entry, _("Set the compiler options.")  ) ;

  GtkWidget *configure_c_project_cflags_button = create_button(PATH_TO_BUTTON_ICON "/flag-blue.png", _("Set the commons project FLAGS (CFLAGS or CXXFLAGS) !\nYou can set the flags you want by editing the entry by hand.")) ;

  g_signal_connect(G_OBJECT(configure_c_project_cflags_button), "clicked", G_CALLBACK(select_flags), configure_c_project_cflags_entry) ;


  GtkWidget *configure_c_project_cppflags_label = gtk_label_new("CPPFLAGS") ;

  GtkWidget *configure_c_project_cppflags_entry = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_c_project_cppflags_entry), project->cppflags) ;

  gtk_widget_set_size_request(configure_c_project_cppflags_entry, COMPILER_ENTRY_SIZE, -1)  ;

  gtk_widget_set_name(configure_c_project_cppflags_entry, "cppflags") ;

  gtk_widget_set_tooltip_text(configure_c_project_cppflags_entry, _("Per example: -DPREFIX=\"/usr/local\"")  ) ;

  GtkWidget *configure_c_project_cppflags_button = create_button(PATH_TO_BUTTON_ICON "/flag-black.png", _("Set the commons project preprocessor definitions (CPPFLAGS) !\nYou can set the flags you want by editing the entry by hand.")) ;

  g_signal_connect(G_OBJECT(configure_c_project_cppflags_button), "clicked",  G_CALLBACK(add_cppflags), configure_c_project_cppflags_entry) ;


  GtkWidget *configure_c_project_ldflags_label = gtk_label_new("LDFLAGS") ;

  GtkWidget *configure_c_project_ldflags_entry = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_c_project_ldflags_entry), project->ldflags) ;

  gtk_widget_set_size_request(configure_c_project_ldflags_entry, COMPILER_ENTRY_SIZE, -1)  ;

  gtk_widget_set_name(configure_c_project_ldflags_entry, "ldflags") ;

  gtk_widget_set_tooltip_text(configure_c_project_ldflags_entry, _("Per example: `pkg-config --cflags gtk+-3.0`\n\nWith pkg-config, use the backticks syntax !") ) ;

  GtkWidget *configure_c_project_ldflags_button = create_button(PATH_TO_BUTTON_ICON "/flag-green.png", _("Choose the \"pkg-config\" (*.pc) to add to your project !\nElse you can set what ever you want by editing the entry by hand.")) ;








  GtkWidget *configure_c_project_ldlibs_label = gtk_label_new("LDLIBS") ;

  GtkWidget *configure_c_project_ldlibs_entry = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_c_project_ldlibs_entry), project->ldlibs) ;

  gtk_widget_set_size_request(configure_c_project_ldlibs_entry, COMPILER_ENTRY_SIZE, -1)  ;

  gtk_widget_set_name(configure_c_project_ldlibs_entry, "ldlibs") ;

  gtk_widget_set_tooltip_text(configure_c_project_ldlibs_entry, _("Per example: `pkg-config --libs gtk+-3.0` -lvte2_90 -lm  \n\nWith pkg-config, use the backticks syntax !") ) ;

  GtkWidget *configure_c_project_ldlibs_button = create_button(PATH_TO_BUTTON_ICON "/flag-yellow.png",_("Choose the linker switch to add to your project (-l) !\nElse you can set what ever you want by editing the entry by hand.")) ;

  g_signal_connect(G_OBJECT(configure_c_project_ldlibs_button), "clicked", G_CALLBACK(add_linkage_to_project), configure_c_project_ldlibs_entry) ;


  libraries_entries *entries = g_slice_new(libraries_entries) ;

  entries->ldflags_entry  = configure_c_project_ldflags_entry ;
  entries->ldlibs_entry   = configure_c_project_ldlibs_entry ;

  g_signal_connect(G_OBJECT(configure_c_project_ldflags_button), "clicked", G_CALLBACK(add_pkg_config_to_project), entries) ;



  GtkWidget *configure_c_project_label_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), configure_c_project_compiler_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), configure_c_project_warns_label,     FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), configure_c_project_cflags_label,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), configure_c_project_cppflags_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), configure_c_project_ldflags_label,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), configure_c_project_ldlibs_label,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_label_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;

  GtkWidget *configure_c_project_data_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), configure_c_project_compiler_entry,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), configure_c_project_warns_entry,     FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), configure_c_project_cflags_entry,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), configure_c_project_cppflags_entry,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), configure_c_project_ldflags_entry,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), configure_c_project_ldlibs_entry,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_data_vbox), gtk_label_new(""),                   TRUE,  TRUE,  0) ;


  GtkWidget *configure_c_project_buttons_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), gtk_label_new(""),                    TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), configure_c_project_compiler_button,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), gtk_label_new(""),                    TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), configure_c_project_warns_button,     FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), gtk_label_new(""),                    TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), configure_c_project_cflags_button,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), gtk_label_new(""),                    TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), configure_c_project_cppflags_button,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), gtk_label_new(""),                    TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), configure_c_project_ldflags_button,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), gtk_label_new(""),                    TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), configure_c_project_ldlibs_button,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_buttons_vbox), gtk_label_new(""),                    TRUE,  TRUE,  0) ;



  GtkWidget *configure_c_project_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(configure_c_project_hbox), configure_c_project_image,      FALSE, FALSE, MARGING) ;
  #endif


  gtk_widget_set_name(configure_c_project_data_vbox, "compiler_settings_container") ;

  gtk_box_pack_start(GTK_BOX(configure_c_project_hbox), configure_c_project_label_vbox,    FALSE, FALSE, MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_hbox), configure_c_project_data_vbox,     TRUE,  TRUE,  MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_hbox), configure_c_project_buttons_vbox,  TRUE, TRUE,  MARGING) ;

  gtk_widget_show_all(configure_c_project_hbox) ;

  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), configure_c_project_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), configure_c_project_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), configure_c_project_hbox, _("Compiler settings") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), configure_c_project_hbox, TRUE) ;

  return ;
}



static void configure_c_project_main(void) {

  GtkWidget *configure_c_project_main_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *configure_c_project_main_label_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;
  GtkWidget *configure_c_project_main_data_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_widget_set_name(configure_c_project_main_data_vbox, "data_c_project") ;

  #ifdef USE_IMG
  GtkWidget *configure_c_project_main_image = gtk_image_new_from_file(PATH_TO_ICON) ;
  #endif


  GtkWidget *configure_c_project_main_file_label = gtk_label_new( _("Main source file") ) ;

  GtkWidget *configure_c_project_main_file_entry = gtk_entry_new() ;

  g_object_set(G_OBJECT(configure_c_project_main_file_entry), "editable", FALSE, NULL) ;

  gtk_widget_set_name(configure_c_project_main_file_entry,  "main_file") ;



  GtkWidget *configure_c_project_main_src_ext_label = gtk_label_new( _("Source file extension") ) ;

  GtkWidget *configure_c_project_main_src_ext_combo = gtk_combo_box_text_new() ;

  gtk_widget_set_tooltip_text(configure_c_project_main_src_ext_label, _("Set the extension you will use, this is important !\nReally because this value become an important make variable !!!")  ) ;
  gtk_widget_set_tooltip_text(configure_c_project_main_src_ext_combo, _("Set the extension you will use, this is important !\nReally because this value become an important make variable !!!") ) ;

  gtk_widget_set_name(configure_c_project_main_src_ext_combo, "ext_src") ;

  g_signal_connect(G_OBJECT(configure_c_project_main_src_ext_combo), "changed", G_CALLBACK(get_combo_value_c_src_ext), configure_c_project_main_file_entry) ;





  GtkWidget *configure_c_project_main_hdr_ext_label = gtk_label_new( _("Header file extension") ) ;

  GtkWidget *configure_c_project_main_hdr_ext_combo = gtk_combo_box_text_new() ;

  gtk_widget_set_tooltip_text(configure_c_project_main_hdr_ext_label, _("Set the extension you will use, this is important !\nReally because this value become an important make variable")  ) ;
  gtk_widget_set_tooltip_text(configure_c_project_main_hdr_ext_combo, _("Set the extension you will use, this is important !\nReally because this value become an important make variable") ) ;

  gtk_widget_set_name(configure_c_project_main_hdr_ext_combo, "ext_hdr") ;

  gtk_combo_box_set_active(GTK_COMBO_BOX(configure_c_project_main_hdr_ext_combo), 0) ;

  g_signal_connect(G_OBJECT(configure_c_project_main_hdr_ext_combo), "changed", G_CALLBACK(get_combo_value_c_hdr_ext), NULL) ;





  GtkWidget *configure_c_project_main_use_lib_label = gtk_label_new( _("Make a program library") ) ;

  GtkWidget *configure_c_project_main_use_lib_chkbox = gtk_check_button_new() ;

  gtk_widget_set_tooltip_text(configure_c_project_main_use_lib_label,   _("Build a static program library if this make sens by using this option.")  ) ;
  gtk_widget_set_tooltip_text(configure_c_project_main_use_lib_chkbox,  _("Build a static program library if this make sens by using this option.") ) ;


  g_signal_connect(G_OBJECT(configure_c_project_main_use_lib_chkbox), "toggled", G_CALLBACK(get_checkbutton_value), &project->program_library) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(configure_c_project_main_use_lib_chkbox), project->program_library) ;


  gtk_box_pack_start(GTK_BOX(configure_c_project_main_label_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_label_vbox), configure_c_project_main_file_label,       FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_label_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_label_vbox), configure_c_project_main_src_ext_label,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_label_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_label_vbox), configure_c_project_main_hdr_ext_label,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_label_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_label_vbox), configure_c_project_main_use_lib_label,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_label_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;


  gtk_box_pack_start(GTK_BOX(configure_c_project_main_data_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_data_vbox), configure_c_project_main_file_entry,       FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_data_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_data_vbox), configure_c_project_main_src_ext_combo,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_data_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_data_vbox), configure_c_project_main_hdr_ext_combo,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_data_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_data_vbox), configure_c_project_main_use_lib_chkbox,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_data_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;

  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_hbox), configure_c_project_main_image,      FALSE, FALSE, MARGING) ;
  #endif

  gtk_box_pack_start(GTK_BOX(configure_c_project_main_hbox), configure_c_project_main_label_vbox, FALSE, FALSE, MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_main_hbox), configure_c_project_main_data_vbox,  TRUE,  TRUE,  MARGING) ;

  gtk_widget_show_all(configure_c_project_main_hbox) ;

  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), configure_c_project_main_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), configure_c_project_main_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

                                                                                                    // No gettext macro to make sure the program is in the English language.
  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), configure_c_project_main_hbox, "Files" ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), configure_c_project_main_hbox, TRUE) ;

  return ;

}



static void configure_disassembling_options(void) {

  GtkWidget *configure_disassembling_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *configure_disassembling_label_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;
  GtkWidget *configure_disassembling_data_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  #ifdef USE_IMG
  GtkWidget *configure_disassembling_image = gtk_image_new_from_file(PATH_TO_ICON) ;
  #endif

  GtkWidget *configure_disassembling_nm_opts_label = gtk_label_new( "nm options") ;

  GtkWidget *configure_disassembling_nm_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_disassembling_nm_opts_entry), project->nm_options) ;

  gtk_widget_set_name(configure_disassembling_nm_opts_entry, "nm_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_nm_opts_label, _("nm: display symbols of object file(s) or a binary.\n\nLook at $ nm -h or $ man nm") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_nm_opts_entry, _("nm: display symbols of object file(s) or a binary.\n\nLook at $ nm -h or $ man nm") ) ;


  GtkWidget *configure_disassembling_strace_opts_label = gtk_label_new("strace options") ;

  GtkWidget *configure_disassembling_strace_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_disassembling_strace_opts_entry), project->strace_options) ;

  gtk_widget_set_name(configure_disassembling_strace_opts_entry, "strace_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_strace_opts_label, _("strace: intercepts and records the system calls which are called by a\nprocess and the signals which are received by a process.\n\nLook at $ strace -h or $ man strace") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_strace_opts_entry, _("strace: intercepts and records the system calls which are called by a\nprocess and the signals which are received by a process.\n\nLook at $ strace -h or $ man strace") ) ;



  GtkWidget *configure_disassembling_ltrace_opts_label = gtk_label_new("ltrace options") ;

  GtkWidget *configure_disassembling_ltrace_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_disassembling_ltrace_opts_entry), project->ltrace_options) ;

  gtk_widget_set_name(configure_disassembling_ltrace_opts_entry, "ltrace_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_ltrace_opts_label, _("ltrace: trace library calls of a given program.\n\nLook at $ ltrace -h or $ man ltrace") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_ltrace_opts_entry, _("ltrace: trace library calls of a given program.\n\nLook at $ ltrace -h or $ man ltrace") ) ;



  GtkWidget *configure_disassembling_objdump_opts_label = gtk_label_new("objdump options") ;

  GtkWidget *configure_disassembling_objdump_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_disassembling_objdump_opts_entry), project->objdump_options) ;

  gtk_widget_set_name(configure_disassembling_objdump_opts_entry, "objdump_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_objdump_opts_label, _("objdump: Display the informations about the object file(s) or a binary.\n\nLook at $ objdump -h or $ man objdump") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_objdump_opts_entry, _("objdump: Display the informations about the object file(s) or a binary.\n\nLook at $ objdump -h or $ man objdump") ) ;



  GtkWidget *configure_disassembling_ldd_opts_label = gtk_label_new("ldd options") ;

  GtkWidget *configure_disassembling_ldd_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_disassembling_ldd_opts_entry), project->ldd_options) ;

  gtk_widget_set_name(configure_disassembling_ldd_opts_entry, "ldd_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_ldd_opts_label, _("ldd: ldd  print the  shared  libraries  required by each program or\nshared library specified on the command line.\n\nLook at $ ldd -h or $ man ldd") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_ldd_opts_entry, _("ldd: ldd  print the  shared  libraries  required by each program or\nshared library specified on the command line.\n\nLook at $ ldd -h or $ man ldd") ) ;




  GtkWidget *configure_disassembling_gprof_opts_label = gtk_label_new("gprof options") ;

  GtkWidget *configure_disassembling_gprof_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_disassembling_gprof_opts_entry), project->gprof_options) ;

  gtk_widget_set_name(configure_disassembling_gprof_opts_entry, "gprof_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_gprof_opts_label, _("gprof: a profiling tool shipped with gcc.\n\nLook at $ gprof -h or $ man gprof") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_gprof_opts_entry, _("gprof: a profiling tool shipped with gcc.\n\nLook at $ gprof -h or $ man gprof") ) ;




  GtkWidget *configure_disassembling_gdb_opts_label = gtk_label_new("gdb options") ;

  GtkWidget *configure_disassembling_gdb_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_disassembling_gdb_opts_entry), project->gdb_options) ;

  gtk_widget_set_name(configure_disassembling_gdb_opts_entry, "gdb_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_gdb_opts_label, _("gdb: Allow you to see what is going on \"inside\" another program while it executes -- or what another program was doing at the moment it crashed\n\nLook at $ gdb --help or $ man gdb for further informations") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_gdb_opts_entry, _("gdb: Allow you to see what is going on \"inside\" another program while it executes -- or what another program was doing at the moment it crashed\n\nLook at $ gdb --help or $ man gdb for further informations") ) ;




  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), configure_disassembling_nm_opts_label,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), configure_disassembling_gdb_opts_label,     FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), configure_disassembling_strace_opts_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), configure_disassembling_ltrace_opts_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), configure_disassembling_objdump_opts_label, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), configure_disassembling_ldd_opts_label,     FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), configure_disassembling_gprof_opts_label,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;


  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), configure_disassembling_nm_opts_entry,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), configure_disassembling_gdb_opts_entry,     FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), configure_disassembling_strace_opts_entry,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), configure_disassembling_ltrace_opts_entry,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), configure_disassembling_objdump_opts_entry, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), configure_disassembling_ldd_opts_entry,     FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), configure_disassembling_gprof_opts_entry,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;


  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(configure_disassembling_hbox), configure_disassembling_image, FALSE, FALSE, MARGING) ;
  #endif

  gtk_box_pack_start(GTK_BOX(configure_disassembling_hbox), configure_disassembling_label_vbox, FALSE, FALSE, MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_hbox), configure_disassembling_data_vbox,  TRUE,  TRUE,  MARGING) ;

  gtk_widget_set_name(configure_disassembling_data_vbox, "disassembling_opts") ;

  gtk_widget_show_all(configure_disassembling_hbox) ;

  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), configure_disassembling_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), configure_disassembling_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), configure_disassembling_hbox, _("Disassembling") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), configure_disassembling_hbox, TRUE) ;

  return ;

}

static void configure_oprofile_options(void) {

  GtkWidget *configure_oprofiling_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *configure_oprofiling_label_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;
  GtkWidget *configure_oprofiling_data_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  #ifdef USE_IMG
  GtkWidget *configure_oprofiling_image = gtk_image_new_from_file(PATH_TO_ICON) ;
  #endif

  GtkWidget *configure_oprofiling_operf_opts_label = gtk_label_new( "operf options") ;

  GtkWidget *configure_oprofiling_operf_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_oprofiling_operf_opts_entry), project->operf_options) ;

  gtk_widget_set_name(configure_oprofiling_operf_opts_entry, "operf_options") ;

  gtk_widget_set_tooltip_text(configure_oprofiling_operf_opts_label, _("Operf: is the profiler tool provided with OProfile. Operf uses the Linux Performance  Events  Subsystem.\n\nLook at $ operf -h or $ man operf\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\n\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;
  gtk_widget_set_tooltip_text(configure_oprofiling_operf_opts_entry, _("Operf: is the profiler tool provided with OProfile. Operf uses the Linux Performance  Events  Subsystem.\n\nLook at $ operf -h or $ man operf\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\n\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;


  GtkWidget *configure_oprofiling_ocount_opts_label = gtk_label_new("ocount options") ;

  GtkWidget *configure_oprofiling_ocount_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_oprofiling_ocount_opts_entry), project->ocount_options) ;

  gtk_widget_set_name(configure_oprofiling_ocount_opts_entry, "ocount_options") ;

  gtk_widget_set_tooltip_text(configure_oprofiling_ocount_opts_label, _("ocount: is an OProfile tool that can be used to count native hardware events occurring in either a given application, a set of processes or threads, a subset of active system processors, or  the  entire  system.\n\nLook at $ ocount -h or $ man ocount\n\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html") ) ;
  gtk_widget_set_tooltip_text(configure_oprofiling_ocount_opts_entry, _("ocount: is an OProfile tool that can be used to count native hardware events occurring in either a given application, a set of processes or threads, a subset of active system processors, or  the  entire  system.\n\nLook at $ ocount -h or $ man ocount\n\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html") ) ;



  GtkWidget *configure_oprofiling_opreport_opts_label = gtk_label_new("opreport options") ;

  GtkWidget *configure_oprofiling_opreport_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_oprofiling_opreport_opts_entry), project->opreport_options) ;

  gtk_widget_set_name(configure_oprofiling_opreport_opts_entry, "opreport_options") ;

  gtk_widget_set_tooltip_text(configure_oprofiling_opreport_opts_label, _("opreport: opreport outputs binary image summaries, or per-symbol data, from OProfile profiling sessions.\nUse operf or ocount to write profile specifications.\n\nLook at $ opreport -h or $ man opreport\n\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;
  gtk_widget_set_tooltip_text(configure_oprofiling_opreport_opts_entry, _("opreport: opreport outputs binary image summaries, or per-symbol data, from OProfile profiling sessions.\nUse operf or ocount to write profile specifications.\n\nLook at $ opreport -h or $ man opreport\n\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;



  GtkWidget *configure_oprofiling_opannotate_opts_label = gtk_label_new("opannotate options") ;

  GtkWidget *configure_oprofiling_opannotate_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_oprofiling_opannotate_opts_entry), project->opannotate_options) ;

  gtk_widget_set_name(configure_oprofiling_opannotate_opts_entry, "opannotate_options") ;

  gtk_widget_set_tooltip_text(configure_oprofiling_opannotate_opts_label, _("opannotate  outputs  annotated source and/or assembly from profile data of an OProfile session.\nUse operf or ocount to write profile specifications.\n\nLook at $ opannotate -h or $ man opannotate\n\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;
  gtk_widget_set_tooltip_text(configure_oprofiling_opannotate_opts_entry, _("opannotate  outputs  annotated source and/or assembly from profile data of an OProfile session.\nUse operf or ocount to write profile specifications.\n\nLook at $ opannotate -h or $ man opannotate\n\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;


  GtkWidget *configure_oprofiling_opgprof_opts_label = gtk_label_new("opgprof options") ;

  GtkWidget *configure_oprofiling_opgprof_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_oprofiling_opgprof_opts_entry), project->opgprof_options) ;

  gtk_widget_set_name(configure_oprofiling_opgprof_opts_entry, "opgprof_options") ;

  gtk_widget_set_tooltip_text(configure_oprofiling_opgprof_opts_label, _("opgprof: outputs  gprof-format  profile  data for a given binary image, from an OProfile session.\nUse operf or ocount to write profile specifications.\n\nLook at $ opgprof -h or $ man opgprof\n\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;
  gtk_widget_set_tooltip_text(configure_oprofiling_opgprof_opts_entry, _("opgprof: outputs  gprof-format  profile  data for a given binary image, from an OProfile session.\nUse operf or ocount to write profile specifications.\n\nLook at $ opgprof -h or $ man opgprof\n\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;








  gtk_box_pack_start(GTK_BOX(configure_oprofiling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_label_vbox), configure_oprofiling_operf_opts_label,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_label_vbox), configure_oprofiling_ocount_opts_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_label_vbox), configure_oprofiling_opreport_opts_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_label_vbox), configure_oprofiling_opannotate_opts_label, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_label_vbox), configure_oprofiling_opgprof_opts_label,     FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;


  gtk_box_pack_start(GTK_BOX(configure_oprofiling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_data_vbox), configure_oprofiling_operf_opts_entry,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_data_vbox), configure_oprofiling_ocount_opts_entry,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_data_vbox), configure_oprofiling_opreport_opts_entry,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_data_vbox), configure_oprofiling_opannotate_opts_entry, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_data_vbox), configure_oprofiling_opgprof_opts_entry,     FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;


  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_hbox), configure_oprofiling_image, FALSE, FALSE, MARGING) ;
  #endif

  gtk_box_pack_start(GTK_BOX(configure_oprofiling_hbox), configure_oprofiling_label_vbox, FALSE, FALSE, MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_oprofiling_hbox), configure_oprofiling_data_vbox,  TRUE,  TRUE,  MARGING) ;

  gtk_widget_set_name(configure_oprofiling_data_vbox, "oprofiling_opts") ;

  gtk_widget_show_all(configure_oprofiling_hbox) ;

  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), configure_oprofiling_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), configure_oprofiling_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), configure_oprofiling_hbox, _("Oprofile") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), configure_oprofiling_hbox, TRUE) ;

  return ;

}

static void configure_valgrind_options(void) {

  GtkWidget *configure_valgrind_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *configure_valgrind_label_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;
  GtkWidget *configure_valgrind_data_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  #ifdef USE_IMG
  GtkWidget *configure_valgrind_image = gtk_image_new_from_file(PATH_TO_ICON) ;
  #endif

  GtkWidget *configure_valgrind_memcheck_opts_label = gtk_label_new("memcheck options") ;

  GtkWidget *configure_valgrind_memcheck_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_valgrind_memcheck_opts_entry), project->valgrind_memcheck) ;

  gtk_widget_set_name(configure_valgrind_memcheck_opts_entry, "memcheck_options") ;

  gtk_widget_set_tooltip_text(configure_valgrind_memcheck_opts_label, _("valgrind memcheck: is a memory profiler tool.\n\nLook at $ vagrind -h or $ man valgrind (section MEMCHECK OPTIONS).\nfor further informations.") ) ;
  gtk_widget_set_tooltip_text(configure_valgrind_memcheck_opts_entry, _("valgrind memcheck: is a memory profiler tool.\n\n.Look at $ man valgrind (section MEMCHECK OPTIONS).\nfor further informations.")) ;


  GtkWidget *configure_valgrind_cachegrind_opts_label = gtk_label_new("cachegrind options") ;

  GtkWidget *configure_valgrind_cachegrind_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_valgrind_cachegrind_opts_entry), project->valgrind_cachegrind) ;

  gtk_widget_set_name(configure_valgrind_cachegrind_opts_entry, "cachegrind_options") ;

  gtk_widget_set_tooltip_text(configure_valgrind_cachegrind_opts_label, _("valgrind cachegrind: a cache and branch-prediction profiler.\n\nLook at $ valgrind -h or $ man valgrind (CACHEGRIND OPTIONS).\nfor further informations.") ) ;
  gtk_widget_set_tooltip_text(configure_valgrind_cachegrind_opts_entry, _("valgrind cachegrind: a cache and branch-prediction profiler.\n\nLook at $ valgrind -h or $ man valgrind (CACHEGRIND OPTIONS).\nfor further informations.") ) ;



  GtkWidget *configure_valgrind_callgrind_opts_label = gtk_label_new("callgrind options") ;

  GtkWidget *configure_valgrind_callgrind_opts_entry  = gtk_entry_new() ;

  gtk_widget_set_name(configure_valgrind_callgrind_opts_entry, "callgrind_options") ;

  gtk_entry_set_text(GTK_ENTRY(configure_valgrind_callgrind_opts_entry), project->valgrind_callgrind) ;

  gtk_widget_set_tooltip_text(configure_valgrind_callgrind_opts_label, _("valgrind callgrind: a call-graph generating cache profiler.\n\nLook at $ valgrind -h or $ man valgrind (CALLGRIND OPTIONS).\nfor further informations.") ) ;
  gtk_widget_set_tooltip_text(configure_valgrind_callgrind_opts_entry, _("valgrind callgrind: a call-graph generating cache profiler.\n\nLook at $ valgrind -h or $ man valgrind (CALLGRIND OPTIONS).\nfor further informations.") ) ;



  GtkWidget *configure_valgrind_helgrind_opts_label = gtk_label_new("helgrind options") ;

  GtkWidget *configure_valgrind_helgrind_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_valgrind_helgrind_opts_entry), project->valgrind_helgrind) ;

  gtk_widget_set_name(configure_valgrind_helgrind_opts_entry, "helgrind_options") ;

  gtk_widget_set_tooltip_text(configure_valgrind_helgrind_opts_label, _("valgrind helgrind: a thread error detector.\n\nLook at $ valgrind -h or  $ man valgrind (HELGRIND OPTIONS).\nfor further informations.") ) ;
  gtk_widget_set_tooltip_text(configure_valgrind_helgrind_opts_entry, _("valgrind helgrind: a thread error detector.\n\nLook at $ valgrind -h or  $ man valgrind (HELGRIND OPTIONS).\nfor further informations.") ) ;




  gtk_box_pack_start(GTK_BOX(configure_valgrind_label_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_label_vbox), configure_valgrind_memcheck_opts_label,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_label_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_label_vbox), configure_valgrind_cachegrind_opts_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_label_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_label_vbox), configure_valgrind_callgrind_opts_label,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_label_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_label_vbox), configure_valgrind_helgrind_opts_label,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_label_vbox), gtk_label_new(""),                         TRUE,  TRUE,  0) ;


  gtk_box_pack_start(GTK_BOX(configure_valgrind_data_vbox), gtk_label_new(""),                        TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_data_vbox), configure_valgrind_memcheck_opts_entry,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_data_vbox), gtk_label_new(""),                        TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_data_vbox), configure_valgrind_cachegrind_opts_entry, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_data_vbox), gtk_label_new(""),                        TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_data_vbox), configure_valgrind_callgrind_opts_entry,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_data_vbox), gtk_label_new(""),                        TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_data_vbox), configure_valgrind_helgrind_opts_entry,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_data_vbox), gtk_label_new(""),                        TRUE,  TRUE,  0) ;

  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(configure_valgrind_hbox), configure_valgrind_image, FALSE, FALSE, MARGING) ;
  #endif

  gtk_box_pack_start(GTK_BOX(configure_valgrind_hbox), configure_valgrind_label_vbox, FALSE, FALSE, MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_valgrind_hbox), configure_valgrind_data_vbox,  TRUE,  TRUE,  MARGING) ;

  gtk_widget_set_name(configure_valgrind_data_vbox, "valgrind_opts") ;

  gtk_widget_show_all(configure_valgrind_hbox) ;

  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), configure_valgrind_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), configure_valgrind_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), configure_valgrind_hbox, _("Valgrind") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), configure_valgrind_hbox, TRUE) ;

  return ;

}



static void configure_code_c_fmt_project(void) {

  GtkWidget *configure_code_c_fmt_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *configure_code_c_fmt_label_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;
  GtkWidget *configure_code_c_fmt_data_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  #ifdef USE_IMG
  GtkWidget *configure_code_fmt_image = gtk_image_new_from_file(PATH_TO_ICON) ;
  #endif

  GtkWidget *configure_code_fmt_indent_label = gtk_label_new( _("Use indent") ) ;

  GtkWidget *configure_code_fmt_indent_chbbox = gtk_check_button_new() ;

  g_signal_connect(G_OBJECT(configure_code_fmt_indent_chbbox), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_indent) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(configure_code_fmt_indent_chbbox), project->use_indent) ;



  GtkWidget *configure_code_fmt_indent_opts_label = gtk_label_new( _("indent options") ) ;

  GtkWidget *configure_code_fmt_indent_opts_entry = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_code_fmt_indent_opts_entry), project->indent_options) ;

  gtk_widget_set_name(configure_code_fmt_indent_opts_entry, "indent_options") ;

  gtk_widget_set_tooltip_text(configure_code_fmt_indent_opts_entry,  _("You can set here the options given for the indent-user target\nSee $ indent -h or $ man indent") ) ;




  GtkWidget *configure_code_fmt_astyle_label = gtk_label_new( _("Use astyle") ) ;

  GtkWidget *configure_code_fmt_astyle_chbbox = gtk_check_button_new() ;

  g_signal_connect(G_OBJECT(configure_code_fmt_astyle_chbbox), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_astyle) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(configure_code_fmt_astyle_chbbox), project->use_astyle) ;



  GtkWidget *configure_code_fmt_astyle_opts_label = gtk_label_new( _("astyle options") ) ;

  GtkWidget *configure_code_fmt_astyle_opts_entry = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_code_fmt_astyle_opts_entry), project->astyle_options) ;

  gtk_widget_set_name(configure_code_fmt_astyle_opts_entry, "astyle_options") ;

  gtk_widget_set_tooltip_text(configure_code_fmt_astyle_opts_entry,  _("You can set here the options given for the astyle-user target\nSee $ astyle -h or $ man astyle") ) ;



  GtkWidget *configure_code_fmt_bcpp_label = gtk_label_new( _("Use bcpp") ) ;

  GtkWidget *configure_code_fmt_bcpp_chbbox = gtk_check_button_new() ;

  g_signal_connect(G_OBJECT(configure_code_fmt_bcpp_chbbox), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_bcpp) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(configure_code_fmt_bcpp_chbbox), project->use_bcpp) ;


  GtkWidget *configure_code_fmt_tabs_label = gtk_label_new( _("Use tabs") ) ;

  GtkWidget *configure_code_fmt_tabs_chbbox = gtk_check_button_new() ;

  g_signal_connect(G_OBJECT(configure_code_fmt_tabs_chbbox), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_tabs) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(configure_code_fmt_tabs_chbbox), project->use_tabs) ;



  GtkWidget *configure_code_fmt_identation_label = gtk_label_new( _("Indentation width") ) ;

  GtkWidget *configure_code_fmt_indentation_spinbut = gtk_spin_button_new_with_range(0, 32, 2) ;

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(configure_code_fmt_indentation_spinbut), project->indentation_width) ;

  g_signal_connect(G_OBJECT(configure_code_fmt_indentation_spinbut), "value-changed", G_CALLBACK(get_spinbutton_value_indentation), &project->indentation_width) ;


  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), gtk_label_new(""),                     TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), configure_code_fmt_indent_label,       FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), gtk_label_new(""),                     TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), configure_code_fmt_indent_opts_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), gtk_label_new(""),                     TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), configure_code_fmt_astyle_label,       FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), gtk_label_new(""),                     TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), configure_code_fmt_astyle_opts_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), gtk_label_new(""),                     TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), configure_code_fmt_bcpp_label,         FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), gtk_label_new(""),                     TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), configure_code_fmt_identation_label,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), gtk_label_new(""),                     TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), configure_code_fmt_tabs_label,         FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_label_vbox), gtk_label_new(""),                     TRUE,  TRUE,  0) ;

  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), configure_code_fmt_indent_chbbox,       FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), configure_code_fmt_indent_opts_entry,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), configure_code_fmt_astyle_chbbox,       FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), configure_code_fmt_astyle_opts_entry,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), configure_code_fmt_bcpp_chbbox,         FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), configure_code_fmt_indentation_spinbut, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), configure_code_fmt_tabs_chbbox,         FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_data_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;

  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_hbox), configure_code_fmt_image,        FALSE, FALSE, MARGING) ;
  #endif

  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_hbox), configure_code_c_fmt_label_vbox, FALSE, FALSE, MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_code_c_fmt_hbox), configure_code_c_fmt_data_vbox,  TRUE,  TRUE,  MARGING) ;

  gtk_widget_set_name(configure_code_c_fmt_data_vbox, "code_fmt") ;

  gtk_widget_show_all(configure_code_c_fmt_hbox) ;
  
  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), configure_code_c_fmt_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), configure_code_c_fmt_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), configure_code_c_fmt_hbox, _("Code beautifiers") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), configure_code_c_fmt_hbox, TRUE) ;

  return ;
}

static void configure_about_project(void) {

  GtkWidget *configure_about_project_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *configure_about_project_image = gtk_image_new_from_file(PATH_TO_ICON) ;

  GtkWidget *configure_about_project_label_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *configure_about_project_data_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  GtkWidget *configure_about_project_author_label = gtk_label_new( _("Author(s)") ) ;

  GtkWidget *configure_about_project_author_entry = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_about_project_author_entry), project->author_s) ;

  gtk_widget_set_name(configure_about_project_author_entry, "author_s") ;



  GtkWidget *configure_about_project_mail_label = gtk_label_new( _("Mail address") ) ;

  GtkWidget *configure_about_project_mail_entry = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_about_project_mail_entry), project->mail_address) ;

  gtk_widget_set_name(configure_about_project_mail_entry, "mail_address") ;



  GtkWidget *configure_about_project_prgweburl_label = gtk_label_new( _("Program URL") ) ;

  GtkWidget *configure_about_project_prgweburl_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_about_project_prgweburl_entry, "program_url") ;



  GtkWidget *configure_about_project_copyright_str_label = gtk_label_new(  _("Copyright") ) ;

  GtkWidget *configure_about_project_copyright_str_entry = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_about_project_copyright_str_entry), project->copyright_string) ;

  gtk_widget_set_name(configure_about_project_copyright_str_entry, "copyright_string") ;

  gtk_entry_set_placeholder_text(GTK_ENTRY(configure_about_project_copyright_str_entry),  _("Copyright (C) <year>  <name of author>") ) ;




  gtk_box_pack_start(GTK_BOX(configure_about_project_label_vbox), gtk_label_new(""),                            TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_label_vbox), configure_about_project_author_label,         FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_label_vbox), gtk_label_new(""),                            TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_label_vbox), configure_about_project_mail_label,           FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_label_vbox), gtk_label_new(""),                            TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_label_vbox), configure_about_project_prgweburl_label,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_label_vbox), gtk_label_new(""),                            TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_label_vbox), configure_about_project_copyright_str_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_label_vbox), gtk_label_new(""),                            TRUE,  TRUE,  0) ;



  gtk_box_pack_start(GTK_BOX(configure_about_project_data_vbox), gtk_label_new(""),                            TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_data_vbox), configure_about_project_author_entry,         FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_data_vbox), gtk_label_new(""),                            TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_data_vbox), configure_about_project_mail_entry,           FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_data_vbox), gtk_label_new(""),                            TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_data_vbox), configure_about_project_prgweburl_entry,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_data_vbox), gtk_label_new(""),                            TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_data_vbox), configure_about_project_copyright_str_entry,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_data_vbox), gtk_label_new(""),                            TRUE,  TRUE,  0) ;

  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(configure_about_project_hbox), configure_about_project_image, FALSE, FALSE, MARGING) ;
  #endif

  gtk_box_pack_start(GTK_BOX(configure_about_project_hbox), configure_about_project_label_vbox, FALSE, FALSE, MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_about_project_hbox), configure_about_project_data_vbox,  TRUE,  TRUE,  MARGING) ;

  gtk_widget_set_name(configure_about_project_data_vbox, "about_infos") ;
  
  gtk_widget_show_all(configure_about_project_hbox) ;
  
  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), configure_about_project_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), configure_about_project_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), configure_about_project_hbox, _("About informations") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), configure_about_project_hbox, TRUE) ;

  return ;
}



static char *get_language(void) {

  char **envp= g_get_environ() ;

  char *lang = (char *) g_environ_getenv(envp, "LANGUAGE") ;
  
  if (lang == NULL) {
    
    lang = (char *) g_environ_getenv(envp, "LANG") ;
    
  }    
    
  g_strfreev(envp) ;

  return lang ;

}


static void configure_new_doc_project(void) {



  #ifdef USE_IMG
  GtkWidget *configure_doc_image = gtk_image_new_from_file(PATH_TO_ICON) ;
  #endif



  GtkWidget *sphinx_checkbuttton = create_checkbox("Use sphinx-doc", _("Use the sphinx-doc documentation generator."), FALSE) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sphinx_checkbuttton), (project->use_sphinx) ? TRUE : FALSE) ;

  if (sphinx_quickstart == NULL) {

    gtk_widget_set_state_flags(sphinx_checkbuttton, GTK_STATE_FLAG_INSENSITIVE, TRUE);

  }

  g_signal_connect(G_OBJECT(sphinx_checkbuttton), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_sphinx) ;

  GtkWidget *sphinx_language_combobox = gtk_combo_box_text_new() ;
  
  
  #ifndef __APPLE__
  
  gchar *system_lang = g_strdup(get_language()) ;

  int c = 0 ;

  while (system_lang[c] != '_') {

    ++c ;
  }

  system_lang[c] = '\0' ;
  
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(sphinx_language_combobox), NULL, "en") ;

  if (g_strcmp0(system_lang, "en")) {

    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(sphinx_language_combobox), NULL, system_lang) ;

  }

  gtk_combo_box_set_active(GTK_COMBO_BOX(sphinx_language_combobox), 0);
  
  
  system_lang[c] = '_' ;
  
  g_free(system_lang) ;
  
  #else
  
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(sphinx_language_combobox), NULL, "en") ;
  
  gtk_combo_box_set_active(GTK_COMBO_BOX(sphinx_language_combobox), 0);
  
  #endif
  
  

  GtkWidget *hbox_doc_lang = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_box_pack_start(GTK_BOX(hbox_doc_lang), gtk_label_new( _("Documentation language: ")), FALSE,  FALSE,   0) ;
  gtk_box_pack_start(GTK_BOX(hbox_doc_lang), gtk_label_new(""),                             TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(hbox_doc_lang), sphinx_language_combobox,                      FALSE,  FALSE,   0) ;

  g_signal_connect(G_OBJECT(sphinx_language_combobox), "changed", G_CALLBACK(get_combo_value), project->sphinx_options->language) ;

  GtkWidget *use_epub_builder = create_checkbox("Use epub builder", _("Sphinx will be able to output the documenation into the *.epub format."), FALSE) ;

  g_signal_connect(G_OBJECT(use_epub_builder), "toggled", G_CALLBACK(get_checkbutton_value), &project->sphinx_options->epub) ;

  GtkWidget *listbox_extension = gtk_list_box_new() ;

  g_object_set(G_OBJECT(listbox_extension), "selection-mode", GTK_SELECTION_NONE, NULL) ;

  gtk_list_box_unselect_all(GTK_LIST_BOX(listbox_extension)) ;

  int idx = 0 ;

  while (sphinx_extensions != NULL) {

    if (sphinx_extensions->data != NULL) {

      gtk_list_box_insert(GTK_LIST_BOX(listbox_extension), create_checkbox(g_strdup(sphinx_extensions->data), NULL, FALSE), idx) ;

      ++idx ;

     }

     if (sphinx_extensions->next != NULL) {

       sphinx_extensions = sphinx_extensions->next ;
     }
     else {

       break ;

     }

  }

  if (sphinx_quickstart != NULL) {

    g_list_free_full(sphinx_extensions, (GDestroyNotify) free);

    sphinx_extensions = NULL ;

  }

  GtkWidget *expander_sphinx = gtk_expander_new("Configure sphinx") ;

  gtk_expander_set_expanded(GTK_EXPANDER(expander_sphinx), TRUE);

  if (sphinx_quickstart == NULL) {

    gtk_widget_set_state_flags(expander_sphinx, GTK_STATE_FLAG_INSENSITIVE, TRUE);

  }

  g_free(sphinx_quickstart) ;

  GtkWidget *vbox_sphinx = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_widget_set_name(vbox_sphinx, "vbox") ;

  gtk_box_pack_start(GTK_BOX(vbox_sphinx), hbox_doc_lang, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(vbox_sphinx), use_epub_builder, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(vbox_sphinx), listbox_extension, FALSE, FALSE, 0) ;

  gtk_container_add(GTK_CONTAINER(expander_sphinx), vbox_sphinx) ;

  GtkWidget *main_vbox_sphinx = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_widget_set_name(main_vbox_sphinx, "sphinx") ;

  gtk_box_set_spacing(GTK_BOX(main_vbox_sphinx), 8) ;

  gtk_box_pack_start(GTK_BOX(main_vbox_sphinx), sphinx_checkbuttton, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(main_vbox_sphinx), expander_sphinx, FALSE, FALSE, 0) ;

  GtkWidget *rst2man_checkbuttton = create_checkbox("Use rst2man", _("Use rst2man for building man-page."), TRUE) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rst2man_checkbuttton), project->use_rst2man) ;

  g_signal_connect(G_OBJECT(rst2man_checkbuttton), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_rst2man) ;

  gtk_box_pack_start(GTK_BOX(main_vbox_sphinx), rst2man_checkbuttton, FALSE, FALSE, 0) ;



  GtkWidget *configure_doc_project_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_box_set_spacing(GTK_BOX(configure_doc_project_hbox), 16) ;

  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(configure_doc_project_hbox), configure_doc_image,  FALSE, FALSE, MARGING) ;
  #endif

  gtk_box_pack_start(GTK_BOX(configure_doc_project_hbox), main_vbox_sphinx,     TRUE,  TRUE,  MARGING) ;
  
  
  gtk_widget_show_all(configure_doc_project_hbox) ;

  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), configure_doc_project_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), configure_doc_project_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), configure_doc_project_hbox, _("Doc generators") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), configure_doc_project_hbox, TRUE) ;


  return ;

}



static void configure_others_info_project(void) {

  GtkWidget *configure_others_info_project_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *configure_others_info_project_image = gtk_image_new_from_file(PATH_TO_ICON) ;

  GtkWidget *configure_others_info_project_label_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *configure_others_info_project_data_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  // NOTE: The user editor is reserved for future use...
  GtkWidget *configure_others_info_project_editor_label = gtk_label_new( _("Used editor") ) ;

  GtkWidget *configure_others_info_project_editor_combo = gtk_combo_box_text_new() ;


  // FIXME: cannot make this mimetype dynamic according to the project language !!!
  GList *apps =  g_app_info_get_all_for_type("text/x-c") ;


  if (apps != NULL) {

    g_list_foreach(apps, &insert_data, configure_others_info_project_editor_combo);

    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(configure_others_info_project_editor_combo), NULL, _("Other") ) ;

    gtk_combo_box_set_active(GTK_COMBO_BOX(configure_others_info_project_editor_combo), 0) ;

    g_list_free(apps) ;
  }
  else {

    GAppInfo *editor = g_app_info_get_default_for_type("text/x-c", FALSE) ;

    if (editor != NULL) {

      gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(configure_others_info_project_editor_combo), NULL, g_path_get_basename(g_app_info_get_executable(editor))) ;

      gtk_combo_box_set_active(GTK_COMBO_BOX(configure_others_info_project_editor_combo), 0) ;

      g_object_unref(editor) ;

    }

  }

  SEC_FREE(project->editor) ;

  project->editor = g_strdup_printf("%s", gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(configure_others_info_project_editor_combo)) ) ;

  g_signal_connect(G_OBJECT(configure_others_info_project_editor_combo), "changed", G_CALLBACK(get_combo_value), project->editor) ;


  GtkWidget *configure_others_info_project_make_opts_label = gtk_label_new( _("Make options") ) ;

  GtkWidget *configure_others_info_project_make_opts_entry = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_others_info_project_make_opts_entry), project->make_options) ;

  gtk_widget_set_name(configure_others_info_project_make_opts_entry, "make_options") ;

  gtk_widget_set_tooltip_text(configure_others_info_project_make_opts_entry, _("Options given to make at every call.\n\nI dislike directory printing behaviour of make:\nit look's like an error message cause of formatting !!!\n\nYou can set the -j (jobs options too)") ) ;



  if (project->make_options != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_others_info_project_make_opts_entry), project->make_options) ;
  }


  GtkWidget *configure_others_info_project_bash_label = gtk_label_new( _("Bash location") ) ;

  GtkWidget *configure_others_info_project_bash_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_others_info_project_bash_entry, "bash_location") ;

  char *bash_location = have_app_application("bash") ;

  gtk_entry_set_text(GTK_ENTRY(configure_others_info_project_bash_entry), bash_location) ;

  if (project->bash_location == NULL) {

    project->bash_location = g_strdup(bash_location) ;
  }

  free(bash_location) ;

  g_object_set(G_OBJECT(configure_others_info_project_bash_entry), "editable", FALSE, NULL) ;


  GtkWidget *configure_others_info_project_compression_label = gtk_label_new( _("Compression level") ) ;

  GtkWidget *configure_others_info_project_compression_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 9, 1) ;

  gtk_widget_set_tooltip_text(configure_others_info_project_compression_label,   _("Set the compression level for building archives from your project")  ) ;
  gtk_widget_set_tooltip_text(configure_others_info_project_compression_scale,   _("Set the compression level for building archives from your project")  ) ;

  gtk_range_set_value(GTK_RANGE(configure_others_info_project_compression_scale), 3) ;

  gtk_scale_set_digits(GTK_SCALE(configure_others_info_project_compression_scale), 0) ;

  gtk_scale_set_value_pos(GTK_SCALE(configure_others_info_project_compression_scale), GTK_POS_TOP) ;

  gtk_scale_set_has_origin(GTK_SCALE(configure_others_info_project_compression_scale), TRUE) ;

  g_signal_connect(G_OBJECT(configure_others_info_project_compression_scale), "value-changed", G_CALLBACK(get_scale_value_compression_level), &project->compression_level) ;


  gtk_box_pack_start(GTK_BOX(configure_others_info_project_label_vbox), gtk_label_new(""),                                  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_label_vbox), configure_others_info_project_editor_label,         FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_label_vbox), gtk_label_new(""),                                  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_label_vbox), configure_others_info_project_make_opts_label,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_label_vbox), gtk_label_new(""),                                  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_label_vbox), configure_others_info_project_bash_label,           FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_label_vbox), gtk_label_new(""),                                  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_label_vbox), configure_others_info_project_compression_label,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_label_vbox), gtk_label_new(""),                                  TRUE,  TRUE,  0) ;


  gtk_box_pack_start(GTK_BOX(configure_others_info_project_data_vbox), gtk_label_new(""),                                  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_data_vbox), configure_others_info_project_editor_combo,         FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_data_vbox), gtk_label_new(""),                                  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_data_vbox), configure_others_info_project_make_opts_entry,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_data_vbox), gtk_label_new(""),                                  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_data_vbox), configure_others_info_project_bash_entry,           FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_data_vbox), gtk_label_new(""),                                  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_data_vbox), configure_others_info_project_compression_scale,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_data_vbox), gtk_label_new(""),                                  TRUE,  TRUE,  0) ;


  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_hbox), configure_others_info_project_image, FALSE, FALSE, MARGING) ;
  #endif

  gtk_box_pack_start(GTK_BOX(configure_others_info_project_hbox), configure_others_info_project_label_vbox, FALSE, FALSE, MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_others_info_project_hbox), configure_others_info_project_data_vbox,  TRUE,  TRUE,  MARGING) ;

  gtk_widget_set_name(configure_others_info_project_data_vbox, "others_infos") ;
  
  gtk_widget_show_all(configure_others_info_project_hbox) ;
  
  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), configure_others_info_project_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), configure_others_info_project_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), configure_others_info_project_hbox, _("Other infos") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), configure_others_info_project_hbox, TRUE) ;


  return ;

}

static void configure_licensing_project(void) {

  GtkWidget *configure_licensing_project_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *configure_licensing_project_label = gtk_label_new( _("Licensing boilerplate: to edit.")) ;

  GtkWidget *configure_licensing_project_viewport = gtk_scrolled_window_new(NULL, NULL) ;



  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(configure_licensing_project_viewport), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  GtkWidget *configure_licensing_project_textview = gtk_text_view_new() ;

  gtk_widget_set_tooltip_text(configure_licensing_project_textview, _("Edit this licensing boilerplate...\nYou can prepend it to every source file with the target:\n$ make prepend-license") ) ;

  gtk_widget_set_name(configure_licensing_project_textview, "licensing_textview") ;

  gtk_container_add(GTK_CONTAINER(configure_licensing_project_viewport), configure_licensing_project_textview) ;

  gtk_widget_set_name(configure_licensing_project_viewport, "licensing_viewport") ;

  GtkTextBuffer *configure_licensing_project_buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW(configure_licensing_project_textview) ) ;

  g_object_set(G_OBJECT(configure_licensing_project_textview), "left-margin", 8, NULL) ;


  gtk_text_buffer_set_text(configure_licensing_project_buffer, project->licensing_boilerplate, -1) ;




  gtk_box_pack_start(GTK_BOX(configure_licensing_project_vbox), configure_licensing_project_label,    FALSE, FALSE, MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_vbox), configure_licensing_project_viewport, TRUE,  TRUE,  MARGING) ;

  gtk_widget_set_name(configure_licensing_project_vbox, "licensing_hbox") ;


  GtkWidget *configure_licensing_project_format_label = gtk_label_new( _("File formats")) ;

  GtkWidget *configure_licensing_project_format_dbk_checkbutton   = create_checkbox("docbook",  _("Include a docbook (*.dbk) license file to project"),   project->use_licensing_dkb_format)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_dbk_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_licensing_dkb_format) ;

  GtkWidget *configure_licensing_project_format_epub_checkbutton  = create_checkbox("epub",     _("Include a epub (*.epub) license file to project"),   project->use_licensing_epub_format)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_epub_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_licensing_epub_format) ;

  GtkWidget *configure_licensing_project_format_pdf_checkbutton   = create_checkbox("pdf",      _("Include a pdf (*.pdf) license file to project"),   project->use_licensing_pdf_format)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_pdf_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_licensing_pdf_format) ;

  GtkWidget *configure_licensing_project_format_html_checkbutton  = create_checkbox("html",     _("Include a html (*.html) license file to project"),  project->use_licensing_html_format)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_html_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_licensing_html_format) ;

  GtkWidget *configure_licensing_project_format_tex_checkbutton   = create_checkbox("latex",    _("Include a latex (*.tex) license file to project"),   FALSE)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_tex_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_licensing_latex_format) ;

  GtkWidget *configure_licensing_project_format_texi_checkbutton  = create_checkbox("texinfo",  _("Include a texinfo (*.texi) license file to project"),  project->use_licensing_texinfo_format)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_texi_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_licensing_texinfo_format) ;

  GtkWidget *configure_licensing_project_format_txt_checkbutton   = create_checkbox("text",     _("Include a text (*.txt) license file to project"),   project->use_licensing_text_format)   ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_txt_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &project->use_licensing_text_format) ;

  GtkWidget *configure_licensing_project_format_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),configure_licensing_project_format_label, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),gtk_label_new(""), TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),configure_licensing_project_format_dbk_checkbutton, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),gtk_label_new(""), TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),configure_licensing_project_format_epub_checkbutton, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),gtk_label_new(""), TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),configure_licensing_project_format_pdf_checkbutton, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),gtk_label_new(""), TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),configure_licensing_project_format_html_checkbutton, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),gtk_label_new(""), TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),configure_licensing_project_format_tex_checkbutton, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),gtk_label_new(""), TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),configure_licensing_project_format_texi_checkbutton, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),gtk_label_new(""), TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),configure_licensing_project_format_txt_checkbutton, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_format_vbox),gtk_label_new(""), TRUE, TRUE, 0) ;



  GtkWidget *configure_licensing_project_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_box_pack_start(GTK_BOX(configure_licensing_project_hbox), configure_licensing_project_vbox, TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_hbox), configure_licensing_project_format_vbox, FALSE, FALSE, 0) ;
  
  gtk_widget_show_all(configure_licensing_project_hbox) ;
  
  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), configure_licensing_project_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), configure_licensing_project_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), configure_licensing_project_hbox, _("Licensing") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), configure_licensing_project_hbox, TRUE) ;

  return ;

}

static void configure_desktop_file_project(void) {

  GtkWidget *configure_desktop_file_project_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *configure_desktop_file_project_label = gtk_label_new( _("Desktop file template: to edit.")) ;

  GtkWidget *configure_desktop_file_project_viewport = gtk_scrolled_window_new(NULL, NULL) ;

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(configure_desktop_file_project_viewport), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  GtkWidget *configure_desktop_file_project_textview = gtk_text_view_new() ;

  gtk_widget_set_tooltip_text(configure_desktop_file_project_textview, _("Edit this destop file boilerplate...\nYou can use it after as desktop file support.") ) ;

  gtk_widget_set_name(configure_desktop_file_project_textview, "desktop_file_textview") ;

  gtk_container_add(GTK_CONTAINER(configure_desktop_file_project_viewport), configure_desktop_file_project_textview) ;


  GtkTextBuffer *configure_desktop_file_project_buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW(configure_desktop_file_project_textview) ) ;

  g_object_set(G_OBJECT(configure_desktop_file_project_textview), "left-margin", 8, NULL) ;


  gtk_text_buffer_set_text(configure_desktop_file_project_buffer, project->desktop_file_boilerplate, -1) ;

  gtk_box_pack_start(GTK_BOX(configure_desktop_file_project_vbox), configure_desktop_file_project_label,            FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_desktop_file_project_vbox), configure_desktop_file_project_viewport,         TRUE,  TRUE,  0) ;

  gtk_widget_set_name(configure_desktop_file_project_viewport, "desktop_file_viewport") ;
  
  gtk_widget_show_all(configure_desktop_file_project_vbox) ;
  
  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), configure_desktop_file_project_vbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), configure_desktop_file_project_vbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), configure_desktop_file_project_vbox, _("desktop file") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), configure_desktop_file_project_vbox, TRUE) ;

  return ;

}

static void summary_of_project(void) {

  GtkWidget *summary_of_project_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *summary_of_project_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *summary_of_project_image = gtk_image_new_from_file(PATH_TO_ICON) ;


  GtkWidget *summary_of_project_progressbar = gtk_progress_bar_new() ;

  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(summary_of_project_progressbar), 1.0) ;

  gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(summary_of_project_progressbar), TRUE) ;

  gtk_progress_bar_set_text(GTK_PROGRESS_BAR(summary_of_project_progressbar), _("Project construction 100% (Completed)") );


  gchar *summary_text =    g_strdup_printf( _("<big>Creating new project named:</big> <big><b>%s</b></big>.\n\n"
                                              "<big>Version:</big> <big><b>%s</b></big>\n\n<big>Using the</big> <big><b>%s</b></big> <big>language</big>.\n\n"
                                              "<big>To Install in folder:</big>\n<big><i>%s</i></big>"),

                                              project->prgname, project->version_string, project->language, project->project_folderpath) ;

  GtkWidget *summary_of_project_label = gtk_label_new(summary_text) ;

  gtk_widget_set_name(summary_of_project_label, "summary_of_project_label") ;

  free(summary_text) ;

  GtkWidget *configure_others_export_as_profile = gtk_button_new_with_label( _("Export settings as profile") ) ;

  g_signal_connect(G_OBJECT(configure_others_export_as_profile), "clicked", G_CALLBACK(save_as_profile), NULL) ;

  gtk_box_pack_start(GTK_BOX(summary_of_project_vbox), gtk_label_new(""),                   TRUE, TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(summary_of_project_vbox), summary_of_project_progressbar,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(summary_of_project_vbox), gtk_label_new(""),                   TRUE, TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(summary_of_project_vbox), summary_of_project_label,            FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(summary_of_project_vbox), gtk_label_new(""),                   TRUE, TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(summary_of_project_vbox), configure_others_export_as_profile,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(summary_of_project_vbox), gtk_label_new(""),                   TRUE, TRUE,   0) ;

  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(summary_of_project_hbox), summary_of_project_image, FALSE, FALSE, 0) ;
  #endif


  gtk_box_pack_start(GTK_BOX(summary_of_project_hbox), summary_of_project_vbox, TRUE, TRUE, MARGING) ;

  gtk_widget_set_name(summary_of_project_vbox, "summary_of_project_container") ;
  
  gtk_widget_show_all(summary_of_project_hbox) ;
  
  gtk_assistant_append_page(GTK_ASSISTANT(new_project_assistant), summary_of_project_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(new_project_assistant), summary_of_project_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(new_project_assistant), summary_of_project_hbox, _("Summary") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(new_project_assistant), summary_of_project_hbox, TRUE) ;

  return ;

}


static void cancel_event(GtkAssistant *assistant, gpointer pointer) {
  /** Check if any file still unsaved before exit the application **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  //free_cur_project_settings() ;

  free_project_settings() ;

  init_project_settings() ;

  gtk_widget_destroy(GTK_WIDGET(assistant)) ;

  assistant = NULL ;

  return ;
}
