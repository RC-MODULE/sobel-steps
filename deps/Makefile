SHELL = cmd

-include proxy.mk
#http_proxy ?=http://username:password@proxy:80/

ifeq ($(OS),Windows_NT)
  SHELL = cmd
  OS_UNZIP = unzip
  OS_SDK_MC5103 = mc5103_distrib_v_01_01_x32.zip
  OS_SDK_MB7707 = mb7707_distrib_v_01_02_x32.zip
  OS_NMSDK = nmsdk306en_20150611.zip
  OS_VSHELL= VSHELL_1.0.0.24.zip
else
  OS_UNZIP = gunzip
  OS_SDK_MC5103 = mc5103_distrib_v_01_01.tar.gz
  OS_SDK_MB7707 = mb7707_distrib_v_01_00.tar.gz
  OS_NMSDK = module-nmc-20140702.tar.gz
  OS_VSHELL=
endif

NMPP = nmpp_2015-07-24.zip
NMPROFILER= nmprofiler_2015-06-26.zip


PATH := $(PATH);$(realpath ../gnuwin32/bin)

$(eval OUT=$(shell unzip ))
ifeq ($(OUT),)
$(warning ------------------------------------------------------------------------------------------ )
$(warning WARNING: unzip not found. Download it by 'sobel-steps/gnuwin32/get_unzip.bat' and install  )
$(warning WARNING: Install to sobel-steps/gnuwin32/ or another folder which accessible by %PATH% )
$(warning ------------------------------------------------------------------------------------------ )
endif


all: get install 

get: $(NMPP) $(NMPROFILER)  $(OS_SDK_MB7707) $(OS_SDK_MC5103) $(OS_NMSDK) $(OS_VSHELL)

install: nmpp nmprofiler mc5103sdk mb7707sdk vshell

nmprofiler: $(NMPROFILER)
	unzip $(<)

nmpp: $(NMPP)
	unzip $(<)
	
mc5103sdk: $(OS_SDK_MC5103)
	$(OS_UNZIP) $(<) -d mc5103sdk
	
mb7707sdk: $(OS_SDK_MB7707)
	$(OS_UNZIP) $(<) -d mb7707sdk

vshell: $(OS_VSHELL)
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
	-rd /Q /S nmpp
	-rd /Q /S nmprofiler
	-rd /Q /S mc5103sdk
	-rd /Q /S mb7707sdk
