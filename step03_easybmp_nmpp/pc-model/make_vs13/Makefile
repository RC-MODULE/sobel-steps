# This makefile builds simple win32-application containing single cpp-file  
# Rule 'run' executes the application under Windows OS and stores return code in ".exitcode"  file
# TOP_LEVEL points to root directory of NMPP and should be exported from parent Makefile or set manualy in toplevel.mk (for local usage)
.SUFFIXES:



ifndef VS120COMNTOOLS
$(warning *** WARNING: 'VS120COMNTOOLS' environment variable is not defined! Microsoft Visual Studio 13  might not have installed correctly. )
.DEFAULT_GOAL := skip
endif 

ifeq ($(OS),Windows_NT)
  SHELL = cmd
endif






ROOT             = ../../..
PATH            := $(realpath $(ROOT))/deps/gnuwin32/bin;$(PATH)
NMPP             = $(ROOT)/deps/nmpp
#--------------  target & input dirs -------------------
PROJECT          = sobel
INC_DIRS         = -I"$(NMPP)/include" -I../.. -I$(ROOT)/deps/EasyBMP
LIB_DIRS         = -L"$(NMPP)/lib"     
SRC_DIRS         = .. ../.. $(ROOT)/deps/EasyBMP
TMP_DIR          = Release
TMP_DIRD         = Debug
TARGET           = $(TMP_DIR)/$(PROJECT).exe
TARGETD          = $(TMP_DIRD)/$(PROJECT).exe
LIBS             = nmpp_vs13.lib
LIBSD            = $(subst vs13,vs13d,$(LIBS))

#--------------  Visual Studio config (for vs8.mk)--
HEADER_DIRS      = ..
RESOURCES        =Makefile

# regular search of *.c *.cpp,*.asm sources in all $(SRC_DIRS)
ALL_CPP =$(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
ALL_C   =$(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
ALL_H   =$(wildcard $(addsuffix /*.h,$(HEADER_DIRS)))


#======================== BUILD RULES ====================================


.PHONY: run clean vs13

VPATH    = $(subst -l,,$(LIB_DIRS)) 

$(TARGETD): $(PROJECT).vcxproj $(ALL_CPP)
	"$(VS120COMNTOOLS)vsvars32" && msbuild $(PROJECT).vcxproj

run: $(TARGETD)
	$(TARGETD)

clean:
	-rm -f -r .* *.o *.ncb *.ilk $(TARGET) $(TARGETD) *.dep *.ac *.map *.suo *.ncb *.sdf *.htm *.user $(TMP_DIR) $(TMP_DIRD)
	
export HEADER_DIRS
export INC_DIRS LIB_DIRS
export LIBS LIBSD
export ALL_CPP ALL_ASM ALL_C ALL_H
export TARGET TARGETD
	
vs13: $(PROJECT).vcxproj

$(PROJECT).vcxproj: Makefile
	make --file=$(ROOT)/deps/projector/vs13.mk vc-app --silent >$(@)	

skip:
	@echo Compilation is skipped!
	

