# This makefile builds simple win32-application containing single cpp-file  
# Rule 'run' executes the application under Windows OS and stores return code in ".exitcode"  file
# TOP_LEVEL points to root directory of NMPP and should be exported from parent Makefile or set manualy in toplevel.mk (for local usage)
.SUFFIXES:



ifndef VS80COMNTOOLS
$(warning *** WARNING: 'VS80COMNTOOLS' environment variable is not defined! Microsoft Visual Studio 8  might not have installed correctly. )
.DEFAULT_GOAL := skip
endif 




ROOT             = ../../..
PATH            := $(realpath $(ROOT))/deps/gnuwin32/bin;$(PATH)/..
MB7707           = $(ROOT)/deps/mb7707sdk
#--------------  target & input dirs -------------------
PROJECT          = sobel
INC_DIRS         = -I"$(MB7707)/libload" -I$(ROOT)/deps/connector -I$(ROOT)/deps/EasyBMP
LIB_DIRS         = -L"$(MB7707)/libload"
SRC_DIRS         = .. $(ROOT)/deps/EasyBMP
TMP_DIR          = Release
TMP_DIRD         = Debug
TARGET           = $(TMP_DIR)/$(PROJECT).exe
TARGETD          = $(TMP_DIRD)/$(PROJECT)d.exe
LIBS             = mb7707load.lib
LIBSD            = $(subst vs80,vs80d,$(LIBS))

#--------------  Visual Studio config (for vs8.mk)--
HEADER_DIRS      = $(ROOT)/connector 
RESOURCES        =Makefile

# regular search of *.c *.cpp,*.asm sources in all $(SRC_DIRS)
ALL_CPP =$(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
ALL_C   =$(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
ALL_H   =$(wildcard $(addsuffix /*.h,$(HEADER_DIRS)))


#======================== BUILD RULES ====================================
-include vs8.mk

.PHONY: run clean vs8stdout vs8

VPATH    = $(subst -l,,$(LIB_DIRS)) 

$(TARGETD): $(PROJECT).vcproj $(ALL_CPP)
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(PROJECT).vcproj

run: $(TARGETD)
	$(MAKE) -C ../../nm DEBUG=y
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
	

