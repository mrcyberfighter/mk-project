# No license prefixing, you are free to use the license you want.

#################### [START] Distributing targets [START] ######################

COMPRESSION = %d

DIST_DIR  = ./dist

RELEASE_DIR = ./.release

PATH_TO_RELEASE_FILE = $(RELEASE_DIR)/RELEASE.txt

GET_RELEASE_NB = $(shell cat $(PATH_TO_RELEASE_FILE))

SET_RELEASE_NB = $(file $1 > $(PATH_TO_RELEASE_FILE))


DIST_NAME = $(PRGNAME)_$(VERSION)-$(RELEASE)

DIST_NAME = $(PRGNAME)_$(VERSION)-$$RELEASE

DIST_EXCLUDE_FOLDER = bin dist

TAR_EXCLUDE_CMD = $(foreach var, $(DIST_EXCLUDE_FOLDER), --exclude=$(var)/*)

ZIP_EXCLUDE_CMD = $(foreach var, $(DIST_EXCLUDE_FOLDER), -x $(var)/\*)

RAR_EXCLUDE_CMD = $(foreach var, $(DIST_EXCLUDE_FOLDER), -x=./$(var)/*)



.PHONY: $(DIST_DIR)

$(DIST_DIR):
	@- if `test ! -d $(DIST_DIR)` ; then $(MKDIR_P) $(DIST_DIR) ; fi
	@- if `test ! -d $(RELEASE_DIR)` ; then $(MKDIR_P) $(RELEASE_DIR) ; fi
	@- if `test ! -f  $(PATH_TO_RELEASE_FILE)` ; then echo 0 > $(PATH_TO_RELEASE_FILE) ; fi

ifneq ($(ZIP), )
.ONESHELL:
.PHONY: pkg-zip
pkg-zip: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)_$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_RELEASE_FILE)
	$(ZIP) -r  $(ZIP_EXCLUDE_CMD)  -$(COMPRESSION) -o -v  $(TMP_DIR)/$(DIST_NAME).zip .
	$(ZIP) $(TMP_DIR)/$(DIST_NAME).zip $(DIST_EXCLUDE_FOLDER)
	$(MV) $(TMP_DIR)/$(DIST_NAME).zip $(DIST_DIR)/$(DIST_NAME).zip
	$(ZIP) -T $(DIST_DIR)/$(DIST_NAME).zip
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).zip
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).zip
endif

ifneq ($(TAR), )
.ONESHELL:
.PHONY: pkg-tar
pkg-tar: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)_$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_RELEASE_FILE)
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar $(DIST_DIR)/$(DIST_NAME).tar
	$(TAR) --test-label -f $(DIST_DIR)/$(DIST_NAME).tar
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar
endif

ifneq ($(TAR), )
ifneq ($(GZ), )
.ONESHELL:
.PHONY: pkg-tar-gz
################################################################
# This work with the archive manager decompressing or          #
# by using the tar tool like this:                             #
# $ tar --gzip -xf $(TARNAME).tar.gz                           #
# Uncompress all in the current directory                      #
################################################################
pkg-tar-gz: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)_$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_RELEASE_FILE)
	$(TAR) $(TAR_EXCLUDE_CMD) -acvf  $(TMP_DIR)/$(DIST_NAME).tar.gz .
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar.gz $(DIST_DIR)/$(DIST_NAME).tar.gz
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar.gz $(TMP_DIR)/$(DIST_NAME).tar.gz
	$(GZ) -v -t $(DIST_DIR)/$(DIST_NAME).tar.gz
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar.gz
endif
endif

ifneq ($(TAR), )
ifneq ($(BZ2), )
.ONESHELL:
.PHONY: pkg-tar-bz2
################################################################
# This work with the archive manager decompressing or          #
# by using the tar tool like this:                             #
# $ tar --bzip2 -xf $(TARNAME).tar.bz2                         #
# Uncompress all in the current directory                      #
################################################################
pkg-tar-bz2: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)_$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_RELEASE_FILE)
	$(TAR) $(TAR_EXCLUDE_CMD) -acvf  $(TMP_DIR)/$(DIST_NAME).tar.bz2 .
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar.bz2 $(DIST_DIR)/$(DIST_NAME).tar.bz2
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar.bz2 $(TMP_DIR)/$(DIST_NAME).tar.bz2
	$(BZ2) -v -t $(DIST_DIR)/$(DIST_NAME).tar.bz2
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar.bz2
endif
endif

ifneq ($(TAR), )
ifneq ($(XZ), )
.ONESHELL:
.PHONY: pkg-tar-lzma
################################################################
# This work with the archive manager decompressing or          #
# by using the tar tool like this:                             #
# $ tar --lzma -xf $(TARNAME).tar.lzma                         #
# Uncompress all in the current directory                      #
################################################################
pkg-tar-lzma: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)_$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_RELEASE_FILE)
	$(TAR) $(TAR_EXCLUDE_CMD) -acvf  $(TMP_DIR)/$(DIST_NAME).tar.lzma .
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar.lzma $(DIST_DIR)/$(DIST_NAME).tar.lzma
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar.lzma
	$(XZ) -v -t $(DIST_DIR)/$(DIST_NAME).tar.lzma
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar.lzma
endif
endif

ifneq ($(TAR), )
ifneq ($(LZOP), )
.ONESHELL:
.PHONY: pkg-tar-lzop
################################################################
# This work with the archive manager decompressing or          #
# by using the tar tool like this:                             #
# $ tar --lzop -xf $(TARNAME).tar.lzo                          #
# Uncompress all in the current directory                      #
################################################################
pkg-tar-lzop: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)_$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_RELEASE_FILE)
	$(TAR) $(TAR_EXCLUDE_CMD) -acvf  $(TMP_DIR)/$(DIST_NAME).tar.lzo .
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar.lzo $(DIST_DIR)/$(DIST_NAME).tar.lzo
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar.lzo
	$(LZOP) -v -t $(DIST_DIR)/$(DIST_NAME).tar.lzo
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar.lzo
endif
endif

ifneq ($(TAR), )
ifneq ($(LZIP), )
.ONESHELL:
.PHONY: pkg-tar-lzip
################################################################
# This work with the archive manager decompressing or          #
# by using the tar tool like this:                             #
# $ tar --lzip -xf $(TARNAME).tar.lz                           #
# Uncompress all in the current directory                      #
################################################################
pkg-tar-lzip: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)_$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_RELEASE_FILE)
	$(TAR) $(TAR_EXCLUDE_CMD) -acvf  $(TMP_DIR)/$(DIST_NAME).tar.lz .
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar.lz $(DIST_DIR)/$(DIST_NAME).tar.lz
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar.lz
	$(LZIP) -v -t $(DIST_DIR)/$(DIST_NAME).tar.lz
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar.lz
endif
endif

ifneq ($(TAR), )
ifneq ($(XZ), )
.ONESHELL:
.PHONY: pkg-tar-xz
################################################################
# This work with the archive manager decompressing or          #
# by using the tar tool like this:                             #
# $ tar --xz -xf $(TARNAME).tar.xz                             #
# Uncompress all in the current directory                      #
################################################################
pkg-tar-xz: $(DIST_DIR)
	$(MAKE) clean
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)_$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_RELEASE_FILE)
	$(TAR) $(TAR_EXCLUDE_CMD) -acvf  $(TMP_DIR)/$(DIST_NAME).tar.xz .
	$(MV) $(TMP_DIR)/$(DIST_NAME).tar.xz $(DIST_DIR)/$(DIST_NAME).tar.xz
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar.xz
	$(XZ) -v -t --format=xz $(DIST_DIR)/$(DIST_NAME).tar.xz
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).tar.xz
endif
endif

ifneq ($(RAR), )
.ONESHELL:
.PHONY: pkg-rar
######################################################################
# -m<n>   Set compression method:                                    #
#                                                                    #
#       -m0   store     do not compress file when adding to archive  #
#       -m1   fastest   use fastest method (less compressive)        #
#       -m2   fast      use fast compression method                  #
#       -m3   normal    use normal (default) compression method      #
#       -m4   good      use good compression method (more            #
#                       compressive, but slower)                     #
#       -m5   best      use best compression method (slightly more   #
#                       compressive, but slowest)                    #
#                                                                    #
#            If this switch is not specified, RAR uses -m3 method    #
#            (normal compression).                                   #
######################################################################
pkg-rar: $(DIST_DIR)
	declare -i RELEASE=$(GET_RELEASE_NB)+1
	export RELEASE
	export DIST_NAME=$(PRGNAME)_$(VERSION)-$$RELEASE
	echo $(DIST_NAME)
	echo $$RELEASE >  $(PATH_TO_RELEASE_FILE)
	$(RAR) a $(TMP_DIR)/$(DIST_NAME).rar va $(RAR_EXCLUDE_CMD) -r -s .
	$(MV) $(TMP_DIR)/$(DIST_NAME).rar $(DIST_DIR)/$(DIST_NAME).rar
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).rar
	$(RAR) t $(DIST_DIR)/$(DIST_NAME).rar
	$(LS_SIZE) $(DIST_DIR)/$(DIST_NAME).rar
endif

#################### [END] Distributing targets [END] ##########################
