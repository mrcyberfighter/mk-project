#include "./reconf_project.h"

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

GtkWidget *reconfigure_project_assistant = NULL ;

static void cancel_event(GtkAssistant *assistant, gpointer pointer) ;


/** GUI generating functions. **/

static void configure_compiler_project(void) ;

static void configure_disassembling_options(void) ;

static void configure_oprofile_options(void) ;

static void configure_valgrind_options(void) ;

static void configure_code_c_fmt_project(void) ;

static void configure_others_info_project(void) ;

static void configure_licensing_project(void)  ;

static void configure_desktop_file_project(void) ;


/** Compiler check **/

static gboolean is_compiler_focus_out(GtkWidget *widget, GdkEvent  *event, gpointer   user_data) ;

static bool check_compiler(const char *compiler) ;


/** Summary of project  **/

static void summary_of_project(void) ;



/** On cancel page **/
static void cancel_event(GtkAssistant *assistant, gpointer pointer) ;


/** On prepare page: before the page is shown **/

static void on_prepare_page(GtkAssistant *assistant, GtkWidget *page, gpointer user_data) ;

/** On apply page: When the user press the Next button. **/

static void on_apply_page(GtkAssistant *assistant, gpointer user_data) ;

/** On close: When finished configurating project. **/

static void on_close_project(GtkAssistant *assistant, gpointer user_data) ;



/** Updating functions **/

static void update_summary(GList *content) ;


void reconfigure_project(void) {

  reconfigure_project_assistant = gtk_assistant_new() ;



  GtkWidget *mk_project_presentation_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  #ifdef USE_IMG
  GtkWidget *mk_project_presentation_image = gtk_image_new_from_file(PATH_TO_ICON) ;
  #endif


  GtkWidget *mk_project_presentation_label = gtk_label_new("") ;




  gtk_label_set_markup(GTK_LABEL(mk_project_presentation_label), _("You can reconfigure your project here.\n"
                                                                   "By setting or changing most of the options from the project.\n"
                                                                   "You can reconfigure your project as many times as you want.\n"
                                                                   "Through using this interface.") )  ;


  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(mk_project_presentation_hbox), mk_project_presentation_image, FALSE, FALSE, MARGING) ;
  #endif
  gtk_box_pack_start(GTK_BOX(mk_project_presentation_hbox), mk_project_presentation_label, TRUE,  TRUE,  MARGING) ;

  gtk_assistant_append_page(GTK_ASSISTANT(reconfigure_project_assistant), mk_project_presentation_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(reconfigure_project_assistant), mk_project_presentation_hbox, GTK_ASSISTANT_PAGE_INTRO) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(reconfigure_project_assistant), mk_project_presentation_hbox, _("Reconfigure project")) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(reconfigure_project_assistant), mk_project_presentation_hbox, TRUE);




  configure_compiler_project() ;

  configure_disassembling_options() ;

  configure_oprofile_options() ;

  configure_valgrind_options() ;

  configure_code_c_fmt_project() ;


  configure_others_info_project() ;

  configure_licensing_project() ;


  configure_desktop_file_project() ;

  summary_of_project() ;

  gtk_window_set_resizable(GTK_WINDOW(reconfigure_project_assistant),  FALSE) ;
  gtk_window_set_position(GTK_WINDOW(reconfigure_project_assistant), GTK_WIN_POS_CENTER_ALWAYS);

  g_signal_connect_after(G_OBJECT(reconfigure_project_assistant), "cancel",  G_CALLBACK(cancel_event), NULL) ;
  g_signal_connect_after(G_OBJECT(reconfigure_project_assistant), "prepare", G_CALLBACK(on_prepare_page), NULL) ;
  g_signal_connect_after(G_OBJECT(reconfigure_project_assistant), "apply",   G_CALLBACK(on_apply_page), NULL) ;
  g_signal_connect_after(G_OBJECT(reconfigure_project_assistant), "close",   G_CALLBACK(on_close_project), NULL) ;


  gtk_widget_show_all(reconfigure_project_assistant) ;

  while ( g_main_context_pending(NULL)) {

    // Process pending events...

    g_main_context_iteration(NULL, FALSE) ;

  }

  return ;
}

