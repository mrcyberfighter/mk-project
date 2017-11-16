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

#ifndef MK_PROJECT_CMDLINE_HH
#define MK_PROJECT_CMDLINE_HH

#include "../headers/includes.h"

#include "../headers/defines.h"

#include "../project/load_project.h"

#include "../xml_utils/xml_getter.h"

extern bool check_load_project_cmdline(const char *filepath) ;

//extern const bool check_add_file_to_project(const char *filepath, bool *in_project_path, bool *in_source_path) ;

#endif
