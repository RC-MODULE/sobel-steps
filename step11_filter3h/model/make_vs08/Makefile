# This makefile builds simple win32-application containing single cpp-file  
# Rule 'run' executes the application under Windows OS and stores return code in ".exitcode"  file
# TOP_LEVEL points to root directory of NMPP and should be exported from parent Makefile or set manualy in toplevel.mk (for local usage)
.SUFFIXES:



ifndef VS80COMNTOOLS
$(warning *** WARNING: 'VS80COMNTOOLS' environment variable is not defined! Microsoft Visual Studio 8  might not have installed correctly. )
.DEFAULT_GOAL := skip
endif 






ROOT             = ../../..
PATH            := $(realpath $(ROOT))/deps/gnuwin32/bin;$(PATH)
NMPP             = $(ROOT)/deps/nmpp
#--------------  target & input dirs -------------------
PROJECT          = sobel
INC_DIRS         = -I"$(NMPP)/include" -I$(ROOT)/include -I"$(VSHELL)/include" -I../../src/common 
LIB_DIRS         = -L"$(NMPP)/lib"     -L$(ROOT)/lib     -L"$(VSHELL)/lib"
SRC_DIRS         = .. ../../src/common ../../src/pc  
TMP_DIR          = Release
TMP_DIRD         = Debug
TARGET           = $(TMP_DIR)/$(PROJECT).exe
TARGETD          = $(TMP_DIRD)/$(PROJECT)d.exe
LIBS             = vshell.lib nmpp_vs80.lib
LIBSD            = $(subst vs80,vs80d,$(LIBS))

#--------------  Visual Studio config (for vs8.mk)--
HEADER_DIRS      = ../..
RESOURCES        =Makefile about.txt

# regular search of *.c *.cpp,*.asm sources in all $(SRC_DIRS)
ALL_CPP =$(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
ALL_C   =$(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
#======================== BUILD RULES ====================================
-include vs8.mk

.PHONY: run clean vs8stdout vs8

VPATH    = $(subst -l,,$(LIB_DIRS)) 

$(TARGETD): $(PROJECT).vcproj $(ALL_CPP)
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(PROJECT).vcproj

run:  $(TARGETD) 
	$(TARGETD) 
	
clean:
	-rm -f -r .* *.o *.ncb *.ilk $(TARGET) $(TARGETD) *.dep *.ac *.map *.suo *.ncb *.user $(TMP_DIR) $(TMP_DIRD)
	
$(PROJECT).vcproj: Makefile
	$(MAKE) vs8stdout --silent >$(PROJECT).vcproj

vs8stdout:	
	$(info $(VC_APP))

vs8: $(PROJECT).vcproj

	
skip:
	@echo Compilation is skipped!
	

