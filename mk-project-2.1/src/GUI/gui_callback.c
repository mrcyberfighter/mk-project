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

#include "./gui_callback.h"

static gchar *generate_target_folder(const gchar *new_folder, const gchar *filepath) ;

static gchar *strip_archive_sufffix(gchar *archive_basename_without_extension, const gchar *pattern) ;

static gchar *extract_file(const gchar *filepath) ;

static void move_archive_file(const gchar *archive_path, const gchar *dst_dir) ;

void load_project(GtkWidget *widget) {

  /** Load a project file callback. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *file_chooser = gtk_file_chooser_dialog_new( _("Choose a mk-project file to load"), GTK_WINDOW(gui->window), GTK_FILE_CHOOSER_ACTION_OPEN, _("Open"), GTK_RESPONSE_ACCEPT, _("Cancel"), GTK_RESPONSE_CANCEL, NULL);

  GtkFileFilter *file_filter = gtk_file_filter_new() ;

  gtk_file_filter_set_name(file_filter, "mk-project file (*.mkp)") ;

  gtk_file_filter_add_pattern(file_filter, "*.mkp" ) ;

  gtk_file_filter_add_pixbuf_formats(file_filter) ;

  gtk_file_chooser_set_show_hidden(GTK_FILE_CHOOSER(file_chooser), FALSE) ;

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser), g_get_home_dir()) ;

  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), file_filter) ;

  gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(file_chooser), file_filter) ;

  int ret = gtk_dialog_run(GTK_DIALOG(file_chooser)) ;

  gchar *filepath = NULL ;

  switch (ret) {

    case GTK_RESPONSE_ACCEPT :

      filepath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)) ;
      break ;

    default :
      gtk_widget_destroy(file_chooser) ;
      return ;


  }

  gtk_widget_destroy(file_chooser) ;


  load_project_callback(filepath) ;

  g_free(filepath) ;


  while (g_main_context_pending(NULL) ) {

    // Process pending events...

    g_main_context_iteration(NULL, FALSE) ;

  }

  return ;

}

static gchar *generate_target_folder(const gchar *new_folder, const gchar *filepath) {

  /** This function generate and return a new folder-path with ensuring that it does not exist for extracting purpose. **/

  gchar *dirname = g_path_get_dirname(filepath) ;

  gchar *new_folderpath = g_strconcat(dirname, "/", new_folder, NULL) ;

  int c = 1 ;

  while (g_file_test(new_folderpath, G_FILE_TEST_EXISTS)) {

    gchar *new_folderpath_cp = g_strdup(new_folderpath) ;

    gchar *tmp_folder_path = g_strdup_printf("%s-%d", new_folderpath_cp, c) ;

    free(new_folderpath_cp) ;

    free(new_folderpath) ;

    new_folderpath = g_strdup(tmp_folder_path) ;

    free(tmp_folder_path) ;

    ++c ;
  }

  return new_folderpath ;
}

static gchar *strip_archive_sufffix(gchar *archive_basename_without_extension, const gchar *pattern) {

  /** Strip any archive suffix and return the folder basename. **/

  gchar *new_folder_basename = g_strrstr(archive_basename_without_extension, pattern) ;

  size_t idx = strlen(pattern) ;

  while (idx) {

    new_folder_basename[strlen(new_folder_basename)-1] = '\0' ;

    --idx ;
  }

  return archive_basename_without_extension ;
}

