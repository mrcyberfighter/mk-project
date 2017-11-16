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

#include "./headers/includes.h"

#include "./headers/defines.h"

#include "./headers/structures/GUI_structures.h"

#include "./headers/structures/Settings_structure.h"

#include "./headers/structures/Project_structure.h"

#include "./global_vars.h"

#include "./GUI/setup_gui.h"

#include "./cmdline/cmdline.h"

#include "./terminals/terminals.h"

#include "./terminals/GtkMkTerm.h"

#include "./structures_initialize.h"

/** GtkApplication open callback function: for cmdline file(s) and/or folder opening. **/
static void open_files(GApplication  *application, GFile **files, gint n_files, const gchar *hint) ;

/** GtkApplication activate callback function. **/
static void activate(GApplication *application) ;

/** GtkApplication startup callback function. **/
static void startup(GApplication *application, gpointer user_data) ;

/** GtkApplication shutdown callback function. **/
static void shutdown_app(GApplication *application, gpointer user_data) ;

#ifdef G_OS_UNIX

/** GtkApplication (application menu) open file callback function. **/
static void new_project_activated(GSimpleAction *action, GVariant *parameter, gpointer app) ;

/** GtkApplication (application menu) preferences callback function. **/
static void preferences_activated(GSimpleAction *action, GVariant *parameter, gpointer app) ;

/** GtkApplication (application menu) preferences callback function. **/
static void load_project_activated(GSimpleAction *action, GVariant *parameter, gpointer app) ;

/** GtkApplication (application menu) About callback function. **/
static void about_activated(GSimpleAction *action, GVariant *parameter, gpointer app) ;

/** GtkApplication (application menu) quit callback function. **/
static void quit_activated(GSimpleAction *action, GVariant *parameter, gpointer app) ;
#endif

static void destroy(GtkWidget *widget, GtkApplication *app) ;
static gboolean delete_event(GtkWidget *widget, GdkEvent *event) ;

static GError *errors = NULL ;

#ifdef MAC_INTEGRATION
static int attention = -1 ;
#endif



