ROOT = ..
-include $(ROOT)/environment.mk
-include $(ROOT)/proxy.mk
#http_proxy ?=http://username:password@proxy:80/


#$(eval OUT=$(shell wget ))
#ifeq ($(OUT),)
#$(info -------------------------------------------------------------------)
#$(error ERROR: wget not found. Install setup wget from http://gnuwin32.sourceforge.net/packages/wget.htm to sobel-steps/gnuwin32/ or to another folder accessible by PATH )
#endif
#
#
#$(eval OUT=$(shell unzip ))
#ifeq ($(OUT),)
#$(info -------------------------------------------------------------------)
#$(error ERROR: unzip not found. Install setup unzip from http://gnuwin32.sourceforge.net/packages/unzip.htm to sobel-steps/gnuwin32/ or to another folder accessible by PATH )
#endif



ifeq ($(OS),Windows_NT)
  OS_SDK_MC5103_PACK = mc5103_distrib_v_01_01_x32.zip
  OS_SDK_MB7707_PACK = mb7707_distrib_v_01_02_x32.zip
  OS_SDK_MC7601_PACK = mc7601_distrib_non_official.zip
  OS_NMSDK_PACK      = nmsdk306en_20150611.zip
  OS_VSHELL32_PACK   = VSHELL32.ZIP
  OS_VSHELL32_DIST   = VSHELL32_1.0.0.26.exe
  
 
  PATH := $(PATH);$(realpath ../gnuwin32/bin)
  
else
  OS_SDK_MC5103_PACK = mc5103_distrib_v_01_01.tar.gz
  OS_SDK_MB7707_PACK = mb7707_distrib_v_01_00.tar.gz
  OS_NMSDK_PACK      = module-nmc-20140702.tar.gz

 
endif

NMPP_PACK       = nmpp_2015-08-05.zip
NMPROFILER_PACK = nmprofiler_2015-06-26.zip


all: get-libs get-sdk install-libs install-sdk  

get: get-libs get-sdk

get-libs: $(NMPROFILER_PACK) $(NMPP_PAK) $(VSHELL32_PACK) $(OS_VSHELL32_DIST)

get-sdk:$(OS_SDK_MB7707_PACK) $(OS_SDK_MC5103_PACK) $(OS_SDK_MC7601_PACK) $(OS_NMSDK_PACK) 

install-libs: nmpp nmprofiler vshell32

install-sdk:  mc5103sdk mb7707sdk mc7601sdk nmsdk

#------------------------- unpacking of packages --------------------

nmprofiler: $(NMPROFILER_PACK)
	$(OS_UNZIP) $(<)

nmpp: $(NMPP_PACK)
	$(OS_UNZIP) $(<)
	
mc5103sdk: $(OS_SDK_MC5103_PACK)
	mkdir $(@)
	$(OS_UNZIP) $(<) $(OS_TODIR) $(@)
	
mb7707sdk: $(OS_SDK_MB7707_PACK)
	mkdir $(@)
	$(OS_UNZIP) $(<) $(OS_TODIR) $(@) 

mc7601sdk: $(OS_SDK_MC7601_PACK)
	mkdir $(@)
	$(OS_UNZIP) $(<) $(OS_TODIR) $(@) 

nmsdk: $(OS_NMSDK_PACK)
	mkdir $(@)
	$(OS_UNZIP) $(<) $(OS_TODIR) $(@) 

vshell32: $(OS_VSHELL32_PACK)
	$(OS_UNZIP) $(<) 
	
#------------------------- getting depended packs from www.module.ru --------------------
setup:
	$(OS_WGET) https://htmlweb.ru/download/sinonim.rar

png:	
	$(OS_WGET) http://savepic.ru/7691336.png

zip:
	$(OS_UNZIP) nmprofiler_2015-06-26.zip 

$(NMPP_PACK):
	$(OS_WGET) http://www.module.ru/mb7707/NeuroMatrix/$(@) 

$(NMPROFILER_PACK):
	$(OS_WGET) http://www.module.ru/mb7707/NeuroMatrix/$(@) 
	
$(OS_SDK_MB7707_PACK):
	$(OS_WGET) http://www.module.ru/mb7707/NeuroMatrix/boards/$(@)

$(OS_SDK_MC5103_PACK):
	$(OS_WGET) http://www.module.ru/mb7707/NeuroMatrix/boards/$(@)

$(OS_SDK_MC7601_PACK):
	$(OS_WGET) http://www.module.ru/mb7707/NeuroMatrix/boards/$(@)
	
$(OS_VSHELL32_PACK):
	$(OS_WGET) http://www.module.ru/mb7707/NeuroMatrix/$(@)

$(OS_VSHELL32_DIST):
	$(OS_WGET) http://www.module.ru/mb7707/NeuroMatrix/$(@)
	
$(OS_NMSDK_PACK):	
	$(OS_WGET) http://www.module.ru/mb7707/toolchains-neuromatrix/$(@)
	
#------------------------------------------------------------------------------------	
clean:
	-$(OS_RM) *.zip *.exe
	-$(OS_RD) mb7707sdk mc5103sdk mc7601sdk nmpp nmprofiler nmsdk vshell32 
	