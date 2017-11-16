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

#ifndef MK_PROJECT_INCLUDE_HH
#define MK_PROJECT_INCLUDE_HH

#define _GNU_SOURCE

/** Include gtk utilities **/
#include <gtk/gtk.h>

/** Include glib utilities **/
#include <glib.h>
#include <glib/gstdio.h>
#include <glib/gprintf.h>

/** Include vte-2.91 utilities **/
#include <vte-2.91/vte/vte.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <inttypes.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <math.h>

#include <errno.h>

#ifdef __APPLE__
#include <gtkmacintegration/gtkosxapplication.h>
#endif

/** @Note: using an unique @includes.h file has the same effect has including into every header file.
  * I know because I had proove it to myself. And inclusion guards are not done for nothing.
  * The same is valid for a header file containing all global variables declarations.
  ***************************************************************************************************/

#endif