static void configure_compiler_project(void) {


  #ifdef USE_IMG
  GtkWidget *configure_c_project_image = gtk_image_new_from_file(PATH_TO_ICON) ;
  #endif


  GtkWidget *configure_c_project_compiler_label = gtk_label_new( _("Compiler") ) ;

  GtkWidget *configure_c_project_compiler_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_c_project_compiler_entry, "compiler_entry") ;

  gtk_entry_set_text(GTK_ENTRY(configure_c_project_compiler_entry), "cc") ;

  gtk_widget_set_tooltip_text(configure_c_project_compiler_entry, _("cc is your default C compiler")) ;


  if (cur_project->compiler != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_c_project_compiler_entry), cur_project->compiler) ;
  }

  GtkWidget *configure_c_project_compiler_button = gtk_button_new() ;

  gtk_button_set_relief(GTK_BUTTON(configure_c_project_compiler_button), GTK_RELIEF_NONE) ;



  g_signal_connect(G_OBJECT(configure_c_project_compiler_entry), "realize", G_CALLBACK(on_realize_widget), NULL) ;

  g_signal_connect_after(G_OBJECT(configure_c_project_compiler_entry), "focus-out-event", G_CALLBACK(is_compiler_focus_out), NULL) ;


  GtkWidget *configure_c_project_warns_label = gtk_label_new("Warnings") ;

  GtkWidget *configure_c_project_warns_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_c_project_warns_entry, "warnings") ;


  if (cur_project->warnings != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_c_project_warns_entry), cur_project->warnings) ;
  }

  GtkWidget *configure_c_project_warns_button = create_button(PATH_TO_BUTTON_ICON "/flag-red.png", _("Set the commons project WARNINGS !\nYou can set the warnings you want by editing the entry widget by hand.")) ;

  g_signal_connect(G_OBJECT(configure_c_project_warns_button), "clicked", G_CALLBACK(select_warnings), configure_c_project_warns_entry) ;




  GtkWidget *configure_c_project_cflags_label = gtk_label_new("CFLAGS") ;

  GtkWidget *configure_c_project_cflags_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_c_project_cflags_entry, "cflags") ;

  gtk_widget_set_tooltip_text(configure_c_project_cflags_entry, _("Set the compiler options.")  ) ;

  if (cur_project->cflags != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_c_project_cflags_entry), cur_project->cflags) ;
  }

  gtk_widget_set_size_request(configure_c_project_warns_entry, COMPILER_ENTRY_SIZE, -1)  ;

  gtk_widget_set_can_default(configure_c_project_warns_entry, TRUE) ;

  if (gtk_widget_get_can_default(configure_c_project_warns_entry) ) {

    gtk_widget_set_receives_default(configure_c_project_warns_entry, TRUE) ;

  }

  gtk_widget_set_name(configure_c_project_warns_entry, "warnings") ;

  GtkWidget *configure_c_project_cflags_button = create_button(PATH_TO_BUTTON_ICON "/flag-blue.png", _("Set the commons project FLAGS (CFLAGS or CXXFLAGS) !\nYou can set the flags you want by editing the entry by hand.")) ;

  g_signal_connect(G_OBJECT(configure_c_project_cflags_button), "clicked", G_CALLBACK(select_flags), configure_c_project_cflags_entry) ;






  GtkWidget *configure_c_project_cppflags_label = gtk_label_new("CPPFLAGS") ;

  GtkWidget *configure_c_project_cppflags_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_c_project_cppflags_entry, "cppflags") ;

  gtk_widget_set_tooltip_text(configure_c_project_cppflags_entry, _("Per example: -DPREFIX=\"/usr/local\"")  ) ;


  if (cur_project->cppflags != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_c_project_cppflags_entry), cur_project->cppflags) ;
  }

  GtkWidget *configure_c_project_cppflags_button = create_button(PATH_TO_BUTTON_ICON "/flag-black.png", _("Set the commons project preprocessor definitions (CPPFLAGS) !\nYou can set the flags you want by editing the entry by hand.")) ;

  g_signal_connect(G_OBJECT(configure_c_project_cppflags_button), "clicked",  G_CALLBACK(add_cppflags), configure_c_project_cppflags_entry) ;



  GtkWidget *configure_c_project_ldflags_label = gtk_label_new("LDFLAGS") ;

  GtkWidget *configure_c_project_ldflags_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_c_project_ldflags_entry, "ldflags") ;

  gtk_widget_set_tooltip_text(configure_c_project_ldflags_entry, _("Per example: `pkg-config --cflags gtk+-3.0`\n\nWith pkg-config use the backticks syntax !") ) ;


  if (cur_project->ldflags != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_c_project_ldflags_entry), cur_project->ldflags) ;
  }

  GtkWidget *configure_c_project_ldflags_button = create_button(PATH_TO_BUTTON_ICON "/flag-green.png", _("Choose the \"pkg-config\" (*.pc) to add to your project !\nElse you can set what ever you want by editing the entry by hand.")) ;



  GtkWidget *configure_c_project_ldlibs_label = gtk_label_new("LDLIBS") ;

  GtkWidget *configure_c_project_ldlibs_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_c_project_ldlibs_entry, "ldlibs") ;

  gtk_widget_set_tooltip_text(configure_c_project_ldlibs_entry, _("Per example: `pkg-config --libs gtk+-3.0` -lvte2_90 -lm  \n\nWith pkg-config use the backticks syntax !") ) ;


  if (cur_project->ldlibs != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_c_project_ldlibs_entry), cur_project->ldlibs) ;
  }

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
  gtk_box_pack_start(GTK_BOX(configure_c_project_hbox), configure_c_project_image, FALSE, FALSE, MARGING) ;
  #endif

  gtk_widget_set_name(configure_c_project_data_vbox, "compiler_settings_container") ;

  gtk_box_pack_start(GTK_BOX(configure_c_project_hbox), configure_c_project_label_vbox,    FALSE, FALSE, MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_hbox), configure_c_project_data_vbox,     TRUE,  TRUE,  MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_c_project_hbox), configure_c_project_buttons_vbox,  TRUE, TRUE,  MARGING) ;

  gtk_widget_show_all(configure_c_project_hbox) ;

  gtk_assistant_append_page(GTK_ASSISTANT(reconfigure_project_assistant), configure_c_project_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(reconfigure_project_assistant), configure_c_project_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(reconfigure_project_assistant), configure_c_project_hbox, _("Compiler settings") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(reconfigure_project_assistant), configure_c_project_hbox, TRUE) ;

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

  gtk_widget_set_name(configure_disassembling_nm_opts_entry, "nm_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_nm_opts_label, _("nm: display symbols of object file(s) or a program.\nHere it takes all object files as argument.\n\nLook at $ nm -h or $ man nm") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_nm_opts_entry, _("nm: display symbols of object file(s) or a program.\nHere it takes all object files as argument.\n\nLook at $ nm -h or $ man nm") ) ;


  if (cur_project->nm_options != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_disassembling_nm_opts_entry), cur_project->nm_options) ;
  }



  GtkWidget *configure_disassembling_strace_opts_label = gtk_label_new("strace options") ;

  GtkWidget *configure_disassembling_strace_opts_entry  = gtk_entry_new() ;

  gtk_widget_set_name(configure_disassembling_strace_opts_entry, "strace_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_strace_opts_label, _("strace: intercepts and records the system calls which are called by a\nprocess and the signals which are received by a process.\n\nLook at $ strace -h or $ man strace") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_strace_opts_entry, _("strace: intercepts and records the system calls which are called by a\nprocess and the signals which are received by a process.\n\nLook at $ strace -h or $ man strace") ) ;


  if (cur_project->strace_options != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_disassembling_strace_opts_entry), cur_project->strace_options) ;
  }


  GtkWidget *configure_disassembling_ltrace_opts_label = gtk_label_new("ltrace options") ;

  GtkWidget *configure_disassembling_ltrace_opts_entry  = gtk_entry_new() ;

  gtk_widget_set_name(configure_disassembling_ltrace_opts_entry, "ltrace_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_ltrace_opts_label, _("ltrace: trace library calls of a given program.\n\nLook at $ ltrace -h or $ man ltrace") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_ltrace_opts_entry, _("ltrace: trace library calls of a given program.\n\nLook at $ ltrace -h or $ man ltrace") ) ;


  if (cur_project->ltrace_options != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_disassembling_ltrace_opts_entry), cur_project->ltrace_options) ;
  }


  GtkWidget *configure_disassembling_objdump_opts_label = gtk_label_new("objdump options") ;

  GtkWidget *configure_disassembling_objdump_opts_entry  = gtk_entry_new() ;

  gtk_widget_set_name(configure_disassembling_objdump_opts_entry, "objdump_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_objdump_opts_label, _("objdump: Display the informations about the object file(s) or a binary.\n\nLook at $ objdump -h or $ man objdump") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_objdump_opts_entry, _("objdump: Display the informations about the object file(s) or a binary.\n\nLook at $ objdump -h or $ man objdump") ) ;


  if (cur_project->objdump_options != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_disassembling_objdump_opts_entry), cur_project->objdump_options) ;
  }



  GtkWidget *configure_disassembling_ldd_opts_label = gtk_label_new("ldd options") ;

  GtkWidget *configure_disassembling_ldd_opts_entry  = gtk_entry_new() ;

  gtk_widget_set_name(configure_disassembling_ldd_opts_entry, "ldd_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_ldd_opts_label, _("ldd: ldd  print the  shared  libraries  required by each program or\nshared library specified on the command line.\n\nLook at $ ldd -h or $ man ldd") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_ldd_opts_entry, _("ldd: ldd  print the  shared  libraries  required by each program or\nshared library specified on the command line.\n\nLook at $ ldd -h or $ man ldd") ) ;


  if (cur_project->ldd_options != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_disassembling_ldd_opts_entry), cur_project->ldd_options) ;
  }


  GtkWidget *configure_disassembling_gprof_opts_label = gtk_label_new("gprof options") ;

  GtkWidget *configure_disassembling_gprof_opts_entry  = gtk_entry_new() ;

  gtk_widget_set_name(configure_disassembling_gprof_opts_entry, "gprof_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_gprof_opts_label, _("gprof: a profiling tool shipped with gcc.\n\nLook at $ gprof -h or $ man gprof") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_gprof_opts_entry, _("gprof: a profiling tool shipped with gcc.\n\nLook at $ gprof -h or $ man gprof") ) ;

  if (cur_project->gprof_options != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_disassembling_gprof_opts_entry), cur_project->gprof_options) ;
  }



  GtkWidget *configure_disassembling_gdb_opts_label = gtk_label_new("gdb options") ;

  GtkWidget *configure_disassembling_gdb_opts_entry  = gtk_entry_new() ;

  gtk_widget_set_name(configure_disassembling_gdb_opts_entry, "gdb_options") ;

  gtk_widget_set_tooltip_text(configure_disassembling_gdb_opts_label, _("gdb: Allow you to see what is going on \"inside\" another program while it executes -- or what another program was doing at the moment it crashed\n\nLook at $ gdb --help or $ man gdb for further informations") ) ;
  gtk_widget_set_tooltip_text(configure_disassembling_gdb_opts_entry, _("gdb: Allow you to see what is going on \"inside\" another program while it executes -- or what another program was doing at the moment it crashed\n\nLook at $ gdb --help or $ man gdb for further informations") ) ;


  if (cur_project->gdb_options != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_disassembling_gdb_opts_entry), cur_project->gdb_options) ;
  }



  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), configure_disassembling_nm_opts_label,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), gtk_label_new(""),                      TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(configure_disassembling_label_vbox), configure_disassembling_gdb_opts_label, FALSE, FALSE, 0) ;
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
  gtk_box_pack_start(GTK_BOX(configure_disassembling_data_vbox), configure_disassembling_gdb_opts_entry, FALSE, FALSE, 0) ;
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

  gtk_assistant_append_page(GTK_ASSISTANT(reconfigure_project_assistant), configure_disassembling_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(reconfigure_project_assistant), configure_disassembling_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(reconfigure_project_assistant), configure_disassembling_hbox, _("Debugging settings") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(reconfigure_project_assistant), configure_disassembling_hbox, TRUE) ;

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

  g_signal_connect(G_OBJECT(configure_code_fmt_indent_chbbox), "toggled", G_CALLBACK(get_checkbutton_value), &cur_project->use_indent) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(configure_code_fmt_indent_chbbox), (cur_project->use_indent) ? TRUE : FALSE ) ;



  GtkWidget *configure_code_fmt_indent_opts_label = gtk_label_new( _("indent options") ) ;

  GtkWidget *configure_code_fmt_indent_opts_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_code_fmt_indent_opts_entry, "indent_options") ;

  gtk_widget_set_tooltip_text(configure_code_fmt_indent_opts_entry,  _("You can set here the options given for the indent-user target\nSee $ indent -h or $ man indent") ) ;


  if (cur_project->indent_options != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_code_fmt_indent_opts_entry), cur_project->indent_options) ;
  }



  GtkWidget *configure_code_fmt_astyle_label = gtk_label_new( _("Use astyle") ) ;

  GtkWidget *configure_code_fmt_astyle_chbbox = gtk_check_button_new() ;

  g_signal_connect(G_OBJECT(configure_code_fmt_astyle_chbbox), "toggled", G_CALLBACK(get_checkbutton_value), &cur_project->use_astyle) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(configure_code_fmt_astyle_chbbox), cur_project->use_astyle) ;



  GtkWidget *configure_code_fmt_astyle_opts_label = gtk_label_new( _("astyle options") ) ;

  GtkWidget *configure_code_fmt_astyle_opts_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_code_fmt_astyle_opts_entry, "astyle_options") ;

  gtk_widget_set_tooltip_text(configure_code_fmt_astyle_opts_entry,  _("You can set here the options given for the astyle-user target\nSee $ astyle -h or $ man astyle") ) ;


  if (cur_project->astyle_options != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_code_fmt_astyle_opts_entry), cur_project->astyle_options) ;
  }


  GtkWidget *configure_code_fmt_bcpp_label = gtk_label_new( _("Use bcpp") ) ;

  GtkWidget *configure_code_fmt_bcpp_chbbox = gtk_check_button_new() ;

  g_signal_connect(G_OBJECT(configure_code_fmt_bcpp_chbbox), "toggled", G_CALLBACK(get_checkbutton_value), &cur_project->use_bcpp) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(configure_code_fmt_bcpp_chbbox), (cur_project->use_bcpp) ? TRUE : FALSE) ;


  GtkWidget *configure_code_fmt_tabs_label = gtk_label_new( _("Use tabs") ) ;

  GtkWidget *configure_code_fmt_tabs_chbbox = gtk_check_button_new() ;

  g_signal_connect(G_OBJECT(configure_code_fmt_tabs_chbbox), "toggled", G_CALLBACK(get_checkbutton_value), &cur_project->use_tabs) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(configure_code_fmt_tabs_chbbox), (cur_project->use_tabs) ? TRUE : FALSE) ;



  GtkWidget *configure_code_fmt_identation_label = gtk_label_new( _("Indentation width") ) ;

  GtkWidget *configure_code_fmt_indentation_spinbut = gtk_spin_button_new_with_range(0, 32, 2) ;

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(configure_code_fmt_indentation_spinbut), cur_project->indentation_width) ;

  g_signal_connect(G_OBJECT(configure_code_fmt_indentation_spinbut), "value-changed", G_CALLBACK(get_spinbutton_value_indentation), &cur_project->indentation_width) ;


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

  gtk_assistant_append_page(GTK_ASSISTANT(reconfigure_project_assistant), configure_code_c_fmt_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(reconfigure_project_assistant), configure_code_c_fmt_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(reconfigure_project_assistant), configure_code_c_fmt_hbox, _("Code beautifier") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(reconfigure_project_assistant), configure_code_c_fmt_hbox, TRUE) ;

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

  gtk_entry_set_text(GTK_ENTRY(configure_oprofiling_operf_opts_entry), cur_project->operf_options) ;

  gtk_widget_set_name(configure_oprofiling_operf_opts_entry, "operf_options") ;

  gtk_widget_set_tooltip_text(configure_oprofiling_operf_opts_label, _("Operf: is the profiler tool provided with OProfile. Operf uses the Linux Performance  Events  Subsystem.\n\nLook at $ operf -h or $ man operf\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;
  gtk_widget_set_tooltip_text(configure_oprofiling_operf_opts_entry, _("Operf: is the profiler tool provided with OProfile. Operf uses the Linux Performance  Events  Subsystem.\n\nLook at $ operf -h or $ man operf\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;


  GtkWidget *configure_oprofiling_ocount_opts_label = gtk_label_new("ocount options") ;

  GtkWidget *configure_oprofiling_ocount_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_oprofiling_ocount_opts_entry), cur_project->ocount_options) ;

  gtk_widget_set_name(configure_oprofiling_ocount_opts_entry, "ocount_options") ;

  gtk_widget_set_tooltip_text(configure_oprofiling_ocount_opts_label, _("ocount: is an OProfile tool that can be used to count native hardware events occurring in either\na given application,\na set of processes or\nthreads,\na subset of active system processors,\nor  the  entire  system.\n\nLook at $ ocount -h or $ man ocount\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;
  gtk_widget_set_tooltip_text(configure_oprofiling_ocount_opts_entry, _("ocount: is an OProfile tool that can be used to count native hardware events occurring in either\na given application,\na set of processes or\nthreads,\na subset of active system processors,\nor  the  entire  system.\n\nLook at $ ocount -h or $ man ocount\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;



  GtkWidget *configure_oprofiling_opreport_opts_label = gtk_label_new("opreport options") ;

  GtkWidget *configure_oprofiling_opreport_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_oprofiling_opreport_opts_entry), cur_project->opreport_options) ;

  gtk_widget_set_name(configure_oprofiling_opreport_opts_entry, "opreport_options") ;

  gtk_widget_set_tooltip_text(configure_oprofiling_opreport_opts_label, _("opreport: opreport outputs binary image summaries, or per-symbol data, from OProfile profiling sessions.\nUse operf or ocount to write profile specifications.\n\nLook at $ opreport -h or $ man opreport\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;
  gtk_widget_set_tooltip_text(configure_oprofiling_opreport_opts_entry, _("opreport: opreport outputs binary image summaries, or per-symbol data, from OProfile profiling sessions.\nUse operf or ocount to write profile specifications.\n\nLook at $ opreport -h or $ man opreport\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;



  GtkWidget *configure_oprofiling_opannotate_opts_label = gtk_label_new("opannotate options") ;

  GtkWidget *configure_oprofiling_opannotate_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_oprofiling_opannotate_opts_entry), cur_project->opannotate_options) ;

  gtk_widget_set_name(configure_oprofiling_opannotate_opts_entry, "opannotate_options") ;

  gtk_widget_set_tooltip_text(configure_oprofiling_opannotate_opts_label, _("opannotate  outputs  annotated source and/or assembly from profile data of an OProfile session.\nUse operf or ocount to write profile specifications.\n\nLook at $ opannotate -h or $ man opannotate\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;
  gtk_widget_set_tooltip_text(configure_oprofiling_opannotate_opts_entry, _("opannotate  outputs  annotated source and/or assembly from profile data of an OProfile session.\nUse operf or ocount to write profile specifications.\n\nLook at $ opannotate -h or $ man opannotate\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;



  GtkWidget *configure_oprofiling_opgprof_opts_label = gtk_label_new("opgprof options") ;

  GtkWidget *configure_oprofiling_opgprof_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_oprofiling_opgprof_opts_entry), cur_project->opgprof_options) ;

  gtk_widget_set_name(configure_oprofiling_opgprof_opts_entry, "opgprof_options") ;

  gtk_widget_set_tooltip_text(configure_oprofiling_opgprof_opts_label, _("opgprof: outputs  gprof-format  profile  data for a given binary image, from an OProfile session.\nUse operf or ocount to write profile specifications.\n\nLook at $ opgprof -h or $ man opgprof\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;
  gtk_widget_set_tooltip_text(configure_oprofiling_opgprof_opts_entry, _("opgprof: outputs  gprof-format  profile  data for a given binary image, from an OProfile session.\nUse operf or ocount to write profile specifications.\n\nLook at $ opgprof -h or $ man opgprof\nOr read the file: file:///usr/share/doc/oprofile/oprofile.html\nYou will find informations for configuring Oprofile at $ man ophelp") ) ;








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

  gtk_assistant_append_page(GTK_ASSISTANT(reconfigure_project_assistant), configure_oprofiling_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(reconfigure_project_assistant), configure_oprofiling_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(reconfigure_project_assistant), configure_oprofiling_hbox, _("Oprofile") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(reconfigure_project_assistant), configure_oprofiling_hbox, TRUE) ;

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

  gtk_entry_set_text(GTK_ENTRY(configure_valgrind_memcheck_opts_entry), cur_project->valgrind_memcheck) ;

  gtk_widget_set_name(configure_valgrind_memcheck_opts_entry, "memcheck_options") ;

  gtk_widget_set_tooltip_text(configure_valgrind_memcheck_opts_label, _("valgrind memcheck: is a memory profiler tool.\n\nLook at $ vagrind -h or $ man valgrind (section MEMCHECK OPTIONS).\nfor further informations.") ) ;
  gtk_widget_set_tooltip_text(configure_valgrind_memcheck_opts_entry, _("valgrind memcheck: is a memory profiler tool.\n\n.Look at $ man valgrind (section MEMCHECK OPTIONS).\nfor further informations.")) ;


  GtkWidget *configure_valgrind_cachegrind_opts_label = gtk_label_new("cachegrind options") ;

  GtkWidget *configure_valgrind_cachegrind_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_valgrind_cachegrind_opts_entry), cur_project->valgrind_cachegrind) ;

  gtk_widget_set_name(configure_valgrind_cachegrind_opts_entry, "cachegrind_options") ;

  gtk_widget_set_tooltip_text(configure_valgrind_cachegrind_opts_label, _("valgrind cachegrind: a cache and branch-prediction profiler.\n\nLook at $ valgrind -h or $ man valgrind (CACHEGRIND OPTIONS).\nfor further informations.") ) ;
  gtk_widget_set_tooltip_text(configure_valgrind_cachegrind_opts_entry, _("valgrind cachegrind: a cache and branch-prediction profiler.\n\nLook at $ valgrind -h or $ man valgrind (CACHEGRIND OPTIONS).\nfor further informations.") ) ;



  GtkWidget *configure_valgrind_callgrind_opts_label = gtk_label_new("callgrind options") ;

  GtkWidget *configure_valgrind_callgrind_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_valgrind_callgrind_opts_entry), cur_project->valgrind_callgrind) ;

  gtk_widget_set_name(configure_valgrind_callgrind_opts_entry, "callgrind_options") ;

  gtk_widget_set_tooltip_text(configure_valgrind_callgrind_opts_label, _("valgrind callgrind: a call-graph generating cache profiler.\n\nLook at $ valgrind -h or $ man valgrind (CALLGRIND OPTIONS).\nfor further informations.") ) ;
  gtk_widget_set_tooltip_text(configure_valgrind_callgrind_opts_entry, _("valgrind callgrind: a call-graph generating cache profiler.\n\nLook at $ valgrind -h or $ man valgrind (CALLGRIND OPTIONS).\nfor further informations.") ) ;



  GtkWidget *configure_valgrind_helgrind_opts_label = gtk_label_new("helgrind options") ;

  GtkWidget *configure_valgrind_helgrind_opts_entry  = gtk_entry_new() ;

  gtk_entry_set_text(GTK_ENTRY(configure_valgrind_helgrind_opts_entry), cur_project->valgrind_helgrind) ;

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

  gtk_assistant_append_page(GTK_ASSISTANT(reconfigure_project_assistant), configure_valgrind_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(reconfigure_project_assistant), configure_valgrind_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(reconfigure_project_assistant), configure_valgrind_hbox, _("Valgrind") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(reconfigure_project_assistant), configure_valgrind_hbox, TRUE) ;

  return ;

}

static void configure_others_info_project(void) {

  GtkWidget *configure_others_info_project_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *configure_others_info_project_image = gtk_image_new_from_file(PATH_TO_ICON) ;

  GtkWidget *configure_others_info_project_label_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *configure_others_info_project_data_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


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

  SEC_FREE(cur_project->editor) ;

  cur_project->editor = g_strdup_printf("%s", gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(configure_others_info_project_editor_combo)) ) ;

  g_signal_connect(G_OBJECT(configure_others_info_project_editor_combo), "changed", G_CALLBACK(get_combo_value), cur_project->editor) ;


  GtkWidget *configure_others_info_project_make_opts_label = gtk_label_new( _("Make options") ) ;

  GtkWidget *configure_others_info_project_make_opts_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_others_info_project_make_opts_entry, "make_options") ;

  gtk_widget_set_tooltip_text(configure_others_info_project_make_opts_entry, _("Options given to make at every call.\n\nI dislike directory printing behaviour of make:\nit look's like an error message cause of formatting !!!\n\nYou can set the -j (jobs options too)") ) ;

  if (cur_project->make_options != NULL) {
    gtk_entry_set_text(GTK_ENTRY(configure_others_info_project_make_opts_entry), cur_project->make_options) ;
  }


  GtkWidget *configure_others_info_project_bash_label = gtk_label_new( _("Bash location") ) ;

  GtkWidget *configure_others_info_project_bash_entry = gtk_entry_new() ;

  gtk_widget_set_name(configure_others_info_project_bash_entry, "bash_location") ;

  char *bash_location = have_app_application("bash") ;

  gtk_entry_set_text(GTK_ENTRY(configure_others_info_project_bash_entry), bash_location) ;

  if (cur_project->bash_location == NULL) {

    cur_project->bash_location = g_strdup(bash_location) ;
  }

  free(bash_location) ;

  g_object_set(G_OBJECT(configure_others_info_project_bash_entry), "editable", FALSE, NULL) ;


  GtkWidget *configure_others_info_project_compression_label = gtk_label_new( _("Compression level") ) ;

  GtkWidget *configure_others_info_project_compression_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 9, 1) ;

  gtk_widget_set_tooltip_text(configure_others_info_project_compression_label,   _("Set the compression level for building archives from your cur_project")  ) ;
  gtk_widget_set_tooltip_text(configure_others_info_project_compression_scale,   _("Set the compression level for building archives from your cur_project")  ) ;

  gtk_range_set_value(GTK_RANGE(configure_others_info_project_compression_scale), cur_project->compression_level) ;

  gtk_scale_set_digits(GTK_SCALE(configure_others_info_project_compression_scale), 0) ;

  gtk_scale_set_value_pos(GTK_SCALE(configure_others_info_project_compression_scale), GTK_POS_TOP) ;

  gtk_scale_set_has_origin(GTK_SCALE(configure_others_info_project_compression_scale), TRUE) ;

  g_signal_connect(G_OBJECT(configure_others_info_project_compression_scale), "value-changed", G_CALLBACK(get_scale_value_compression_level), &cur_project->compression_level) ;

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

  gtk_assistant_append_page(GTK_ASSISTANT(reconfigure_project_assistant), configure_others_info_project_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(reconfigure_project_assistant), configure_others_info_project_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(reconfigure_project_assistant), configure_others_info_project_hbox, _("Other infos") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(reconfigure_project_assistant), configure_others_info_project_hbox, TRUE) ;


  return ;

}










static void configure_licensing_project(void) {



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


  gtk_text_buffer_set_text(configure_licensing_project_buffer, cur_project->licensing_boilerplate, -1) ;


  GtkWidget *configure_licensing_project_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_box_pack_start(GTK_BOX(configure_licensing_project_vbox), configure_licensing_project_label,    FALSE, FALSE, MARGING) ;
  gtk_box_pack_start(GTK_BOX(configure_licensing_project_vbox), configure_licensing_project_viewport, TRUE,  TRUE,  MARGING) ;

  gtk_widget_set_name(configure_licensing_project_vbox, "licensing_hbox") ;

  GtkWidget *configure_licensing_project_format_label = gtk_label_new( _("File formats")) ;

  GtkWidget *configure_licensing_project_format_dbk_checkbutton   = create_checkbox("docbook",  _("Include a docbook (*.dbk) license file to project"),   cur_project->use_licensing_dkb_format)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_dbk_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &cur_project->use_licensing_dkb_format) ;

  GtkWidget *configure_licensing_project_format_epub_checkbutton  = create_checkbox("epub",     _("Include a epub (*.epub) license file to project"),  cur_project->use_licensing_epub_format)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_epub_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &cur_project->use_licensing_epub_format) ;

  GtkWidget *configure_licensing_project_format_pdf_checkbutton   = create_checkbox("pdf",      _("Include a pdf (*.pdf) license file to project"),   cur_project->use_licensing_pdf_format)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_pdf_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &cur_project->use_licensing_pdf_format) ;

  GtkWidget *configure_licensing_project_format_html_checkbutton  = create_checkbox("html",     _("Include a html (*.html) license file to project"),  cur_project->use_licensing_html_format)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_html_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &cur_project->use_licensing_html_format) ;

  GtkWidget *configure_licensing_project_format_tex_checkbutton   = create_checkbox("latex",    _("Include a latex (*.tex) license file to project"),   cur_project->use_licensing_latex_format)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_tex_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &cur_project->use_licensing_latex_format) ;

  GtkWidget *configure_licensing_project_format_texi_checkbutton  = create_checkbox("texinfo",  _("Include a texinfo (*.texi) license file to project"),  cur_project->use_licensing_texinfo_format)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_texi_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &cur_project->use_licensing_texinfo_format) ;

  GtkWidget *configure_licensing_project_format_txt_checkbutton   = create_checkbox("text",     _("Include a text (*.txt) license file to project"),   cur_project->use_licensing_text_format)  ;

  g_signal_connect(G_OBJECT(configure_licensing_project_format_txt_checkbutton), "toggled", G_CALLBACK(get_checkbutton_value), &cur_project->use_licensing_text_format) ;

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

  gtk_assistant_append_page(GTK_ASSISTANT(reconfigure_project_assistant), configure_licensing_project_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(reconfigure_project_assistant), configure_licensing_project_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(reconfigure_project_assistant), configure_licensing_project_hbox, _("Licensing") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(reconfigure_project_assistant), configure_licensing_project_hbox, TRUE) ;

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


  gtk_text_buffer_set_text(configure_desktop_file_project_buffer, cur_project->desktop_file_boilerplate, -1) ;


  gtk_box_pack_start(GTK_BOX(configure_desktop_file_project_vbox), configure_desktop_file_project_label,            FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(configure_desktop_file_project_vbox), configure_desktop_file_project_viewport,         TRUE,  TRUE,  0) ;

  gtk_widget_set_name(configure_desktop_file_project_viewport, "desktop_file_viewport") ;

  gtk_assistant_append_page(GTK_ASSISTANT(reconfigure_project_assistant), configure_desktop_file_project_vbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(reconfigure_project_assistant), configure_desktop_file_project_vbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(reconfigure_project_assistant), configure_desktop_file_project_vbox, _("desktop file") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(reconfigure_project_assistant), configure_desktop_file_project_vbox, TRUE) ;

  return ;

}

