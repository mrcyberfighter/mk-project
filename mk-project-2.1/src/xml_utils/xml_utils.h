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

#ifndef LIB_MK_PROJECT_XML_UTILS_HH
#define LIB_MK_PROJECT_XML_UTILS_HH



#include <libxml/tree.h>
#include <libxml/parser.h>

#include "../headers/includes.h"

extern xmlNodePtr create_root_node(xmlDocPtr doc, const char *name) ;

extern xmlNodePtr add_new_node(xmlNodePtr parent, const char *name, const char *content) ;

extern xmlNodePtr add_new_doc_comment(xmlDocPtr doc, xmlNodePtr root_node, const char *comment) ;

extern xmlNodePtr create_new_node(xmlDocPtr doc, const char *name, const char *content) ;

extern void replace_node_content(xmlNodePtr node, const char *new_content) ;

extern xmlAttrPtr set_property(xmlNodePtr node, const char *name, const char * value) ;

extern xmlChar *get_prop_name(xmlNodePtr node, const char *name) ;

extern xmlNodePtr add_child(xmlNodePtr parent, xmlNodePtr child) ;

extern void set_compression(xmlDocPtr doc, int mode) ;

extern int unset_property(xmlNodePtr node,const char *attr) ;

extern void rename_attribut(xmlNodePtr node, const char *old_attr, const char *new_attr) ;

#endif
