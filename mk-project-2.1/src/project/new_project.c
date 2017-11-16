#include "./new_project.h"

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

void create_new_project(void) {


  #if DEBUG

  fprintf(stderr,"language: %s\n",project->language) ;

  fprintf(stderr,"prgname: %s\n",project->prgname) ;

  fprintf(stderr,"version: %s\n", project->version_string) ;

  fprintf(stderr,"license: %s\n",project->license) ;

  fprintf(stderr, "folderpath %s\n",project->project_folderpath) ;


  /** Compiler settings: **/

  fprintf(stderr,"compiler: %s\n", project->compiler) ;

  fprintf(stderr,"warnings: %s\n",project->warnings) ;

  fprintf(stderr,"cflags: %s\n",project->cflags) ;

  fprintf(stderr,"cppflags: %s\n",project->cppflags) ;

  fprintf(stderr,"ldflags: %s\n",project->ldflags) ;

  fprintf(stderr,"ldlibs: %s\n",project->ldlibs) ;


  /** Files informations: **/

  fprintf(stderr,"main file: %s\n", project->main_file) ;

  fprintf(stderr,"ext src: %s\n", project->ext_src) ;
  fprintf(stderr,"ext hdr: %s\n", project->ext_hdr) ;

  fprintf(stderr,"program library: %d\n", project->program_library) ;


  /** Debugging informations: **/

  fprintf(stderr,"nm options :%s\n", project->nm_options) ;
  fprintf(stderr,"gdb options :%s\n", project->gdb_options) ;
  fprintf(stderr,"strace options :%s\n", project->strace_options) ;
  fprintf(stderr,"ltrace options :%s\n", project->ltrace_options) ;
  fprintf(stderr,"ldd options :%s\n", project->ldd_options) ;
  fprintf(stderr,"gprof options :%s\n", project->gprof_options) ;


  /** Oprofile informations: **/

  fprintf(stderr,"operf options: %s\n", project->operf_options) ;
  fprintf(stderr,"ocount options: %s\n", project->ocount_options) ;
  fprintf(stderr,"opreport options: %s\n", project->opreport_options) ;
  fprintf(stderr,"opannotate options: %s\n", project->opannotate_options) ;
  fprintf(stderr,"opgprof options: %s\n", project->opgprof_options) ;

  /** valgrind informations: **/

  fprintf(stderr,"valgrind_memcheck: %s\n", project->valgrind_memcheck) ;
  fprintf(stderr,"valgrind_cachegrind: %s\n", project->valgrind_cachegrind) ;
  fprintf(stderr,"valgrind_callgrind: %s\n", project->valgrind_callgrind) ;
  fprintf(stderr,"valgrind_helgrind: %s\n", project->valgrind_helgrind) ;

  /** C/C++ Code formatter settings: **/

  fprintf(stderr," use indent %d options: %s\n",project->use_indent, project->indent_options) ;
  fprintf(stderr," use astyle %d options: %s\n",project->use_astyle, project->astyle_options) ;
  fprintf(stderr," use bcpp %d \n",project->use_bcpp) ;

  fprintf(stderr,"indentation width %d use tabs: %d\n", project->indentation_width, project->use_tabs) ;


  fprintf(stderr,"use sphinx: %d\n",project->use_sphinx) ;



  /** About informations: **/

  fprintf(stderr,"author: %s\n",project->author_s) ;
  fprintf(stderr,"mail: %s\n",project->mail_address) ;
  fprintf(stderr,"url: %s\n",project->program_url) ;
  fprintf(stderr,"copyright: %s\n",project->copyright_string) ;



  /** Other informations: **/

  fprintf(stderr,"editor: %s\n",project->editor) ;
  fprintf(stderr,"make options: %s\n",project->make_options) ;
  fprintf(stderr,"bash location: %s\n",project->bash_location) ;
  fprintf(stderr,"compression_level: %d\n",project->compression_level) ;

  #endif

  // This works perfectly.
  GtkWidget *submenu ;

  if ((submenu = gtk_menu_item_get_submenu(GTK_MENU_ITEM(gtk_smart_menu_item_get_menuitem(gui->menu->make_menubutton)))) != NULL) {

    #ifdef DEBUG
    fprintf(stdout,"Submenu found\n") ;
    #endif
   
    if (gui->menu->make_menu != NULL) {
   
      gtk_widget_destroy(gui->menu->make_menu) ;
    
    }
     
    gui->menu->make_menu = gtk_menu_new() ;

  }
  #ifdef DEBUG
  else {
    fprintf(stdout,"No submenu !\n") ;
   

   
  }
  #endif


  gchar *prgname_cp = g_strdup(project->prgname);

  /** If a character from @project->prgname not in this characters sequence it is replaced by an underscore:              **/
  prgname_cp = g_strcanon(prgname_cp, "0123456789" "_-:." "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ", '_') ;

  g_free(project->prgname) ;

  project->prgname = g_strdup(prgname_cp) ;

  g_free(prgname_cp) ;

  #if 1
  if (project->version_string == NULL || (! g_strcmp0(project->version_string,""))) {

    // Abitrary setting the version string because it is better anyway and for the pkg-* targets.

    project->version_string = g_strdup("1.0") ;

  }
  #endif

  // Format main Makefile.
  fmt_makefile(PATH_TO_MAIN_MAKEFILE_TEMPLATE, g_strconcat(project->project_folderpath, "/Makefile", NULL) ) ;

  #ifdef THREADING
  /** This comes into dysfunctionalities... **/
  GThread *sphinx_thread = NULL ;

  if (project->use_sphinx) {

     gchar *makefile_path = g_strconcat(project->project_folderpath, "/Makefile", NULL) ;

     sphinx_thread = g_thread_new("sphinx_gen", (GThreadFunc) generate_sphinx_doc, makefile_path) ;
  }
  #endif

  gchar *project_filepath = g_strconcat(project->project_folderpath, "/", project->prgname, ".mkp", NULL) ;

  xml_writer(project_filepath, project) ;

  g_free(project_filepath) ;

  /** Remove leading and trailing spaces: **/
  g_strstrip(project->warnings) ;
  g_strstrip(project->cflags)   ;
  g_strstrip(project->cppflags) ;
  g_strstrip(project->ldflags)  ;
  g_strstrip(project->ldlibs)   ;


  /** Creating folders: **/
  creat_dir_p_and_files(g_strdup(project->project_folderpath), NULL) ;
  creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/src/headers", NULL), NULL) ;
  creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/share/locale", NULL), NULL) ;
  creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/share", "/", project->prgname, NULL), NULL) ;
  creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/bin", NULL), NULL) ;
  creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/dist", NULL), NULL) ;
  creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/.scripts", NULL), NULL) ;


  /** Create *.desktop and licensing boilerplate folders. **/
  creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/desktop", NULL), NULL) ;
  creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/.licensing", NULL), NULL) ;

  /** Creating SubMakefiles folder. **/
  creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/.SubMakefiles", NULL), NULL) ;

  /** Creating pkg-* targets auto incrementing temporary file. **/
  creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/.release", "/RELEASE.txt", NULL), NULL) ;

  creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/doc", NULL), NULL) ;



  gchar *path_to_license = g_strconcat(project->project_folderpath, "/LICENSE", NULL) ;

  creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/LICENSE", NULL), NULL) ;

  add_license(project) ;

  g_free(path_to_license) ;



  // Copy the prepend license python script.
  gchar *licensing_filepath = g_strconcat(project->project_folderpath, "/.scripts/prepend_license.py", NULL) ;
  copy_file(PATH_TO_PREPEND_LICENSE_FILE, licensing_filepath) ;
  g_free(licensing_filepath) ;

  // Create *.desktop boilerplate file with content.
  create_file(g_strconcat(project->project_folderpath, "/desktop", NULL), project->desktop_file_boilerplate, g_strconcat(project->prgname, ".desktop", NULL) ) ;

  // Write content to licensing boilerplate file.
  write_content_to_file(g_strconcat(project->project_folderpath, "/.licensing", "/licensing.tmpl", NULL), project->licensing_boilerplate) ;


  // Format Makefile(s).
  fmt_makefile_dist(PATH_TO_DIST_MK_TEMPLATE, g_strconcat(project->project_folderpath, "/.SubMakefiles/distributing.mk", NULL) ) ;

  fmt_makefile_doc(PATH_TO_DOC_MK_TEMPLATE, g_strconcat(project->project_folderpath, "/.SubMakefiles/documentation.mk", NULL) ) ;

  gchar *sphinx_show_filepath = g_strconcat(project->project_folderpath, "/.SubMakefiles/sphinx-show.mk", NULL) ;
  copy_file(PATH_TO_SPHINX_SHOW_MK, sphinx_show_filepath) ;
  g_free(sphinx_show_filepath) ;

  // Copy Makefile(s)
  gchar *binary_check_filepath = g_strconcat(project->project_folderpath, "/.SubMakefiles/binary_checks.mk", NULL) ;
  copy_file(PATH_TO_BIN_CHECK_MK_TEMPLATE,  binary_check_filepath ) ;
  g_free(binary_check_filepath) ;

  gchar *make_path_filepath = g_strconcat(project->project_folderpath, "/.SubMakefiles/path.mk", NULL) ;
  copy_file(PATH_TO_PATH_MK_TEMPLATE, make_path_filepath) ;
  g_free(make_path_filepath) ;

  fmt_makefile_code_fmt(PATH_TO_FMT_CODE_MK_TEMPLATE, g_strconcat(project->project_folderpath, "/.SubMakefiles/code_formatter.mk", NULL) ) ;

  // Copy file
  gchar *readme_filepath = g_strconcat(project->project_folderpath, "/src", "/README.html", NULL) ;
  copy_file(PATH_TO_C_CXX_PROJECT_README,  readme_filepath) ;
  g_free(readme_filepath) ;

  if (project->program_library) {

    // Program library enabled we process...

    creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/src", "/lib", project->prgname, NULL), NULL) ;

    fmt_lib_makefile(PATH_TO_PATH_LIB_MK_TEMPLATE, g_strconcat(project->project_folderpath, "/src", "/lib", project->prgname, "/", "Makefile", NULL) ) ;


    gchar *lib_readme_filepath = g_strconcat(project->project_folderpath, "/src", "/lib", project->prgname, "/README.rst", NULL) ;
    copy_file(PATH_TO_C_CXX_LIB_README, lib_readme_filepath) ;
    g_free(lib_readme_filepath) ;

    if (! g_strcmp0(project->language, "C") ) {

      fmt_h_guard_only(PATH_TO_C_LIB_H_TEMPLATE, g_strconcat(project->project_folderpath, "/src", "/lib", project->prgname, "/", "libprint_it", project->ext_hdr, NULL) ) ;

      gchar *libprint_it_filepath = g_strconcat(project->project_folderpath, "/src", "/lib", project->prgname, "/", "libprint_it", project->ext_src, NULL) ;
      copy_file(PATH_TO_C_LIB_C_TEMPLATE,  libprint_it_filepath) ;
      g_free(libprint_it_filepath) ;

    }
    else if (! g_strcmp0(project->language, "C++") ) {

      fmt_h_guard_only(PATH_TO_CXX_LIB_H_TEMPLATE, g_strconcat(project->project_folderpath, "/src", "/lib", project->prgname, "/", "libprint_it", project->ext_hdr, NULL) ) ;

      fmt_global_vars_cxx_src(PATH_TO_CXX_LIB_C_TEMPLATE, g_strconcat(project->project_folderpath, "/src", "/lib", project->prgname, "/", "libprint_it", project->ext_src, NULL) ) ;

    }

  }

  if (! g_strcmp0(project->language, "C")) {

    // Format and copy C project specific files:

    fmt_defines_h(PATH_TO_C_DEFINES_H_TEMPLATE, g_strconcat(project->project_folderpath, "/src/headers/defines", project->ext_hdr, NULL) ) ;

    fmt_h_guard_only(PATH_TO_C_INCLUDES_H_TEMPLATE, g_strconcat(project->project_folderpath, "/src/headers/includes", project->ext_hdr, NULL) ) ;
    fmt_h_guard_only(PATH_TO_C_GLOBAL_VARS_H_TEMPLATE, g_strconcat(project->project_folderpath, "/src/global_vars", project->ext_hdr, NULL) ) ;


    gchar *global_vars_filepath = g_strconcat(project->project_folderpath, "/src/global_vars", project->ext_src, NULL) ;
    copy_file(PATH_TO_C_GLOBAL_VARS_C_TEMPLATE,  global_vars_filepath) ;
    g_free(global_vars_filepath) ;

    gchar *main_filepath = g_strconcat(project->project_folderpath, "/src/main", project->ext_src, NULL) ;
    copy_file(PATH_TO_C_MAIN_TEMPLATE, main_filepath ) ;
    g_free(main_filepath) ;

  }
  else if (! g_strcmp0(project->language, "C++")) {

    // Format and copy C++ project specific files:

    fmt_defines_h(PATH_TO_CXX_DEFINES_H_TEMPLATE, g_strconcat(project->project_folderpath, "/src/headers/defines", project->ext_hdr, NULL) ) ;

    fmt_h_guard_only(PATH_TO_CXX_INCLUDES_H_TEMPLATE, g_strconcat(project->project_folderpath, "/src/headers/includes", project->ext_hdr, NULL) ) ;

    fmt_global_vars_cxx_hdr(PATH_TO_CXX_GLOBAL_VARS_H_TEMPLATE, g_strconcat(project->project_folderpath, "/src/global_vars", project->ext_hdr, NULL) ) ;

    fmt_global_vars_cxx_src(PATH_TO_CXX_GLOBAL_VARS_C_TEMPLATE, g_strconcat(project->project_folderpath, "/src/global_vars", project->ext_src, NULL) ) ;

    fmt_main_cxx(PATH_TO_CXX_MAIN_TEMPLATE, g_strconcat(project->project_folderpath, "/src/main", project->ext_src, NULL) ) ;

  }

  gchar *have_rst2man = have_app_application("rst2man") ;

  if (have_rst2man && project->use_rst2man) {

    gchar *rst2man_file[2] = { g_strconcat(project->project_folderpath, "/rst2man","/", project->prgname, ".rst", NULL), NULL} ;

    creat_dir_p_and_files( g_strconcat(project->project_folderpath, "/rst2man", NULL), rst2man_file )   ;

    g_free(have_rst2man) ;

  }



  int fd = -1 ;

  gchar *readme_project_filepath = g_strconcat(project->project_folderpath, "/", "README", NULL) ;
  fd=g_creat(readme_project_filepath  , 0644);
  g_free(readme_project_filepath) ;
  g_close(fd,NULL);

  gchar *ChangeLog_project_filepath = g_strconcat(project->project_folderpath, "/", "ChangeLog", NULL) ;
  fd=g_creat(ChangeLog_project_filepath, 0644) ;
  g_free(ChangeLog_project_filepath) ;
  g_close(fd,NULL);

  gchar *thanks_project_filepath = g_strconcat(project->project_folderpath, "/", "THANKS", NULL) ;
  fd=g_creat(thanks_project_filepath, 0644) ;
  g_free(thanks_project_filepath) ;
  g_close(fd,NULL);

  gchar *news_project_filepath = g_strconcat(project->project_folderpath, "/", "NEWS", NULL) ;
  fd=g_creat(news_project_filepath, 0644) ;
  g_free(news_project_filepath) ;
  g_close(fd,NULL);

  gchar *whoami_project_filepath = g_strconcat(project->project_folderpath, "/", "WHOAMI", NULL) ;
  fd=g_creat(whoami_project_filepath, 0644) ;
  g_free(whoami_project_filepath) ;
  g_close(fd,NULL);

  gchar *hackme_project_filepath = g_strconcat(project->project_folderpath, "/", "HACKME", NULL) ;
  fd=g_creat(hackme_project_filepath, 0644) ;
  g_free(hackme_project_filepath) ;
  g_close(fd,NULL);

  gchar *todo_project_filepath = g_strconcat(project->project_folderpath, "/", "TODO", NULL) ;
  fd=g_creat(todo_project_filepath, 0644) ;
  g_free(todo_project_filepath) ;
  g_close(fd,NULL);

  gchar *contributors_project_filepath = g_strconcat(project->project_folderpath, "/", "CONTRIBUTORS", NULL) ;
  fd=g_creat(contributors_project_filepath, 0644) ;
  g_free(contributors_project_filepath) ;
  g_close(fd,NULL);
 
  sync() ;
 
  #ifdef THREADING

  if (project->use_sphinx) {

    g_thread_join(sphinx_thread) ;

    g_thread_unref(sphinx_thread) ;

  }

  #else

  if (project->use_sphinx) {

    gchar *makefile_path = g_strconcat(project->project_folderpath, "/Makefile", NULL) ;

    generate_sphinx_doc(makefile_path) ;
  }

  #endif

  sync() ;

  gtk_widget_set_state_flags( gtk_smart_menu_item_get_menuitem(gui->menu->reconf_project), GTK_STATE_FLAG_ACTIVE, TRUE) ;
  gtk_widget_set_state_flags( gtk_smart_menu_item_get_menuitem(gui->menu->add_file_to_project), GTK_STATE_FLAG_ACTIVE, TRUE) ;

  // Getting the $ make help output to construct the menu-items.
  get_output_make(project->project_folderpath) ;
 
  sync() ;

  // Change directory to project directory so that the user can type make commands directly into the terminal.
  gchar *cd_to_Makefile_dir_cmd = g_strdup_printf("cd %s \r", project->project_folderpath) ;
  vte_terminal_feed_child( VTE_TERMINAL(gtk_mkterm_get_vte_terminal(gui->make_terminal)), cd_to_Makefile_dir_cmd, strlen(cd_to_Makefile_dir_cmd) ) ;
  free(cd_to_Makefile_dir_cmd) ;

  // Pop-up and pop-down menu to activated it one time:
  #if (GTK_MINOR_VERSION < 22)
  gtk_menu_popup(GTK_MENU(gui->menu->make_menu), NULL, NULL, NULL, NULL, 0, gtk_get_current_event_time())  ;
  #else
  gtk_menu_popup_at_pointer(GTK_MENU(gui->menu->make_menu), NULL);
  #endif

  gtk_menu_popdown(GTK_MENU(gui->menu->make_menu)) ;

  #ifdef MAC_INTEGRATION // The library gtk-mac-integration-gtk3 define this.
  // @NOTE: the mac top application menu doesn't update correctly the menu radio buttons !
  //        I cant' use gtkosx_application_insert_app_menu_item(...) properly.
  //gtkosx_application_set_menu_bar(gtkosx_application_get(), GTK_MENU_SHELL(menu_bar)) ;
  gtkosx_application_sync_menubar(gtkosx_application_get());
  #endif

  return ;

}







