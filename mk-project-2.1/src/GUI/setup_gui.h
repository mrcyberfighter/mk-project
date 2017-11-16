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

#ifndef MK_PROJECT_SETUP_GUI_HH
#define MK_PROJECT_SETUP_GUI_HH

#include "../headers/includes.h"

#include "../headers/defines.h"

#include "../headers/structures/GUI_structures.h"

#include "../project/project.h"

#include "../project/reconf_project.h"

#include "../terminals/terminals.h"

#include "../terminals/GtkMkTerm.h"

#include "./GtkSmartMenuItem.h"

#include "./gui_callback.h"

#include "../terminals/GtkMkTermTab.h"

#include "../configuration/configuration_dialog.h"


extern void initialize_menu(Menu *menu) ;

extern void set_new_terminals(GtkWidget *terminals_notebook) ;


#endif
