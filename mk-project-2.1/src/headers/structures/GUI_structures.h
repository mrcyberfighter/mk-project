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

#ifndef MK_PROJECT_GUI_STRUCTURE_HH
#define MK_PROJECT_GUI_STRUCTURE_HH

#include "../includes.h"

typedef struct {

  /** Convenience structure for passing 2 values into one pointer to a @Gtk callback. **/

  GtkWidget *ldflags_entry ;

  GtkWidget *ldlibs_entry ;

} libraries_entries ;


typedef struct {

  /** Main menu structure **/

  GtkWidget *menu_bar  ;

  GtkAccelGroup *menu_accel_group ;

  GtkWidget *projects_menubutton ;

  GtkWidget *projects_raw ;

  GtkWidget *projects_from_profile ;

  GtkWidget *new_project_menu ;

  GtkWidget *projects_menu ;

  GtkWidget *new_project ;

  GtkWidget *reconf_project ;

  GtkWidget *load_project ;

  GtkWidget *extract_and_load_project ;

  GtkWidget *add_file_to_project ;



  GtkWidget *terms_menu ;

  GtkWidget *make_menu ;

  GtkWidget *configuration_menu ;

  GtkWidget *user_info_menu ;


  GtkWidget *make_show_menu   ;

  GtkWidget *make_clean_menu   ;

  GtkWidget *make_pkg_menu   ;

  GtkWidget *make_astyle_menu ;

  GtkWidget *make_indent_menu ;

  GtkWidget *make_pindent_menu ;

  GtkWidget *make_bcpp_menu ;

  GtkWidget *make_debug_menu ;

  GtkWidget *make_bin_menu ;

  GtkWidget *make_utils_menu ;

  GtkWidget *make_oprofile_menu ;
 
  GtkWidget *make_valgrind_menu ;
 
 
  GtkWidget *make_sphinx_menu ;

  GtkWidget *make_sphinx_show_menu ;

  GtkWidget *terminals_menubutton ;

  GtkWidget *terminal_make ;

  GtkWidget *terminal_edit ;



  GtkWidget *make_menubutton ;


  GtkWidget *configure_menubutton ;

  GtkWidget *configuration ;


  GtkWidget *user_info_menubutton ;

  GtkWidget *user_info_doc ;

  GtkWidget *user_info_about ;


} Menu ;

typedef struct {

  /** Main GUI structure **/

  GtkApplication *app ;

  GtkWidget *window ; /** Main window **/

  GtkWidget *main_vbox ;   /** Main container **/



  GtkWidget *make_notebook_vbox ;

  GtkWidget *make_notebook_status_bar ;

  GtkWidget *make_notebook ;

  GtkWidget *main_notebook ;

  GtkWidget *terminal_notebook ;


  GtkWidget *make_terminal ;

  Menu *menu ;  /** Menu structure **/


} GUI ;

#endif
