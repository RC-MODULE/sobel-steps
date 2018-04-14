ROOT = ../..
include $(ROOT)/global.mk
#-include ../local.mk

# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:


ifndef MC5103
$(error ERROR: 'MC5103' environment variable is not defined!  )
endif 


BOARD    = mc5103
HOST     = $(BOARD)-x86
PROJECT  = sobel
CONFIGURATION = Debug

TARGET   = $(PROJECT).abs
INC_DIRS = -I"$(MC5103)/include" -I$(ROOT)/include -I"$(NEURO)/include" -I$(HAL)/include -I$(NMPP)/include -I../src/common
LIB_DIRS = -L"$(MC5103)/lib" -L$(HAL)/lib -L$(NMPP)/lib
LIBS     = hal-mc5103.lib mc5103lib.lib nmpp-nmc3.lib libint05.lib
CFG      = mc5103brd.cfg
SRC_DIRS = ../src_target ../src/common ../src/nm
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,$(SRC_DIRS)))
HEAPS    = -heap=25000 -heap1=32500 -heap2=32500 -heap3=32500 


ALL: $(TARGET) 

$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile
	nmcc -nmc3 -g -O2 -o$(TARGET) -m.main.map  -c$(CFG) $(HEAPS) $(SRC_CPP) $(SRC_ASM) $(LIBS)  $(INC_DIRS) $(LIB_DIRS) 
PATH:=$(MC5103)/bin;$(PATH)
	
vs2005: $(PROJECT).sln
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(PROJECT).sln  "$(CONFIGURATION)|Win32"
	

vs2015:	$(PROJECT).sln
	"$(VS140COMNTOOLS)vsvars32" && msbuild $(PROJECT).sln /t:Build /p:Configuration=$(CONFIGURATION)

	
$(PROJECT).sln:	premake5.lua 
	premake5 $(MAKECMDGOALS) 

run: 
	bin\debug\$(HOST)
	
	
include $(ROOT)/clean.mk
	