static void summary_of_project(void) {

  GtkWidget *summary_of_project_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *summary_of_project_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *summary_of_project_image = gtk_image_new_from_file(PATH_TO_ICON) ;


  GtkWidget *summary_of_project_progressbar = gtk_progress_bar_new() ;

  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(summary_of_project_progressbar), 1.0) ;

  gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(summary_of_project_progressbar), TRUE) ;

  gtk_progress_bar_set_text(GTK_PROGRESS_BAR(summary_of_project_progressbar), _("Project reconfiguration 100% (Completed)") );


  gchar *summary_text =    g_strdup( _("<big>Project reconfiguration completed</big>.") ) ;

  GtkWidget *summary_of_project_label = gtk_label_new("") ;

  gtk_label_set_markup(GTK_LABEL(summary_of_project_label), summary_text) ;

  gtk_widget_set_name(summary_of_project_label, "summary_of_project_label") ;

  free(summary_text) ;


  gtk_box_pack_start(GTK_BOX(summary_of_project_vbox), gtk_label_new(""),               TRUE, TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(summary_of_project_vbox), summary_of_project_progressbar,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(summary_of_project_vbox), gtk_label_new(""),               TRUE, TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(summary_of_project_vbox), summary_of_project_label,        FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(summary_of_project_vbox), gtk_label_new(""),               TRUE, TRUE,   0) ;


  #ifdef USE_IMG
  gtk_box_pack_start(GTK_BOX(summary_of_project_hbox), summary_of_project_image, FALSE, FALSE, 0) ;
  #endif


  gtk_box_pack_start(GTK_BOX(summary_of_project_hbox), summary_of_project_vbox, TRUE, TRUE, MARGING) ;

  gtk_widget_set_name(summary_of_project_vbox, "summary_of_project_container") ;

  gtk_assistant_append_page(GTK_ASSISTANT(reconfigure_project_assistant), summary_of_project_hbox) ;

  gtk_assistant_set_page_type(GTK_ASSISTANT(reconfigure_project_assistant), summary_of_project_hbox, GTK_ASSISTANT_PAGE_CONFIRM) ;

  gtk_assistant_set_page_title(GTK_ASSISTANT(reconfigure_project_assistant), summary_of_project_hbox, _("Summary") ) ;

  gtk_assistant_set_page_complete(GTK_ASSISTANT(reconfigure_project_assistant), summary_of_project_hbox, TRUE) ;

  return ;

}

