ROOT=../../..


include $(ROOT)/global.mk
	   
HOST = host
TARGET = target.abs
EXE  = $(call OSX,bin/Release/$(HOST))

vs2015: 
	premake5 vs2015
	"$(VS140COMNTOOLS)vsvars32" && msbuild $(HOST).vcxproj /p:Configuration=Release
	$(MAKE) -f Makefile0
	
vs2005:
	premake5 vs2005
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(HOST).vcproj

$(EXE): vs2015
	
.PHONY: run 
	
run:	
	$(EXE)
	
	
$(TARGET): 	
	
	
	
include $(ROOT)/clean.mk	