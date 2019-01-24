
include $(ROOT)/global.mk

-include ../local.mk
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:



PROJECT  = test_mc5103
INC_DIRS = -I"$(NMPP)/include" -I"$(MC5103)/include" -I"$(HAL)/include" -I../.. -I$(ROOT)/deps/EasyPGM
LIB_DIRS = -L"$(NMPP)/lib"  -L"$(MC5103)/lib" -L$(HAL)/lib
LIBS     = hal-mc5103.lib mc5103lib.lib nmpp-nmc3.lib libint05.lib  
TARGET   = main.abs
CFG      = mc5103brd.cfg
HEAP    ?= -heap=4194304 -heap1=16384 -heap2=16384 -heap3=16384
#            [L00]:16MB   [L01]:64kB  [G00]:64kB   [G01]:64kB

SRC_DIRS = . .. ../.. ../../src/nm ../../src/common $(SRC_DEPS)

SRC_CPP  = $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,$(SRC_DIRS)))


VPATH    = $(subst -L,,$(LIB_DIRS)) $(NEURO)/lib

$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile 
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -6405 -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) $(HEAP) -full_names


PATH:=$(MC5103)/bin;$(PATH)

run: $(TARGET)
	mc5103run  $(TARGET) $(RUN_OPT_MC5103)

vs2015:  
	premake5 vs2015
	"$(VS140COMNTOOLS)vsvars32" && msbuild $(PROJECT).vcxproj /p:Configuration=Release
	
vs2005:    	
	premake5 vs2005
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(PROJECT).vcproj
	

proflist:
	tclsh $(HAL)/script/generate_proflist.tcl proflist_generated.asm   
	@echo "========= first pass compiling ==========================="
	$(MAKE) 
	tclsh $(HAL)/script/generate_proflist.tcl proflist_generated.asm .main.map
	$(OS_RM) $(TARGET)
	@echo "========================================================="	

	
-include $(ROOT)/local.mk
-include $(ROOT)/clean.mk


	

