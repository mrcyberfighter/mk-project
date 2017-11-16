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

#include "./xml_getter.h"

static bool get_node_property(xmlNodePtr n, const char *name) {

  xmlChar *prop_value = get_prop_name(n, name) ;

  bool ret = false ;

  if (prop_value != NULL) {

    ret = (! strcmp((const char *) prop_value, "T")) ? true : false ;
 
    xmlFree(prop_value) ;
  
  }
   
  return ret ;
}

static void parse_xml(xmlNodePtr node, Project *project) {

  xmlNodePtr n = NULL ;

  for (n = node ; n != NULL ; n = n->next) {

    if ((XML_ELEMENT_NODE == n->type) && (n->children != NULL)) {

      #ifdef DEBUG
      fprintf(stdout,"Node: %s\n", (const char *) n->name) ;
      #endif

      if (! strcmp((const char *) n->name, "PRG_LANG") ) {
  
        project->language = g_strdup((char *) xmlNodeGetContent(n)) ;
 
        if (project->language != NULL) {
     
     
     
          #ifdef DEBUG
          fprintf(stdout,"%s project->language == %s\n", __func__, project->language) ;
          #endif

        }

        parse_xml(n->children, project) ;

      }
      else if (! strcmp((const char *) n->name, "PRGNAME") ) {

        project->prgname = g_strdup((char *) xmlNodeGetContent(n)) ;

        if (project->prgname != NULL) {

          #ifdef DEBUG
          fprintf(stdout,"%s project->prgname == %s\n",  __func__,  project->prgname) ;
          #endif

        }

        parse_xml(n->children, project) ;

      }
      else if (! strcmp((const char *) n->name, "EXT_SRC") ) {

        project->ext_src = g_strdup((char *) xmlNodeGetContent(n)) ;

        if (project->ext_src != NULL) {

          #ifdef DEBUG
          fprintf(stdout,"%s project->ext_src == %s\n",  __func__, project->ext_src) ;
          #endif

        }

        parse_xml(n->children, project) ;

      }
      else if (! strcmp((const char *) n->name, "EXT_HDR") ) {

        project->ext_hdr = g_strdup((char *) xmlNodeGetContent(n)) ;

        if (project->ext_hdr != NULL) {

          #ifdef DEBUG
          fprintf(stdout,"%s project->ext_hdr == %s\n",  __func__, project->ext_hdr) ;
          #endif

        }

        parse_xml(n->children, project) ;

      }
      else if (! strcmp((const char *) n->name, "LICENSING")) {
      
         project->use_licensing_dkb_format      = get_node_property(n, "USE_DBK") ;
         project->use_licensing_epub_format     = get_node_property(n, "USE_EPUB") ;
         project->use_licensing_pdf_format      = get_node_property(n, "USE_PDF") ;
         project->use_licensing_html_format     = get_node_property(n, "USE_HTML") ;
         project->use_licensing_latex_format    = get_node_property(n, "USE_LATEX") ;
         project->use_licensing_texinfo_format  = get_node_property(n, "USE_TEXINFO") ;
         project->use_licensing_text_format     = get_node_property(n, "USE_TEXT") ;
      
         parse_xml(n->children, project) ;
      
      }
      else if (! strcmp((const char *) n->name, "LICENSE")) {
     
        project->license = g_strdup((char *) xmlNodeGetContent(n)) ;
     
        #ifdef DEBUG
        fprintf(stdout,"%s project->license == %s\n", __func__, project->license) ;
        #endif
      
        parse_xml(n->children, project) ;
      
      }
      else {

        parse_xml(n->children, project);
      }


    }
  }

  return ;

}

static bool is_mk_project_xml(xmlNodePtr node) {

  xmlNodePtr n ;

  for (n = node ; n != NULL ; n = n->next) {

    if ((XML_ELEMENT_NODE == n->type) && (n->children != NULL)) {

      #ifdef DEBUG
      fprintf(stdout,"Node: %s\n", (const char *) n->name) ;
      #endif

      if (! strcmp((const char *) n->name, "mk-project") ) {

        return true ;

      }
      else {

        is_mk_project_xml(n->children) ;

      }


    }
  }

  return false ;

}

bool valid_xml_mk_project(const char *filepath) {

  xmlDocPtr xmldoc = NULL ;



  //xmldoc = xmlParseFile(filepath) ;
  xmldoc = xmlParseEntity(filepath) ;

  //xmldoc->parseFlags = XML_PARSE_NOERROR | XML_PARSE_NOWARNING ;

  if (xmldoc == NULL) {

    #ifdef DEBUG
    fprintf(stderr,"Failed to acess xml file\n") ;
    #endif

    return false ;
  }



  xmlNodePtr root = NULL ;

  root = xmlDocGetRootElement(xmldoc) ;

  #ifdef DEBUG
  xmlDocFormatDump(stderr, xmldoc, 1) ;
  #endif

  if (root == NULL) {

    xmlFreeDoc(xmldoc) ;

    #ifdef DEBUG
    fprintf(stderr,"Cannot access root node\n") ;
    #endif

    return false ;
  }

  if (! is_mk_project_xml(root) ) {

    xmlFreeDoc(xmldoc) ;

    return false ;
  }

  xmlFreeDoc(xmldoc) ;

  return true ;

}

void get_xml_data(const char *filepath, Project *project) {

  xmlDocPtr xmldoc = NULL ;

  xmldoc = xmlParseFile(filepath) ;

  if (xmldoc == NULL) {

    #ifdef DEBUG
    fprintf(stderr,"Failed to acess xml file\n") ;
    #endif

    return ;
  }

  xmlNodePtr root = NULL ;

  root = xmlDocGetRootElement(xmldoc) ;

  if (root == NULL) {

    #ifdef DEBUG
    fprintf(stderr,"Cannot access root node\n") ;
    #endif

    return ;
  }

  parse_xml(root, project) ;

  xmlFreeDoc(xmldoc) ;

  return ;

}



