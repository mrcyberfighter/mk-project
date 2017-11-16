.. Copyright (c)  2016,2017  Brüggemann Eddie.
   Permission is granted to copy, distribute and/or modify this document
   under the terms of the GNU Free Documentation License, Version 1.3
   or any later version published by the Free Software Foundation;
   with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
   A copy of the license is included in the section entitled "GNU
   Free Documentation License".

================================
:program:`mk-project` Gtk3 types
================================

.. sectionauthor:: Brüggemann Eddie <mailto:mrcyberfighter@gmail.com>

:program:`mk-project` implement some few derivate Widgets, which I will present here.

You can take a look at the source located in the sub-folders from :file:`/usr(/local)/share/mk-project/src`.

To learn how to implement this kind of Widgets:

:note: Here you can sea how a sphinx documentation looks like, with this theme, for C code (c++ code can be documented too) with sphinx.

------------------
GtkSmartIconButton
------------------

A simple button with an icon without label and tool-tip which embed an universal short-cut text.

.. c:function:: GtkWidget* gtk_smart_menu_item_new_all(const gchar *label, const gchar *icon_filepath, GtkAccelGroup *accel_group, const GdkModifierType accel_modifier, const guint accel_key) ;

  :param  label: The label to display into the menu item.
  :type   label: :c:type:`const gchar *`
  :param  icon_filepath: The menu item icon file-path.
  :type   icon_filepath: :c:type:`const gchar *`
  :param  accel_group: The shortcut accelerator group.
  :type   accel_group: :c:type:`GtkAccelGroup *`
  :param  accel_modifier: The shortcut modifier.
  :type   accel_modifier: :c:type:`const GdkModifierType`
  :param  accel_key: The shortcut accelerator key.
  :type   accel_key: :c:type:`const guint`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the :c:type:`GtkSmartMenuItem`.

.. c:function:: GtkWidget* gtk_smart_check_menu_item_new_all(const gchar *label, const gboolean draw_as_radio, const gchar *icon_filepath, GtkAccelGroup *accel_group, const GdkModifierType accel_modifier, const guint accel_key) ;

  :param  label: The label to display into the menu item.
  :type   label: :c:type:`const gchar *`
  :param  draw_as_radio: draw_as_radio
  :type   draw_as_radio: :c:type:`const gboolean`
  :param  icon_filepath: The menu item icon file-path.
  :type   icon_filepath: :c:type:`const gchar *`
  :param  accel_group: The shortcut accelerator group.
  :type   accel_group: :c:type:`GtkAccelGroup *`
  :param  accel_modifier: The shortcut modifier.
  :type   accel_modifier: :c:type:`const GdkModifierType`
  :param  accel_key: The shortcut accelerator key.
  :type   accel_key: :c:type:`const guint`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the :c:type:`GtkSmartMenuItem` check button.

.. c:function:: GtkWidget* gtk_smart_radio_menu_item_new_all(const gchar *label, const gchar *icon_filepath, GtkAccelGroup *accel_group, const GdkModifierType accel_modifier, const guint accel_key, GtkWidget* widget) ;

  :param  label: The label to display into the menu item.
  :type   label: :c:type:`const gchar *`
  :param  draw_as_radio: draw_as_radio
  :type   draw_as_radio: :c:type:`const gboolean`
  :param  icon_filepath: The menu item icon file-path.
  :type   icon_filepath: :c:type:`const gchar *`
  :param  accel_group: The shortcut accelerator group.
  :type   accel_group: :c:type:`GtkAccelGroup *`
  :param  accel_modifier: The shortcut modifier.
  :type   accel_modifier: :c:type:`const GdkModifierType`
  :param  accel_key: The shortcut accelerator key.
  :type   accel_key: :c:type:`const guint`
  :param  widget: A member from the radio button group.
  :type   widget: :c:type:`NULL` or :c:type:`GtkWidget*`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the :c:type:`GtkSmartMenuItem` radio button.

.. note:: You can pass a :c:type:`NULL` pointer or ``0`` to the parameters :

  * icon_filepath

  * accel_group

  * accel_modifier

  * accel_key.

  * widgets.

:note: You can build others constructors if you have understand How-To build this kind of widgets. 

~~~~~~~
Getters
~~~~~~~

.. c:function:: GtkWidget* gtk_smart_menu_item_get_image(GtkWidget* smart_menu_item) ;

  :param smart_menu_item: The return value from the constructors.
  :type  smart_menu_item: :c:type:`GtkWidget*`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the :c:type:`GtkImage` widget.

.. c:function:: GtkWidget* gtk_smart_menu_item_get_menuitem(GtkWidget* smart_menu_item) ;

  :param smart_menu_item: The return value from the constructors.
  :type  smart_menu_item: :c:type:`GtkWidget*`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the :c:type:`GtkMenuItem` widget.

