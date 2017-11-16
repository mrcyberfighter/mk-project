#ifndef MK_PROJECT_FMT_FILES_HH
#define MK_PROJECT_FMT_FILES_HH

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

#include "../headers/defines.h"
#include "../headers/includes.h"

#include "../GUI/message_dialog.h"

#include "../global_vars.h"

extern void fmt_defines_h(const char *tmpl_file_path, char *output_file) ;

extern void fmt_h_guard_only(const char *tmpl_file_path, char *output_file) ;


extern void write_content_to_file(gchar *filepath, const gchar *content) ;

extern char *get_file_content(const char *filepath) ;

extern void copy_file(const gchar *src_file_ptr, const gchar *dst_file_ptr) ;

extern void fmt_global_vars_cxx_hdr(const char *input_file, char *output_file) ;

extern void fmt_global_vars_cxx_src(const char *input_file, char *output_file) ;

extern void fmt_main_cxx(const char *input_file, char *output_file) ;

extern void fmt_makefile(const char *input_file, char *output_file) ;

extern void fmt_lib_makefile(const char *input_file, char *output_file) ;

extern void fmt_makefile_code_fmt(const char *input_file, char *output_file) ;

extern void fmt_makefile_dist(const char *input_file, char *output_file) ;

extern void fmt_makefile_doc(const char *input_file, char *output_file) ;

extern void create_file(char *dirpath, const char *file_content, char *output_file) ;

extern void creat_dir_p_and_files(char *dirpath, char *filenames[]) ;

/** **/

extern void add_license(Project *project) ;

#endif
