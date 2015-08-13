# This makefile builds simple win32-application containing single cpp-file  
# Rule 'run' executes the application under Windows OS and stores return code in ".exitcode"  file
# TOP_LEVEL points to root directory of NMPP and should be exported from parent Makefile or set manualy in toplevel.mk (for local usage)
.SUFFIXES:

ifndef VS120COMNTOOLS
$(warning *** WARNING: 'VS120COMNTOOLS' environment variable is not defined! Microsoft Visual Studio 13  might not have installed correctly. )
.DEFAULT_GOAL := skip
endif 

ROOT             = ../../../..
include $(ROOT)/environment.mk
#--------------  target & input dirs -------------------
PROJECT          = sobel
INC_DIRS         = -I"$(NMPP)/include" -I"$(VSHELL32)/include" -I"$(MC7601)/include" -I$(NMPROFILER)/include -I$(ROOT)/deps/connector
LIB_DIRS         = -L"$(NMPP)/lib"     -L"$(VSHELL32)/lib"     -L"$(MC7601)/lib"
SRC_DIRS         = ..
TMP_DIR          = Release
TMP_DIRD         = Debug
TARGET           = $(TMP_DIR)/$(PROJECT).exe
TARGETD          = $(TMP_DIRD)/$(PROJECT).exe
LIBS             = vshell32.lib mc7601_ll_pc.lib
LIBSD            = $(subst vs80,vs80d,$(LIBS))

#--------------  Visual Studio config (for vs8.mk)--
HEADER_DIRS      = $(ROOT)/connector 
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
	$(MAKE) -C ../../nm DEBUG=y
	$(TARGETD)

clean:
	-$(OS_RM) .* *.o *.ncb *.ilk *.dep *.ac *.map *.suo *.ncb *.user
	-$(OS_RD) $(TMP_DIR) $(TMP_DIRD)
	
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
	