.. c:function:: GtkWidget* gtk_smart_menu_item_get_label(GtkWidget* smart_menu_item) ;

  :param smart_menu_item: The return value from the constructors.
  :type  smart_menu_item: :c:type:`GtkWidget*`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the :c:type:`GtkLabel` widget.

.. c:function:: GtkWidget* gtk_smart_menu_item_get_accel_label(GtkWidget* smart_menu_item) ;

  :param smart_menu_item: The return value from the constructors.
  :type  smart_menu_item: :c:type:`GtkWidget*`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the :c:type:`GtkAccelLabel` widget.

------------------
GtkSmartIconButton
------------------

A simple button with an icon without label and tool-tip which embed an universal short-cut text.

~~~~~~~~~~~~
Constructors
~~~~~~~~~~~~

.. c:function:: GtkWidget* gtk_smart_icon_button_new_all(const gchar *filepath, const gchar *tooltip_text, const guint accel_key, const GdkModifierType accel_modifier) ;

  :param filepath: The filepath to the image to use as icon.
  :type  filepath: :c:type:`const gchar *`
  :param tooltip_text: The tool-tip text without the accelerator label.
  :type  tooltip_text: :c:type:`const gchar *`
  :param  accel_key: The shortcut accelerator key.
  :type   accel_key: :c:type:`const guint`
  :param  accel_modifier: The shortcut modifier.
  :type   accel_modifier: :c:type:`const GdkModifierType`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the :c:type:`GtkSmartIconButton` widget.

.. c:function::  GtkWidget* gtk_smart_icon_toggle_button_new_all(const gchar *filepath, const gchar *tooltip_text, const guint accel_key, const GdkModifierType accel_modifier) ;

  :param filepath: The filepath to the image to use as icon.
  :type  filepath: :c:type:`const gchar *`
  :param tooltip_text: The tool-tip text without the accelerator label.
  :type  tooltip_text: :c:type:`const gchar *`
  :param  accel_key: The shortcut accelerator key.
  :type   accel_key: :c:type:`const guint`
  :param  accel_modifier: The shortcut modifier.
  :type   accel_modifier: :c:type:`const GdkModifierType`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the :c:type:`GtkSmartIconButton` toggle button widget.

:note: This widget is not used into :program:`mk-project` but provided in the hope to be useful.

----------
GtkTermTab
----------

  A GtkNoteBook tab with an decorative icon, a label, and close icon button.

~~~~~~~~~~~
Constructor
~~~~~~~~~~~

.. c:function:: GtkWidget* gtk_mk_term_tab_new(const gchar *icon_filepath, const gchar *label, const gchar *close_filepath) ;

  :param  icon_filepath:   Image filepath to display as decoration on the right of the tab-label.
  :type   icon_filepath:   :c:type:`const gchar *`
  :param  label: The label to display in the :c:type:`GtkMkTermTab`.
  :type   label: :c:type:`const gchar *`
  :param  close_filepath: Image filepath to display in the :c:type:`GtkMkTermTab` as close button icon.
  :type   close_filepath: :c:type:`const gchar *`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the Widget :c:type:`GtkMkTerm`.

~~~~~~~
Getters
~~~~~~~

.. c:function:: GtkWidget* gtk_mk_term_tab_get_close_button(GtkMkTermTab *tab);

  :param  tab:   An instance of the :c:type:`GtkMkTermTab`.
  :type   tab:   :c:type:`const gchar *`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the Widget :c:type:`GtkButton` at the right of the label.

---------
GtkMkTerm
---------

:warning: This widget implementation is not reusable as is, because of :c:type:`VteTerminal` configuration variables.

~~~~~~~~~~~
Constructor
~~~~~~~~~~~

.. c:function:: GtkWidget* gtk_mkterm_new(gboolean initialize, gboolean is_edit_term) ;

  :param  initialize:   Initializing or reconfiguring the :c:type:`GtkMkTerm`.
  :type   initialize:   :c:type:`gboolean`
  :param  is_edit_term: Whether or not the :c:type:`GtkMkTerm` is a editor widget.
  :type   is_edit_term: :c:type:`gboolean`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the Widget :c:type:`GtkMkTerm`.

~~~~~~~
Getters
~~~~~~~

.. c:function:: GtkWidget* gtk_mkterm_get_vte_terminal(GtkWidget* mkterm) ;

  :param  mkterm: An instance of the :c:type:`GtkMkTerm` Widget.
  :type   mkterm: :c:type:`GtkWidget*`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the :c:type:`VteTerminal`.

.. c:function:: GtkWidget* gtk_mkterm_get_clipboard_menu(GtkWidget* mkterm) ;

  :param  mkterm:   Initializing or reconfiguring the :c:type:`GtkMkTerm`.
  :type   mkterm:   :c:type:`GtkWidget*`
  :rtype: :c:type:`GtkWidget*`
  :return: A pointer to the :c:type:`GtkMenu` associated to the :c:type:`GtkMkTerm`.

  
