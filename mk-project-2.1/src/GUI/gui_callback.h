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

#ifndef MK_PROJECT_GUI_CALLBACK_HH
#define MK_PROJECT_GUI_CALLBACK_HH

#include "../headers/includes.h"

#include "../headers/defines.h"

#include "../headers/structures/GUI_structures.h"

#include "../global_vars.h"

#include "../make/make_actions.h"

#include "../project/fmt_files.h"

#include "../project/reconf_project.h"

#include "../project/load_project.h"

#include "../make/make_utils.h"

#include "../structures_initialize.h"

#include "../xml_utils/xml_getter.h"

extern void add_file_to_project(GtkWidget *widget) ;

extern void load_project(GtkWidget *widget) ;

extern void switch_terminals(GtkWidget *widget, gint *page_num) ;

extern void reconfiguring_project(GtkWidget *widget) ;

extern void launch_readme_html(GtkWidget *widget) ;

extern void display_about_dialog(GtkWidget *widget) ;

extern void extract_and_load_project(GtkWidget *widget) ;

extern gchar *find_mkp_file(const gchar *folderpath) ;

#endif
