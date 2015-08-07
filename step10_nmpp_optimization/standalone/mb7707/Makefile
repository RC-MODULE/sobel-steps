###########################################################################################
# (RC)Module 7/8/2015
#
# This is a universal Makefile for NeuroMatrix projects (application or library) 
# with automatic search of source files , compiling and linking.
# Makefile is processed by GNU make and may be used both in Linux and Windows OS
# Under OS Windows you need:
# * GNU Make           http://gnuwin32.sourceforge.net/packages/make.htm
#
# USAGE:
#   For release build                    run 'make'
#   For debug   build                    run 'make DEBUG=y'
#   For debug & release  build           run 'make all'
#   For full  rebuild                    run 'make -B'
#   Multithread build (speed up)         run 'make -j4'
#   To clean                             run 'make clean'
#   To create VisualStudio 2005 project  run 'make vs8'
#   To create VisualStudio 2013 project  run 'make vs13'
#   Execute target                       run 'make run'
#   Execute debug target                 run 'make rund'
#
# WARNING:
#   Makefile is sensitive to leading or trailing spaces and backslashes in the pathes
#
# DEFENITIONS:
#   PROJECT         - project name     
#   TARGET          - output target (.lib or .abs) file with path
#   INC_DIRS        - set of search pathes for the macro libraries and includes (with -I flag separated)
#   SRC_DIRS        - set of explicit  search pathes of all (.c .cpp .asm) source files (with space separated)
#   LIB_DIRS        - set of search library pathes (with -l flag separated)
#   TMP_DIR         - temporary build-folder (Debug/Release)
#   LIBS            - set of (.lib) libraries to be linked (with space separated)
#   
#   CC              - C/C++ compiler(nmcpp/nmcc)
#   CC_FLAGS        - C/C++ compiler(nmcpp/nmcc) flags   
#   AS				- assembler(asm/nmcc)
#   AS_FLAGS        - assembler(asm/nmcc) flags for compiling of pure .asm files 
#   AS_FLAGS_C2ASM  - assembler(asm/nmcc) flags for compiling of .asm files compiled from .c/.cpp sources
#   BUILDER         - builder  (libr/linker) 			
#   BUILDER_FLAGS   - build flags of (libr/linker)
#
#   HEADER_DIRS     - set of pathes for .h   files to be included into Visual Studio project (with space separated)
#   RESOURCES       - set of any additionals files to be included into Visual Studio project
###############################################################################################

#============== PROJECT & BUILD CONFIGURATION ==========
#

ifndef MB7707_MAC
$(warning*** WARNING: 'MB7707_MAC' environment variable is not defined! Loading abs-file on MB7707 board is not possible. )
endif 

ROOT             = ../../..
include $(ROOT)/env.mk
#--------------  target & input dirs -------------------
PROJECT          = sobel_mb7707_nm
OUT_DIR          = .
TARGET           = $(OUT_DIR)/$(PROJECT).abs
INC_DIRS         = -I"$(NEURO)/include" -I"$(MB7707)/include" -I"$(NMPP)/include" -I. -I../.. -I$(ROOT)/deps/EasyPGM -I../../src/common
SRC_DIRS         = .. ../../src/nm ../../src/common $(ROOT)/deps/EasyPGM
LIB_DIRS         = -l"$(NEURO)/lib" -l"$(MB7707)/lib" -l"$(NMPP)/lib"
TMP_DIR          = Release
#--------------  RELEASE/ALL config -------------------
AS               = asm 				 
AS_FLAGS         = -nmc3 -nm2ms  $(INC_DIRS)
AS_FLAGS_C2ASM   = -nmc3 -nm2ms  $(INC_DIRS)
LIBS             = libint_soc.lib mb7707lib.lib libc05.lib cppnew05.lib nmpp_nmc3.lib
CC               = nmcpp
CC_FLAGS         = -6405 -DNEURO -OPT2 -inline 
BUILDER          = linker
BUILDER_FLAGS    = -cmb7707brd.cfg -m  -heap=26700 -heap1=32700 -heap2=32700 -heap3=32700 -full_names -o$(TARGET) $(LIB_DIRS)
#--------------  DEBUG config -------------------------
ifdef DEBUG      
TARGET           = $(OUT_DIR)/$(PROJECT)d.abs
CC_FLAGS         = -6405 -DNEURO -OPT0 -inline -debug 
LIBS            := $(subst nmc3.lib,nmc3d.lib,$(LIBS))
AS_FLAGS        += -ga
BUILDER_FLAGS   += -d0
TMP_DIR          = Debug
endif 
#--------------  Visual Studio config (for vs8.mk)--
HEADER_DIRS      = ../../src/common
RESOURCES        =Makefile mb7707brd.cfg

