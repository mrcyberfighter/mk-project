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

#include "GtkMkTerm.h"

/** Private structure definition. **/
struct _GtkMkTermPrivate {

  GtkWidget *vteterm ;

  GtkWidget *clipboard_menu ;

};

static void gtk_mkterm_class_init(GtkMkTermClass *class); /** Initialize  **/
static void gtk_mkterm_init(GtkMkTerm *mkterm);           /** Constructor **/
static void gtk_mkterm_finalize(GObject *object);         /** Destructor  **/
static void gtk_mkterm_dispose(GObject *object) ;

G_DEFINE_TYPE_WITH_PRIVATE(GtkMkTerm, gtk_mkterm, GTK_TYPE_SCROLLED_WINDOW)

static void gtk_mkterm_class_init(GtkMkTermClass *class) {

  g_return_if_fail(class != NULL);

  G_OBJECT_CLASS(class)->dispose = gtk_mkterm_dispose;

  G_OBJECT_CLASS(class)->finalize = gtk_mkterm_finalize ;

}

static void gtk_mkterm_init(GtkMkTerm *mkterm) {

  g_return_if_fail(mkterm != NULL);

  /** Permit to access object private data. **/
  GtkMkTermPrivate *priv = gtk_mkterm_get_instance_private(mkterm);

  /** Initialize private datas. **/
  priv->vteterm = vte_terminal_new() ;
  priv->clipboard_menu = gtk_menu_new() ;

}

static void gtk_mkterm_dispose(GObject *object) {

  GtkMkTermPrivate *priv = gtk_mkterm_get_instance_private(GTK_MKTERM(object));

  /* In dispose(), you are supposed to free all types referenced from this
   * object which might themselves hold a reference to self. Generally,
   * the most simple solution is to unref all members on which you own a
   * reference.
   */

  /* dispose() might be called multiple times, so we must guard against
   * calling g_object_unref() on an invalid GObject by setting the member
   * NULL; g_clear_object() does this for us.
   */

  priv->clipboard_menu = g_object_ref_sink(priv->clipboard_menu) ;

  priv->vteterm = g_object_ref_sink(priv->vteterm) ;

  /* Always chain up to the parent class; there is no need to check if
   * the parent class implements the dispose() virtual function: it is
   * always guaranteed to do so
   */
  G_OBJECT_CLASS(gtk_mkterm_parent_class)->dispose(object);

}


static void gtk_mkterm_finalize(GObject *object) {

  /** Permit to access object private data. **/
  GtkMkTermPrivate *priv = gtk_mkterm_get_instance_private(GTK_MKTERM(object));

  g_clear_object(&priv->vteterm);

  GList *clipboard_menu_child_list = gtk_container_get_children(GTK_CONTAINER(priv->clipboard_menu)) ;

  clipboard_menu_child_list = g_list_nth (clipboard_menu_child_list, 0) ;

  while (clipboard_menu_child_list != NULL) {

    if (clipboard_menu_child_list->data != NULL) {

      gtk_widget_destroy(GTK_WIDGET(clipboard_menu_child_list->data)) ;

    }

    if (clipboard_menu_child_list->next != NULL) {

      clipboard_menu_child_list = clipboard_menu_child_list->next ;
    }
    else {

      break ;
    }

  }

  g_clear_object(&priv->clipboard_menu);

  /** Private datas destructor if necessary. **/
  G_OBJECT_CLASS(gtk_mkterm_parent_class)->finalize(object);

  #ifdef DEBUG
  fprintf(stderr,"GtkMkTerm: %s (priv->vteterm)         -> %p\n", __func__, (void *) priv->vteterm) ;
  fprintf(stderr,"GtkMkTerm: %s (priv->clipboard_menu)  -> %p\n", __func__, (void *) priv->clipboard_menu) ;
  #endif

}

void vte_terminal_spawn_async_callback(VteTerminal *terminal, GPid pid, GError *error) {



  if (error || pid == -1) {
  
    /** Case the g_spawn_async failed ! **/
     
    char *argv_cmd[2] = {settings.user_shell, NULL} ;
  
    gchar **envp = g_get_environ() ;
  
    GPid child_pid = -1 ;
  
    vte_terminal_spawn_sync(VTE_TERMINAL(terminal),
                            VTE_PTY_DEFAULT,
                            settings.start_dir,
                            argv_cmd,
                            envp,
                            G_SPAWN_DEFAULT, NULL, NULL, &child_pid, NULL,  NULL);
                   
    while (child_pid == -1) {

      g_main_context_iteration(NULL, FALSE) ;
    }

  }

  /** Else this function is a necessary stumb. **/

  return ;

}

