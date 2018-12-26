#!lua
ROOT = "../../.."
-- A solution contains projects, and defines the available configurations
solution "app_mb7707"

	configurations { "Debug", "Release" }
	project "host"
      kind "ConsoleApp"
      language "C++"
      files { "../pc-src/*.cpp","../../*.cpp",ROOT.."/deps/EasyBMP/*.cpp" }
	  links { "nmpp-x86","mb7707load.lib"} 
	  libdirs { "$(NMPP)/lib","$(HAL)/lib","$(MB7707)/libload"}
	  includedirs { "$(NMPP)/include","$(HAL)/include",ROOT.."/deps/EasyBMP","../.."}
	  
      configuration "Debug"
		links {  "hal-mb7707-x86d"} 
        defines { "DEBUG" }
        symbols  "On" 
		 
		 

      configuration "Release"
		links {  "hal-mb7707-x86"} 
        defines { "NDEBUG" }
        symbols  "Off" 
		 


		 
	configurations { "Debug", "Release" }
	project "target"
      kind "Makefile"
      files { "../nm-src/*.cpp", "../../*.cpp", "*.cfg", "Makefile0" }
	  includedirs {"$(NMPP)/include","$(HAL)/include"}
	  configuration "Debug"
		   buildcommands {"make DEBUG=y -f Makefile0"}
		   rebuildcommands {"make -B DEBUG=y -f Makefile0"}
		   cleancommands {"make clean"}
		   
	  configuration "Release"
		   buildcommands {"make -f Makefile0"}
		   rebuildcommands {"make -B -f Makefile0"}
		   cleancommands {"make clean"}		   
		   
		  