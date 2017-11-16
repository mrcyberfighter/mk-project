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

#include "./terminals.h"

void add_new_terminals(GtkWidget *widget, gpointer user_data) {

  /** Add new terminals to the edit ternimals notebook. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  set_new_terminals(gui->terminal_notebook) ;

  return ;
}

void apply_terminal_change(void) {

  gint page_nb = gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->terminal_notebook)) ;

  int c ;

  for (c=0 ; c < page_nb ; c++) {

    GtkWidget *terminal = g_object_get_data(G_OBJECT(gtk_notebook_get_nth_page(GTK_NOTEBOOK(gui->terminal_notebook),c)), "terminals") ;

    gtk_mkterm_configure_terminal(terminal, false) ;
  }


  gtk_mkterm_configure_terminal(gui->make_terminal, false) ;

  return ;
}
