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

#ifndef MK_PROJECT_MAKE_ACTIONS_HH
#define MK_PROJECT_MAKE_ACTIONS_HH

#include "../headers/defines.h"
#include "../headers/includes.h"
#include "../global_vars.h"

#include "../GUI/message_dialog.h"

#include  "../project/fmt_files.h"

extern void get_main_makefile_values(const char *makefile_filepath) ;

extern void get_code_fmt_makefile_values(const char *makefile_filepath) ;

extern void get_dist_makefile_values(const char *makefile_filepath) ;

extern void set_main_makefile_values(const char *filepath) ;

extern void set_code_fmt_makefile_values(const char *filepath) ;

extern void set_dist_makefile_values(const char *filepath) ;

extern char *exec_replacement(const char *pattern, const char *in_text, const char *replacement) ;

extern void insert_new_file_in_makefile(const char *mk_filepath, const char *variable, const char *extension, const char *filepath_to_append) ;

extern void replace_into_file(const char *filepath, const char *pattern_replacement[]) ;

#endif