static void move_archive_file(const gchar *archive_path, const gchar *dst_file) {

  GFile *g_file_archive = g_file_new_for_path(archive_path) ;

  GFile *g_file_dst = g_file_new_for_path(dst_file) ;

  GError *error = NULL ;

  g_file_copy(g_file_archive, g_file_dst, G_FILE_COPY_NONE | G_FILE_COPY_OVERWRITE, NULL, NULL, NULL, &error);

  if (error != NULL) {

    display_message_dialog( _("Error archive moving !"), error->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_error_free(error) ;

  }

  g_object_unref(g_file_archive) ;

  g_object_unref(g_file_dst) ;

  return ;

}

static gchar *extract_file(const gchar *filepath) {

  gchar *archive_basename_without_extension = g_path_get_basename(filepath) ;

  gchar *archive_basename_with_extension = g_strdup(archive_basename_without_extension) ;

  gchar *cmdline = NULL ;

  gchar *new_folder = NULL ;

  gchar *final_archive_path = NULL ;

  char *worker =  NULL ;

  char *compressor = NULL ;

  if (g_str_has_suffix(archive_basename_with_extension, ".tar") && (worker = have_app_application("tar")) != NULL) {

    gchar *new_folder_basename = strip_archive_sufffix(archive_basename_without_extension,".tar") ; // tar archive.

    new_folder = generate_target_folder(new_folder_basename, filepath) ;

    free(new_folder_basename) ;

    g_mkdir_with_parents(new_folder, 0755) ;

    final_archive_path = g_strdup_printf("%s/%s", new_folder, archive_basename_with_extension) ;

    move_archive_file(filepath, final_archive_path) ;

    cmdline = g_strdup_printf("%s -xf \"%s\"", worker, final_archive_path) ;
  }
  else if (g_str_has_suffix(archive_basename_with_extension, ".tar.gz") && (worker = have_app_application("tar")) != NULL && (compressor = have_app_application("gzip")) != NULL) { // gz compression

    gchar *new_folder_basename = strip_archive_sufffix(archive_basename_without_extension,".tar.gz") ;

    new_folder = generate_target_folder(new_folder_basename, filepath) ;

    free(new_folder_basename) ;

    g_mkdir_with_parents(new_folder, 0755) ;

    final_archive_path = g_strdup_printf("%s/%s", new_folder, archive_basename_with_extension) ;

    move_archive_file(filepath, final_archive_path) ;

    cmdline = g_strdup_printf("%s -xzf '%s'", worker, final_archive_path) ;

  }
  else if (g_str_has_suffix(archive_basename_with_extension, ".tar.bz2") && ((worker = have_app_application("tar")) != NULL) && ((compressor = have_app_application("gzip")) != NULL)) {

    gchar *new_folder_basename = strip_archive_sufffix(archive_basename_without_extension,".tar.bz2") ; // bz2 compression.

    new_folder = generate_target_folder(new_folder_basename, filepath) ;

    free(new_folder_basename) ;

    g_mkdir_with_parents(new_folder, 0755) ;

    final_archive_path = g_strdup_printf("%s/%s", new_folder, archive_basename_with_extension) ;

    move_archive_file(filepath, final_archive_path) ;

    cmdline = g_strdup_printf("%s -xjf '%s'", worker, final_archive_path) ;
  }
  else if (g_str_has_suffix(archive_basename_with_extension, ".tar.xz") && ((worker = have_app_application("tar")) != NULL) && ((compressor = have_app_application("xz")) != NULL)) {

    gchar *new_folder_basename = strip_archive_sufffix(archive_basename_without_extension,".tar.xz") ; // xz compression.

    new_folder = generate_target_folder(new_folder_basename, filepath) ;

    free(new_folder_basename) ;

    g_mkdir_with_parents(new_folder, 0755) ;

    final_archive_path = g_strdup_printf("%s/%s", new_folder, archive_basename_with_extension) ;

    move_archive_file(filepath, final_archive_path) ;

    cmdline = g_strdup_printf("%s -xJf '%s'", worker, final_archive_path) ;
  }
  else if (g_str_has_suffix(archive_basename_with_extension, ".tar.lz") && ((worker = have_app_application("tar")) != NULL) && ((compressor = have_app_application("lzip")) != NULL)) {  // lzip compression.

    gchar *new_folder_basename = strip_archive_sufffix(archive_basename_without_extension,".tar.lz") ;

    new_folder = generate_target_folder(new_folder_basename, filepath) ;

    free(new_folder_basename) ;

    g_mkdir_with_parents(new_folder, 0755) ;

    final_archive_path = g_strdup_printf("%s/%s", new_folder, archive_basename_with_extension) ;

    move_archive_file(filepath, final_archive_path) ;

    cmdline = g_strdup_printf("%s --lzip -xf '%s'", worker, final_archive_path) ;
  }
  else if (g_str_has_suffix(archive_basename_with_extension, ".tar.lzo") && ((worker = have_app_application("tar")) != NULL) && ((compressor = have_app_application("lzop")) != NULL)) {

    gchar *new_folder_basename = strip_archive_sufffix(archive_basename_without_extension,".tar.lzo") ; // lzop compression.

    new_folder = generate_target_folder(new_folder_basename, filepath) ;

    free(new_folder_basename) ;

    g_mkdir_with_parents(new_folder, 0755) ;

    final_archive_path = g_strdup_printf("%s/%s", new_folder, archive_basename_with_extension) ;

    move_archive_file(filepath, final_archive_path) ;

    cmdline = g_strdup_printf("%s --lzop -xf '%s'", worker, final_archive_path) ;
  }
  else if (g_str_has_suffix(archive_basename_with_extension, ".tar.lzma")  && ((worker = have_app_application("tar")) != NULL) && ((compressor = have_app_application("lzma")) != NULL)) {

    gchar *new_folder_basename = strip_archive_sufffix(archive_basename_without_extension,".tar.lzma") ; // lzma compression.

    new_folder = generate_target_folder(new_folder_basename, filepath) ;

    free(new_folder_basename) ;

    g_mkdir_with_parents(new_folder, 0755) ;

    final_archive_path = g_strdup_printf("%s/%s", new_folder, archive_basename_with_extension) ;

    move_archive_file(filepath, final_archive_path) ;

    cmdline = g_strdup_printf("%s --lzma -xf '%s'", worker, final_archive_path) ;

  }
  else if (g_str_has_suffix(archive_basename_with_extension, ".zip") && (worker = have_app_application("unzip")) != NULL) { // zip compression.

    gchar *new_folder_basename = strip_archive_sufffix(archive_basename_without_extension,".zip") ;

    new_folder = generate_target_folder(new_folder_basename, filepath) ;

    free(new_folder_basename) ;

    g_mkdir_with_parents(new_folder, 0755) ;

    final_archive_path = g_strdup_printf("%s/%s", new_folder, archive_basename_with_extension) ;

    move_archive_file(filepath, final_archive_path) ;

    cmdline = g_strdup_printf("%s -o -d '%s' '%s'",worker, new_folder, final_archive_path) ;

  }
  else if (g_str_has_suffix(archive_basename_with_extension, ".rar") && (worker = have_app_application("unrar")) != NULL) { // rar compression.

    gchar *new_folder_basename = strip_archive_sufffix(archive_basename_without_extension,".rar") ;

    new_folder = generate_target_folder(new_folder_basename, filepath) ;

    free(new_folder_basename) ;

    g_mkdir_with_parents(new_folder, 0755) ;

    final_archive_path = g_strdup_printf("%s/%s", new_folder, archive_basename_with_extension) ;

    cmdline = g_strdup_printf("%s '%s'", worker, final_archive_path) ;
  }

  g_chdir(new_folder) ;

  GError *error = NULL ;

  gint exit_status = -1 ;

  g_spawn_command_line_sync(cmdline, NULL, NULL, &exit_status, NULL) ;

  g_free(cmdline) ;

  g_spawn_check_exit_status(exit_status, &error);

  if (error != NULL) {

    display_message_dialog(_("Error extracting archive !"), error->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_error_free(error) ;

    return NULL ;

  }

  gchar *archive_rm_commandline = g_strdup_printf("rm %s", final_archive_path) ;

  int ret = system(archive_rm_commandline) ;

  if (ret != 0) {

    perror("Error removing archive: ") ;

  }

  g_free(archive_rm_commandline) ;

  if (! g_file_test(new_folder, G_FILE_TEST_IS_DIR)) {

    g_free(new_folder) ;

    gchar *new_folder_fallback = g_path_get_dirname(final_archive_path) ;

    return new_folder_fallback ;
  }

  return new_folder ;

}

gchar *find_mkp_file(const gchar *folderpath) {

  if (folderpath == NULL) {

    return NULL ;
  }

  GDir *dir = NULL ;

  GError *error = NULL ;

  dir = g_dir_open (folderpath, 0, &error) ;

  if (error != NULL) {

    display_message_dialog( _("Error open folder !"), error->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_clear_error(&error) ;
  }

  char *mkp_filepath = NULL ;

  gchar *mkp_file = NULL ;

  while ((mkp_file = (gchar *) g_dir_read_name(dir)) != NULL) {

    if (g_str_has_suffix(mkp_file, ".mkp")) {

      g_chdir(folderpath) ;

      mkp_filepath = realpath(mkp_file, NULL) ;

      break ;

    }
  }

  g_dir_close(dir) ;

  return mkp_filepath ;

}


void extract_and_load_project(GtkWidget *widget) {

  GtkWidget *file_chooser = gtk_file_chooser_dialog_new( _("Choose a mk-project file to load"), GTK_WINDOW(gui->window), GTK_FILE_CHOOSER_ACTION_OPEN, _("Extract and load"), GTK_RESPONSE_ACCEPT, _("Cancel"), GTK_RESPONSE_CANCEL, NULL);

  GtkFileFilter *file_filter = gtk_file_filter_new() ;

  gtk_file_filter_set_name(file_filter, "mk-project archive") ;

  gtk_file_filter_add_pattern(file_filter, "*.tar" ) ;
  gtk_file_filter_add_pattern(file_filter, "*.tar.gz" ) ;
  gtk_file_filter_add_pattern(file_filter, "*.tar.bz2" ) ;
  gtk_file_filter_add_pattern(file_filter, "*.tar.lzma" ) ;
  gtk_file_filter_add_pattern(file_filter, "*.tar.lzo" ) ;
  gtk_file_filter_add_pattern(file_filter, "*.tar.lp" ) ;
  gtk_file_filter_add_pattern(file_filter, "*.zip" ) ;
  gtk_file_filter_add_pattern(file_filter, "*.rar" ) ;

  gtk_file_filter_add_pixbuf_formats(file_filter) ;

  gtk_file_chooser_set_show_hidden(GTK_FILE_CHOOSER(file_chooser), FALSE) ;

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser), g_get_home_dir()) ;

  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), file_filter) ;

  gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(file_chooser), file_filter) ;

  int ret = gtk_dialog_run(GTK_DIALOG(file_chooser)) ;

  gchar *mkp_archive_path = NULL ;

  gchar *extracted_folderpath = NULL ;

  switch (ret) {

    case GTK_RESPONSE_ACCEPT :

      mkp_archive_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)) ;

      extracted_folderpath = extract_file(mkp_archive_path) ;

      free(mkp_archive_path) ;
   
      break ;

    default :
 
      gtk_widget_destroy(file_chooser) ;
 
      return ;

  }

  gtk_widget_destroy(file_chooser) ;

  gchar *filepath = find_mkp_file(extracted_folderpath) ;

  if (filepath == NULL) {

    display_message_dialog(_("Error no *.mkp file found !"), _("mk-project has not found an valid *.mkp file.\nSo mk-project cannot load the project."), GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    return ;

  }

  load_project_callback(filepath) ;

  g_free(filepath) ;


  while (g_main_context_pending(NULL) ) {

    // Process pending events...

    g_main_context_iteration(NULL, FALSE) ;

  }

  return ;

}


