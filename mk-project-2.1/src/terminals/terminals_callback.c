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

#include "terminals_callback.h"

void update_page_number_terminal(GtkWidget *notebook) {

  /** Update the page number data from the tab_button. **/

  gint nb_page = gtk_notebook_get_n_pages(GTK_NOTEBOOK(notebook)) ;

  int c ;

  for (c=0 ; c < nb_page ; c++) {

    gint *page_number = g_object_get_data(G_OBJECT(gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), c)), "term_page_number") ;

    *page_number = c ;

    g_object_set_data(G_OBJECT(gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), c)), "term_page_number", page_number) ;

  }

  return ;

}

void terminals_page_reorder(GtkNotebook *notebook, GtkWidget   *child, guint page_num) {

  /** Page-reordering callback. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  update_page_number_terminal(GTK_WIDGET(notebook)) ;

  return ;

}

gboolean display_clipboard_menu(GtkWidget *widget, GdkEvent  *event, GtkWidget *clipboard_menu) {

  /** Display the clipbpoard menu from the terminals. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if ((event->type == GDK_BUTTON_PRESS) && (((GdkEventButton*)event)->button == 3)) {
 
    #if (GTK_MINOR_VERSION < 22)
    gtk_menu_popup(GTK_MENU(clipboard_menu),
                   NULL,
                   NULL,
                   NULL,
                   NULL,
                   ((GdkEventButton*)event)->button,
                   gtk_get_current_event_time());

    #else

      gtk_menu_popup_at_pointer(GTK_MENU(clipboard_menu), event);

    #endif
 
 

    return TRUE ;
  }

  return FALSE ;
}



void clipboard_copy(GtkMenuItem *menuitem, gpointer user_data) {

  /** Copy the selected text from an terminal to the clipboard. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  vte_terminal_copy_clipboard(VTE_TERMINAL(user_data) );

  return ;

}

void clipboard_paste(GtkMenuItem *menuitem, VteTerminal *user_data) {

  /** Paste the clipboard content into an terminal. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  vte_terminal_paste_clipboard(VTE_TERMINAL(user_data)) ;

  return ;
}

void increase_font_size(VteTerminal *vte_terminal, VteTerminal *vteterminal) {

  double font_size = vte_terminal_get_font_scale(vteterminal);

  if  (font_size < 4) {
    font_size += 0.1 ;
    vte_terminal_set_font_scale(vteterminal, font_size) ;
  }

  return ;

}

void decrease_font_size(VteTerminal *vte_terminal, VteTerminal *vteterminal) {

  double font_size = vte_terminal_get_font_scale(vteterminal);

  if  (font_size > 0.25) {

    font_size -= 0.1 ;

    vte_terminal_set_font_scale(vteterminal, font_size) ;
  }

  return ;

}

void reset_terminal(GtkMenuItem *menuitem, GtkWidget *vteterminal) {

  vte_terminal_reset(VTE_TERMINAL(vteterminal), TRUE, TRUE) ;

  /** Configure terminal partially according to the configuration stored settings. **/
  gtk_mkterm_configure_terminal(vteterminal, false) ;

  char *argv_cmd[2] = {settings.user_shell, NULL} ;

  /** Fork a new process: your default shell. The configurations files like .bashrc will be reading. **/
  GPid child_pid = -1 ;

  gchar **envp = g_get_environ() ;

  #if (VTE_MINOR_VERSION < 48)

    vte_terminal_spawn_sync(VTE_TERMINAL(vteterminal),
                            VTE_PTY_DEFAULT,
                            settings.start_dir,
                            argv_cmd,
                            envp,
                            G_SPAWN_DEFAULT, NULL, NULL, &child_pid, NULL,  NULL);
                    
    while (child_pid == -1) {

      g_main_context_iteration(NULL, FALSE) ;

    }                  

  #else

  vte_terminal_spawn_async(VTE_TERMINAL(vteterminal),
                            VTE_PTY_DEFAULT,
                            settings.start_dir, // Working directory.
                            argv_cmd,
                            envp,
                            G_SPAWN_DEFAULT,
                            NULL,
                            NULL,
                            NULL,
                            -1,
                            NULL,
                            NULL,
                            NULL);

  #endif


  g_strfreev(envp) ;

  #if (VTE_MINOR_VERSION < 48)

    vte_terminal_watch_child(VTE_TERMINAL(vteterminal), child_pid) ;

  #endif


  return ;
}

void remove_terminal_tabs_from_clipboard(GtkWidget *widget, gint *page_num) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->terminal_notebook)) == 1) {

    /** One terminal minimum required **/

    return ;
  }


  gtk_notebook_remove_page(GTK_NOTEBOOK(gui->terminal_notebook), gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->terminal_notebook))) ;

  update_page_number_terminal(gui->terminal_notebook) ;

  free(page_num) ;

  return ;

}


void remove_terminal_tabs(GtkWidget *widget, GtkWidget *user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if (gtk_notebook_get_n_pages(GTK_NOTEBOOK(gui->terminal_notebook)) == 1) {

    /** One terminal minimum required. **/

    return ;
  }

  gtk_notebook_remove_page(GTK_NOTEBOOK(gui->terminal_notebook), gtk_notebook_page_num(GTK_NOTEBOOK(gui->terminal_notebook), user_data) ) ;

  update_page_number_terminal(gui->terminal_notebook) ;

  return ;

}

