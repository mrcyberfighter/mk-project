/** ***********************************************************************************
  *                                                                                   *
  * mk-project a tool to ease the development process                                 *
  * and a good bridge for the distributing process.                                   *
  *                                                                                   *
  * Copyright (C) 2016 Brüggemann Eddie                                               *
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

#include "setup_gui.h"



void initialize_menu(Menu *menu) {
  /** Generate all the menu, partially trought setup_menu_item() calls. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  menu->menu_bar = gtk_menu_bar_new() ;

  menu->projects_menu = gtk_menu_new() ;

  menu->projects_menubutton = gtk_smart_menu_item_new_all(_("  Projects"), PATH_TO_MENU_ICON "applications-development.png", NULL, 0, 0) ;

  GtkWidget *projects_menubutton_menuitem = gtk_smart_menu_item_get_menuitem(menu->projects_menubutton) ;

  menu->new_project = gtk_smart_menu_item_new_all(_("  New project  "), PATH_TO_MENU_ICON "folder-development.png", NULL, 0, 0) ;

  GtkWidget *new_project_menuitem = gtk_smart_menu_item_get_menuitem(menu->new_project) ;


  menu->projects_raw = gtk_smart_menu_item_new_all(_("  New project"), PATH_TO_MENU_ICON "applications-development-web.png", NULL, 0, 0) ;

  GtkWidget *new_raw_project_menuitem = gtk_smart_menu_item_get_menuitem(menu->projects_raw) ;

  gtk_widget_set_name(new_raw_project_menuitem, "raw") ;

  g_signal_connect(G_OBJECT(new_raw_project_menuitem), "activate", G_CALLBACK(new_project), NULL) ;


  menu->projects_from_profile = gtk_smart_menu_item_new_all(_("  From profile"), PATH_TO_MENU_ICON "applications-development-translation.png", NULL, 0, 0) ;

  GtkWidget *new_project_from_profile_menuitem = gtk_smart_menu_item_get_menuitem(menu->projects_from_profile) ;

  gtk_widget_set_name(new_project_from_profile_menuitem, "profile") ;

  g_signal_connect(G_OBJECT(new_project_from_profile_menuitem), "activate", G_CALLBACK(new_project), NULL) ;




  menu->load_project = gtk_smart_menu_item_new_all(_("  Load project  "), PATH_TO_MENU_ICON "project-open.png", NULL, 0, 0) ;

  GtkWidget *load_project_menuitem = gtk_smart_menu_item_get_menuitem(menu->load_project) ;

  gtk_widget_set_name(load_project_menuitem, "raw") ;

  g_signal_connect(G_OBJECT(load_project_menuitem), "activate", G_CALLBACK(load_project), NULL) ;


  menu->extract_and_load_project = gtk_smart_menu_item_new_all(_("  Extract and load project  "), PATH_TO_MENU_ICON "folder-tar.png", NULL, 0, 0) ;

  GtkWidget *extract_and_load_project_menuitem = gtk_smart_menu_item_get_menuitem(menu->extract_and_load_project) ;

  g_signal_connect(G_OBJECT(extract_and_load_project_menuitem), "activate", G_CALLBACK(extract_and_load_project), NULL) ;


  menu->reconf_project = gtk_smart_menu_item_new_all(_("  Reconfigure project  "), PATH_TO_MENU_ICON "folder-activities.png", NULL, 0, 0) ;

  GtkWidget *reconf_project_menuitem = gtk_smart_menu_item_get_menuitem(menu->reconf_project) ;

  g_signal_connect(G_OBJECT(reconf_project_menuitem), "activate", G_CALLBACK(reconfiguring_project), NULL) ;

  gtk_widget_set_state_flags(reconf_project_menuitem, GTK_STATE_FLAG_INSENSITIVE, FALSE) ;


  menu->add_file_to_project = gtk_smart_menu_item_new_all(_("  Add file(s) to project  "), PATH_TO_MENU_ICON "preferences-desktop-filetype-association.png", NULL, 0, 0) ;

  GtkWidget *add_file_to_project_menuitem = gtk_smart_menu_item_get_menuitem(menu->add_file_to_project) ;

  g_signal_connect(G_OBJECT(add_file_to_project_menuitem), "activate", G_CALLBACK(add_file_to_project), NULL) ;

  gtk_widget_set_state_flags(add_file_to_project_menuitem, GTK_STATE_FLAG_INSENSITIVE, FALSE) ;


  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), projects_menubutton_menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(projects_menubutton_menuitem), menu->projects_menu);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->projects_menu), new_project_menuitem) ;

  menu->new_project_menu = gtk_menu_new() ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(new_project_menuitem), menu->new_project_menu);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->new_project_menu), new_raw_project_menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->new_project_menu), new_project_from_profile_menuitem) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->projects_menu), load_project_menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->projects_menu), extract_and_load_project_menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->projects_menu), reconf_project_menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->projects_menu), add_file_to_project_menuitem) ;


  menu->terminals_menubutton = gtk_smart_menu_item_new_all(_("  Terminals  "), PATH_TO_MENU_ICON "yakuake.png", NULL, 0, 0) ;

  GtkWidget *terminals_menubutton_menuitem = gtk_smart_menu_item_get_menuitem(menu->terminals_menubutton) ;

  menu->terminal_make = gtk_smart_radio_menu_item_new_all(_("  make terminal  "), PATH_TO_MENU_ICON "terminal-down-red.png", NULL, 0, 0, NULL) ;

  GtkWidget *menu_terminal_make_menuitem = gtk_smart_menu_item_get_menuitem(menu->terminal_make) ;


  menu->terminal_edit = gtk_smart_radio_menu_item_new_all(_("  Edit terminal  "), PATH_TO_MENU_ICON "terminal-down-black.png", NULL, 0, 0, menu_terminal_make_menuitem) ;

  GtkWidget *menu_terminal_edit_menuitem = gtk_smart_menu_item_get_menuitem(menu->terminal_edit) ;

  int *page_0 = malloc(sizeof(int)) ;

  *page_0 = 0 ;

  int *page_1 = malloc(sizeof(int)) ;

  *page_1 = 1 ;

  g_signal_connect(G_OBJECT(menu_terminal_make_menuitem), "activate", G_CALLBACK(switch_terminals), page_0) ;

  g_signal_connect(G_OBJECT(menu_terminal_edit_menuitem), "activate", G_CALLBACK(switch_terminals), page_1) ;





  menu->terms_menu = gtk_menu_new() ;


  menu->make_menubutton = gtk_smart_menu_item_new_all(_("  targets "), PATH_TO_MENU_ICON "preferences-desktop.png", NULL, 0, 0) ;

  GtkWidget *make_menubutton = gtk_smart_menu_item_get_menuitem(menu->make_menubutton) ;



  menu->make_menu = gtk_menu_new() ;





  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), terminals_menubutton_menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(terminals_menubutton_menuitem), menu->terms_menu);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->terms_menu), menu_terminal_make_menuitem) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->terms_menu), menu_terminal_edit_menuitem) ;


  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), make_menubutton) ;

  /** We doesn't not set the sub-menu at start because else we get a bad displaying of the menu.
    * We will set the sub-menu when generating the sub-menu: i.e by loading, creating or reconfiguring a project.
    * gtk_menu_item_set_submenu(GTK_MENU_ITEM(make_menubutton), menu->make_menu);
    */



  menu->configuration_menu = gtk_menu_new() ;


  menu->configure_menubutton = gtk_smart_menu_item_new_all(_("  Configuration "), PATH_TO_MENU_ICON "preferences-system.png", NULL, 0, 0) ;

  GtkWidget *configure_menubutton_menuitem = gtk_smart_menu_item_get_menuitem(menu->configure_menubutton) ;

  menu->configuration = gtk_smart_menu_item_new_all(_("  Configure program "), PATH_TO_MENU_ICON "preferences-other.png", NULL, 0, 0) ;

  GtkWidget *configuration_menuitem = gtk_smart_menu_item_get_menuitem(menu->configuration) ;

  g_signal_connect(G_OBJECT(configuration_menuitem), "activate", G_CALLBACK(display_configuration_dialog), NULL) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), configure_menubutton_menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(configure_menubutton_menuitem), menu->configuration_menu);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->configuration_menu), configuration_menuitem) ;


  menu->user_info_menu = gtk_menu_new() ;


  menu->user_info_menubutton = gtk_smart_menu_item_new_all(_("  Info "), PATH_TO_MENU_ICON "user-info.png", NULL, 0, 0) ;

  GtkWidget *user_info_menuitem = gtk_smart_menu_item_get_menuitem(menu->user_info_menubutton) ;


  menu->user_info_doc = gtk_smart_menu_item_new_all(_("  Documentation "), PATH_TO_MENU_ICON "document-readme.png", NULL, 0, 0) ;

  GtkWidget *user_info_doc_menuitem = gtk_smart_menu_item_get_menuitem(menu->user_info_doc) ;

  g_signal_connect(G_OBJECT(user_info_doc_menuitem), "activate", G_CALLBACK(launch_readme_html), NULL) ;


  menu->user_info_about = gtk_smart_menu_item_new_all(_("  About "), PATH_TO_MENU_ICON "help-about.png", NULL, 0, 0) ;

  GtkWidget *user_info_about_menuitem = gtk_smart_menu_item_get_menuitem(menu->user_info_about) ;

  g_signal_connect(G_OBJECT(user_info_about_menuitem), "activate", G_CALLBACK(display_about_dialog), NULL) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), user_info_menuitem) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(user_info_menuitem), menu->user_info_menu);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu->user_info_menu), user_info_doc_menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->user_info_menu), user_info_about_menuitem) ;



}