int main(int argc, char *argv[]) {




  #ifdef GETTEXT_SUPPORT

  /** No translation files available (*.mo) but the calls are done to make
    * sure the program is in english independently from the localisation !!!
    *
    * @NOTE: the macro _("") is used in this program so that the translation
    *        can be done by someone which get interest into it.
    *    
    ************************************************************************/

  setlocale(LC_ALL, "");

  bindtextdomain(PACKAGE, LOCALEDIR) ;
  bind_textdomain_codeset(PACKAGE, "UTF-8") ;
  textdomain(PACKAGE) ;

  #ifdef DEBUG
  fprintf(stdout,"PACKAGE: %s\n",   PACKAGE)    ;
  fprintf(stdout,"LOCALEDIR: %s\n", LOCALEDIR)  ;
  #endif

  #endif

  /** GUI structure initialization. **/
  GUI    pgui     ;
  gui = &pgui     ;           



  g_set_application_name(PRGNAME) ;

  fprintf(stderr,"App: %s launched\n",g_get_application_name()) ;

  const char *app_id = "mk.project.mrcyberfighter" ; /** @Hint: For using Gtk notification you will have create a *.desktop file named has the id (prgname.org in this case) and getting a dbus connection. ; **/

  if ( ! g_application_id_is_valid(app_id) ) {

    fprintf(stderr, "Wrong app id\n") ;
    exit(EXIT_FAILURE) ;

  }



  int app_flags = G_APPLICATION_NON_UNIQUE | G_APPLICATION_SEND_ENVIRONMENT | G_APPLICATION_HANDLES_OPEN ;

  gui->app = gtk_application_new(app_id, app_flags) ;

  bool registered = g_application_register(G_APPLICATION(gui->app), NULL, &errors) ;

  if (errors != NULL || (! registered)) {

    fprintf(stderr,"Cannot register app: %s\n", errors->message) ;

    g_clear_error(&errors) ;

    exit(EXIT_FAILURE) ;

  }

  #ifdef MAC_INTEGRATION
  gtkosx_application_ready(gtkosx_application_get()) ;
  gtkosx_application_set_use_quartz_accelerators(gtkosx_application_get(), TRUE) ;
  
  #ifdef DEBUG
  fprintf(stdout,"Mac app use quartz accels: %d\n", gtkosx_application_use_quartz_accelerators(osx_application)) ;
  #endif
  g_set_prgname("gfast-copy") ; // Don't automatically set from the GtkApplication system like on Linux.

  //gtkosx_application_attention_request(gtkosx_application_get(), INFO_REQUEST);
  gtkosx_application_attention_request(gtkosx_application_get(), CRITICAL_REQUEST);


  #endif

  #ifdef G_OS_UNIX

  if (gtk_application_prefers_app_menu(gui->app)) {

    g_signal_connect( G_APPLICATION(gui->app),  "activate",              G_CALLBACK(activate),       NULL) ;
    g_signal_connect( G_APPLICATION(gui->app),  "open",                  G_CALLBACK(open_files),     NULL) ;
    g_signal_connect( G_APPLICATION(gui->app),  "startup",               G_CALLBACK(startup),        NULL) ;
    g_signal_connect( G_APPLICATION(gui->app),  "shutdown",              G_CALLBACK(shutdown_app),   NULL) ;

    GtkBuilder *builder = NULL  ;
    GMenuModel *app_menu = NULL ;

    static GActionEntry app_entries[5] = {

      { "newproject",   new_project_activated,    NULL, NULL, NULL },
      { "loadproject",  load_project_activated,   NULL, NULL, NULL },
      { "preferences",  preferences_activated,    NULL, NULL, NULL },
      { "about",        about_activated,          NULL, NULL, NULL },
      { "quit",         quit_activated,           NULL, NULL, NULL }

    };

    g_action_map_add_action_entries(G_ACTION_MAP(gui->app), app_entries, G_N_ELEMENTS(app_entries), gui->app);

    builder = gtk_builder_new_from_string("<?xml version=\"1.0\"?>"
                                            "<interface>"
                                              "<menu id=\"appmenu\">"
                                                "<section>"
                                                  "<item>"
                                                    "<attribute name=\"label\" translatable=\"no\">New project</attribute>"
                                                    "<attribute name=\"action\">app.newproject</attribute>"
                                                  "</item>"
                                               "</section>"
                                               "<section>"
                                                  "<item>"
                                                    "<attribute name=\"label\" translatable=\"no\">Load project</attribute>"
                                                    "<attribute name=\"action\">app.loadproject</attribute>"
                                                  "</item>"
                                                "</section>"
                                               "<section>"
                                                  "<item>"
                                                    "<attribute name=\"label\" translatable=\"no\">Preferences</attribute>"
                                                    "<attribute name=\"action\">app.preferences</attribute>"
                                                  "</item>"
                                                "</section>"
                                                "<section>"
                                                  "<item>"
                                                    "<attribute name=\"label\" translatable=\"no\">About</attribute>"
                                                    "<attribute name=\"action\">app.about</attribute>"
                                                  "</item>"
                                                "</section>"
                                                "<section>"
                                                  "<item>"
                                                    "<attribute name=\"label\" translatable=\"no\">Quit</attribute>"
                                                    "<attribute name=\"action\">app.quit</attribute>"
                                                 "</item>"
                                               "</section>"
                                              "</menu>"
                                            "</interface>",

                                            -1) ;

    app_menu = G_MENU_MODEL(gtk_builder_get_object(builder, "appmenu"));

    gtk_application_set_app_menu(GTK_APPLICATION(gui->app), app_menu);

    g_object_unref(builder) ;

  }

  #endif

  gui->window = gtk_application_window_new(gui->app)  ;


  GdkPixbuf *window_pixbuf = gdk_pixbuf_new_from_file(PATH_TO_ICON, NULL) ;

  gtk_window_set_icon(GTK_WINDOW(gui->window), window_pixbuf) ;

  #ifdef MAC_INTEGRATION
  gtkosx_application_set_dock_icon_pixbuf(gtkosx_application_get(), window_pixbuf) ;
  #endif

  g_object_unref(window_pixbuf) ;
 
  #if 0
  /** Setting theme to dark if Adwaita present. **/
 
  GtkSettings *gtk_settings_for_screen = gtk_settings_get_for_screen(gtk_window_get_screen(GTK_WINDOW(gui->window))) ;

  g_object_set(G_OBJECT(gtk_settings_for_screen), "gtk-cursor-theme-name", "default", NULL) ;

  GtkCssProvider *provider = NULL ;

  char *theme_name = NULL ;

  g_object_get(G_OBJECT(gtk_settings_for_screen), "gtk-theme-name", &theme_name, NULL) ;

  g_object_unref(gtk_settings_for_screen) ;

  if (theme_name != NULL) {

    provider = gtk_css_provider_get_named(theme_name, "dark") ;

  }
  else {

    provider = gtk_css_provider_get_default() ;

  }

  g_free(theme_name) ;

  if (provider != NULL) {

    GdkDisplay *display = gdk_display_get_default() ;

    GdkScreen *screen = gdk_display_get_default_screen(display) ;

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION) ;

    g_object_unref(provider);

  }
 
  /** ***** End of dark theming (I feel light theme better but it up to the taste of the user) ***** **/
  #endif
 
  cur_project = g_malloc0(sizeof(Project)) ;
  project = g_malloc0(sizeof(Project)) ;

  // Project structures initialization
  set_default_terminal_settings() ;
  init_project_settings() ;
  init_cur_project_settings() ;



  gtk_window_set_default_icon_from_file(PATH_TO_ICON, NULL) ;
  gtk_window_set_resizable(GTK_WINDOW(gui->window),   TRUE) ;
  gtk_window_set_title(GTK_WINDOW(gui->window),       PRGNAME) ;
  gtk_window_set_position(GTK_WINDOW(gui->window),    GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_set_default_icon_from_file(PATH_TO_ICON, NULL) ;

  /** Main GUI container containing all the widgets. **/
  gui->main_vbox   = gtk_box_new(GTK_ORIENTATION_VERTICAL,   0) ;


  /** Menu: **/
  gui->menu = g_malloc(sizeof(Menu)) ;

  gui->menu->menu_accel_group    = gtk_accel_group_new() ;

  initialize_menu(gui->menu) ;

  gtk_window_add_accel_group(GTK_WINDOW(gui->window), gui->menu->menu_accel_group)   ;


  gui->make_notebook_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gui->make_notebook_status_bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;


  GtkWidget *make_terminal_displaying_label = gtk_label_new("") ;

  gtk_label_set_markup(GTK_LABEL(make_terminal_displaying_label),"<big><b>make terminal</b></big>") ;

  //gtk_label_set_ellipsize(GTK_LABEL(make_terminal_displaying_label), PANGO_ELLIPSIZE_START | PANGO_ELLIPSIZE_END) ;

  gtk_widget_set_size_request(make_terminal_displaying_label, -1, 38) ;

  gtk_box_pack_start(GTK_BOX(gui->make_notebook_status_bar), gtk_label_new(""),               TRUE, TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(gui->make_notebook_status_bar), make_terminal_displaying_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->make_notebook_status_bar), gtk_label_new(""),               TRUE, TRUE,   0) ;


  gui->main_notebook = gtk_notebook_new() ;

  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(gui->main_notebook), FALSE) ;
  gtk_notebook_set_show_border(GTK_NOTEBOOK(gui->main_notebook), FALSE) ;




  gui->make_notebook = gtk_notebook_new() ;

  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(gui->make_notebook), FALSE) ;
  gtk_notebook_set_show_border(GTK_NOTEBOOK(gui->make_notebook), FALSE) ;

  gui->make_terminal = gtk_mkterm_new(TRUE, FALSE) ;

  gtk_notebook_append_page(GTK_NOTEBOOK(gui->make_notebook), gui->make_terminal, NULL) ;

  gtk_box_pack_start(GTK_BOX(gui->make_notebook_vbox), gui->make_notebook_status_bar, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->make_notebook_vbox), gui->make_notebook,            TRUE, TRUE, 0) ;




  /** Hard GUI coded terminals notebook container: **/
  gui->terminal_notebook = gtk_notebook_new() ;

  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(gui->terminal_notebook), TRUE) ;
  gtk_notebook_set_tab_pos(GTK_NOTEBOOK(gui->terminal_notebook), GTK_POS_TOP) ;
  gtk_notebook_set_show_border(GTK_NOTEBOOK(gui->terminal_notebook), TRUE);
  gtk_notebook_set_scrollable(GTK_NOTEBOOK(gui->terminal_notebook),  TRUE);
  gtk_notebook_popup_enable(GTK_NOTEBOOK(gui->terminal_notebook));

  set_new_terminals(gui->terminal_notebook) ;

  gtk_notebook_append_page(GTK_NOTEBOOK(gui->main_notebook), gui->make_notebook_vbox, NULL) ;

  gtk_notebook_append_page(GTK_NOTEBOOK(gui->main_notebook), gui->terminal_notebook,  NULL) ;

  gtk_widget_set_size_request(gui->terminal_notebook,  ((80 * 8) + 24), 24 * 16) ;

  gtk_notebook_set_current_page(GTK_NOTEBOOK(gui->main_notebook), 1) ;

  gtk_box_pack_start(GTK_BOX(gui->main_vbox), gui->menu->menu_bar,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->main_vbox), gui->main_notebook,   TRUE,  TRUE,  0) ;


  g_signal_connect(G_OBJECT(gui->window), "delete-event", G_CALLBACK(delete_event), NULL) ;
  g_signal_connect(G_OBJECT(gui->window), "destroy",      G_CALLBACK(destroy),      gui->app) ;


  gtk_container_add(GTK_CONTAINER(gui->window), gui->main_vbox) ;

  gtk_widget_show_all(GTK_WIDGET(gui->window)) ;

  gtk_notebook_set_current_page(GTK_NOTEBOOK(gui->main_notebook), 0) ;

  #ifdef MAC_INTEGRATION // The library gtk-mac-integration-gtk3 define this.
  // @NOTE: the mac top application menu doesn't update correctly the menu radio buttons !
  //        I cant' use gtkosx_application_insert_app_menu_item(...) properly.
  gtkosx_application_set_menu_bar(gtkosx_application_get(), GTK_MENU_SHELL(gui->menu->menu_bar)) ;
  gtkosx_application_sync_menubar(gtkosx_application_get());
  #endif

  int status = 1 ;

  status = g_application_run(G_APPLICATION(gui->app),argc, argv);

  return status ;

}



