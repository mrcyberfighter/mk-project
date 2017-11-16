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

#ifndef MK_PROJECT_SETTINGS_STRUCTURE_HH
#define MK_PROJECT_SETTINGS_STRUCTURE_HH

typedef struct {

  /** Terminal settings: **/

   gdouble font_scale ;

   gchar *term_font      ;

   gchar  *user_shell    ;

   gchar  *start_dir     ;

   gchar *term_bg        ;

   gchar *term_fg        ;

   gchar *bold_color ;

   gchar *emulation ;

   gchar *encoding  ;

   gchar *command ;

   gchar *cursor_color ;
 
   gint  scrollback_lines ; // -1 unlimited.

   gint backspace_binding ;

   gint delete_binding ;

   gint cursor_blink ;
 
   gboolean scroll_on_output ; // disable per default.

   gboolean scroll_on_keystroke ;

   gboolean bold_allow ;

   gboolean pointer_autohide ;

   gboolean audible_bell ;

   gint cursor_shape : 3 ;

} Settings ;

#endif
