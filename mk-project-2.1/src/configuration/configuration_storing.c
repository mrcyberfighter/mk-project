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

#include "./configuration_storing.h"

static void apply_configuration_change(GKeyFile *conf_file) {

  /** Apply configuration changes to structure **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  g_key_file_set_value(conf_file,   "Terminal", "font",                   settings.term_font);
  g_key_file_set_double(conf_file,  "Terminal", "font_scale",             settings.font_scale);
  g_key_file_set_integer(conf_file, "Terminal", "cursor_shape",           settings.cursor_shape);
  g_key_file_set_value(conf_file,   "Terminal", "background",             settings.term_bg) ;
  g_key_file_set_value(conf_file,   "Terminal", "foreground",             settings.term_fg) ;
  g_key_file_set_value(conf_file,   "Terminal", "user_shell",             settings.user_shell)  ;
  g_key_file_set_value(conf_file,   "Terminal", "start_dir",              settings.start_dir)  ;
  g_key_file_set_integer(conf_file, "Terminal", "cursor_blink",           settings.cursor_blink) ;
  g_key_file_set_integer(conf_file, "Terminal", "scrollback_lines",       settings.scrollback_lines) ;
  g_key_file_set_boolean(conf_file, "Terminal", "scroll_on_output",       settings.scroll_on_output) ;
  g_key_file_set_boolean(conf_file, "Terminal", "scroll_on_keystroke",    settings.scroll_on_keystroke) ;
  g_key_file_set_boolean(conf_file, "Terminal", "pointer_autohide",       settings.pointer_autohide) ;
  g_key_file_set_boolean(conf_file, "Terminal", "audible_bell",           settings.audible_bell) ;
  g_key_file_set_boolean(conf_file, "Terminal", "bold_allow",             settings.bold_allow) ;
  g_key_file_set_integer(conf_file, "Terminal", "backspace_binding",      settings.backspace_binding) ;

  g_key_file_set_integer(conf_file, "Terminal", "delete_binding",         settings.delete_binding) ;
  g_key_file_set_string(conf_file,  "Terminal", "command",                settings.command) ;
  g_key_file_set_string(conf_file,  "Terminal", "cursor_color",           settings.cursor_color)  ;
  g_key_file_set_string(conf_file,  "Terminal", "bold_color",             settings.bold_color)  ;

  return ;

}

void write_changes_to_conf_file(void) {

  /** Write all settings to configuration file. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif



  GKeyFile *conf_file = g_key_file_new() ;

  GError *error = NULL ;

  g_key_file_load_from_file(conf_file, PATH_TO_CONF_FILE, G_KEY_FILE_NONE, &error) ;

  if (error != NULL) {

    char *msg = g_strdup_printf( _("Configuration file error:\n%s\n%s"), g_path_get_basename(PATH_TO_CONF_FILE), error->message) ;

    display_message_dialog(_("Error configuration !"), msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    free(msg) ;

    g_error_free(error) ;

    return ;

  }

  error= NULL ;


  apply_configuration_change(conf_file) ;

  g_key_file_save_to_file(conf_file, PATH_TO_CONF_FILE, &error);

  if (error != NULL) {

    char *msg = g_strdup_printf( _("Cannot save conf file:\n%s\n") ,error->message) ;

    display_message_dialog( _("Error configuration !"), msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    free(msg) ;

    g_error_free(error) ;
  }

  error= NULL ;

  g_key_file_unref(conf_file) ;

  return ;

}

void set_default_settings_main_conf(void) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** Terminal settings **/
  settings.term_font            = g_strdup("Monospace 11") ;
  settings.font_scale           = 1.0   ;
  settings.term_bg              = g_strdup("#000000") ;
  settings.term_fg              = g_strdup("#FFFFFF") ;

  settings.user_shell           = g_strdup(vte_get_user_shell()) ;
  settings.start_dir            = g_strdup(g_get_home_dir()) ;
  settings.cursor_shape         =  0 ;
  settings.scrollback_lines     = -1 ;
  settings.scroll_on_output     = TRUE ;

  settings.scroll_on_keystroke  = FALSE ;
  settings.backspace_binding    = 0     ;
  settings.delete_binding       = 0     ;
  settings.command              = g_strdup("") ;

  settings.cursor_color         = g_strdup("#FFFFFF") ;
  settings.cursor_blink         = 0 ;

  settings.bold_allow           = TRUE ;
  settings.bold_color           = g_strdup("#FFFFFF") ;

  settings.pointer_autohide     = FALSE ;

  settings.audible_bell         = TRUE ;

  GKeyFile *conf_file = g_key_file_new() ;

  GError *error = NULL ;

  apply_configuration_change(conf_file) ;

  g_key_file_save_to_file(conf_file, PATH_TO_CONF_FILE, &error);

  if (error != NULL) {

    char *msg = g_strdup_printf( _("Cannot save conf file:\n%s\n"),error->message) ;

    display_message_dialog( _("Error configuration !"), msg, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    free(msg) ;

    g_error_free(error) ;
  }

  error= NULL ;

  g_key_file_unref(conf_file) ;

  return ;

}

void get_main_configuration(void) {

  /** Read configuration file if available else set to default. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  /** Programm configuration file. **/
  GKeyFile *conf_file = g_key_file_new() ;
  GError *err = NULL ;
  g_key_file_load_from_file(conf_file, PATH_TO_CONF_FILE, G_KEY_FILE_NONE, &err) ;

  if (err != NULL) {
    set_default_settings_main_conf() ;
    g_error_free(err)  ;
    return ;
  }





  /** Read the configuration file:  getting strings values: **/
  settings.term_font        = g_key_file_get_string(conf_file, "Terminal", "font",              NULL)  ;
  settings.term_bg          = g_key_file_get_string(conf_file, "Terminal", "background",        NULL)  ;
  settings.term_fg          = g_key_file_get_string(conf_file, "Terminal", "foreground",        NULL)  ;
  settings.user_shell       = g_key_file_get_string(conf_file, "Terminal", "user_shell",        NULL)  ;
  settings.start_dir        = g_key_file_get_string(conf_file, "Terminal", "start_dir",         NULL)  ;
  settings.command          = g_key_file_get_string(conf_file, "Terminal", "command",           NULL)  ;
  settings.cursor_color     = g_key_file_get_string(conf_file, "Terminal", "cursor_color",      NULL)  ;
  settings.bold_color       = g_key_file_get_string(conf_file, "Terminal", "bold_color",        NULL)  ;

  /** Read the configuration file: getting boolean or integer values. **/

  settings.cursor_shape           = g_key_file_get_integer(conf_file, "Terminal", "cursor_shape",         NULL) ;
  settings.cursor_blink           = g_key_file_get_integer(conf_file, "Terminal", "cursor_blink",         NULL) ;
  settings.scrollback_lines       = g_key_file_get_integer(conf_file, "Terminal", "scrollback_lines",     NULL) ;
  settings.backspace_binding      = g_key_file_get_integer(conf_file, "Terminal", "backspace_binding",    NULL) ;
  settings.delete_binding         = g_key_file_get_integer(conf_file, "Terminal", "delete_binding",       NULL) ;
  settings.scroll_on_output       = g_key_file_get_boolean(conf_file, "Terminal", "scroll_on_output",     NULL) ;
  settings.scroll_on_keystroke    = g_key_file_get_boolean(conf_file, "Terminal", "scroll_on_keystroke",  NULL) ;
  settings.pointer_autohide       = g_key_file_get_boolean(conf_file, "Terminal", "pointer_autohide",     NULL) ;
  settings.audible_bell           = g_key_file_get_boolean(conf_file, "Terminal", "audible_bell",         NULL) ;
  settings.bold_allow             = g_key_file_get_boolean(conf_file, "Terminal", "bold_allow",           NULL) ;

  /** Read the configuration file:  getting double values: **/
  settings.font_scale             = g_key_file_get_double(conf_file,  "Terminal", "font_scale",           NULL);

  g_key_file_unref(conf_file) ;

  return ;
}
