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

#include "message_dialog.h"

void display_message_dialog(const gchar *message, gchar *secondary_message, gint message_type, gint buttons)  {
  /** Return a message dialog according to the given arguments. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *message_dialog = gtk_message_dialog_new( GTK_WINDOW(gui->window),
                                                      GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT ,
                                                      message_type,       /** GTK_MESSAGE_INFO || GTK_MESSAGE_ERROR  **/
                                                      buttons,            /** GTK_BUTTONS_NONE || GTK_BUTTONS_CLOSE  **/
                                                      message,
                                                      NULL) ;

  gtk_window_set_position(GTK_WINDOW(message_dialog), GTK_WIN_POS_CENTER) ;

  if (secondary_message != NULL) {
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(message_dialog), secondary_message, NULL) ;
  }

  gtk_dialog_run(GTK_DIALOG(message_dialog))  ; // Display message dialog.

  gtk_widget_destroy(message_dialog) ;

  return ;
}

bool display_message_dialog_question(const gchar *message, gchar *secondary_message)  {
  /** Return a message dialog according to the given arguments. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *message_dialog = gtk_message_dialog_new( GTK_WINDOW(gui->window),
                                                      GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT ,
                                                      GTK_MESSAGE_QUESTION,   
                                                      GTK_BUTTONS_YES_NO,
                                                      message,
                                                      NULL) ;

  gtk_window_set_position(GTK_WINDOW(message_dialog), GTK_WIN_POS_CENTER) ;

  if (secondary_message != NULL) {
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(message_dialog), secondary_message, NULL) ;
  }

  int ret = gtk_dialog_run(GTK_DIALOG(message_dialog))  ; // Display message dialog.

  switch (ret) {

    case GTK_RESPONSE_YES :
  
      gtk_widget_destroy(message_dialog) ;
  
      return true ;

    case GTK_RESPONSE_NO :
  
      gtk_widget_destroy(message_dialog) ;
  
      return false ;
    
    default :
   
      gtk_widget_destroy(message_dialog) ;
  
      return true ;
  
  }

}                            