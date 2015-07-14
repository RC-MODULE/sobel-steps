# This makefile builds simple win32-application containing single cpp-file  
# Rule 'run' executes the application under Windows OS and stores return code in ".exitcode"  file
# TOP_LEVEL points to root directory of NMPP and should be exported from parent Makefile or set manualy in toplevel.mk (for local usage)
.SUFFIXES:



ifndef VS80COMNTOOLS
$(warning *** WARNING: 'VS80COMNTOOLS' environment variable is not defined! Microsoft Visual Studio 8  might not have installed correctly. )
.DEFAULT_GOAL := skip
endif 

ifeq ($(OS),Windows_NT)
  SHELL = cmd
endif






ROOT = ../../..
NMPP = $(ROOT)/deps/nmpp
#--------------  target & input dirs -------------------
PROJECT          = sobel
INC_DIRS         = -I"$(NMPP)/include" -I"$(VSHELL)/include" -I../..
LIB_DIRS         = -L"$(NMPP)/lib"     -L"$(VSHELL)/lib"
SRC_DIRS         = .. ../.. 
TMP_DIR          = Release
TMP_DIRD         = Debug
TARGET           = $(TMP_DIR)/$(PROJECT).exe
TARGETD          = $(TMP_DIRD)/$(PROJECT)d.exe
LIBS             = vshell.lib nmpp_vs80.lib
LIBSD            = $(subst vs80,vs80d,$(LIBS))

#--------------  Visual Studio config (for vs8.mk)--
HEADER_DIRS      = ../..
RESOURCES        =Makefile

# regular search of *.c *.cpp,*.asm sources in all $(SRC_DIRS)
ALL_CPP =$(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
ALL_C   =$(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
ALL_H   =$(wildcard $(addsuffix /*.h,$(HEADER_DIRS)))


#======================== BUILD RULES ====================================


.PHONY: run clean 

VPATH    = $(subst -l,,$(LIB_DIRS)) 

$(TARGETD): $(PROJECT).vcproj $(ALL_CPP)
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(PROJECT).vcproj

run: $(TARGETD)
	$(TARGETD)
	
clean:
	-rm -f -r .* *.o *.ncb *.ilk $(TARGET) $(TARGETD) *.dep *.ac *.map *.suo *.ncb *.user $(TMP_DIR) $(TMP_DIRD)
	
export HEADER_DIRS
export INC_DIRS LIB_DIRS
export LIBS LIBSD
export ALL_CPP ALL_ASM ALL_C ALL_H
export TARGET TARGETD
	
vs8: $(PROJECT).vcproj

$(PROJECT).vcproj: Makefile
	make --file=$(ROOT)/deps/projector/vs8.mk vc-app --silent >$(@)

	
skip:
	@echo Compilation is skipped!
	

