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

#include "./cmdline.h"

bool check_load_project_cmdline(const char *filepath) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (filepath == NULL) {

    return false ;

  }

  gchar *file_basename = g_path_get_basename(filepath) ;

  if (! g_file_test(filepath, G_FILE_TEST_EXISTS)) {

    /** The file doesn't exist !\n **/

    fprintf(stderr,_("\n""The file: %s doesn't exist !""\n"), file_basename) ;

    SEC_FREE(file_basename)

    return false ;
  }

  if (! g_str_has_suffix(filepath, ".mkp")) {

    /** The file is not a mk-project file ! **/

    fprintf(stderr, _("\n""The file: %s is not a mk-project file !""\n""Extension is not *.mkp !""\n"), file_basename) ;

    SEC_FREE(file_basename)

    return false ;

  }

  if (! valid_xml_mk_project(filepath) ) {

    /** The file is not a valid mk-project file ! **/

    fprintf(stderr,_("\n""The file: %s is not a valid mk-project file !""\n"), file_basename) ;

    SEC_FREE(file_basename)

    return false ;

  }

  g_free(file_basename) ;

  return true ;



}
