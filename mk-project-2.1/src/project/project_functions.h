#ifndef MK_PROJECT_ASSISTANT_FUNCTIONS_HH
#define MK_PROJECT_ASSISTANT_FUNCTIONS_HH

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

#include "../headers/includes.h"

#include "../headers/defines.h"
#include "../headers/structures/Project_structure.h"

#include "../GUI/message_dialog.h"

#include "../GUI/GtkSmartIconButton.h"

#include "../make/make_utils.h"

/** On realize page: in this case when the page is displayed. ***/
extern void on_realize_widget(GtkWidget *widget, gpointer   user_data) ;

extern void get_spinbutton_value_indentation(GtkSpinButton *spinbutton, int *user_data) ;

extern void get_scale_value_compression_level(GtkRange *range, int *user_data) ;

extern void get_checkbutton_value(GtkToggleButton *togglebutton, bool *user_data) ;

extern void get_combo_value(GtkComboBox *widget, gchar *user_data) ;

extern gboolean get_entry_value_project_version_string(GtkWidget *widget, GdkEvent  *event, char *user_data) ;

extern void insert_data(gpointer data, gpointer widget) ;

extern char *have_app_application(const char *application) ;

extern void get_sphinx_extension(GtkWidget *container) ;

/** Updating functions **/

extern void update_compiler(GList *children, Project *project) ;

extern void update_c_project(GList *children, Project *project) ;

extern void update_python_project(GList *children, Project *project) ;

extern void update_licensing(GList *children, Project *project) ;

/** Getters functions **/

extern void get_compiler_datas(GList *children, Project *project) ;

extern void get_disassembling_opts(GList *children, Project *project) ;

extern void get_oprofile_opts(GList *children, Project *project) ;

extern void get_valgrind_opts(GList *children, Project *project) ;

extern void get_code_fmt_opts(GList *children, Project *project) ;

extern void get_about_infos(GList *children, Project *project) ;

extern void get_other_infos(GList *children, Project *project) ;

extern void get_python_project_infos(GList *children, Project *project) ;

extern void get_licensing_boilerplate(GList *content, Project *project) ;

extern void get_desktop_file_boilerplate(GList *content, Project *project) ;

/** Widgets creation functions **/

extern GtkWidget *create_button(const gchar *filepath, const gchar *tooltip_text) ;

extern GtkWidget *create_checkbox(const gchar *text, const gchar *tooltip_text, const gboolean checked) ;


/** Buttons callback **/

extern void select_warnings(GtkWidget *widget, GtkWidget *window) ;

extern void add_cppflags(GtkWidget *widget, GtkWidget *entry) ;

extern void select_flags(GtkWidget *widget, GtkWidget *window) ;

extern void add_pkg_config_to_project(GtkWidget *button, libraries_entries *entries) ;

extern void add_linkage_to_project(GtkWidget *button, GtkWidget *entry) ;

/** Buttons callbacks helper: dynamic linker listers **/

extern GList* get_pkg_config_list(void) ;

extern GList* get_linkage_list(void) ;

/** Documentation functions **/

extern void generate_sphinx_doc(gchar *main_mk_filepath) ;

#endif
