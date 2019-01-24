
include $(ROOT)/global.mk
-include ../local.mk
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:
PROJECT = test_mc7601

INC_DIRS = -I"$(NMPP)/include" -I"$(MC7601)/include" -I$(HAL)/include -I"$(HAL)/include" -I../.. -I$(ROOT)/deps/EasyPGM
LIB_DIRS = -L"$(NMPP)/lib"  -L"$(MC7601)/lib" -L$(HAL)/lib
LIBS     = hal-mc7601.lib mc7601_ll_nm.lib nmpp-nmc3.lib libint_soc.lib  
TARGET   = main.abs
CFG      = mc7601brd.cfg
HEAP    ?= -heap=16384 -heap1=16384 -heap2=16384 -heap3=16384
#            [L00]:64kB   [L01]:64kB  [G00]:64kB   [G01]:64kB

SRC_DIRS = .. ../.. $(SRC_DEPS)

SRC_CPP  = $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,$(SRC_DIRS)))


VPATH    = $(subst -L,,$(LIB_DIRS)) $(NEURO)/lib

$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile 
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -soc -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) $(HEAP) -full_names


PATH:=$(MC5103)/bin;$(PATH)

run: $(TARGET)
	mc7601run $(TARGET) $(RUN_OPT_MC7601)
	
vs2015:  
	premake5 vs2015
	"$(VS140COMNTOOLS)vsvars32" && msbuild $(PROJECT).vcxproj /p:Configuration=Release
	
vs2005:    	
	premake5 vs2005
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(PROJECT).vcproj
	


-include $(ROOT)/local.mk
-include $(ROOT)/clean.mk

	