void gtk_mkterm_setup(GtkWidget *mkterm, gboolean is_sidebar) {

  char *argv_cmd[2] = {settings.user_shell, NULL} ;

  /** Fork a new process: your default shell or the one you have configurated.
    *
    * The process is killed per example if you closing a terminals tab or by resetting the terminal
    * else it is automatic killed by exiting the application.
    *
    * So we let no zoombies after us.
    *
    ***********************************************************************************************/

  GtkWidget *vteterminal = gtk_mkterm_get_vte_terminal(mkterm) ;
  GtkWidget *clipboard_menu = gtk_mkterm_get_clipboard_menu(mkterm) ;

  GPid child_pid = -1 ;

  gchar **envp = g_get_environ() ;


  #if (VTE_MINOR_VERSION < 48)

    vte_terminal_spawn_sync(VTE_TERMINAL(vteterminal),
                            VTE_PTY_DEFAULT,
                            settings.start_dir,
                            argv_cmd,
                            envp,
                            G_SPAWN_DEFAULT, NULL, NULL, &child_pid, NULL,  NULL);
                   
    while (child_pid == -1) {

      g_main_context_iteration(NULL, FALSE) ;

    }                  

  #else

  vte_terminal_spawn_async(VTE_TERMINAL(vteterminal),
                            VTE_PTY_DEFAULT,
                            settings.start_dir, // Working directory.
                            argv_cmd,
                            envp,
                            G_SPAWN_DEFAULT,
                            NULL,
                            NULL,
                            NULL,
                            -1,
                            NULL,
                            (VteTerminalSpawnAsyncCallback) vte_terminal_spawn_async_callback,
                            NULL);

  #endif

  g_strfreev(envp) ;

  #if (VTE_MINOR_VERSION < 48)

    vte_terminal_watch_child(VTE_TERMINAL(vteterminal), child_pid) ;
  
  #endif

  /** Build a clipboard menu connecting to the terminal. **/

  GtkWidget *copy_label  = gtk_menu_item_new_with_label( _("Copy from terminal") ) ;
  GtkWidget *paste_label = gtk_menu_item_new_with_label( _("Paste  to terminal") ) ;


  GtkWidget *new_tab_label    = gtk_menu_item_new_with_label( _("Open new tab") ) ;
  GtkWidget *close_tab_label  = gtk_menu_item_new_with_label( _("Close tab") ) ;

  GtkWidget *decr_font_label = gtk_menu_item_new_with_label( _("Decrease font-scale") ) ;
  GtkWidget *incr_font_label = gtk_menu_item_new_with_label( _("Increase font-scale") ) ;

  GtkWidget *reset_label      = gtk_menu_item_new_with_label( _("Reset terminal") ) ;

  gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu), copy_label)  ;
  gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu), paste_label) ;


  if (is_sidebar) {

    gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu), gtk_separator_menu_item_new())     ;
    gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu), new_tab_label)   ;
    gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu), close_tab_label) ;

  }


  gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu), gtk_separator_menu_item_new())       ;
  gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu), decr_font_label)   ;
  gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu), incr_font_label)   ;
  gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu), gtk_separator_menu_item_new())       ;
  gtk_menu_shell_append(GTK_MENU_SHELL(clipboard_menu), reset_label)       ;


  GtkAccelGroup *accel_group = gtk_accel_group_new() ;

  gtk_window_add_accel_group(GTK_WINDOW(gui->window), accel_group);

  gtk_widget_add_accelerator(GTK_WIDGET(copy_label),  "activate", accel_group, GDK_KEY_Copy,   GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE) ;
  gtk_widget_add_accelerator(GTK_WIDGET(paste_label), "activate", accel_group, GDK_KEY_Insert, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE) ;

  gtk_widget_add_accelerator(GTK_WIDGET(incr_font_label),  "activate", accel_group, GDK_KEY_plus,   GDK_CONTROL_MASK | GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE) ;
  gtk_widget_add_accelerator(GTK_WIDGET(decr_font_label),  "activate", accel_group, GDK_KEY_minus,  GDK_CONTROL_MASK | GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE) ;

  if (is_sidebar) {

    gtk_widget_add_accelerator(GTK_WIDGET(new_tab_label),  "activate", accel_group, GDK_KEY_t,      GDK_CONTROL_MASK | GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE) ;

  }


  gtk_widget_show_all(clipboard_menu) ;

  g_signal_connect(G_OBJECT(vteterminal), "button-press-event", G_CALLBACK(display_clipboard_menu), clipboard_menu) ;

  g_signal_connect(G_OBJECT(copy_label),  "activate", G_CALLBACK(clipboard_copy),  vteterminal) ;
  g_signal_connect(G_OBJECT(paste_label), "activate", G_CALLBACK(clipboard_paste), vteterminal) ;

  g_signal_connect(G_OBJECT(reset_label), "activate", G_CALLBACK(reset_terminal),  vteterminal) ;

  g_signal_connect(G_OBJECT(incr_font_label),  "activate", G_CALLBACK(increase_font_size),  vteterminal) ;
  g_signal_connect(G_OBJECT(decr_font_label),  "activate", G_CALLBACK(decrease_font_size), vteterminal) ;

  g_signal_connect(G_OBJECT(vteterminal), "increase-font-size", G_CALLBACK(increase_font_size),  vteterminal) ;
  g_signal_connect(G_OBJECT(vteterminal), "decrease-font-size", G_CALLBACK(decrease_font_size),  vteterminal) ;


  if (is_sidebar) {

    g_signal_connect(G_OBJECT(new_tab_label),   "activate", G_CALLBACK(add_new_terminals),    NULL) ;

    gint *ret = g_malloc(sizeof(gint)) ;

    *ret = gtk_notebook_get_current_page(GTK_NOTEBOOK(gui->terminal_notebook)) ;

    ++(*ret) ;


    g_signal_connect(G_OBJECT(close_tab_label), "activate", G_CALLBACK(remove_terminal_tabs_from_clipboard),  ret ) ;

  }


  if (! is_sidebar) {



    gtk_widget_destroy(new_tab_label)  ;
    gtk_widget_destroy(close_tab_label)  ;



  }

  return ;

}

