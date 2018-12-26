#!lua
ROOT = "../../.."
-- A solution contains projects, and defines the available configurations
solution "host"

	configurations { "Debug", "Release" }
	project "host"
		kind "ConsoleApp"
		language "C++"
		files { "../pc-src/*.cpp",ROOT.."/deps/EasyBMP/*.cpp" }
		links { "nmpp-x86"} 
		libdirs { "$(NMPP)/lib","$(HAL)/lib"}
		includedirs { "$(NMPP)/include","$(HAL)/include",ROOT.."/deps/EasyBMP","../.."}
	  
		configuration "Debug"
			links {  "hal-virtual-x86d"} 
			defines { "DEBUG" }
			symbols  "On" 
			 
		 

		configuration "Release"
			links {  "hal-virtual-x86"} 
			defines { "NDEBUG" }
			symbols  "Off" 
			 


solution "target"		 
	configurations { "Debug", "Release" }
	project "target"
		kind "ConsoleApp"
		files { "../nm-src/*.cpp", "../../*.cpp",}
		libdirs { "$(NMPP)/lib","$(HAL)/lib"}
      	links { "nmpp-x86","hal-virtual-x86"} 
		includedirs {"$(NMPP)/include","$(HAL)/include","../.."}
		configuration "Debug"
			links {  "hal-virtual-x86d"} 
			defines { "DEBUG" }
			symbols  "On" 
		 
		 

		configuration "Release"
			links {  "hal-virtual-x86"} 
			defines { "NDEBUG" }
			symbols  "Off" 
	   
		   
		  