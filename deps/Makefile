SHELL = cmd

-include proxy.mk
#http_proxy ?=http://username:passwordw@proxy:80/


PATH := $(PATH);$(realpath ../gnuwin32/bin)

$(eval OUT=$(shell unzip ))
ifeq ($(OUT),)
$(warning ------------------------------------------------------------------------------------------ )
$(warning WARNING: unzip not found. Download it by 'sobel-steps/gnuwin32/get_unzip.bat' and install  )
$(warning WARNING: Install to sobel-steps/gnuwin32/ or another folder which accessible by %PATH% )
$(warning ------------------------------------------------------------------------------------------ )
endif

NMPP_ZIP = nmpp_2015-07-01.zip
NMSDK_ZIP= nmsdk306en_20150611.zip

all: get install 

get: $(NMPP_ZIP) nmprofiler_2015-06-26.zip mb7707_distrib.zip mc5103_distrib.zip $(NMSDK_ZIP) VSHELL_1.0.0.24.zip 

install: nmpp nmprofiler mc5103sdk mb7707sdk vshell

nmprofiler: nmprofiler_2015-06-26.zip
	unzip $(<)

nmpp: $(NMPP_ZIP)
	unzip $(<)
	
mc5103sdk: mc5103_distrib.zip
	unzip $(<)
	
mb7707sdk: mb7707_distrib.zip
	unzip $(<)

vshell: VSHELL_1.0.0.24.zip
	unzip $(<)
	VSHELL_1.0.0.24.exe

	
$(NMPP_ZIP):
	wget http://www.module.ru/mb7707/NeuroMatrix/$(@)

nmprofiler_2015-06-26.zip:
	wget http://www.module.ru/mb7707/NeuroMatrix/$(@)
	
mb7707_distrib.zip:
	wget http://www.module.ru/mb7707/NeuroMatrix/$(@)

mc5103_distrib.zip:
	wget http://www.module.ru/mb7707/NeuroMatrix/$(@)

VSHELL_1.0.0.24.zip:
	wget http://www.module.ru/mb7707/NeuroMatrix/$(@)
	
$(NMSDK_ZIP):	
	wget http://www.module.ru/mb7707/toolchains-win32/$(@)
	
clean:
	-rd /Q /S nmpp
	-rd /Q /S nmprofiler
	-rd /Q /S mc5103sdk
	-rd /Q /S mb7707sdk