GtkWidget *gtk_mkterm_new(gboolean initialize, gboolean is_edit_term) {

  /** Create a new (G_OBJECT) object. **/

  GtkMkTerm *mkterm = NULL;

  /** Create a new object. **/
  mkterm  = g_object_new(GTK_TYPE_MKTERM, NULL);

  /** Get the private data pointer. **/
  GtkMkTermPrivate *priv = gtk_mkterm_get_instance_private(mkterm);

  /** Configure the (vte) terminal parent widget: a @GTK_SCROLLED_WINDOW. **/
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(mkterm), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
  
  #if (GTK_MINOR_VERSION >= 16)
  gtk_scrolled_window_set_overlay_scrolling(GTK_SCROLLED_WINDOW(mkterm), FALSE) ;
  #endif 
  gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(mkterm), gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(priv->vteterm))) ;
  gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(mkterm),   ((80 * 8) + 24)) ; // 80 chars width on a screen with a resolution of 1920/1080.
  gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(mkterm),  24 * 16        );

  gtk_widget_set_redraw_on_allocate(priv->vteterm , TRUE) ;

  /** Add the (vte) terminal into his parent container. **/
  gtk_container_add(GTK_CONTAINER(mkterm), priv->vteterm) ;

  /** Configure the (vte) terminal. **/
  gtk_mkterm_configure_terminal(priv->vteterm, initialize);

  /** setup @GtkMkTerm **/
  gtk_mkterm_setup(GTK_WIDGET(mkterm), is_edit_term);

  /** Return the entire @GtkMkTerm object as @GtkWidget pointer (for compatibility). **/
  return GTK_WIDGET(mkterm) ;

}

GtkWidget* gtk_mkterm_get_vte_terminal(GtkWidget *mkterm) {

  if ( mkterm == NULL || ! IS_GTK_MKTERM(mkterm) ) {

      g_printerr("%s(...) error: *mkterm is not a valid pointer on a GtkMkTerm object\n", __func__);

      return NULL;
  }

  /** Getting a pointer on the private datas. **/
  GtkMkTermPrivate *priv = gtk_mkterm_get_instance_private (GTK_MKTERM(mkterm));

  return priv->vteterm;
}

GtkWidget* gtk_mkterm_get_clipboard_menu(GtkWidget *mkterm) {

  if ( mkterm == NULL || ! IS_GTK_MKTERM(mkterm) ) {

      g_printerr("%s(...) error: *mkterm is not a valid pointer on a GtkMkTerm object\n", __func__);

      return NULL;
  }

  /** Getting a pointer on the private datas. **/
  GtkMkTermPrivate *priv = gtk_mkterm_get_instance_private(GTK_MKTERM(mkterm));

  return priv->clipboard_menu ;
}