#=================== SOURCE & OBJECTS COLLECTION ===========================

.SUFFIXES:

# regular search of *.c *.cpp,*.asm sources in all $(SRC_DIRS)
ALL_CPP =$(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
ALL_ASM =$(wildcard $(addsuffix /*.asm,$(SRC_DIRS)))
ALL_C   =$(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
ALL_H   =$(wildcard $(addsuffix /*.h,$(HEADER_DIRS)))
VPATH    = $(SRC_DIRS)

# collecting of objects
OBJECTS_CPP = $(notdir $(patsubst %.cpp,%.o,$(ALL_CPP)))
OBJECTS_ASM = $(notdir $(patsubst %.asm,%.o,$(ALL_ASM)))
OBJECTS_C   = $(notdir $(patsubst %.c,%.o,$(ALL_C)))
OBJECTS     = $(addprefix $(TMP_DIR)/,$(OBJECTS_C) $(OBJECTS_CPP)  $(OBJECTS_ASM))

#======================== BUILD RULES ====================================
.PHONY:all  clean skip

.DEFAULT_GOAL=default
default: $(TMP_DIR) $(OUT_DIR)  $(TARGET)

all: 
	$(MAKE) -j4 DEBUG=y
	$(MAKE) -j4

	
$(TMP_DIR):
	-mkdir "$(@)"

$(TARGET): $(TMP_DIR) $(OBJECTS) Makefile
	$(BUILDER) $(BUILDER_FLAGS) $(OBJECTS) $(LIBS)

$(OUT_DIR): 
	-mkdir "$(@)"
	
$(TMP_DIR)/%.o: %.asm 
	$(AS) $(AS_FLAGS) $(<) -o$(@)
	
$(TMP_DIR)/%.o: $(TMP_DIR)/%.asmx 
	$(AS) $(AS_FLAGS_C2ASM) $(<) -o$(@)

$(TMP_DIR)/%.asmx: %.cpp 
	$(CC) $(CC_FLAGS) $(<) -O$(@) $(INC_DIRS) 

$(TMP_DIR)/%.asmx: %.c
	$(CC) $(CC_FLAGS) $(<) -O$(@) $(INC_DIRS) 

clean:
	-$(OS_RM) *.abs *.o *.ncb *.ilk  *.dep *.ac *.map *.suo *.user *.ncb *.pgm
	-$(OS_RD) Debug Release
 

run: $(TARGET)
	mb7707run -i -a$(MB7707_MAC) $(TARGET) --send_file_name=$(ROOT)/input/Lena224x240.pgm --send_sect=.data_shared_src.bss --recv_file_name=Sobel.pgm --recv_sect=.data_shared_dst.bss  --recv_size=0x348a

#========================== Visual Studio 8 support ===================
export ALL_CPP ALL_ASM ALL_C ALL_H

vs8: $(PROJECT).vcproj

$(PROJECT).vcproj: Makefile
	make --file=$(ROOT)/deps/projector/vs8.mk nmc-app --silent >$(@)

vs13: $(PROJECT).vcxproj

$(PROJECT).vcxproj: Makefile
	make --file=$(ROOT)/deps/projector/vs13.mk nmc-app --silent >$(@)

	

