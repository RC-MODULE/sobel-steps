include $(ROOT)/global.mk
	   
HOST = host
TARGET = target
HOST_EXE   = $(call OSX,bin/Release/$(HOST))
TARGET_EXE = $(call OSX,bin/Release/$(TARGET))
vs2015 : 
	premake5 vs2015
#	"$(VS140COMNTOOLS)vsvars32" && msbuild $(PROJECT).vcxproj
	"$(VS140COMNTOOLS)vsvars32" && msbuild $(HOST).vcxproj /p:Configuration=Release
	"$(VS140COMNTOOLS)vsvars32" && msbuild $(TARGET).vcxproj /p:Configuration=Release

	
vs2005 : 
	premake5 vs2005
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(HOST).vcproj
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(TARGET).vcproj
	

	
.PHONY: run 

run: vs2015
	$(MAKE) -j2 runhost runtarget
	
	
runhost: 
	$(HOST_EXE)
	
	
runtarget:
	$(TARGET_EXE)
	
	
	
include $(ROOT)/clean.mk	