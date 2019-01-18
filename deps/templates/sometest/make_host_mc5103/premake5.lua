#!lua
ROOT = "../../.."
-- A solution contains projects, and defines the available configurations
solution "app_mc5103"

	configurations { "Debug", "Release" }
	project "host"
      kind "ConsoleApp"
      language "C++"
      files { "../pc-src/*.cpp","../../*.cpp", "../src/nm/*.cpp","../src/common/*.cpp",ROOT.."/deps/EasyBMP/*.cpp" }
	  links { "nmpp-x86","vshell","mc5103load"} 
	  libdirs { "$(NMPP)/lib","$(HAL)/lib","$(MC5103)/libload","$(VSHELL)/lib"}
	  includedirs { "$(NMPP)/include","$(HAL)/include",ROOT.."/deps/EasyBMP","../..","$(VSHELL)/include"}
	  
      configuration "Debug"
		links {  "hal-mc5103-x86d"} 
        defines { "DEBUG" }
        symbols  "On" 
		 
		 

      configuration "Release"
		links {  "hal-mc5103-x86"} 
        defines { "NDEBUG" }
        symbols  "Off" 
		 


		 
	configurations { "Debug", "Release" }
	project "target"
      kind "Makefile"
      files { "./*.asm","../nm-src/*.cpp", "../../*.cpp", "../src/nm/*.*","../src/common/*.*","*.cfg", "Makefile0" }
	  includedirs {"$(NMPP)/include","$(HAL)/include"}
	  configuration "Debug"
		   buildcommands {"make DEBUG=y -f Makefile0"}
		   rebuildcommands {"make -B DEBUG=y -f Makefile0"}
		   cleancommands {"make clean"}
		   
	  configuration "Release"
		   buildcommands {"make -f Makefile0"}
		   rebuildcommands {"make -B -f Makefile0"}
		   cleancommands {"make clean"}		   
		   
		  