-include ../env.mk
-include proxy.mk
#http_proxy ?=http://username:password@proxy:80/

ifeq ($(OS),Windows_NT)
  OS_SDK_MC5103 = mc5103_distrib_v_01_01_x32.zip
  OS_SDK_MB7707 = mb7707_distrib_v_01_02_x32.zip
  OS_NMSDK = nmsdk306en_20150611.zip
  OS_VSHELL32= VSHELL32_1.0.0.26.exe
  #VSHELL32_1.0.0.24.zip

  SHELL = cmd
  OS_UNZIP = unzip 
  OS_TODIR = -d
  OS_RM = rd /Q /S 
  OS_MKDIR = md
  PATH := $(PATH);$(realpath ../gnuwin32/bin)
  
else
  OS_SDK_MC5103 = mc5103_distrib_v_01_01.tar.gz
  OS_SDK_MB7707 = mb7707_distrib_v_01_00.tar.gz
  OS_NMSDK = module-nmc-20140702.tar.gz
  OS_VSHELL32=
  
  OS_UNZIP = tar xvzf 
  OS_TODIR = -C
  OS_RM = rm -d -r
endif

NMPP = nmpp_2015-08-05.zip
NMPROFILER= nmprofiler_2015-06-26.zip

$(eval OUT=$(shell unzip ))
ifeq ($(OUT),)
$(warning ------------------------------------------------------------------------------------------ )
$(warning WARNING: unzip not found. Download it by 'sobel-steps/gnuwin32/get_unzip.bat' and install  )
$(warning WARNING: Install to sobel-steps/gnuwin32/ or another folder which accessible by %PATH% )
$(warning ------------------------------------------------------------------------------------------ )
endif

all: get-libs get-sdk install 

get-libs: $(NMPP) $(NMPROFILER)  $(OS_VSHELL32)

get-sdk:$(OS_SDK_MB7707) $(OS_SDK_MC5103) $(OS_NMSDK)

install: nmpp nmprofiler 

nmprofiler: $(NMPROFILER)
	unzip $(<)

nmpp: $(NMPP)
	unzip $(<)
	
mc5103sdk: $(OS_SDK_MC5103)
	mkdir $(@)
	$(OS_UNZIP) $(<) $(OS_TODIR) $(@)
	
mb7707sdk: $(OS_SDK_MB7707)
	mkdir $(@)
	$(OS_UNZIP) $(<) $(OS_TODIR) $(@) 

$(OS_VSHELL32): 
	unzip $(<)
	VSHELL32_1.0.0.24.exe

	
$(NMPP):
	$(OS_WGET) http://www.module.ru/mb7707/NeuroMatrix/$(@)
	
#	$(OS_WGET) http://downloads.sourceforge.net/project/gnuwin32/unzip/5.51-1/unzip-5.51-1.exe
	


$(NMPROFILER):
	$(OS_WGET) http://www.module.ru/mb7707/NeuroMatrix/$(@)
	
$(OS_SDK_MB7707):
	$(OS_WGET) http://www.module.ru/mb7707/NeuroMatrix/boards/$(@)

$(OS_SDK_MC5103):
	$(OS_WGET) http://www.module.ru/mb7707/NeuroMatrix/boards/$(@)

$(OS_VSHELL32):
	$(OS_WGET) http://www.module.ru/mb7707/NeuroMatrix/$(@)
	
$(OS_NMSDK):	
	$(OS_WGET) http://www.module.ru/mb7707/toolchains-neuromatrix/$(@)
	
clean:
	-$(OS_RM) nmpp
	-$(OS_RM) nmprofiler
	-$(OS_RM) mc5103sdk
	-$(OS_RM) mb7707sdk
