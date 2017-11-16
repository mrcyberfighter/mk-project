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

#include "xml_utils.h"

xmlNodePtr create_root_node(xmlDocPtr doc, const char *name) {

  xmlNodePtr new_node = xmlNewDocNode(doc, NULL, BAD_CAST name, NULL) ;

  xmlDocSetRootElement(doc, new_node) ;

  return new_node ;

}

xmlNodePtr add_new_node(xmlNodePtr parent, const char *name, const char *content) {

  return xmlNewTextChild(parent, NULL, BAD_CAST name, BAD_CAST content) ;
}

xmlNodePtr add_new_doc_comment(xmlDocPtr doc, xmlNodePtr root_node, const char *comment) {

  return xmlAddChild(root_node, xmlNewDocComment(doc, BAD_CAST comment)) ;

}

xmlNodePtr create_new_node(xmlDocPtr doc, const char *name, const char *content) {

  xmlNodePtr root_elt_node_ptr ;

  if ((root_elt_node_ptr = xmlDocGetRootElement(doc)) == NULL) {

    xmlNodePtr new_node = xmlNewDocNode(doc, NULL, BAD_CAST name, BAD_CAST content) ;

    xmlDocSetRootElement(doc, new_node) ;

    return new_node ;

  }
  else {

    return xmlNewDocNode(doc, NULL, BAD_CAST name, BAD_CAST content) ;
  }

}

xmlAttrPtr set_property(xmlNodePtr node, const char *name, const char *value) {

  // Set or reset a property.

  return xmlSetProp(node, BAD_CAST name, BAD_CAST value) ;

}

void replace_node_content(xmlNodePtr node, const char *new_content) {

  xmlNodeSetContent(node, BAD_CAST new_content) ;

}


xmlChar *get_prop_name(xmlNodePtr node, const char *name) {

 return xmlGetProp(node, BAD_CAST name) ; /** It's up to the caller to free the memory with xmlFree(). */

}

xmlNodePtr add_child(xmlNodePtr parent, xmlNodePtr child) {

  return xmlAddChild(parent, child) ;

}

void set_compression(xmlDocPtr doc, int mode) {

  xmlSetDocCompressMode(doc, mode) ;

  return ;

}


int unset_property(xmlNodePtr node, const char *attr) {

  /** Return 0 on success ; -1 on failure. **/

  return xmlUnsetProp(node, BAD_CAST attr) ;
}

void rename_attribut(xmlNodePtr node, const char *old_attr, const char *new_attr) {

  xmlChar *val;

  val = xmlGetProp(node, BAD_CAST old_attr);

  if (val != NULL) {
    xmlSetProp(node, BAD_CAST new_attr, val);
    xmlUnsetProp(node, BAD_CAST old_attr);
  }

  return ;
}
