#!lua


-- A solution contains projects, and defines the available configurations
solution "sobel-host"
   configurations { "Debug", "Release" }

   -- A project defines one build target
   project "sobel-host"
		kind "ConsoleApp"
		language "C++"
		files { "../src_host/*.cpp"}
		links { "hal-virtual-x86.lib","vshell.lib" } 
		includedirs { "$(HAL)/include","$(VSHELL)/include"}	  
		libdirs { "$(HAL)/lib","$(VSHELL)/lib"}

		configuration "Debug"
			defines { "DEBUG" }
			symbols  "On" 

		configuration "Release"
			defines { "NDEBUG" }
			symbols  "Off" 
		 
solution "sobel-target"
    configurations { "Debug", "Release" }
	 
	project "sobel-target"
		kind "ConsoleApp"
		files { "../src_target/*.cpp","../../src/common/*.cpp","../../src/pc/*.cpp",}
		links { "hal-virtual-x86.lib","nmpp-x86.lib" } 
		includedirs { "$(HAL)/include","$(NMPP)/include","../src/common"}	  
		libdirs { "$(HAL)/lib","$(NMPP)/lib"}
		
		configuration "Debug"
			defines { "DEBUG" }
			symbols  "On" 

		configuration "Release"
			defines { "NDEBUG" }
			symbols  "Off" 
		