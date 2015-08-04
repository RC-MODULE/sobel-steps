
-include proxy.mk
#http_proxy ?=http://username:password@proxy:80/

ifeq ($(OS),Windows_NT)
  OS_SDK_MC5103 = mc5103_distrib_v_01_01_x32.zip
  OS_SDK_MB7707 = mb7707_distrib_v_01_02_x32.zip
  OS_NMSDK = nmsdk306en_20150611.zip
  OS_VSHELL= VSHELL_1.0.0.24.zip

  SHELL = cmd
  OS_UNZIP = unzip 
  OS_TODIR = -d
  OS_RM = rd /Q /S 
  PATH := $(PATH);$(realpath ../gnuwin32/bin)
  
else
  OS_SDK_MC5103 = mc5103_distrib_v_01_01.tar.gz
  OS_SDK_MB7707 = mb7707_distrib_v_01_00.tar.gz
  OS_NMSDK = module-nmc-20140702.tar.gz
  OS_VSHELL=
  
  OS_UNZIP = tar xvzf 
  OS_TODIR = -C
  OS_RM = rm -d -r
endif

NMPP = nmpp_2015-08-04.zip
NMPROFILER= nmprofiler_2015-06-26.zip


$(eval OUT=$(shell unzip ))
ifeq ($(OUT),)
$(warning ------------------------------------------------------------------------------------------ )
$(warning WARNING: unzip not found. Download it by 'sobel-steps/gnuwin32/get_unzip.bat' and install  )
$(warning WARNING: Install to sobel-steps/gnuwin32/ or another folder which accessible by %PATH% )
$(warning ------------------------------------------------------------------------------------------ )
endif


all: get install 

get: $(NMPP) $(NMPROFILER)  $(OS_SDK_MB7707) $(OS_SDK_MC5103) $(OS_NMSDK) $(OS_VSHELL)

install: nmpp nmprofiler mc5103sdk mb7707sdk $(OS_VSHELL)

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

$(OS_VSHELL): 
	unzip $(<)
	VSHELL_1.0.0.24.exe

	
$(NMPP):
	wget http://www.module.ru/mb7707/NeuroMatrix/sobel/$(@)

$(NMPROFILER):
	wget http://www.module.ru/mb7707/NeuroMatrix/$(@)
	
$(OS_SDK_MB7707):
	wget http://www.module.ru/mb7707/NeuroMatrix/boards/$(@)

$(OS_SDK_MC5103):
	wget http://www.module.ru/mb7707/NeuroMatrix/boards/$(@)

$(OS_VSHELL):
	wget http://www.module.ru/mb7707/NeuroMatrix/$(@)
	
$(OS_NMSDK):	
	wget http://www.module.ru/mb7707/toolchains-neuromatrix/$(@)
	
clean:
	-$(OS_RM) nmpp
	-$(OS_RM) nmprofiler
	-$(OS_RM) mc5103sdk
	-$(OS_RM) mb7707sdk