static void foreach_selected_file(gpointer data, bool *add_header) {

  /** For each selected file: **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif


  // Must set the header or __init__.py file too:
  bool add_header_file = *add_header ;


  // Check wether the file is in project folder and correct ./source folder.
  bool file_in_project_path = false ;
  bool file_into_source_folder = false ;


  if (! (file_in_project_path = is_in_project_path(project->project_folderpath, (const gchar *) data)) ) {

    /** File not in project folder. **/

    bool ret = display_message_dialog_question( _("File not in project folder !"), _("This will break the project tree structure and is not recommanded !\nAdd file to the project anyway ?") ) ;

    if (! ret) {

      return ;

    }

  }

  if (! (file_into_source_folder = is_folder_source((const gchar *) data) ) ) {

    /** "File not in ./source folder ! **/

    bool ret = display_message_dialog_question("File not in the (project) ./src folder !", "This will break the project tree structure and is not recommanded !\nAdd file to the project anyway ?") ;

    if (! ret) {

      return ;

    }

  }

  add_file_to_project_callback((const char*) data, add_header_file, file_in_project_path, file_into_source_folder) ;

  gchar *msg = g_strdup_printf( _("File:\n%s\nadded to project."), (const char*) data) ;

  display_message_dialog(_("file added to project"), msg, GTK_MESSAGE_INFO, GTK_BUTTONS_OK) ;

  g_free(msg) ;

  return ;

}