static void activate(GApplication *application) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif



  /** This signal is receive by calling: g_application_run() function,
    *
    * so the just by starting the application to run by calling the g_application_activate() function.
    *
  **/

  GAppInfo *default_app = g_app_info_get_default_for_type("application/x-extension-mkp", FALSE) ;

  if (! G_IS_APP_INFO(default_app))      {

    /** Setting mk-project as default applicationation for *.mkp files **/

    GAppInfo *mk_project_app = g_app_info_create_from_commandline(PATH_TO_MK_PROJECT, NULL, G_APP_INFO_CREATE_NONE, &errors) ;

    if (errors != NULL) {
    
      g_printerr("%s",errors->message) ;
    
      g_clear_error(&errors) ;

      g_object_unref(default_app) ;

      return ;

    }

    g_app_info_set_as_default_for_extension(mk_project_app, "mkp", &errors) ;

    if (errors != NULL) {
    
      g_printerr("%s",errors->message) ;
    
      g_clear_error(&errors) ;

      g_object_unref(default_app) ;
      g_object_unref(mk_project_app) ;

      return ;
    }
  
    g_app_info_set_as_default_for_type(mk_project_app, "application/x-extension-mkp", &errors) ;

    if (errors != NULL) {
    
      g_printerr("%s",errors->message) ;
    
      g_clear_error(&errors) ;

      g_object_unref(default_app) ;
      g_object_unref(mk_project_app) ;

      return ;
    }


    g_app_info_add_supports_type(mk_project_app, "application/x-extension-mkp", &errors);

    if (errors != NULL) {

      fprintf(stderr,"%s\n", errors->message) ;

      g_clear_error(&errors) ;

      g_object_unref(default_app) ;
      g_object_unref(mk_project_app) ;

      return ;
    }

    #ifdef DEBUG
    fprintf(stdout,"%s set as default app for extension: *.mkp\n", g_app_info_get_executable(mk_project_app)) ;
  
    GAppInfo *app_info_default_for_mkp = g_app_info_get_default_for_type("application/x-extension-mkp", TRUE) ;
  
    fprintf(stderr,"default for *.mkp  files: %s\n", g_app_info_get_executable(app_info_default_for_mkp)) ;
  
    #endif
  
  
  
    g_object_unref(default_app) ;
    g_object_unref(mk_project_app) ;

  }
  else {

    #ifdef DEBUG
    fprintf(stdout,"default app for *.mkp file's: %s\n", g_app_info_get_name(default_app)) ;
    #endif

    g_object_unref(default_app) ;

  }

  return ;

  #ifdef G_OS_UNIX
  GDBusConnection *dbus_connection = g_application_get_dbus_connection(G_APPLICATION(gui->app)) ;

  if (dbus_connection != NULL && G_IS_DBUS_CONNECTION(dbus_connection) ) {

    g_dbus_connection_start_message_processing(dbus_connection) ;

  }

  /** Send a notification at startup and at exit. **/

  g_application_set_default(G_APPLICATION(gui->app)) ;

  /** 15 seconds before it-edit becomes idle. **/
  g_application_set_inactivity_timeout(G_APPLICATION(gui->app), 15000) ;



  #ifdef DEBUG
  fprintf(stdout,"GtkApplication DBUS path: %s\n", g_application_get_dbus_object_path(G_APPLICATION(gui->app)) ) ;
  #endif

  #endif

  return ;

}

