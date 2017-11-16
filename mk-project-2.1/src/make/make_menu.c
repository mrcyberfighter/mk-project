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

#include "make_menu.h"

static void activate_make_menu_item(GtkWidget *widget, const char *command) {

   /** Activating target callback. **/

   #ifdef DEBUG
     DEBUG_FUNC_MARK
   #endif

   if (gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->main_notebook)) != 0) {

     gtk_notebook_set_current_page(GTK_NOTEBOOK(gui->main_notebook), 0) ;
   }


   vte_terminal_feed_child(VTE_TERMINAL(gtk_mkterm_get_vte_terminal(gui->make_terminal)), command, strlen(command) ) ;

   #ifdef DEBUG
   fprintf(stdout,"Command: %s\n", command) ;
   #endif

   return ;
}

void setup_make_menu_item(const char *label, const char *tooltip_text, const char *makefile_filepath, GtkWidget *menu) {

  /** Generate one menu item according to the given settings **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  gchar *menuitem_text = g_strdup_printf("make %s", label) ;

  gchar *dirname = g_path_get_dirname(makefile_filepath) ;

  gchar *command = g_strdup_printf("make --no-print-directory -C %s %s \r", dirname, label) ;

  g_free(dirname) ;

  GtkWidget *menu_item = gtk_menu_item_new_with_label(menuitem_text) ;

  g_free(menuitem_text) ;

  if (tooltip_text != NULL) {

    gtk_widget_set_tooltip_text(menu_item, tooltip_text) ;
  }

  g_signal_connect(G_OBJECT(menu_item), "activate", G_CALLBACK(activate_make_menu_item), command) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item) ;

  gtk_widget_show_now(menu_item) ;

  return ;
}