void gtk_mkterm_configure_terminal(GtkWidget *vteterminal, gboolean initialize) {

  /** Configure the (vte) terminal according to the configuration. **/

  if ( vteterminal == NULL ) {                    

    g_printerr("%s(...) error: vteterminal == NULL\n", __func__);

    return;

  }

  vte_terminal_set_default_colors(VTE_TERMINAL(vteterminal)) ;

  /** Font settings: **/
  PangoFontDescription *font_desc = pango_font_description_from_string(settings.term_font) ;

  g_object_set(G_OBJECT(vteterminal), "font-desc", font_desc, NULL) ;

  vte_terminal_set_font_scale(VTE_TERMINAL(vteterminal),  settings.font_scale) ;


  /** Cursor settings: **/
  vte_terminal_set_cursor_shape(VTE_TERMINAL(vteterminal), (settings.cursor_shape == 0) ? VTE_CURSOR_SHAPE_BLOCK : (settings.cursor_shape == 1) ? VTE_CURSOR_SHAPE_IBEAM : VTE_CURSOR_SHAPE_UNDERLINE) ;

  vte_terminal_set_cursor_blink_mode(VTE_TERMINAL(vteterminal), (settings.cursor_blink == 0) ? VTE_CURSOR_BLINK_SYSTEM : (settings.cursor_blink == 1) ? VTE_CURSOR_BLINK_ON : VTE_CURSOR_BLINK_OFF) ;

  vte_terminal_set_audible_bell(VTE_TERMINAL(vteterminal), settings.audible_bell) ;

  vte_terminal_set_mouse_autohide(VTE_TERMINAL(vteterminal), settings.pointer_autohide) ;

  /** Bold setting: **/

  vte_terminal_set_allow_bold(VTE_TERMINAL(vteterminal), settings.bold_allow) ;

  GdkRGBA bold_color ;
  gdk_rgba_parse(&bold_color, settings.bold_color) ;
  vte_terminal_set_color_bold(VTE_TERMINAL(vteterminal), &bold_color) ;



  /** Erasing keys binding. **/
  g_object_set(G_OBJECT(vteterminal), "backspace-binding", (settings.backspace_binding == 0) ? VTE_ERASE_AUTO :
                                                           (settings.backspace_binding == 1) ? VTE_ERASE_ASCII_BACKSPACE :
                                                           (settings.backspace_binding == 2) ? VTE_ERASE_ASCII_DELETE :
                                                           (settings.backspace_binding == 3) ? VTE_ERASE_DELETE_SEQUENCE :
                                                                                               VTE_ERASE_TTY,
                                                           NULL) ;

  g_object_set(G_OBJECT(vteterminal), "delete-binding", (settings.delete_binding == 0) ? VTE_ERASE_AUTO :
                                                        (settings.delete_binding == 1) ? VTE_ERASE_ASCII_BACKSPACE :
                                                        (settings.delete_binding == 2) ? VTE_ERASE_ASCII_DELETE :
                                                        (settings.delete_binding == 3) ? VTE_ERASE_DELETE_SEQUENCE :
                                                                                         VTE_ERASE_TTY,
                                                         NULL) ;



  /** Colors settings: **/
  GdkRGBA bg_terminal ;
  gdk_rgba_parse(&bg_terminal, settings.term_bg) ;
  GdkRGBA fg_terminal ;
  gdk_rgba_parse(&fg_terminal, settings.term_fg) ;

  vte_terminal_set_color_foreground(VTE_TERMINAL(vteterminal), &fg_terminal) ;

  vte_terminal_set_color_background(VTE_TERMINAL(vteterminal), &bg_terminal) ;


  /** Usual default settings: **/
  vte_terminal_set_scrollback_lines(VTE_TERMINAL(vteterminal),    settings.scrollback_lines) ;

  vte_terminal_set_scroll_on_output(VTE_TERMINAL(vteterminal),    settings.scroll_on_output) ;

  vte_terminal_set_scroll_on_keystroke(VTE_TERMINAL(vteterminal), settings.scroll_on_keystroke) ;

  if (initialize) {

    vte_terminal_set_encoding(VTE_TERMINAL(vteterminal), vte_terminal_get_encoding(VTE_TERMINAL(vteterminal)), NULL)  ;  // default
    
    #if  (VTE_MINOR_VERSION <= 16)
    /** Mouse left button double click word separators: The following characters are not register as word separators. **/
    vte_terminal_set_word_char_exceptions(VTE_TERMINAL(vteterminal), vte_terminal_get_word_char_exceptions(VTE_TERMINAL(vteterminal)) ) ;
    #endif    


    vte_terminal_set_rewrap_on_resize(VTE_TERMINAL(vteterminal), TRUE) ;

    vte_terminal_set_size(VTE_TERMINAL(vteterminal), 80, 24) ;

  }

  return ;
}