void add_file_to_project(GtkWidget *widget) {

  /** Add a file to project Makefile in the @SRC_FILES make variable. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *file_chooser = gtk_file_chooser_dialog_new( _("Choose a file to add to project"), GTK_WINDOW(gui->window), GTK_FILE_CHOOSER_ACTION_OPEN, _("Add file"), GTK_RESPONSE_ACCEPT, NULL);


  GtkFileFilter *file_filter = gtk_file_filter_new() ;

  gchar *file_filter_name = g_strdup_printf( _("Source files ( *%s )"), project->ext_src) ;

  gtk_file_filter_set_name(file_filter, file_filter_name) ;

  g_free(file_filter_name) ;


  gchar *file_filter_pattern = g_strdup_printf("*%s", project->ext_src) ;

  gtk_file_filter_add_pattern(file_filter, file_filter_pattern) ;


  g_free(file_filter_pattern) ;

  gtk_file_filter_add_pixbuf_formats(file_filter) ;

  gtk_file_chooser_set_show_hidden(GTK_FILE_CHOOSER(file_chooser), FALSE) ;

  if ( g_file_test(project->project_folderpath, G_FILE_TEST_IS_DIR) ) {

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser), project->project_folderpath ) ;
  }
  else {

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser),  g_get_home_dir()) ;
  }

  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), file_filter) ;

  gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(file_chooser), file_filter) ;

  gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(file_chooser), TRUE) ;

  GtkWidget *toggle = gtk_check_button_new_with_label(  _("Add the corresponding header file to Makefile too ?") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle), TRUE) ;

  gtk_widget_show(toggle) ;

  gtk_file_chooser_set_extra_widget(GTK_FILE_CHOOSER(file_chooser), toggle);

  int ret = gtk_dialog_run(GTK_DIALOG(file_chooser)) ;

  switch (ret) {

    case GTK_RESPONSE_ACCEPT : {

      GSList *selected_files = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(file_chooser)) ;

      bool *add_header = g_malloc(sizeof(bool)) ;

      *add_header = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle)) ;

      gtk_widget_destroy(file_chooser) ;

      g_slist_foreach(selected_files, (GFunc) &foreach_selected_file, add_header) ;

      g_slist_free(selected_files) ;

      free(add_header) ;

      gchar *makefile_path = g_strconcat(project->project_folderpath, "/", "Makefile", NULL) ;

      remove_trailing_space_from_file(makefile_path) ;

      g_free(makefile_path) ;

      break ;

    }

    default :
      gtk_widget_destroy(file_chooser) ;
      break ;

  }



  return ;

}

void switch_terminals(GtkWidget *widget, gint *page_num) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gtk_notebook_set_current_page(GTK_NOTEBOOK(gui->main_notebook), *page_num) ;

  #ifdef MAC_INTEGRATION // The library gtk-mac-integration-gtk3 define this.
  // @NOTE: the mac top application menu doesn't update correctly the menu radio buttons !
  //        I cant' use gtkosx_application_insert_app_menu_item(...) properly.
  //gtkosx_application_set_menu_bar(gtkosx_application_get(), GTK_MENU_SHELL(menu_bar)) ;
  gtkosx_application_sync_menubar(gtkosx_application_get());
  #endif

  return ;

}

void reconfiguring_project(GtkWidget *widget) {

  /** Reconfigure project menun item callback **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  #if (GTK_MINOR_VERSION < 22)
  gtk_menu_popup(GTK_MENU(gui->menu->make_menu), NULL, NULL, NULL, NULL, 0, gtk_get_current_event_time())  ;
  #else
  gtk_menu_popup_at_pointer(GTK_MENU(gui->menu->make_menu), NULL);
  #endif

  gtk_menu_popdown(GTK_MENU(gui->menu->make_menu)) ;

  cur_project->prgname = g_strdup(project->prgname) ;

  gchar *makefile_path = g_strconcat(project->project_folderpath, "/", "Makefile", NULL) ;

  gchar *makefile_code_fmt_path = g_strconcat(project->project_folderpath, "/", ".SubMakefiles", "/code_formatter.mk",  NULL) ;

  gchar *makefile_doc_path = g_strconcat(project->project_folderpath, "/", ".SubMakefiles", "/documentation.mk",  NULL) ;

  gchar *makefile_dist_path = g_strconcat(project->project_folderpath, "/", ".SubMakefiles", "/distributing.mk",  NULL) ;

  #ifdef THREADING
  /** @NOTE: the Makefile values parsing is not (I think) entirely thread-safe because of
             accessing the `same structure' different members into many threads.
  **/
  GThread *main_makefile_thread = g_thread_new("main_makefile", (GThreadFunc) &get_main_makefile_values, makefile_path) ;
  GThread *makefile_code_fmt_thread= g_thread_new("makefile_fmt_code", (GThreadFunc) &get_code_fmt_makefile_values, makefile_code_fmt_path) ;
  //GThread *makefile_doc_thread= g_thread_new("makefile_doc", (GThreadFunc) &get_doc_makefile_values, makefile_doc_path) ;
  GThread *makefile_dist_thread= g_thread_new("makefile_dist", (GThreadFunc) &get_dist_makefile_values, makefile_dist_path) ;

  g_thread_join(main_makefile_thread) ;
  g_thread_join(makefile_code_fmt_thread) ;
  g_thread_join(makefile_doc_thread) ;
  g_thread_join(makefile_dist_thread) ;
  #else
  get_main_makefile_values(makefile_path) ;
  get_code_fmt_makefile_values(makefile_code_fmt_path) ;
  //get_doc_makefile_values(makefile_doc_path) ;
  get_dist_makefile_values(makefile_dist_path) ;
  #endif


  gchar *xml_project_filepath = g_strconcat(project->project_folderpath, "/", cur_project->prgname, ".mkp", NULL) ;

  if (xml_project_filepath == NULL) {

    fprintf(stdout,"%s xml_project_filepath == NULL\n", __func__) ;

    exit(EXIT_FAILURE) ;

  }


  get_xml_data(xml_project_filepath, cur_project) ;

  // Copy informations from pointer to pointer ;

  SEC_FREE(project->ext_src)

  project->ext_src = g_strdup(cur_project->ext_src) ;

  SEC_FREE(project->ext_hdr)

  cur_project->ext_hdr = g_strdup(cur_project->ext_hdr) ;


  gchar *licensing_filepath = g_strconcat(project->project_folderpath, "/.licensing", "/licensing.tmpl", NULL) ;

  cur_project->licensing_boilerplate = get_file_content(licensing_filepath) ;

  gchar *desktop_filepath = g_strconcat(project->project_folderpath, "/desktop", "/", cur_project->prgname, ".desktop", NULL) ;



  cur_project->desktop_file_boilerplate = get_file_content(desktop_filepath) ;



  g_free(licensing_filepath) ;

  g_free(desktop_filepath) ;

  g_free(makefile_path) ;

  g_free(makefile_code_fmt_path) ;

  g_free(makefile_doc_path) ;

  g_free(makefile_dist_path) ;

  // Big call to reconfigure project.
  reconfigure_project() ;

  return ;

}


