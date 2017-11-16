#include "./load_project.h"

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

void load_project_callback(const char *filepath) {

  // This works perfectly:
  GtkWidget *submenu ;

  if ((submenu = gtk_menu_item_get_submenu(GTK_MENU_ITEM(gtk_smart_menu_item_get_menuitem(gui->menu->make_menubutton)))) != NULL) {

    #ifdef DEBUG
    fprintf(stdout,"Submenu found\n") ;
    #endif

    gtk_widget_destroy(gui->menu->make_menu) ;

    gui->menu->make_menu = gtk_menu_new() ;

  }
  else {

    #ifdef DEBUG
    fprintf(stdout,"No submenu !\n") ;
    #endif
  }



  gtk_widget_set_state_flags( gtk_smart_menu_item_get_menuitem(gui->menu->reconf_project), GTK_STATE_FLAG_ACTIVE, TRUE) ;

  gtk_widget_set_state_flags( gtk_smart_menu_item_get_menuitem(gui->menu->add_file_to_project), GTK_STATE_FLAG_ACTIVE, TRUE) ;

  gchar *project_dirpath = g_path_get_dirname(filepath) ;

  // Copy informations to project.
  SEC_FREE(project->project_folderpath)

  project->project_folderpath = g_strdup(project_dirpath) ;

  SEC_FREE(project->prgname)

  // Retrieve data from *.mkp file
  get_xml_data(filepath, project) ;


  g_strstrip(project->language) ;


  // Change dir command:
  char *cd_to_Makefile_dir_cmd = g_strdup_printf("cd %s \r", project_dirpath) ;

  vte_terminal_feed_child( VTE_TERMINAL(gtk_mkterm_get_vte_terminal(gui->make_terminal)), cd_to_Makefile_dir_cmd, strlen(cd_to_Makefile_dir_cmd) ) ;

  free(cd_to_Makefile_dir_cmd) ;


  char *licensing_filepath = g_strconcat(project_dirpath, "/.licensing", "/licensing.tmpl", NULL) ;

  cur_project->licensing_boilerplate = get_file_content(licensing_filepath) ;

  char *desktop_filepath = g_strconcat(project_dirpath, "/desktop", "/", project->prgname, ".desktop", NULL) ;


  project->desktop_file_boilerplate = get_file_content(desktop_filepath) ;


  // Parse Makefile(s)
  get_output_make(project_dirpath) ;
 
  #ifdef MAC_INTEGRATION // The library gtk-mac-integration-gtk3 define this.
  // @NOTE: the mac top application menu doesn't update correctly the menu radio buttons !
  //        I cant' use gtkosx_application_insert_app_menu_item(...) properly.
  //gtkosx_application_set_menu_bar(gtkosx_application_get(), GTK_MENU_SHELL(menu_bar)) ;
  gtkosx_application_sync_menubar(gtkosx_application_get());
  #endif

  g_free(project_dirpath) ;

}

static char *get_hdr_filepath(const char *filepath) {

  int16_t c ;

  gchar *header_file = g_strdup(filepath) ;

  for (c=strlen(filepath) ; c > 0 ; --c) {

    // Removing extension from source file in the goal to replace it
    // with the header extension.

    if (filepath[c] == '.') {

      header_file[c] = '\0' ;

      break ;
    }
    else {

      header_file[c] = '\0' ;

    }

  }

  gchar *header_file_make_fmt = g_strdup_printf("%s%s", header_file, project->ext_hdr) ;

  g_free(header_file) ;

  return header_file_make_fmt ;

}

