#ifndef MK_PROJECT_LOAD_PROJECT_HH
#define MK_PROJECT_LOAD_PROJECT_HH

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

#include "../headers/structures/GUI_structures.h"

#include "../global_vars.h"

#include "../make/make_utils.h"

#include "../xml_utils/xml_getter.h"

extern void load_project_callback(const char *filepath) ;

extern void add_file_to_project_callback(const char *filepath, bool add_header_file, bool file_in_project_path, bool file_into_source_folder) ;

extern bool is_folder_source_reach(const char *filepath) ;

extern bool is_folder_source(const char *filepath) ;

extern bool is_in_project_path(const char *project_folderpath, const char *filepath) ;

extern void remove_trailing_space_from_file(const char *filepath) ;

#endif
