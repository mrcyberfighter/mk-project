#include "./fmt_files.h"

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

static void use_license_files(const gchar *prefix, const gchar *path_to_license, Project *project) ;

static GError *errors = NULL ;

void fmt_makefile_doc(const char *input_file, char *output_file) {

  /** Format documentation generator Makefile **/

  gchar *tmpl = NULL ;

  gsize size = 0 ;

  GError *error = NULL ;

  g_file_get_contents(input_file, &tmpl, &size, &error) ;

  // Error check
  if (error != NULL) {

    #ifdef DEBUG
    fprintf(stderr, "Failed to open template file\n%s\n", error->message) ;
    #endif

    g_error_free(error) ;

    return ;
  }

  error = NULL ;
                      


  gchar *output = g_strdup_printf( (const gchar *) tmpl, (project->use_sphinx)  ? "T" : "F") ;



 g_file_set_contents(output_file,
                     output,
                     -1,
                     &error);



 g_free(tmpl) ;

 g_free(output) ;

 g_free(output_file) ;

 return ;

}

void fmt_defines_h(const char *tmpl_file_path, char *output_file) {

  /** Format the defines.h file. **/

  gchar *tmpl ;

  gsize size ;

  g_file_get_contents(tmpl_file_path, &tmpl, &size, &errors) ;

  // Error check
  if (errors != NULL) {

    #ifdef DEBUG
    fprintf(stderr, "Failed to open template file\n%s\n", errors->message) ;
    #endif

    g_clear_error(&errors) ;

    return ;
  }

  // To upper:
  gchar *version_string = g_ascii_strup(project->version_string, -1) ;

  version_string = g_strcanon(version_string,  "1234567890" "ABCDEFGHIJKLMNOPQRSTUVWXYZ", '_') ;

  // To upper:
  gchar *prgname_upper = g_ascii_strup(project->prgname, -1);

  // Formatting inclusion guard:
  prgname_upper = g_strcanon(prgname_upper,"ABCDEFGHIJKLMNOPQRSTUVWXYZ_", '_') ;
           
  // Formatting inclusion guard:
  gchar *prgname_hh_string = g_strconcat(prgname_upper, "_", version_string, NULL) ;

  g_free(version_string) ;

  g_free(prgname_upper) ;


  gchar *output = g_strdup_printf( (const gchar *) tmpl,
                                            prgname_hh_string,
                                            prgname_hh_string,
                                            project->author_s,
                                            project->mail_address,
                                            project->prgname,
                                            project->version_string,
                                            project->license,
                                            project->program_url,
                                            project->copyright_string) ;

  g_file_set_contents(output_file,
                      output,
                      -1,
                      NULL);



  g_free(tmpl) ;

  g_free(prgname_hh_string) ;

  g_free(output) ;

  g_free(output_file) ;

  return ;

}

void fmt_h_guard_only(const char *tmpl_file_path, char *output_file) {

  /** Format inclusion guard only **/

  gchar *tmpl ;

  gsize size ;




  g_file_get_contents(tmpl_file_path, &tmpl, &size, &errors) ;

  // Error check
  if (errors != NULL) {

    #ifdef DEBUG
    fprintf(stderr, "Failed to open template file\n%s\n", errors->message) ;
    #endif

    g_clear_error(&errors) ;

    return ;
  }


  // To upper:
  gchar *version_string = g_ascii_strup(project->version_string, -1) ;

  // Allowed characters for a inclusion guard formatting :
  version_string = g_strcanon(version_string,  "1234567890" "ABCDEFGHIJKLMNOPQRSTUVWXYZ", '_') ;

  // To upper:
  gchar *prgname_upper = g_ascii_strup(project->prgname, -1);

  // Formatting inclusion guard:
  prgname_upper = g_strcanon(prgname_upper,"ABCDEFGHIJKLMNOPQRSTUVWXYZ_", '_') ;
           
  // Formatting inclusion guard:
  gchar *prgname_hh_string = g_strconcat(prgname_upper, "_", version_string, NULL) ;

  g_free(version_string) ;

  g_free(prgname_upper) ;

  gchar *output = g_strdup_printf( (const gchar *) tmpl, prgname_hh_string, prgname_hh_string) ;


  g_file_set_contents(output_file,
                      output,
                      -1,
                      NULL);



  g_free(tmpl) ;

  g_free(prgname_hh_string) ;

  g_free(output) ;

  g_free(output_file) ;

  return ;

}