void add_file_to_project_callback(const char *filepath, bool add_header_file, bool file_in_project_path, bool file_into_source_folder) {

  gchar *filepath_dup = g_strdup(filepath) ;

  int c ;

  int cc = 0 ;

  gchar *filepath_relativ = g_malloc0(sizeof(filepath)) ;

  gchar *tmp = g_strconcat( project->project_folderpath, "/", NULL) ;

  if (file_in_project_path && file_into_source_folder) {

    for (c = strlen(filepath_dup)-1 ; c > 0 ; --c, ++cc) {

      if (filepath_dup[c] != '/') {

        filepath_relativ[cc]=filepath_dup[c] ;

        filepath_dup[c] = '\0' ;

      }
      else {

        if (! g_strcmp0(filepath_dup, tmp) ) {

          /** End of string reach **/

          break ;
        }

        if (! is_folder_source_reach(filepath_dup)) {

          filepath_relativ[cc]=filepath_dup[c] ;

          /** File not in ./source folder **/

          filepath_dup[c] = '\0' ;
        }
        else {

          /** File is in ./source folder  **/
          break ;
        }

      }

    }

  }


  gchar *filepath_make_fmt = NULL ;

  gchar *make_filepath = g_strconcat(project->project_folderpath, "/", "Makefile", NULL) ;

  if (file_in_project_path && file_into_source_folder) {

    filepath_make_fmt = g_strdup_printf("$(SRC_DIR)/%s", g_strreverse(filepath_relativ)) ;

    insert_new_file_in_makefile(make_filepath, "SRC_FILES", project->ext_src, filepath_make_fmt) ;

    if (add_header_file) {

      int16_t c = -1 ;

      gchar *header_file = g_strdup(filepath_make_fmt) ;

      if ( (! g_strcmp0(project->language, "C")) || (! g_strcmp0(project->language, "C++")) ) {

        for (c=strlen(filepath_make_fmt) ; c > 0 ; --c) {

          // Removing extension from source file in the goal to replace it
          // with the header extension.

          if (filepath_make_fmt[c] == '.') {

            header_file[c] = '\0' ;

            break ;
          }
          else {

            header_file[c] = '\0' ;

          }

        }

      }



      gchar *header_file_make_fmt = g_strdup_printf("%s%s", header_file, project->ext_hdr) ;

      g_free(header_file) ;


      insert_new_file_in_makefile(make_filepath, "HDR_FILES", project->ext_hdr, header_file_make_fmt) ;

      gchar *header_file_realpath = get_hdr_filepath(filepath) ;

      if (! g_file_test(header_file_realpath, G_FILE_TEST_EXISTS)) {

        FILE *fp = g_fopen(header_file_realpath, "w") ;

        fclose(fp) ;

      }

      g_free(header_file_make_fmt) ;

      g_free(header_file_realpath) ;


    }

  }
  else {

    gchar *header_file_realpath = get_hdr_filepath(filepath) ;

    // Insert new source file in Makefile ; Added to the make @SRC_FILES variable.
    insert_new_file_in_makefile(make_filepath, "SRC_FILES", project->ext_src, filepath) ;

    // Insert new header file in Makefile ; Added to the make @HDR_FILES variable.
    insert_new_file_in_makefile(make_filepath, "HDR_FILES", project->ext_hdr, header_file_realpath) ;


    if (! g_file_test(header_file_realpath, G_FILE_TEST_EXISTS)) {

      // Create header file if not exist.

      FILE *fp = g_fopen(header_file_realpath, "w") ;

      fclose(fp) ;

    }

    g_free(header_file_realpath) ;

  }

  g_free(tmp) ;

  SEC_FREE(filepath_make_fmt) ;

  SEC_FREE(make_filepath) ;


  if (filepath_dup[0] != '\0') {
    SEC_FREE(filepath_dup)
  }

  SEC_FREE(filepath_relativ)

  return ;

}

bool is_folder_source_reach(const char *filepath) {

  /** Is in ./source folder check **/

  if (filepath[0] == '\0') {

    return true ;

  }

  return g_str_has_suffix(filepath, "/src/") ;

}


bool is_folder_source(const char *filepath) {

  /** Is in source (./src) folder check **/

  if (filepath == NULL) {

    return false ;

  }

  // Searches the string haystack for the last occurrence of the string needle.
  gchar *ret = g_strrstr(filepath, "/src");

  if (ret == NULL) {

    return false ;
  }
  else {

    return true ;
  }

}


bool is_in_project_path(const char *project_folderpath, const char *filepath) {

  /** Is in project folder check **/

  if (filepath == NULL) {

    return false ;

  }


  // Searches the string haystack for the last occurrence of the string needle.
  gchar *ret = g_strrstr(filepath, g_path_get_basename(project_folderpath) );

  if (ret == NULL) {

    return false ;
  }
  else {

    return true ;
  }

}

void remove_trailing_space_from_file(const char *filepath) {

  /** Remove trailing space from file using sed (Stream Editor). **/

  gchar *trailing_spaces_deleting = g_strdup_printf("sed -i 's/[[:space:]]$//' '%s'", (char *) filepath) ;

  int ret ;

  if ((ret = system(trailing_spaces_deleting)) == -1) {

    g_warning("Removing trailing space failure:\n%s\n", trailing_spaces_deleting) ;

  }

  free(trailing_spaces_deleting) ;

  return ;

}
