# This makefile builds simple win32-application containing single cpp-file  
# Rule 'run' executes the application under Windows OS and stores return code in ".exitcode"  file
# TOP_LEVEL points to root directory of NMPP and should be exported from parent Makefile or set manualy in toplevel.mk (for local usage)
.SUFFIXES:

ifndef VS80COMNTOOLS
$(warning *** WARNING: 'VS80COMNTOOLS' environment variable is not defined! Microsoft Visual Studio 8  might not have installed correctly. )
.DEFAULT_GOAL := skip
endif 

ROOT             = ../../../..
include $(ROOT)/env.mk#--------------  target & input dirs -------------------
PROJECT          = sobel
INC_DIRS         = -I"$(NMPP)/include" -I"$(VSHELL)/include" -I"$(MC5103)/libload" -I$(ROOT)/deps/connector
LIB_DIRS         = -L"$(NMPP)/lib"     -L"$(VSHELL)/lib"     -L"$(MC5103)/libload"
SRC_DIRS         = ..
TMP_DIR          = Release
TMP_DIRD         = Debug
TARGET           = $(TMP_DIR)/$(PROJECT).exe
TARGETD          = $(TMP_DIRD)/$(PROJECT).exe
LIBS             = mc5103load.lib vshell.lib
LIBSD            = $(subst vs80,vs80d,$(LIBS))

#--------------  Visual Studio config (for vs8.mk)--
HEADER_DIRS      = $(ROOT)/include
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
	
vs8: $(PROJECT).vcproj

$(PROJECT).vcproj: Makefile
	make --file=$(ROOT)/deps/projector/vs8.mk vc-app --silent >$(@)

	
skip:
	@echo Compilation is skipped!
	

