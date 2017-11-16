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

#include "./configuration_dialog.h"

static gchar *get_string_from_key_file(GKeyFile *key_file, const gchar *group, const gchar *key) ;

static bool get_bool_from_key_file(GKeyFile *key_file, const gchar *group, const gchar *key) ;

static void check_user_shell(GtkFileChooserButton *chooser, gpointer user_data) {

  /** Check if the user has select a valid shell. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  if (! g_file_test(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser)), G_FILE_TEST_IS_EXECUTABLE) ) {

    display_message_dialog( _("The file is not an executable !"), _("The shell you have chosen isn't an executable !!!") , GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(chooser), settings.user_shell) ;

    return ;
  }

  char *user_shell_test = g_strdup_printf("%s -c ls $HOME", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser)) ) ;

  if (system(user_shell_test) != 0) {

    display_message_dialog( _("Wrong shell !"), _("The file you have chosen seems not to be a valid shell."), GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(chooser), settings.user_shell) ;

    free(user_shell_test) ;

    return ;

  }

  free(user_shell_test) ;

  return ;
}

static void is_a_new_color_choosen(GtkColorButton *widget, bool *confirm) {

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  *confirm = true ;

  return ;

}


void display_configuration_dialog(GtkWidget *widget, gpointer user_data) {

  /** Generate the application configuration dialog window and register changes if some. **/

  #ifdef DEBUG
    DEBUG_FUNC_MARK
  #endif

  GtkWidget *configuration_dialog = gtk_dialog_new_with_buttons( _("Configure program"),
                                                                GTK_WINDOW(gui->window),
                                                                GTK_DIALOG_USE_HEADER_BAR | GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT ,
                                                                _("Apply settings"), GTK_RESPONSE_APPLY,
                                                                _("Cancel"), GTK_RESPONSE_CANCEL,
                                                                NULL);




  gtk_window_set_transient_for(GTK_WINDOW(configuration_dialog), GTK_WINDOW(gui->window)) ;

  gtk_window_set_resizable(GTK_WINDOW(configuration_dialog), FALSE) ;

  GtkWidget *configuration_dialog_content = gtk_dialog_get_content_area(GTK_DIALOG(configuration_dialog));

  GtkWidget *notebook_configuration = gtk_notebook_new() ;

  gtk_notebook_set_scrollable(GTK_NOTEBOOK(notebook_configuration), TRUE);

  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook_configuration), FALSE) ;


  GtkWidget *terminal_appearance_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_box_set_spacing(GTK_BOX(terminal_appearance_vbox), 5) ;



  GtkWidget *terminal_settings_notebook         = gtk_notebook_new() ;

  GtkWidget *terminal_font_colors_frame         = gtk_frame_new( _("Font settings") ) ;

  GtkWidget *terminal_font_scale_frame          = gtk_frame_new( _("Font scale") ) ;

  GtkWidget *terminal_cursor_frame              = gtk_frame_new( _("Cursor settings") ) ;

  GtkWidget *terminal_colors_frame              = gtk_frame_new( _("Colors settings") ) ;

  GtkWidget *terminal_bold_frame                = gtk_frame_new( _("Bold settings") ) ;

  GtkWidget *terminal_pointer_autohide           = gtk_frame_new( _("Pointer autohide") ) ;


  gtk_container_set_border_width(GTK_CONTAINER(terminal_font_colors_frame),       5) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_font_scale_frame),        5) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_cursor_frame),            5) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_colors_frame),            5) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_bold_frame),              5) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_pointer_autohide),        5) ;

  GtkWidget *terminal_font_colors_button = gtk_font_button_new_with_font(settings.term_font) ;


  g_object_set(G_OBJECT(terminal_font_colors_button), "margin", 5, NULL) ;

  gtk_font_button_set_show_style(GTK_FONT_BUTTON(terminal_font_colors_button),  TRUE) ;
  gtk_font_button_set_show_size(GTK_FONT_BUTTON(terminal_font_colors_button),   TRUE) ;
  gtk_font_button_set_use_font(GTK_FONT_BUTTON(terminal_font_colors_button),    TRUE) ;
  gtk_font_button_set_use_size(GTK_FONT_BUTTON(terminal_font_colors_button),    TRUE) ;


  gtk_container_add(GTK_CONTAINER(terminal_font_colors_frame), terminal_font_colors_button) ;

  gtk_container_set_border_width(GTK_CONTAINER(terminal_font_colors_button), 5) ;




  GtkWidget *terminal_font_scale_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;
  GtkWidget *terminal_font_scale_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *terminal_font_scale_label = gtk_label_new( _("  Font scale  ") ) ;

  GtkWidget *terminal_font_scale_spinbutton = gtk_spin_button_new_with_range(0.25, 4.0, 0.01) ;

  gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(terminal_font_scale_spinbutton), TRUE) ;

  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(terminal_font_scale_spinbutton), 2) ;

  gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(terminal_font_scale_spinbutton), GTK_UPDATE_IF_VALID) ;

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(terminal_font_scale_spinbutton), settings.font_scale) ;


  gtk_container_set_border_width(GTK_CONTAINER(terminal_font_scale_hbox), 5) ;

  gtk_box_pack_start(GTK_BOX(terminal_font_scale_hbox), terminal_font_scale_label,        FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_font_scale_hbox), gtk_label_new(""),                TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(terminal_font_scale_hbox), terminal_font_scale_spinbutton,   FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_font_scale_vbox), terminal_font_scale_hbox, FALSE, FALSE, 0) ;

  gtk_container_add(GTK_CONTAINER(terminal_font_scale_frame), terminal_font_scale_vbox) ;



  GtkWidget *terminal_cursor_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;


  GtkWidget *terminal_cursor_shape_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;


  GtkWidget *cursor_shape_block_radiobutton     = gtk_radio_button_new_with_label(NULL, _("BLOCK") );

  GtkWidget *cursor_shape_ibeam_radiobutton     = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(cursor_shape_block_radiobutton), _("IBEAM") ) ;

  GtkWidget *cursor_shape_underline_radiobutton = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(cursor_shape_block_radiobutton), _("UNDERLINE") ) ;

  switch (settings.cursor_shape) {

    case 0 :
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cursor_shape_block_radiobutton), TRUE );
      break ;

    case 1 :

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cursor_shape_ibeam_radiobutton), TRUE );
      break ;

    case 2 :

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cursor_shape_underline_radiobutton), TRUE );
      break ;
  }

  gtk_box_set_homogeneous(GTK_BOX(terminal_cursor_shape_hbox), TRUE) ;

  gtk_container_set_border_width(GTK_CONTAINER(terminal_cursor_shape_hbox), 5) ;

  gtk_box_pack_start(GTK_BOX(terminal_cursor_shape_hbox), cursor_shape_block_radiobutton,          FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_cursor_shape_hbox), cursor_shape_ibeam_radiobutton,          FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_cursor_shape_hbox), cursor_shape_underline_radiobutton,      FALSE, FALSE, 0) ;


  gtk_box_pack_start(GTK_BOX(terminal_cursor_vbox), terminal_cursor_shape_hbox, FALSE, FALSE, 0) ;







  GtkWidget *terminal_cursor_color_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *terminal_cursor_color_label  = gtk_label_new( _("  Cursor color  ") ) ;

  GdkRGBA cursor_color ;
  if (! gdk_rgba_parse(&cursor_color, settings.cursor_color)) {

    g_warning("Error getting cursor color !\n") ;
  }

  GtkWidget *terminal_cursor_color_button = gtk_color_button_new_with_rgba(&cursor_color) ;

  bool *cursor_color_activated = malloc(sizeof(bool)) ;

  *cursor_color_activated = false ;

  g_signal_connect(G_OBJECT(terminal_cursor_color_button), "color-set", G_CALLBACK(is_a_new_color_choosen), cursor_color_activated) ;

  gtk_container_set_border_width(GTK_CONTAINER(terminal_cursor_color_hbox), 5) ;

  gtk_box_pack_start(GTK_BOX(terminal_cursor_color_hbox), terminal_cursor_color_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_cursor_color_hbox), gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0),  TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_cursor_color_hbox), terminal_cursor_color_button, FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_cursor_vbox), terminal_cursor_color_hbox, FALSE, FALSE, 0) ;





  GtkWidget *terminal_cursor_blinking_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *terminal_cursor_blinking_label = gtk_label_new( _("  Cursor blink mode  ") ) ;

  GtkWidget *terminal_cursor_blinking_combo = gtk_combo_box_text_new() ;

  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(terminal_cursor_blinking_combo), 0, "BLINK SYSTEM" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(terminal_cursor_blinking_combo), 1, "BLINK ON"     ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(terminal_cursor_blinking_combo), 2, "BLINK OFF"    ) ;

  gtk_combo_box_set_active(GTK_COMBO_BOX(terminal_cursor_blinking_combo), settings.cursor_blink) ;

  gtk_container_set_border_width(GTK_CONTAINER(terminal_cursor_blinking_hbox), 5) ;

  gtk_box_pack_start(GTK_BOX(terminal_cursor_blinking_hbox), terminal_cursor_blinking_label,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_cursor_blinking_hbox), gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0),  TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_cursor_blinking_hbox), terminal_cursor_blinking_combo, FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_cursor_vbox), terminal_cursor_blinking_hbox, FALSE, FALSE, 0) ;



  gtk_container_add(GTK_CONTAINER(terminal_cursor_frame), terminal_cursor_vbox) ;




  GtkWidget *terminal_bold_vbox        = gtk_box_new(GTK_ORIENTATION_VERTICAL,    5) ;
  GtkWidget *terminal_bold_color_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,  5) ;

  GtkWidget *terminal_bold_allowed_checkbutton = gtk_check_button_new_with_label( _("  Allow bold  ") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(terminal_bold_allowed_checkbutton), (settings.bold_allow) ? TRUE : FALSE ) ;

  GtkWidget *terminal_bold_color_label  = gtk_label_new( _("  Bold color  ") ) ;

  GdkRGBA bold_color ;
  if (! gdk_rgba_parse(&bold_color, settings.bold_color)) {

    g_warning("Error getting bold color !\n") ;

  }

  GtkWidget *terminal_bold_color_button = gtk_color_button_new_with_rgba(&bold_color) ;

  bool *bold_color_activated = malloc(sizeof(bool)) ;

  *bold_color_activated = false ;

  g_signal_connect(G_OBJECT(terminal_bold_color_button), "color-set", G_CALLBACK(is_a_new_color_choosen), bold_color_activated) ;

  gtk_box_pack_start(GTK_BOX(terminal_bold_color_hbox), terminal_bold_allowed_checkbutton,          FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bold_color_hbox), gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0), TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bold_color_hbox), terminal_bold_color_label,                  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bold_color_hbox), gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0), TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bold_color_hbox), terminal_bold_color_button,                 FALSE, FALSE, 0) ;


  gtk_box_pack_start(GTK_BOX(terminal_bold_vbox), terminal_bold_color_hbox,          FALSE, FALSE, 0) ;


  gtk_container_set_border_width(GTK_CONTAINER(terminal_bold_color_hbox), 5) ;

  gtk_container_add(GTK_CONTAINER(terminal_bold_frame), terminal_bold_vbox) ;




  GtkWidget *terminal_pointer_autohide_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *terminal_pointer_autohide_chkbox = gtk_check_button_new_with_label( _("Pointer autohide") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(terminal_pointer_autohide_chkbox), settings.pointer_autohide) ;

  gtk_box_pack_start(GTK_BOX(terminal_pointer_autohide_hbox), terminal_pointer_autohide_chkbox, TRUE, TRUE, 0) ;


  gtk_container_set_border_width(GTK_CONTAINER(terminal_pointer_autohide_chkbox),        5) ;

  gtk_container_add(GTK_CONTAINER(terminal_pointer_autohide), terminal_pointer_autohide_hbox) ;



  GdkRGBA bg_color ;

  if (! gdk_rgba_parse(&bg_color, settings.term_bg)) {

    g_warning("Error getting terminal background color !\n") ;
  }

  GtkWidget *terminal_bg_color_button = gtk_color_button_new_with_rgba(&bg_color) ;

  GdkRGBA fg_color ;

  if (! gdk_rgba_parse(&fg_color, settings.term_fg)) {

    g_warning("Error getting terminal foreground color !\n") ;

  }

  GtkWidget *terminal_fg_color_button = gtk_color_button_new_with_rgba(&fg_color) ;


  GtkWidget *terminal_colors_hbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;

  GtkWidget *terminal_bg_color_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;
  GtkWidget *terminal_fg_color_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *terminal_bg_color_label = gtk_label_new( _("  Background color  ") ) ;
  GtkWidget *terminal_fg_color_label = gtk_label_new( _("  Foreground color  ") ) ;

  gtk_box_pack_start(GTK_BOX(terminal_bg_color_hbox), terminal_bg_color_label,  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bg_color_hbox), terminal_bg_color_button, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bg_color_hbox), terminal_fg_color_label,  TRUE,  TRUE,  0) ;
  gtk_box_pack_start(GTK_BOX(terminal_bg_color_hbox), terminal_fg_color_button, FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_colors_hbox), terminal_bg_color_hbox, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(terminal_colors_hbox), terminal_fg_color_hbox, FALSE, FALSE, 0) ;


  gtk_container_add(GTK_CONTAINER(terminal_colors_frame), terminal_colors_hbox) ;

  gtk_container_set_border_width(GTK_CONTAINER(terminal_colors_hbox), 5) ;


  GtkWidget *terminal_user_shell_frame          = gtk_frame_new( _("User shell") ) ;

  GtkWidget *terminal_start_dir_frame           = gtk_frame_new( _("Start directory") ) ;

  GtkWidget *terminal_audible_bell_frame        = gtk_frame_new( _("Audible bell") ) ;

  GtkWidget *terminal_scrollback_frame          = gtk_frame_new( _("Scrollback lines") ) ;

  GtkWidget *terminal_scrolling_frame           = gtk_frame_new( _("Scrolling") ) ;

  GtkWidget *terminal_erase_binding_frame       = gtk_frame_new( _("Erasing binding") ) ;


  gtk_container_set_border_width(GTK_CONTAINER(terminal_user_shell_frame),         5) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_start_dir_frame),          5) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_audible_bell_frame),       5) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_scrollback_frame),         5) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_scrolling_frame),          5) ;
  gtk_container_set_border_width(GTK_CONTAINER(terminal_erase_binding_frame),      5) ;



  GtkWidget *user_shell_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *user_shell_label = gtk_label_new(     _("User shell                 ") ) ;

  GtkWidget *user_shell_file_chooser_button = gtk_file_chooser_button_new( _("Select the shell you want to use"), GTK_FILE_CHOOSER_ACTION_OPEN) ;

  g_signal_connect(G_OBJECT(user_shell_file_chooser_button), "file-set", G_CALLBACK(check_user_shell), NULL) ;

  gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(user_shell_file_chooser_button), settings.user_shell) ;

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(user_shell_file_chooser_button), PATH_TO_BIN_FOLDER) ;

  gtk_box_pack_start(GTK_BOX(user_shell_hbox), user_shell_label,               FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(user_shell_hbox), user_shell_file_chooser_button, TRUE,  TRUE,  0) ;

  gtk_container_set_border_width(GTK_CONTAINER(user_shell_file_chooser_button),  5) ;

  gtk_container_set_border_width(GTK_CONTAINER(user_shell_hbox),  5) ;

  gtk_box_set_spacing(GTK_BOX(user_shell_hbox), 5) ;

  gtk_container_add(GTK_CONTAINER(terminal_user_shell_frame), user_shell_hbox) ;





  GtkWidget *start_directory_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *start_directory_label = gtk_label_new( _("Start directory          ") ) ;

  GtkWidget *start_directory_file_chooser_button = gtk_file_chooser_button_new( _("Select the terminal starting directory"), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER) ;

  gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(start_directory_file_chooser_button), settings.start_dir) ;

  gtk_box_pack_start(GTK_BOX(start_directory_hbox), start_directory_label,               FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(start_directory_hbox), start_directory_file_chooser_button, TRUE,  TRUE,  0) ;

  gtk_container_set_border_width(GTK_CONTAINER(start_directory_file_chooser_button),  5) ;

  gtk_container_set_border_width(GTK_CONTAINER(start_directory_hbox),  5) ;

  gtk_box_set_spacing(GTK_BOX(start_directory_hbox), 5) ;

  gtk_container_add(GTK_CONTAINER(terminal_start_dir_frame), start_directory_hbox) ;



  GtkWidget *audible_bell_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *audible_bell_chkbox = gtk_check_button_new_with_label( _("Audible bell") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(audible_bell_chkbox), settings.audible_bell) ;

  gtk_container_set_border_width(GTK_CONTAINER(audible_bell_vbox),  5) ;

  gtk_box_pack_start(GTK_BOX(audible_bell_vbox), audible_bell_chkbox,  TRUE, TRUE,   5) ;

  gtk_container_add(GTK_CONTAINER(terminal_audible_bell_frame), audible_bell_vbox) ;



  GtkWidget *scrollback_lines_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *scrollback_lines_unlimited = gtk_radio_button_new_with_label(NULL, _("Unlimited") ) ;

  GtkWidget *scrollback_lines_nb_hbox   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *scrollback_lines_other     = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(scrollback_lines_unlimited), _("Number of lines:") ) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(scrollback_lines_unlimited), (settings.scrollback_lines == -1) ? TRUE : FALSE) ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(scrollback_lines_other), (settings.scrollback_lines != -1) ? TRUE : FALSE) ;




  GtkWidget *scrollback_lines_nb_spinner    = gtk_spin_button_new_with_range(0, 65535, 1) ;

  gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(scrollback_lines_nb_spinner), TRUE) ;
  gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(scrollback_lines_nb_spinner), GTK_UPDATE_IF_VALID) ;

  if (settings.scrollback_lines > -1) {
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(scrollback_lines_nb_spinner), settings.scrollback_lines) ;
  }

  gtk_container_set_border_width(GTK_CONTAINER(scrollback_lines_vbox), 5) ;

  gtk_container_set_border_width(GTK_CONTAINER(scrollback_lines_nb_hbox), 0) ;

  gtk_box_set_spacing(GTK_BOX(scrollback_lines_nb_hbox), 5) ;


  gtk_box_pack_start(GTK_BOX(scrollback_lines_nb_hbox), scrollback_lines_other,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(scrollback_lines_nb_hbox), scrollback_lines_nb_spinner, FALSE, FALSE, 0) ;


  gtk_box_pack_start(GTK_BOX(scrollback_lines_vbox), scrollback_lines_unlimited,  TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(scrollback_lines_vbox), scrollback_lines_nb_hbox,    TRUE, TRUE, 0) ;



  GtkWidget *scrolling_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *scroll_on_output_checkbutton = gtk_check_button_new_with_label( _("Scroll on output") ) ;

  GtkWidget *scroll_on_keystroke_checkbutton = gtk_check_button_new_with_label( _("Scroll on keystroke") ) ;


  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(scroll_on_output_checkbutton),    settings.scroll_on_output) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(scroll_on_keystroke_checkbutton), settings.scroll_on_keystroke) ;


  gtk_box_pack_start(GTK_BOX(scrolling_vbox), scroll_on_output_checkbutton,    FALSE, FALSE, 5) ;
  gtk_box_pack_start(GTK_BOX(scrolling_vbox), scroll_on_keystroke_checkbutton, FALSE, FALSE, 5) ;

  gtk_container_set_border_width(GTK_CONTAINER(scrolling_vbox), 5) ;

  gtk_container_add(GTK_CONTAINER(terminal_scrolling_frame), scrolling_vbox) ;


  GtkWidget *erasing_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5) ;

  GtkWidget *erasing_backspace_binding_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *erasing_delete_binding_hbox     = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5) ;

  GtkWidget *erasing_backspace_binding_label = gtk_label_new( _("Backspace key generate: ") ) ;

  GtkWidget *erasing_delete_binding_label    = gtk_label_new( _("Delete key generate:       ") ) ;

  GtkWidget *erasing_backspace_binding_combo = gtk_combo_box_text_new() ;

  GtkWidget *erasing_delete_binding_combo    = gtk_combo_box_text_new() ;

  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_backspace_binding_combo), 0, "Automatic" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_backspace_binding_combo), 1, "ASCII backspace character (0x08)" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_backspace_binding_combo), 2, "ASCII delete character (0x7F)" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_backspace_binding_combo), 3, "@7 control sequence" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_backspace_binding_combo), 4, "Terminal's erase setting" ) ;

  gtk_combo_box_set_active(GTK_COMBO_BOX(erasing_backspace_binding_combo), settings.backspace_binding) ;



  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_delete_binding_combo), 0, "Automatic" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_delete_binding_combo), 1, "ASCII backspace character (0x08)" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_delete_binding_combo), 2, "ASCII delete character (0x7F)"  );
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_delete_binding_combo), 3, "@7 control sequence" ) ;
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(erasing_delete_binding_combo), 4, "Terminal's erase setting" ) ;

  gtk_combo_box_set_active(GTK_COMBO_BOX(erasing_delete_binding_combo), settings.delete_binding) ;

  gtk_box_pack_start(GTK_BOX(erasing_backspace_binding_hbox), erasing_backspace_binding_label, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(erasing_backspace_binding_hbox), erasing_backspace_binding_combo, TRUE,  TRUE,  0) ;

  gtk_box_pack_start(GTK_BOX(erasing_delete_binding_hbox), erasing_delete_binding_label, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(erasing_delete_binding_hbox), erasing_delete_binding_combo, TRUE,  TRUE,  0) ;

  gtk_box_set_spacing(GTK_BOX(erasing_backspace_binding_hbox), 5) ;
  gtk_box_set_spacing(GTK_BOX(erasing_delete_binding_hbox),    5) ;


  gtk_box_pack_start(GTK_BOX(erasing_vbox), erasing_backspace_binding_hbox, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(erasing_vbox), erasing_delete_binding_hbox,    FALSE, FALSE, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(erasing_vbox), 5) ;

  gtk_container_add(GTK_CONTAINER(terminal_erase_binding_frame), erasing_vbox) ;




  gtk_box_pack_start(GTK_BOX(terminal_appearance_vbox), terminal_font_colors_frame ,    FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_appearance_vbox), terminal_font_scale_frame,      FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_appearance_vbox), terminal_cursor_frame ,         FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(terminal_appearance_vbox), terminal_colors_frame ,         FALSE, FALSE, 0) ;



  gtk_box_pack_start(GTK_BOX(terminal_appearance_vbox), terminal_bold_frame,            FALSE, FALSE, 0) ;



  gtk_box_pack_start(GTK_BOX(terminal_appearance_vbox), terminal_pointer_autohide,      TRUE,   TRUE, 0) ;

  gtk_container_add(GTK_CONTAINER(terminal_scrollback_frame), scrollback_lines_vbox) ;


  gtk_notebook_append_page(GTK_NOTEBOOK(terminal_settings_notebook), terminal_appearance_vbox, gtk_label_new( _("Appearance") )) ;


  GtkWidget *terminal_settings_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  gtk_box_pack_start(GTK_BOX(terminal_settings_vbox), terminal_user_shell_frame,           FALSE, FALSE,  0) ;

  gtk_box_pack_start(GTK_BOX(terminal_settings_vbox), terminal_start_dir_frame,            FALSE, FALSE,  0) ;

  gtk_box_pack_start(GTK_BOX(terminal_settings_vbox), terminal_audible_bell_frame,         FALSE, FALSE,  0) ;

  gtk_box_pack_start(GTK_BOX(terminal_settings_vbox), terminal_scrollback_frame,           FALSE, FALSE,  0) ;

  gtk_box_pack_start(GTK_BOX(terminal_settings_vbox), terminal_scrolling_frame,            FALSE, FALSE,  0) ;

  gtk_box_pack_start(GTK_BOX(terminal_settings_vbox), terminal_erase_binding_frame,        FALSE, FALSE,  0) ;


  gtk_notebook_append_page(GTK_NOTEBOOK(terminal_settings_notebook), terminal_settings_vbox, gtk_label_new( _("Settings") )) ;

  gtk_notebook_append_page(GTK_NOTEBOOK(notebook_configuration), terminal_settings_notebook, NULL) ;


  gtk_container_add(GTK_CONTAINER(configuration_dialog_content), notebook_configuration) ;

  gtk_widget_show_all(configuration_dialog) ;

  gint result = gtk_dialog_run(GTK_DIALOG(configuration_dialog));

  switch (result) {

      case GTK_RESPONSE_APPLY :

          if (settings.term_font != NULL) {
            free(settings.term_font) ;
          }

          settings.term_font = g_strdup(gtk_font_button_get_font_name(GTK_FONT_BUTTON(terminal_font_colors_button))) ;

          if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cursor_shape_block_radiobutton))  ) {
            settings.cursor_shape = 0 ;
          }
          else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cursor_shape_ibeam_radiobutton))  ) {
            settings.cursor_shape = 1 ;
          }
          else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cursor_shape_underline_radiobutton))  ) {
            settings.cursor_shape = 2 ;
          }

          /** Colors settings: **/
          GdkRGBA term_bg ;
          gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(terminal_bg_color_button), &term_bg);

          if (settings.term_bg != NULL) {
            free(settings.term_bg) ;
          }

          settings.term_bg = g_strdup_printf("#%02x%02x%02x", (int) (term_bg.red * 255.0) , (int) (term_bg.green * 255.0), (int) (term_bg.blue * 255.0) ) ;

          GdkRGBA term_fg ;
          gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(terminal_fg_color_button), &term_fg);

          if (settings.term_fg != NULL) {
            free(settings.term_fg) ;
          }

          settings.term_fg = g_strdup_printf("#%02x%02x%02x", (int) (term_fg.red * 255.0) , (int) (term_fg.green * 255.0) , (int) (term_fg.blue * 255.0) ) ;

          /** Terminals settings **/
          if (settings.user_shell != NULL) {
            g_free(settings.user_shell) ;
          }

          settings.user_shell        = g_strdup(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(user_shell_file_chooser_button))) ;


          if (settings.start_dir != NULL) {
            g_free(settings.start_dir)  ;
          }

          settings.start_dir            = g_strdup(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(start_directory_file_chooser_button))) ;
  
          settings.audible_bell         = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(audible_bell_chkbox)) ;
  
          settings.pointer_autohide     = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(terminal_pointer_autohide_chkbox)) ;
  
          settings.scrollback_lines     = ((gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(scrollback_lines_unlimited)) == TRUE) ? -1 : gtk_spin_button_get_value(GTK_SPIN_BUTTON(scrollback_lines_nb_spinner))) ;

          settings.scroll_on_output     = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(scroll_on_output_checkbutton)) ;
          settings.scroll_on_keystroke  = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(scroll_on_keystroke_checkbutton)) ;


          settings.backspace_binding    = gtk_combo_box_get_active(GTK_COMBO_BOX(erasing_backspace_binding_combo)) ;
          settings.delete_binding       = gtk_combo_box_get_active(GTK_COMBO_BOX(erasing_delete_binding_combo)) ;

          settings.font_scale           = gtk_spin_button_get_value(GTK_SPIN_BUTTON(terminal_font_scale_spinbutton))   ;

          settings.cursor_blink         = gtk_combo_box_get_active(GTK_COMBO_BOX(terminal_cursor_blinking_combo)) ;

          settings.bold_allow           = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(terminal_bold_allowed_checkbutton)) ;


          if (*bold_color_activated) {

            if (settings.bold_color != NULL) {
   
              g_free(settings.bold_color) ;
            }
 
            GdkRGBA bold_color ;
            gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(terminal_bold_color_button), &bold_color) ;
 
            settings.bold_color= g_strdup_printf("#%02x%02x%02x", (int) (bold_color.red * 255.0) , (int) (bold_color.green * 255.0), (int) (bold_color.blue * 255.0) ) ;

          }



          if (*cursor_color_activated) {

            if (settings.cursor_color != NULL) {
   
              g_free(settings.cursor_color) ;
            }
 
            GdkRGBA cursor_color ;
            gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(terminal_cursor_color_button), &cursor_color) ;
 
            settings.cursor_color = g_strdup_printf("#%02x%02x%02x", (int) (cursor_color.red * 255.0) , (int) (cursor_color.green * 255.0), (int) (cursor_color.blue * 255.0) ) ;

          }
  
          free(bold_color_activated) ;
          free(cursor_color_activated) ;

          gtk_widget_destroy(configuration_dialog) ;

          /** Write settings to configuration file. **/
          write_changes_to_conf_file() ;

          /** Terminals changes application. **/
          apply_terminal_change() ;

          while (gtk_events_pending()) {
             /** Waiting for configuration changes completion. **/
             gtk_main_iteration() ;
          }



          break;

      case GTK_RESPONSE_CANCEL :

         gtk_widget_destroy(configuration_dialog) ;
         break;

      default:

         gtk_widget_destroy(configuration_dialog) ;
         break;
    }


  return ;

}

