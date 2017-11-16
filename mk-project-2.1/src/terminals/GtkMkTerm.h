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

#ifndef GTK_MKTERM_HH
#define GTK_MKTERM_HH

#include <gtk/gtk.h>
#include <vte-2.91/vte/vte.h>

#include <limits.h>
#include <stdlib.h>


G_BEGIN_DECLS


#define GTK_MKTERM(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_MKTERM, GtkMkTerm))
#define GTK_MKTERM_CLASS(class)    (G_TYPE_CHECK_CLASS_CAST((class),  GTK_TYPE_MKTERM, GtkMkTermClass))
#define IS_GTK_MKTERM(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_MKTERM))
#define IS_GTK_MKTERM_CLASS(class) (G_TYPE_CHECK_CLASS_TYPE((class),  GTK_TYPE_MKTERM))
#define GTK_MKTERM_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj),  GTK_TYPE_MKTERM, GtkMkTermClass))

typedef struct _GtkMkTerm       GtkMkTerm;
typedef struct _GtkMkTermClass  GtkMkTermClass;

#define GTK_TYPE_MKTERM (gtk_mkterm_get_type())

/** Definition to find in the *.c file **/
typedef struct _GtkMkTermPrivate GtkMkTermPrivate;

/** GtkMkTerm definition. **/
struct _GtkMkTerm {

  GtkScrolledWindow parent;

  GtkMkTermPrivate *priv;

};

/** Class definition. **/
struct _GtkMkTermClass {

   GtkScrolledWindowClass parent_class;

};


GType gtk_mkterm_get_type(void) G_GNUC_CONST ;

/** ************************************************************************ **/

// Inclusion which make the widget not reusable as is !
#include "../global_vars.h"
#include "../terminals/terminals_callback.h"

/** New @GtkMkTerm instance creation. **/
extern GtkWidget *gtk_mkterm_new(gboolean initialize, gboolean is_edit_term);

/** (vte) terminal getter. **/
extern GtkWidget *gtk_mkterm_get_vte_terminal(GtkWidget *mkterm);
extern GtkWidget *gtk_mkterm_get_clipboard_menu(GtkWidget *mkterm);

/** Configuration of the (vte) terminal. **/
extern void gtk_mkterm_configure_terminal(GtkWidget *mkterm, gboolean initialize);

G_END_DECLS

#endif
