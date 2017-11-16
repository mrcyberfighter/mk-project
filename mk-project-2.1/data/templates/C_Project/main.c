#include "./headers/includes.h"

#include "./headers/defines.h"

#include "./global_vars.h"

int main(int argc, char *argv[]) {

  if (argc > 1) {
  
    fprintf(stdout,"argument: %s", argv[1]) ;
  
  }

  #ifdef GETTEXT_SUPPORT
  setlocale (LC_ALL, "");
  bindtextdomain(PACKAGE, LOCALEDIR);
  textdomain(PACKAGE);

  bind_textdomain_codeset(PACKAGE, "UTF-8") ;
  #endif

  fprintf(stdout,"Hello world and welcome to %s\n", name) ;

  return 0 ;

}

