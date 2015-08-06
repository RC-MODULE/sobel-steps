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
  OS_RM = del /Q
  OS_RD = rd /Q /S 
else
  OS_RM = rm -f -r
  OS_RD = rm -d -r
endif






ROOT = ../../..
NMPP = $(ROOT)/deps/nmpp
#--------------  target & input dirs -------------------
PROJECT          = sobel
INC_DIRS         = -I"$(NMPP)/include" -I$(ROOT)/deps/EasyBMP 
LIB_DIRS         =     
SRC_DIRS         = .. $(ROOT)/deps/EasyBMP 
TMP_DIR          = Release
TMP_DIRD         = Debug
TARGET           = $(TMP_DIR)/$(PROJECT).exe
TARGETD          = $(TMP_DIRD)/$(PROJECT).exe
LIBS             = 
LIBSD            = $(subst vs80,vs80d,$(LIBS))

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
	-$(OS_RM) .* *.o *.ncb *.ilk *.dep *.ac *.map *.suo *.ncb *.user
	-$(OS_RD) $(TMP_DIR) $(TMP_DIRD) *.bmp
	
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
	

