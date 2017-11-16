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

#ifndef MK_PROJECT_CONFIGURATION_DIALOG_HH
#define MK_PROJECT_CONFIGURATION_DIALOG_HH

#include "../headers/includes.h"

#include "../headers/structures/GUI_structures.h"

#include "../headers/defines.h"

#include "../global_vars.h"

#include "../GUI/message_dialog.h"

#include "../GUI/message_dialog.h"

#include "../terminals/terminals.h"

#include "./configuration_storing.h"

extern void display_configuration_dialog(GtkWidget *widget, gpointer user_data) ;

extern void export_as_profile(const gchar *filepath) ;

extern bool get_a_profile(const gchar *filepath) ;

#endif