static gboolean is_compiler_focus_out(GtkWidget *widget, GdkEvent  *event, gpointer   user_data) {

  gchar *content = g_path_get_basename(gtk_entry_get_text(GTK_ENTRY(widget))) ;

  g_strstrip(content) ;

  if (! g_strcmp0(cur_project->compiler, content) ) {

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

  if (g_strcmp0(cur_project->language,"C") == 0) {

    gchar *filepath = g_strdup_printf("%s/testit.c", g_get_tmp_dir()) ;

    fp = fopen(filepath, "w") ;

    g_free(filepath) ;

  }
  else if (g_strcmp0(cur_project->language,"C++") == 0) {
    gchar *filepath = g_strdup_printf("%s/testit.cpp", g_get_tmp_dir()) ;

    fp = fopen(filepath, "w") ;

    g_free(filepath) ;
  }
  else {
    gchar *filepath = g_strdup_printf("%s/testit.c", g_get_tmp_dir()) ;

    fp = fopen(filepath, "w") ;

    g_free(filepath) ;
  }

  const char *src_code = "int main(int argc, char *argv[]) {\n"
                          "  \n"
                          "  return 0 ;\n"
                          "}\n" ;

  char *pathname = NULL ;

  if (g_strcmp0(cur_project->language,"C") == 0) {
    pathname = g_strdup_printf("%s/testit.%s",g_get_tmp_dir(), "c") ;
  }
  else if ( g_strcmp0(cur_project->language,"C++") == 0) {
    pathname = g_strdup_printf("%s/testit.%s", g_get_tmp_dir(), "cpp") ;
  }
  else {
    pathname = g_strdup_printf("%s/testit.%s",g_get_tmp_dir(), "c") ;
  }

  fwrite(src_code, strlen(src_code), sizeof(char), fp) ;

  fflush(fp) ;

  fclose(fp) ;

  gchar *a_out_file = g_strdup_printf("%s/a.out",g_get_tmp_dir()) ;

  char *cmdline = g_strdup_printf("%s %s -o %s", compiler, pathname, a_out_file) ;



  if (system(cmdline) != 0) {

    free(cmdline) ;

    remove(pathname) ;

    free(pathname) ;

    free(a_out_file) ;

    return false ;
  }

  remove(pathname) ;

  remove(a_out_file) ;

  free(a_out_file) ;

  free(pathname) ;

  free(cmdline) ;

  return true ;

}


static void update_summary(GList *content) {



  while (content != NULL) {

    if (! g_strcmp0( gtk_widget_get_name(content->data), "summary_of_project_label")) {

      gchar *summary_text =    g_strdup_printf( _("<big>Project reconfiguration completed</big>.") ) ;

      gtk_label_set_markup(GTK_LABEL(content->data), summary_text) ;

      free(summary_text) ;

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

      update_c_project( gtk_container_get_children(GTK_CONTAINER(children->data)), cur_project ) ;
      break ;
    }

    if (! g_strcmp0(gtk_widget_get_name(children->data), "compiler_settings_container")) {

      update_compiler( gtk_container_get_children(GTK_CONTAINER(children->data)), cur_project ) ;
      break ;
    }

    if (! g_strcmp0(gtk_widget_get_name(children->data), "licensing_viewport")) {

      update_licensing( gtk_container_get_children(GTK_CONTAINER(children->data)), cur_project ) ;
      break ;
    }

    if (! g_strcmp0(gtk_widget_get_name(children->data), "summary_of_project_container")) {

      update_summary( gtk_container_get_children(GTK_CONTAINER(children->data)) ) ;
      break ;

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

    if (! g_strcmp0(gtk_widget_get_name(page_content->data),  "licensing_viewport")) {

      get_licensing_boilerplate( gtk_container_get_children(GTK_CONTAINER(page_content->data)), cur_project ) ;
      break ;

    }
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data),  "desktop_file_viewport")) {

      get_desktop_file_boilerplate( gtk_container_get_children(GTK_CONTAINER(page_content->data)), cur_project ) ;
      break ;

    }

    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "compiler_settings_container")) {

      get_compiler_datas( gtk_container_get_children(GTK_CONTAINER(page_content->data)), cur_project ) ;
      break ;

    }
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "disassembling_opts")) {

      get_disassembling_opts( gtk_container_get_children(GTK_CONTAINER(page_content->data)), cur_project ) ;
      break ;

    }
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "code_fmt")) {

      get_code_fmt_opts( gtk_container_get_children(GTK_CONTAINER(page_content->data)), cur_project ) ;
      break ;

    }
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "others_infos")) {

      get_other_infos( gtk_container_get_children(GTK_CONTAINER(page_content->data)), cur_project ) ;
      break ;
    }
    #if 0
    else if (! g_strcmp0(gtk_widget_get_name(page_content->data), "configure_doc")) {

      get_doc_datas(gtk_container_get_children(GTK_CONTAINER(page_content->data)), cur_project) ;
      break ;
    }
    #endif

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

  gchar *makefile_path = g_strconcat(project->project_folderpath, "/", "Makefile", NULL) ;

  gchar *makefile_code_fmt_path = g_strconcat(project->project_folderpath, "/", ".SubMakefiles", "/code_formatter.mk",  NULL) ;

  gchar *makefile_doc_path = g_strconcat(project->project_folderpath, "/", ".SubMakefiles", "/documentation.mk",  NULL) ;

  gchar *makefile_dist_path = g_strconcat(project->project_folderpath, "/", ".SubMakefiles", "/distributing.mk",  NULL) ;

  #ifdef THREADING

  /** @NOTE: the Makefile values parsing is not (I think) entirely thread-safe because of
   *         accessing the `same structure' different members into many threads.
   *    
   *         Thanks to notify me if acessing the same ``typedef struct { } my_type`` but not
   *         the same member in different threads generate need a mutex.
  **/

  GThread *main_makefile_thread = g_thread_new("main_makefile", (GThreadFunc) &set_main_makefile_values, makefile_path) ;
  //GThread *makefile_code_fmt_thread= g_thread_new("makefile_fmt_code", (GThreadFunc) &set_doc_makefile_values, makefile_doc_path) ;
  GThread *makefile_doc_thread= g_thread_new("makefile_doc", (GThreadFunc) &set_code_fmt_makefile_values, makefile_code_fmt_path) ;
  GThread *makefile_dist_thread = g_thread_new("makefile_dist", (GThreadFunc) &set_dist_makefile_values, makefile_dist_path) ;

  g_thread_join(main_makefile_thread) ;
  g_thread_join(makefile_code_fmt_thread) ;
  g_thread_join(makefile_doc_thread) ;
  #else
  set_main_makefile_values(makefile_path) ;
  //set_doc_makefile_values(makefile_doc_path) ;
  set_dist_makefile_values(makefile_dist_path) ;
  set_code_fmt_makefile_values(makefile_code_fmt_path) ;
  #endif

  write_content_to_file(g_strconcat(project->project_folderpath, "/.licensing", "/licensing.tmpl", NULL), cur_project->licensing_boilerplate) ;

  create_file(g_strconcat(project->project_folderpath, "/desktop", NULL), cur_project->desktop_file_boilerplate, g_strconcat(cur_project->prgname, ".desktop", NULL) ) ;

  cur_project->project_folderpath = g_strdup(project->project_folderpath) ;

  gtk_widget_destroy(GTK_WIDGET(assistant)) ;


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


  gchar *mkp_filepath = g_strconcat(cur_project->project_folderpath, "/", cur_project->prgname, ".mkp", NULL) ;

  if (mkp_filepath != NULL) {

    xml_updating(mkp_filepath, cur_project) ;

    g_free(mkp_filepath) ;

  }

  add_license(cur_project) ;

  gchar *project_dirpath = g_path_get_dirname(makefile_path);

  get_output_make(project_dirpath) ;

  #ifdef MAC_INTEGRATION // The library gtk-mac-integration-gtk3 define this.
  // @NOTE: the mac top application menu doesn't update correctly the menu radio buttons !
  //        I cant' use gtkosx_application_insert_app_menu_item(...) properly.
  //gtkosx_application_set_menu_bar(gtkosx_application_get(), GTK_MENU_SHELL(menu_bar)) ;
  gtkosx_application_sync_menubar(gtkosx_application_get());
  #endif

  g_free(makefile_path) ;

  g_free(makefile_code_fmt_path) ;

  g_free(makefile_doc_path) ;

  g_free(makefile_dist_path) ;

  g_free(project_dirpath) ;

  free_cur_project_settings() ;

  init_cur_project_settings() ;

  return ;

}

static void cancel_event(GtkAssistant *assistant, gpointer pointer) {
  /** Check if any file still unsaved before exit the application **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  free_cur_project_settings() ;

  init_cur_project_settings() ;

  gtk_widget_destroy(GTK_WIDGET(assistant)) ;

  return ;
}