void set_new_terminals(GtkWidget *terminals_notebook) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *terminal = gtk_mkterm_new(TRUE, TRUE) ;

  GtkWidget *vteterminal = gtk_mkterm_get_vte_terminal(terminal) ;

  GtkWidget *tab = gtk_mk_term_tab_new(PATH_TO_MENU_ICON "utilities-terminal.png", _(" Terminals "), PATH_TO_MENU_ICON "window-close.png") ;





  /** Unique first page of the terminal notebook: if the terminals are included in an notebook we can add new pages. **/
  gint *ret=malloc(sizeof(gint)) ;
  *ret = gtk_notebook_append_page(GTK_NOTEBOOK(terminals_notebook), terminal, tab) ;

  if (*ret > 0) {
    gtk_widget_show_all(terminal) ;
  }


  /** Store the notebook page **/
  g_object_set_data(G_OBJECT(gtk_notebook_get_nth_page(GTK_NOTEBOOK(terminals_notebook), *ret)), "term_page_number", ret) ;

  /** Store the notebook page. **/
  g_object_set_data(G_OBJECT(gtk_notebook_get_nth_page(GTK_NOTEBOOK(terminals_notebook), *ret)), "terminals", terminal) ;

  g_signal_connect(G_OBJECT(gtk_mk_term_tab_get_close_button( GTK_MK_TERM_TAB(tab))), "clicked", G_CALLBACK(remove_terminal_tabs), gtk_notebook_get_nth_page(GTK_NOTEBOOK(terminals_notebook), *ret) ) ;


  gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(terminals_notebook), terminal, TRUE) ;

  char *tab_text = g_strdup_printf("Terminals %d",(*ret)+1) ;

  gtk_notebook_set_menu_label_text(GTK_NOTEBOOK(terminals_notebook), terminal,  tab_text) ;

  free(tab_text) ;

  gtk_notebook_set_current_page(GTK_NOTEBOOK(terminals_notebook), *ret) ;

  gtk_widget_grab_focus(vteterminal) ;

  return ;

}


