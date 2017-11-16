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


#include "GtkMkTermTab.h"

struct _GtkMkTermTabPrivate {

  /** This structure contains all the members of the new type: **/

  int padding ;

} ;

static void gtk_mk_term_tab_class_init(GtkMkTermTabClass *class);
static void gtk_mk_term_tab_init(GtkMkTermTab *mk_term_tab); // Constructor
static void gtk_mk_term_tab_finalize(GObject *object); // Destructor
static void gtk_mk_term_tab_dispose(GObject *object) ;

G_DEFINE_TYPE_WITH_PRIVATE(GtkMkTermTab, gtk_mk_term_tab, GTK_TYPE_BOX)

static void gtk_mk_term_tab_class_init(GtkMkTermTabClass *class) {

  /** Class initialize. **/

  g_return_if_fail(class != NULL);

  G_OBJECT_CLASS(class)->dispose = gtk_mk_term_tab_dispose ;

  G_OBJECT_CLASS(class)->finalize = gtk_mk_term_tab_finalize ; // Destructor

}

static void gtk_mk_term_tab_init(GtkMkTermTab *mk_term_tab) {

  /** Initialize the members. **/

  g_return_if_fail(mk_term_tab != NULL);

}

static void gtk_mk_term_tab_dispose(GObject *object) {

  G_OBJECT_CLASS(gtk_mk_term_tab_parent_class)->dispose(object);

  return ;
}

static void gtk_mk_term_tab_finalize(GObject *object) {

  /** Private data destructor if necessary. **/
  G_OBJECT_CLASS(gtk_mk_term_tab_parent_class)->finalize(object);

}

GtkWidget* gtk_mk_term_tab_new(const gchar *icon_filepath, const gchar *label, const gchar *close_filepath) {

  GtkMkTermTab *mkterm_tab = NULL;

  /** Create a new object. **/
  mkterm_tab  = g_object_new(GTK_TYPE_MK_TERM_TAB, NULL);

  GtkWidget *button = gtk_button_new() ;

  char *icon_realpath = realpath(icon_filepath, NULL) ;

  errno = 0 ;

  if (! g_file_test(icon_realpath, G_FILE_TEST_IS_REGULAR)) {

    g_printerr("%s", g_strerror(g_file_error_from_errno(errno)) ) ;

    return NULL ;

  }

  GtkWidget *icon_image = gtk_image_new_from_file(icon_realpath) ;

  free(icon_realpath) ;



  gtk_button_set_image(GTK_BUTTON(button), icon_image) ;

  gtk_button_set_always_show_image(GTK_BUTTON(button), TRUE);

  gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE) ;

  GtkWidget *label_widget = gtk_label_new(label) ;

  GtkWidget *close_button = gtk_button_new() ;

  gtk_button_set_relief(GTK_BUTTON(close_button), GTK_RELIEF_NONE) ;

  char *close_realpath = realpath(close_filepath, NULL) ;

  errno = 0 ;

  if (! g_file_test(close_realpath, G_FILE_TEST_IS_REGULAR)) {

    g_printerr("%s", g_strerror(g_file_error_from_errno(errno)) ) ;

    return NULL ;

  }

  GtkWidget *close_image = gtk_image_new_from_file(close_realpath) ;

  gtk_button_set_image(GTK_BUTTON(close_button), close_image) ;

  gtk_button_set_always_show_image(GTK_BUTTON(close_button), TRUE);

  gtk_box_pack_start(GTK_BOX(mkterm_tab), button,        FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(mkterm_tab), label_widget,         FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(mkterm_tab), close_button,  FALSE, FALSE, 0) ;

  gtk_widget_show_all(GTK_WIDGET(mkterm_tab)) ;

  return GTK_WIDGET(mkterm_tab) ;

}

GtkWidget* gtk_mk_term_tab_get_close_button(GtkMkTermTab *tab) {

  GList *g_list_children = gtk_container_get_children(GTK_CONTAINER(tab)) ;

  GtkWidget *ret = g_list_nth_data(g_list_children, 2) ;

  g_list_free(g_list_children) ;

  return ret ;


}
