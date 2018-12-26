

include $(ROOT)/global.mk
	   
PROJECT = host-x86
TARGET  = $(call OSX,bin/Release/$(PROJECT))

vs2015: 
	premake5 vs2015
#	"$(VS140COMNTOOLS)vsvars32" && msbuild $(PROJECT).vcxproj
	"$(VS140COMNTOOLS)vsvars32" && msbuild $(PROJECT).vcxproj /p:Configuration=Release

	
vs2005:
	premake5 vs2005
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(PROJECT).vcproj

$(TARGET): vs2015
	
.PHONY: run 
	
run:	
	$(TARGET)
	

include $(ROOT)/clean.mk	