
############# CRÉATION DES VARIABLES GLOBALES #############
# Options de compilation
include Makefile.compilation
ifeq ($(OS),Windows_NT)
	include Makefile_wind.mk

else
	include Makefile_linux.mk

endif

