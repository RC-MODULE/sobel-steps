#!lua
ROOT = "../../.."
-- A solution contains projects, and defines the available configurations
solution "app_mc5103"

	configurations { "Debug", "Release" }
	project "host"
      kind "ConsoleApp"
      language "C++"
      files { "../pc-src/*.cpp","../../*.cpp",ROOT.."/deps/EasyBMP/*.cpp" }
	  links { "nmpp-x86","hal-mc5103-x86","mc5103load.lib"} 
	  libdirs { "$(NMPP)/lib","$(HAL)/lib","$(MC5103)/libload"}
	  includedirs { "$(NMPP)/include","$(HAL)/include",ROOT.."/deps/EasyBMP","../.."}
	  
      configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 
		 
		 

      configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
		 


		 
	configurations { "Debug", "Release" }
	project "target"
      kind "Makefile"
      files { "../nm-src/*.cpp", "../../*.cpp", "*.cfg", "Makefile" }
	  includedirs {"$(NMPP)/include","$(HAL)/include"}
	  configuration "Debug"
		   buildcommands {"make DEBUG=y -f Makefile0"}
		   rebuildcommands {"make -B DEBUG=y -f Makefile0"}
		   cleancommands {"make clean"}
		   
	  configuration "Release"
		   buildcommands {"make -f Makefile0"}
		   rebuildcommands {"make -B -f Makefile0"}
		   cleancommands {"make clean"}		   
		   
		  