void fmt_global_vars_cxx_hdr(const char *input_file, char *output_file) {

  /** Format global_vars.h C file **/

  gchar *tmpl ;

  gsize size ;



  g_file_get_contents(input_file, &tmpl, &size, &errors) ;

  // Error check
  if (errors != NULL) {

    #ifdef DEBUG
    fprintf(stderr, "Failed to open template file\n%s\n", errors->message) ;
    #endif

    g_clear_error(&errors) ;

    return ;
  }

  // To upper:
  gchar *version_string = g_ascii_strup(project->version_string, -1) ;

  // Allowed characters for a inclusion guard formatting :
  version_string = g_strcanon(version_string,  "1234567890" "ABCDEFGHIJKLMNOPQRSTUVWXYZ", '_') ;

  // To upper:
  gchar *prgname_upper = g_ascii_strup(project->prgname, -1);

  // Formatting inclusion guard:
  prgname_upper = g_strcanon(prgname_upper,"ABCDEFGHIJKLMNOPQRSTUVWXYZ_", '_') ;
           
  // Formatting inclusion guard:
  gchar *prgname_hh_string = g_strconcat(prgname_upper, "_", version_string, NULL) ;

  g_free(version_string) ;

  g_free(prgname_upper) ;


  gchar *output = g_strdup_printf( (const gchar *) tmpl, prgname_hh_string, prgname_hh_string, project->ext_hdr, project->ext_hdr) ;

  g_file_set_contents(output_file,
                      output,
                      -1,
                      NULL);



  g_free(tmpl) ;

  g_free(prgname_hh_string) ;

  g_free(output) ;

  g_free(output_file) ;

  return ;


}

void fmt_global_vars_cxx_src(const char *input_file, char *output_file) {

  /** Format global_vars.h C++ source file **/

  gchar *tmpl ;

  gsize size ;



  g_file_get_contents(input_file, &tmpl, &size, &errors) ;

  // Error check
  if (errors != NULL) {

    #ifdef DEBUG
    fprintf(stderr, "Failed to open template file\n%s\n", errors->message) ;
    #endif

    g_clear_error(&errors) ;

    return ;
  }

  gchar *output = g_strdup_printf( (const gchar *) tmpl, project->ext_hdr) ;

  g_file_set_contents(output_file,
                      output,
                      -1,
                      NULL);



  g_free(tmpl) ;

  g_free(output) ;

  g_free(output_file) ;

  return ;


}

void fmt_main_cxx(const char *input_file, char *output_file) {

  /** Format main file **/

  gchar *tmpl ;

  gsize size ;



  g_file_get_contents(input_file, &tmpl, &size, &errors) ;

  // Error check
  if (errors != NULL) {

    #ifdef DEBUG
    fprintf(stderr, "Failed to open template file\n%s\n", errors->message) ;
    #endif

    g_clear_error(&errors) ;

    return ;
  }

  gchar *output = g_strdup_printf( (const gchar *) tmpl, project->ext_hdr, project->ext_hdr, project->ext_hdr) ;

  g_file_set_contents(output_file,
                      output,
                      -1,
                      NULL);



  g_free(tmpl) ;

  g_free(output) ;

  g_free(output_file) ;

  return ;


}


