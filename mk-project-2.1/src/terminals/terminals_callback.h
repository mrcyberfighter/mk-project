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

#ifndef MK_PROJECT_TERMINALS_CALLBACKS_HH
#define MK_PROJECT_TERMINALS_CALLBACKS_HH

#include "../global_vars.h"

#include "./terminals.h"

#include "../GUI/setup_gui.h"

extern void update_page_number_terminal(GtkWidget *notebook) ;

extern void terminals_page_reorder(GtkNotebook *notebook, GtkWidget   *child, guint page_num) ;

extern gboolean display_clipboard_menu(GtkWidget *widget, GdkEvent  *event, GtkWidget *clipboard_menu) ;

extern void clipboard_copy(GtkMenuItem *menuitem, gpointer user_data) ;

extern void clipboard_paste(GtkMenuItem *menuitem, VteTerminal *user_data) ;

extern void reset_terminal(GtkMenuItem *menuitem, GtkWidget *vteterminal) ;

extern void increase_font_size(VteTerminal *vte_terminal, VteTerminal *vteterminal) ;

extern void decrease_font_size(VteTerminal *vte_terminal, VteTerminal *vteterminal) ;

extern void remove_terminal_tabs_from_clipboard(GtkWidget *widget, gint *page_num) ;

extern void remove_terminal_tabs(GtkWidget *widget, GtkWidget *user_data) ;

#ifdef MINIMAL_SIZE_SUPPORT
extern void terminal_size_allocate(GtkWidget *widget, GdkRectangle *allocation, gpointer user_data) ;
#endif

#ifdef TERM_IMG_SUPPORT
extern void resize_terminal_background_image(GtkWidget *widget, const char *filepath, const int width, const int height) ;

extern void terminal_size_allocate(GtkWidget *widget, GdkRectangle *allocation, gpointer user_data) ;
#endif

#endif