void export_as_profile(const gchar *filepath) {

  GKeyFile *key_file = g_key_file_new() ;

  g_key_file_set_string(key_file, "Compiler", "compiler", project->compiler) ;

  g_key_file_set_string(key_file, "Compiler", "warnings", project->warnings) ;

  g_key_file_set_string(key_file, "Compiler", "cflags", project->cflags) ;

  g_key_file_set_string(key_file, "Compiler", "cppflags", project->cppflags) ;

  g_key_file_set_string(key_file, "Compiler", "ldflags", project->ldflags) ;

  g_key_file_set_string(key_file, "Compiler", "ldlibs", project->ldlibs) ;

  g_key_file_set_string(key_file, "File", "ext_src", project->ext_src) ;

  g_key_file_set_string(key_file, "File", "ext_hdr", project->ext_hdr) ;

  g_key_file_set_boolean(key_file, "Library", "program_library", project->program_library) ;

  g_key_file_set_string(key_file, "Disassembling", "nm_options", project->nm_options) ;                  

  g_key_file_set_string(key_file, "Disassembling", "gdb_options", project->gdb_options) ;                  

  g_key_file_set_string(key_file, "Disassembling", "strace_options", project->strace_options) ;                  

  g_key_file_set_string(key_file, "Disassembling", "ltrace_options", project->ltrace_options) ;
                    
  g_key_file_set_string(key_file, "Disassembling", "objdump_options", project->objdump_options) ;                  

  g_key_file_set_string(key_file, "Disassembling", "ldd_options", project->ldd_options) ;                  

  g_key_file_set_string(key_file, "Disassembling", "gprof_options", project->gprof_options) ;                  

  g_key_file_set_string(key_file, "Oprofile", "operf_options", project->operf_options) ;                  

  g_key_file_set_string(key_file, "Oprofile", "ocount_options", project->ocount_options) ;                  

  g_key_file_set_string(key_file, "Oprofile", "opreport_options", project->opreport_options) ;
                    
  g_key_file_set_string(key_file, "Oprofile", "opannotate_options", project->opannotate_options) ;
                    
  g_key_file_set_string(key_file, "Oprofile", "opgprof_options", project->opgprof_options) ;                  

  g_key_file_set_string(key_file, "Valgrind", "valgrind_memcheck", project->valgrind_memcheck) ;
                    
  g_key_file_set_string(key_file, "Valgrind", "valgrind_cachegrind", project->valgrind_cachegrind) ;                  

  g_key_file_set_string(key_file, "Valgrind", "valgrind_callgrind", project->valgrind_callgrind) ;
                    
  g_key_file_set_string(key_file, "Valgrind", "valgrind_helgrind", project->valgrind_helgrind) ;                  

  g_key_file_set_boolean(key_file, "Code_beautifier", "use_indent", project->use_indent) ;

  g_key_file_set_string(key_file, "Code_beautifier", "indent_options", project->indent_options) ;
       
  g_key_file_set_boolean(key_file, "Code_beautifier", "use_astyle", project->use_astyle) ;

  g_key_file_set_string(key_file, "Code_beautifier", "astyle_options", project->astyle_options) ;

  g_key_file_set_boolean(key_file, "Code_beautifier", "use_bcpp", project->use_bcpp) ;

  g_key_file_set_integer(key_file, "Code_beautifier", "indentation_width", project->indentation_width) ;

  g_key_file_set_boolean(key_file, "Code_beautifier", "use_tabs", project->use_tabs) ;

  g_key_file_set_boolean(key_file, "Documentation", "use_sphinx", project->use_sphinx) ;

  g_key_file_set_boolean(key_file, "Documentation", "use_rst2man", project->use_rst2man) ;

  g_key_file_set_string(key_file, "About", "author_s", project->author_s) ;

  g_key_file_set_string(key_file, "About", "mail_address", project->mail_address) ;

  g_key_file_set_string(key_file, "About", "mail_address", project->mail_address) ;

  g_key_file_set_string(key_file, "About", "copyright_string", project->copyright_string) ;


  g_key_file_set_boolean(key_file, "Licensing", "use_licensing_dkb_format", project->use_licensing_dkb_format) ;
  g_key_file_set_boolean(key_file, "Licensing", "use_licensing_epub_format", project->use_licensing_epub_format) ;
  g_key_file_set_boolean(key_file, "Licensing", "use_licensing_pdf_format", project->use_licensing_pdf_format) ;
  g_key_file_set_boolean(key_file, "Licensing", "use_licensing_html_format", project->use_licensing_html_format) ;
  g_key_file_set_boolean(key_file, "Licensing", "use_licensing_latex_format", project->use_licensing_latex_format) ;
  g_key_file_set_boolean(key_file, "Licensing", "use_licensing_texinfo_format", project->use_licensing_texinfo_format) ;
  g_key_file_set_boolean(key_file, "Licensing", "use_licensing_text_format", project->use_licensing_text_format) ;

  g_key_file_set_string(key_file, "Make", "make_options", project->make_options) ;
  g_key_file_set_integer(key_file, "Make", "compression_level", project->compression_level) ;


  GError *error = NULL ;

  g_key_file_save_to_file(key_file,filepath, &error);

  if (error != NULL) {

    display_message_dialog(_("Error saving file !"), error->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;

    g_error_free(error) ;

    error = NULL ;

  }

  g_key_file_unref(key_file) ;

  return ;

}

static bool get_bool_from_key_file(GKeyFile *key_file, const gchar *group, const gchar *key) {

  bool ret = g_key_file_get_boolean(key_file, group, key, NULL) ;

  return ret ;

}                     


static gchar *get_string_from_key_file(GKeyFile *key_file, const gchar *group, const gchar *key) {

  GError *error = NULL ;

  gchar *ret = g_key_file_get_string(key_file,group, key, &error);

  if (error != NULL) {
 
    display_message_dialog(_("Error getting setting !"), error->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;
 
    g_key_file_unref(key_file) ;
 
    return NULL ;
 
  } 

  return ret ;

}


bool get_a_profile(const gchar *filepath) {

  GError *error = NULL ;

  GKeyFile *key_file = g_key_file_new() ;

  g_key_file_load_from_file(key_file, filepath, G_KEY_FILE_NONE, &error);

  if (error != NULL) {
 
 
    display_message_dialog(_("Error loading profile file !"), error->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;
 
    return false ;
  }

  if ((project->compiler = get_string_from_key_file(key_file, "Compiler", "compiler")) == NULL) {
 
    return false ;

  }

  if ((project->warnings = get_string_from_key_file(key_file, "Compiler", "warnings")) == NULL) {
 
    return false ;

  }

  if ((project->cflags = get_string_from_key_file(key_file, "Compiler", "cflags")) == NULL) {
 
    return false ;

  }

  if ((project->ldflags = get_string_from_key_file(key_file, "Compiler", "ldflags")) == NULL) {
 
    return false ;

  }

  if ((project->ldlibs = get_string_from_key_file(key_file, "Compiler", "ldlibs")) == NULL) {
 
    return false ;

  }

  if ((project->cppflags = get_string_from_key_file(key_file, "Compiler", "cppflags")) == NULL) {
 
    return false ;

  }

  if ((project->ext_src = get_string_from_key_file(key_file, "File", "ext_src")) == NULL) {
 
    return false ;

  }

  if ((project->ext_hdr = get_string_from_key_file(key_file, "File", "ext_hdr")) == NULL) {
 
    return false ;

  }

  project->program_library = get_bool_from_key_file(key_file, "Library", "program_library") ;

  if ((project->nm_options = get_string_from_key_file(key_file, "Disassembling", "nm_options")) == NULL) {
 
    return false ;

  }

  if ((project->gdb_options = get_string_from_key_file(key_file, "Disassembling", "gdb_options")) == NULL) {
 
    return false ;

  }

  if ((project->strace_options = get_string_from_key_file(key_file, "Disassembling", "strace_options")) == NULL) {
 
    return false ;

  }

  if ((project->ltrace_options = get_string_from_key_file(key_file, "Disassembling", "ltrace_options")) == NULL) {
 
    return false ;

  }

  if ((project->objdump_options = get_string_from_key_file(key_file, "Disassembling", "objdump_options")) == NULL) {
 
    return false ;

  }

  if ((project->ldd_options = get_string_from_key_file(key_file, "Disassembling", "ldd_options")) == NULL) {
 
    return false ;

  }

  if ((project->gprof_options = get_string_from_key_file(key_file, "Disassembling", "gprof_options")) == NULL) {
 
    return false ;

  }

  if ((project->operf_options = get_string_from_key_file(key_file, "Oprofile", "operf_options")) == NULL) {
 
    return false ;

  }

  if ((project->ocount_options = get_string_from_key_file(key_file, "Oprofile", "ocount_options")) == NULL) {
 
    return false ;

  }

  if ((project->opreport_options = get_string_from_key_file(key_file, "Oprofile", "opreport_options")) == NULL) {
 
    return false ;

  }

  if ((project->opannotate_options = get_string_from_key_file(key_file, "Oprofile", "opannotate_options")) == NULL) {
 
    return false ;

  }

  if ((project->opgprof_options = get_string_from_key_file(key_file, "Oprofile", "opgprof_options")) == NULL) {
 
    return false ;

  }

  if ((project->valgrind_memcheck = get_string_from_key_file(key_file, "Valgrind", "valgrind_memcheck")) == NULL) {
 
    return false ;

  }

  if ((project->valgrind_cachegrind = get_string_from_key_file(key_file, "Valgrind", "valgrind_cachegrind")) == NULL) {
 
    return false ;

  }

  if ((project->valgrind_callgrind = get_string_from_key_file(key_file, "Valgrind", "valgrind_callgrind")) == NULL) {
 
    return false ;

  }

  if ((project->valgrind_helgrind = get_string_from_key_file(key_file, "Valgrind", "valgrind_helgrind")) == NULL) {
 
    return false ;

  }

  project->use_indent = get_bool_from_key_file(key_file, "Code_beautifier", "use_indent") ;                                
  project->use_astyle = get_bool_from_key_file(key_file, "Code_beautifier", "use_astyle") ;                                
  project->use_bcpp = get_bool_from_key_file(key_file, "Code_beautifier", "use_bcpp") ;                                

  project->indentation_width = g_key_file_get_integer(key_file,"Code_beautifier","indentation_width", NULL);

  if ((project->indent_options = get_string_from_key_file(key_file, "Code_beautifier", "indent_options")) == NULL) {
 
    return false ;

  }

  if ((project->astyle_options = get_string_from_key_file(key_file, "Code_beautifier", "astyle_options")) == NULL) {
 
    return false ;

  }

  project->use_tabs = get_bool_from_key_file(key_file, "Code_beautifier", "use_tabs") ;
  project->use_sphinx = get_bool_from_key_file(key_file, "Documentation", "use_sphinx") ;
  project->use_rst2man = get_bool_from_key_file(key_file, "Documentation", "use_rst2man") ;

  if ((project->author_s = get_string_from_key_file(key_file, "About", "author_s")) == NULL) {
 
    return false ;

  }

  if ((project->mail_address = get_string_from_key_file(key_file, "About", "mail_address")) == NULL) {
 
    return false ;

  }

  if ((project->copyright_string = get_string_from_key_file(key_file, "About", "copyright_string")) == NULL) {
 
    return false ;

  }

  project->use_licensing_dkb_format = get_bool_from_key_file(key_file, "Licensing", "use_licensing_dkb_format") ;
  project->use_licensing_epub_format = get_bool_from_key_file(key_file, "Licensing", "use_licensing_epub_format") ;
  project->use_licensing_pdf_format = get_bool_from_key_file(key_file, "Licensing", "use_licensing_pdf_format") ;
  project->use_licensing_html_format = get_bool_from_key_file(key_file, "Licensing", "use_licensing_html_format") ;
  project->use_licensing_latex_format = get_bool_from_key_file(key_file, "Licensing", "use_licensing_latex_format") ;
  project->use_licensing_texinfo_format = get_bool_from_key_file(key_file, "Licensing", "use_licensing_texinfo_format") ;
  project->use_licensing_text_format = get_bool_from_key_file(key_file, "Licensing", "use_licensing_text_format") ;

  if ((project->make_options = get_string_from_key_file(key_file, "Make", "make_options")) == NULL) {
   
    return false ;

  }
 
  project->compression_level = g_key_file_get_integer(key_file, "Make", "compression_level", &error) ;

  if (error != NULL) {
  
    display_message_dialog(_("Error getting setting !"), error->message, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE) ;
  
    g_error_free(error) ;
  
    return false ;

  } 
 
  g_key_file_unref(key_file) ;

  return true ;

}