void fmt_makefile(const char *input_file, char *output_file) {

  /** Format main Makefile **/

  gchar *tmpl ;

  gsize size ;



  g_file_get_contents(input_file, &tmpl, &size, &errors) ;

  // Error check
  if (errors != NULL) {

    #ifdef DEBUG
    fprintf(stderr, "Failed to open template file\n%s\n", errors->message) ;
    #endif

    g_clear_error(&errors) ;

    return ;
  }  

  gchar *make_library_target_name = g_strdup_printf("\t@echo\n\t@echo \"make lib%s # Build a program static library.\"\n\t@echo", project->prgname) ;

  gchar *output = g_strdup_printf( (const gchar *) tmpl,
                                            project->make_options,
                                            project->bash_location,
                                            project->language,
                                            project->ext_src,
                                            project->ext_hdr,
                                            (! g_strcmp0(project->compiler, "cc")) ? "$(CC)" : (! g_strcmp0(project->compiler, "c++")) ? "$(CXX)" : project->compiler,
                                            project->warnings,
                                            project->cflags,
                                            project->cppflags,
                                            project->ldflags,
                                            project->ldlibs,
                                            (project->program_library) ? "T" : "F",
                                            project->prgname,
                                            project->version_string,
                                            project->ext_src,
                                            project->ext_src,
                                            project->ext_hdr,
                                            project->ext_hdr,
                                            project->ext_hdr,
                                            project->gdb_options,
                                            project->operf_options,
                                            project->ocount_options,
                                            project->opreport_options,
                                            project->opannotate_options,
                                            project->opgprof_options,
                                            project->valgrind_memcheck,
                                            project->valgrind_cachegrind,
                                            project->valgrind_callgrind,
                                            project->valgrind_helgrind,
                                            project->gprof_options,
                                            project->strace_options,
                                            project->ltrace_options,
                                            project->nm_options,
                                            project->objdump_options,
                                            project->ldd_options,
                                            ((project->program_library) ? make_library_target_name : "\t@echo")
                                            ) ;





  g_free(make_library_target_name) ;

  g_free(tmpl) ;

  g_file_set_contents(output_file,
                     output,
                     -1,
                     &errors);



  if (errors != NULL) {

    display_message_dialog( _("Error setting file content !"), errors->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_clear_error(&errors) ;

  }

  g_free(output) ;

  g_free(output_file) ;

  return ;

}



void fmt_lib_makefile(const char *input_file, char *output_file) {

  /** Format program library Makefile  **/

  gchar *tmpl ;

  gsize size ;



  g_file_get_contents(input_file, &tmpl, &size, &errors) ;

  // Error check
  if (errors != NULL) {

    #ifdef DEBUG
    fprintf(stderr, "Failed to open template file\n%s\n", errors->message) ;
    #endif

    g_clear_error(&errors) ;

    return ;
  }

  gchar *libname = g_strconcat("lib", project->prgname, NULL) ;

  gchar *output = g_strdup_printf( (const gchar *) tmpl,
                                    project->make_options,
                                    project->bash_location,
                                    project->language,
                                    project->ext_src,
                                    project->ext_hdr,
                                    (! g_strcmp0(project->compiler, "cc")) ? "$(CC)" : (! g_strcmp0(project->compiler, "c++")) ? "$(CXX)" : project->compiler,
                                    project->warnings,
                                    project->cflags,
                                    project->cppflags,
                                    project->ldflags,
                                    project->ldlibs,
                                    libname
                                    ) ;




  g_free(libname) ;

  g_free(tmpl) ;

  g_file_set_contents(output_file,
                     output,
                     -1,
                     &errors);


  if (errors != NULL) {

    display_message_dialog( _("Error setting file content !"), g_strdup(errors->message), GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_clear_error(&errors) ;

  }

  g_free(output) ;

  g_free(output_file) ;

  return ;

}



void fmt_makefile_code_fmt(const char *input_file, char *output_file) {

  /** Format C/C++ code formatter Makefile **/

  gchar *tmpl ;

  gsize size ;



  g_file_get_contents(input_file, &tmpl, &size, &errors) ;

  // Error check
  if (errors != NULL) {

    #ifdef DEBUG
    fprintf(stderr, "Failed to open template file\n%s\n", errors->message) ;
    #endif

    g_clear_error(&errors) ;

    return ;
  }


           


  gchar *output = g_strdup_printf( (const gchar *) tmpl,
                                            (project->use_indent) ? "T" : "F",
                                            (project->use_astyle) ? "T" : "F",
                                            (project->use_bcpp)   ? "T" : "F",
                                            (project->use_tabs)   ? "T" : "F",
                                            project->indentation_width,
                                            project->indent_options,
                                            project->astyle_options
                                            ) ;



 g_free(tmpl) ;

 g_file_set_contents(output_file, output, -1, NULL);



 g_free(output) ;

 g_free(output_file) ;

 return ;

}

void fmt_makefile_dist(const char *input_file, char *output_file) {

  /** Format distributing Makefile **/

  gchar *tmpl ;

  gsize size ;

  g_file_get_contents(input_file, &tmpl, &size, &errors) ;

  // Error check
  if (errors != NULL) {

    #ifdef DEBUG
    fprintf(stderr, "Failed to open template file\n%s\n", errors->message) ;
    #endif

    g_clear_error(&errors) ;

    return ;
  }

  gchar *output = g_strdup_printf((const gchar *) tmpl, project->compression_level) ;



  g_free(tmpl) ;

  g_file_set_contents(output_file,
                      output,
                      -1,
                      NULL);



  g_free(output) ;

  g_free(output_file) ;

  return ;

}


void copy_file(const gchar *src_file_ptr, const gchar *dst_file_ptr) {

  GFile *src_file = g_file_new_for_path(src_file_ptr) ;
  GFile *dst_file = g_file_new_for_path(dst_file_ptr) ;

  g_file_copy(src_file,
              dst_file,
              G_FILE_COPY_ALL_METADATA | G_FILE_COPY_TARGET_DEFAULT_PERMS,
              NULL,
              NULL,
              NULL,
              NULL);
    
  g_object_unref(src_file) ;
  g_object_unref(dst_file) ;

  return ;

}


void create_file(char *dirpath, const char *file_content, char *output_file) {

  /** Create a file and parent folders **/

  g_mkdir_with_parents(dirpath, 0755) ;

  char *curdir = g_get_current_dir() ;

  g_chdir(dirpath) ;

  gchar *file_content_n ;

  if (file_content[strlen(file_content)-1] != '\n') {

    file_content_n = g_strdup_printf("%s\n",file_content) ;
  }
  else {

    file_content_n = g_strdup(file_content) ;
  }

  g_file_set_contents(output_file,
                      file_content_n,
                      strlen(file_content_n),
                      NULL) ;

  g_free(file_content_n) ;

  g_chdir(curdir) ;

  g_free(curdir) ;

  g_free(dirpath) ;

  g_free(output_file) ;

  return ;

}

void write_content_to_file(gchar *filepath, const gchar *content) {

  /** Write the content to file (UTF-8 formatted) **/



  g_file_set_contents(filepath,
                      content,
                      strlen(content),
                      &errors) ;

  // Error check
  if (errors != NULL) {

    #ifdef DEBUG
    fprintf(stderr,"Error setting file content:\n%s\n", errors->message) ;
    #endif

    g_clear_error(&errors) ;

  }

  g_free(filepath) ;

  return ;
}

char *get_file_content(const char *filepath) {

  /** Return file content (UTF-8 formatted). **/

  if ( ! g_file_test(filepath, G_FILE_TEST_EXISTS) ) {

    return NULL ;

  }

  gchar *file_content ;

  gsize size ;

  g_file_get_contents(filepath, &file_content, &size, &errors) ;

  // Error check
  if (errors != NULL) {

    fprintf(stderr, "Failed to open file\n%s\n", errors->message) ;
  
    g_clear_error(&errors) ;
  
    return NULL ;
  }

  return file_content ;

}



void creat_dir_p_and_files(char *dirpath, char *filenames[]) {

  /** Create files with parents folders **/

  g_mkdir_with_parents(dirpath, 0755) ;

  if (filenames != NULL) {

    int c = 0 ;

    char *curdir = g_get_current_dir() ;

    g_chdir(dirpath) ;

    while (filenames[c] != NULL) {

      int fd = g_creat(filenames[c], S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) ;

      g_close(fd, NULL) ;

      g_free(filenames[c]) ;

      ++c ;
    }

    g_chdir(curdir) ;

    g_free(curdir) ;

  }

  g_free(dirpath) ;

  return ;

}

static void use_license_files(const gchar *prefix, const gchar *path_to_license, Project *pproject) {


  /** Copy licensing file(s) according to the user format(s) choice(s). **/

  gchar *tmp = g_strdup(pproject->license) ;

  tmp = g_strdelimit(tmp, " ", '_') ;

  if (pproject->use_licensing_dkb_format) {

    gchar *license_file = g_strdup_printf("%s/%s.dbk", prefix, tmp) ;

    gchar *license_dbk_file = g_strdup_printf("%s/%s.dbk", path_to_license, tmp) ;

    copy_file(license_file, license_dbk_file) ;

    g_free(license_dbk_file) ;

    g_free(license_file) ;

  }
  if (pproject->use_licensing_epub_format) {

    gchar *license_file = g_strdup_printf("%s/%s.epub", prefix, tmp) ;

    gchar *license_epub_file = g_strdup_printf("%s/%s.epub", path_to_license, tmp) ;

    copy_file(license_file, license_epub_file) ;

    g_free(license_epub_file) ;

    g_free(license_file) ;
  }
  if (pproject->use_licensing_pdf_format) {

    gchar *license_file = g_strdup_printf("%s/%s.pdf", prefix, tmp) ;

    gchar *license_pdf_file = g_strdup_printf("%s/%s.pdf", path_to_license, tmp) ;

    copy_file(license_file, license_pdf_file) ;

    g_free(license_pdf_file) ;

    g_free(license_file) ;
  }
  if (pproject->use_licensing_html_format) {

    gchar *license_file = g_strdup_printf("%s/%s.html", prefix, tmp) ;

    gchar *license_html_file = g_strdup_printf("%s/%s.html", path_to_license, tmp) ;

    copy_file(license_file, license_html_file) ;

    g_free(license_html_file) ;

    g_free(license_file) ;
  }
  if (pproject->use_licensing_latex_format) {

    gchar *license_file = g_strdup_printf("%s/%s.tex", prefix, tmp) ;

    gchar *license_latex_file = g_strdup_printf("%s/%s.tex", path_to_license, tmp) ;

    copy_file(license_file, license_latex_file) ;

    g_free(license_latex_file) ;

    g_free(license_file) ;
  }
  if (pproject->use_licensing_texinfo_format) {

    gchar *license_file = g_strdup_printf("%s/%s.texi", prefix, tmp) ;

    gchar *license_texinfo_file = g_strdup_printf("%s/%s.tex", path_to_license, tmp) ;

    copy_file(license_file, license_texinfo_file) ;

    g_free(license_texinfo_file) ;

    g_free(license_file) ;
  }
  if (pproject->use_licensing_text_format) {

    gchar *license_file = g_strdup_printf("%s/%s.txt", prefix, tmp) ;

    gchar *license_text_file = g_strdup_printf("%s/%s.txt", path_to_license, tmp) ;

    copy_file(license_file, license_text_file) ;

    g_free(license_text_file) ;

    g_free(license_file) ;
  }

  g_free(tmp) ;

  return ;

}

void add_license(Project *pproject) {

  gchar *path_to_license = g_strconcat(pproject->project_folderpath, "/LICENSE", NULL) ;

  if (! g_strcmp0(pproject->license, "gpl")) {

    use_license_files(PATH_TO_LICENSE_FOLDER_GPL, path_to_license, pproject) ;
  }
  else if (! g_strcmp0(pproject->license, "agpl")) {

    use_license_files(PATH_TO_LICENSE_FOLDER_AGPL, path_to_license, pproject) ;
  }
  else if (! g_strcmp0(pproject->license, "lgpl")) {

    use_license_files(PATH_TO_LICENSE_FOLDER_LGPL, path_to_license, pproject) ;
  }
  else if (! g_strcmp0(pproject->license, "fdl")) {

    use_license_files(PATH_TO_LICENSE_FOLDER_FDL, path_to_license, pproject) ;
  }
  else if (! g_strcmp0(pproject->license, "Apache 2.0")) {

    use_license_files(PATH_TO_LICENSE_FOLDER_APACHE_2_0, path_to_license, pproject) ;
  }
  else if (! g_strcmp0(pproject->license, "Clear BSD")) {

    use_license_files(PATH_TO_LICENSE_FOLDER_CLEAR_BSD, path_to_license, pproject) ;
  }
  else if (! g_strcmp0(pproject->license, "Free BSD")) {

    use_license_files(PATH_TO_LICENSE_FOLDER_FREE_BSD, path_to_license, pproject) ;
  }
  else if (! g_strcmp0(pproject->license, _("Other")) ) {

    // FIXME: We must @not provide so many licenses to the user
    // because the user is great enough if he want some others licenses ;

  }

  g_free(path_to_license) ;

  return ;

}