void display_about_dialog(GtkWidget *widget) {


  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif


  GtkWidget *about_dialog = gtk_about_dialog_new() ;

  gtk_window_set_transient_for(GTK_WINDOW(about_dialog), GTK_WINDOW(gui->window)) ;

  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), PRGNAME) ;

  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_dialog),      VERSION)   ;

  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog),    COPYRIGHT)   ;



  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog),   _("mk-project - a tool done to ease the development process\n"
                                                                    "and a good bridge for the distributing process.")) ;

  gchar *file_content ;

  g_file_get_contents(PATH_TO_LICENSE_TEXT, &file_content, NULL, NULL) ;

  gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(about_dialog), file_content) ;

  g_free(file_content) ;

  gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(about_dialog), TRUE);

  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog), PRGWEBURL) ;

  gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog), PRGNAME " Website") ;

  const gchar *author[2] = {AUTHOR " " MAIL, NULL} ;

  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), author);

  gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(about_dialog), author);

  gtk_about_dialog_set_artists(GTK_ABOUT_DIALOG(about_dialog), author);
 
  #if 0
  // Become one !!!
  gtk_about_dialog_set_translator_credits(GTK_ABOUT_DIALOG(about_dialog), AUTHOR " " MAIL);
  #endif
 
  gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog), NULL) ;

  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_dialog), NULL);

  const gchar *thanks[2] = {"Thanks to my beloved mother, my family and the doctors.", NULL} ;

  gtk_about_dialog_add_credit_section(GTK_ABOUT_DIALOG(about_dialog), "Thank's", thanks);

  const gchar *advice[2] = {"Stay away from drugs: drugs destroy your brain and your life.", NULL} ;

  gtk_about_dialog_add_credit_section(GTK_ABOUT_DIALOG(about_dialog), "Advice:", advice);

  gtk_dialog_run(GTK_DIALOG(about_dialog)) ;

  gtk_widget_destroy(about_dialog) ;

  return ;

}


void launch_readme_html(GtkWidget *widget) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GFile *g_file_readme = g_file_new_for_path(PATH_TO_HTML_NOTICE) ;

  GList *g_list = NULL ;

  g_list = g_list_append(g_list, g_file_readme) ;

  GAppInfo *g_app_info_html = g_app_info_get_default_for_type("text/html", TRUE);

  GError *error = NULL ;

  if (! g_app_info_launch(g_app_info_html, g_list, NULL, &error)) {

    if (error != NULL) {

      display_message_dialog( _("Error launch documentation file"), error->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

      g_error_free(error) ;

    }

  }

  g_object_unref(g_file_readme) ;

  g_list_free(g_list) ;

  return ;

}
