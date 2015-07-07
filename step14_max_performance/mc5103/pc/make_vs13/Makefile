# This makefile builds simple win32-application containing single cpp-file  
# Rule 'run' executes the application under Windows OS and stores return code in ".exitcode"  file
# TOP_LEVEL points to root directory of NMPP and should be exported from parent Makefile or set manualy in toplevel.mk (for local usage)
.SUFFIXES:



ifndef VS120COMNTOOLS
$(warning *** WARNING: 'VS120COMNTOOLS' environment variable is not defined! Microsoft Visual Studio 13  might not have installed correctly. )
.DEFAULT_GOAL := skip
endif 






ROOT             = ../../../..
PATH            := $(realpath $(ROOT))/deps/gnuwin32/bin;$(PATH)
MC5103           = $(ROOT)/deps/mc5103sdk
NMPROFILER       = $(ROOT)/deps/nmprofiler
#--------------  target & input dirs -------------------
PROJECT          = sobel
INC_DIRS         = -I"$(VSHELL)/include" -I"$(MC5103)/libload" -I$(ROOT)/deps/connector -I$(NMPROFILER)/include
LIB_DIRS         = -L"$(VSHELL)/lib"     -L"$(MC5103)/libload"
SRC_DIRS         = ..
TMP_DIR          = Release
TMP_DIRD         = Debug
TARGET           = $(TMP_DIR)/$(PROJECT).exe
TARGETD          = $(TMP_DIRD)/$(PROJECT).exe
LIBS             = mc5103load.lib vshell.lib
LIBSD            = $(subst vs80,vs80d,$(LIBS))

#--------------  Visual Studio config (for vs8.mk)--
HEADER_DIRS      = $(ROOT)/connector 
RESOURCES        =Makefile about.txt

# regular search of *.c *.cpp,*.asm sources in all $(SRC_DIRS)
ALL_CPP =$(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
ALL_C   =$(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
ALL_H   =$(wildcard $(addsuffix /*.h,$(HEADER_DIRS)))


#======================== BUILD RULES ====================================
-include vs13.mk

.PHONY: run clean vs8stdout vs13

VPATH    = $(subst -l,,$(LIB_DIRS)) 

$(TARGETD): $(PROJECT).vcproj $(ALL_CPP)
	"$(VS120COMNTOOLS)vsvars32" && msbuild $(PROJECT).vcxproj

run: $(TARGETD)
	$(MAKE) -C ../../nm DEBUG=y
	$(TARGETD)

clean:
	-rm -f -r .* *.o *.ncb *.ilk $(TARGET) $(TARGETD) *.dep *.ac *.map *.suo *.ncb *.sdf *.htm *.user $(TMP_DIR) $(TMP_DIRD)
	
$(PROJECT).vcproj: Makefile
	$(MAKE) vs13stdout --silent >$(PROJECT).vcxproj

vs13stdout:	
	$(info $(VC_APP))

vs13: $(PROJECT).vcproj

	
skip:
	@echo Compilation is skipped!
	