static void open_files(GApplication  *application, GFile **files, gint n_files, const gchar *hint) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  /** GtkApplication command line open folder or files argument treatment function:
    * This will permit the g_win32_get_command_line() function to be automatically called internally.
    * And many others things.
    *************************************************************************************************/

  if (n_files > 0) {

    gchar *argument_file = g_file_get_path(files[0]) ;

    if (! check_load_project_cmdline(argument_file)) {

      gchar *help_text = g_strdup_printf(  _("\n"
                                         "usage : %s filepath.mkp"
                                         "\n"
                                         "\n"
                                         "\t""mk-project a development project manager ;"
                                         "\n"
                                         "\n"
                                         "\t""Look at `$ man mk-project' for further informations."
                                         "\n"
                                         "\t""The full documentation is available as info file."
                                         "\n\n"
                                         "\t""License GPLv3 Copyright (c) 2016 Brüggemann Eddie."
                                         "\n\n"), g_get_application_name()) ;

      fprintf(stderr, "%s", help_text) ;
      g_free(help_text)   ;
      g_free(argument_file) ;
      exit(EXIT_FAILURE)  ;

    }

    load_project_callback(argument_file) ;
    g_free(argument_file) ;



  }

  return ;

}

static void startup(GApplication *application, gpointer user_data) {

  while ( ! g_application_get_is_registered(application) ) {

    while (g_main_context_pending(NULL)) {

      g_main_context_iteration(NULL, FALSE) ;

    }
  }

  return ;
}

#ifdef G_OS_UNIX

static void new_project_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  GtkWindow *window = gtk_application_get_active_window(app) ;

  gtk_widget_set_name(GTK_WIDGET(window), "raw") ;

  new_project(GTK_WIDGET(window)) ;

  return ;

}

static void load_project_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  load_project(NULL) ;

  return ;

}

static void preferences_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  display_configuration_dialog(NULL, NULL) ;

  return ;

}

static void about_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  display_about_dialog(NULL) ;

  return ;

}

static void quit_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  destroy(NULL, gui->app) ;

  return ;

}
#endif

static void shutdown_app(GApplication *application, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

}


static void destroy(GtkWidget *widget, GtkApplication *app) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  /** Upon return to the mainloop, g_application_run() will return, calling only the 'shutdown' function before doing so. **/
  g_application_quit(G_APPLICATION(app)) ;

  exit(EXIT_SUCCESS) ;

}



static gboolean delete_event(GtkWidget *widget,GdkEvent *event) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  return FALSE ;
}

