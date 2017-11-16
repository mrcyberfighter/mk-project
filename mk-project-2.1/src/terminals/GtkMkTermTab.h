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

#ifndef GTK_MK_TERM_TAB_HH
#define GTK_MK_TERM_TAB_HH

#define _GNU_SOURCE

#include <gtk/gtk.h>

#include <limits.h>
#include <stdlib.h>
#include <errno.h>

G_BEGIN_DECLS


#define GTK_MK_TERM_TAB(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_MK_TERM_TAB, GtkMkTermTab))
#define GTK_MK_TERM_TAB_CLASS(class)    (G_TYPE_CHECK_CLASS_CAST((class),  GTK_TYPE_MK_TERM_TAB, GtkMkTermTabClass))
#define IS_GTK_MK_TERM_TAB(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_MK_TERM_TAB))
#define IS_GTK_MK_TERM_TAB_CLASS(class) (G_TYPE_CHECK_CLASS_TYPE((class),  GTK_TYPE_MK_TERM_TAB))
#define GTK_MK_TERM_TAB_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj),  GTK_TYPE_MK_TERM_TAB, GtkMkTermTabClass))

typedef struct _GtkMkTermTab       GtkMkTermTab;
typedef struct _GtkMkTermTabClass  GtkMkTermTabClass;

#define GTK_TYPE_MK_TERM_TAB (gtk_mk_term_tab_get_type())

/** Definition to find in the *.c file **/
typedef struct _GtkMkTermTabPrivate GtkMkTermTabPrivate;

/** GtkMkTermTab definition. **/
struct _GtkMkTermTab {

  GtkBox parent;

  GtkMkTermTabPrivate *priv;

};

/** Class definition. **/
struct _GtkMkTermTabClass {

   GtkBoxClass parent_class;

};


GType gtk_mk_term_tab_get_type(void) G_GNUC_CONST ;

/** ************************************************************************ **/

/** New @GtkMkTermTab instance creation. **/
extern GtkWidget* gtk_mk_term_tab_new(const gchar *icon_filepath, const gchar *label, const gchar *close_filepath);

/** (vte) close button getter. **/
extern GtkWidget* gtk_mk_term_tab_get_close_button(GtkMkTermTab *tab);

G_END_DECLS

#endif
