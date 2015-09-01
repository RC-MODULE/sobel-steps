ROOT = ..
-include $(ROOT)/environment.mk
#-include $(ROOT)/proxy.mk
#http_proxy ?=http://username:password@proxy:80/


#$(eval OUT=$(shell wget ))
#ifeq ($(OUT),)
#$(info -------------------------------------------------------------------)
#$(error ERROR: wget not found. Install setup wget from http://gnuwin32.sourceforge.net/URLages/wget.htm to sobel-steps/gnuwin32/ or to another folder accessible by PATH )
#endif
#
#
#$(eval OUT=$(shell unzip ))
#ifeq ($(OUT),)
#$(info -------------------------------------------------------------------)
#$(error ERROR: unzip not found. Install setup unzip from http://gnuwin32.sourceforge.net/URLages/unzip.htm to sobel-steps/gnuwin32/ or to another folder accessible by PATH )
#endif



NMPP_URL         = http://www.module.ru/mb7707/NeuroMatrix/nmpp_2015-09-01.zip
NMPROFILER_URL   = http://www.module.ru/mb7707/NeuroMatrix/nmprofiler_2015-06-26.zip

ifeq ($(OS),Windows_NT)
  SDK_MC5103_URL = http://www.module.ru/mb7707/NeuroMatrix/boards/mc5103_distrib_v_01_01_x32.zip
  SDK_MB7707_URL = http://www.module.ru/mb7707/NeuroMatrix/boards/mb7707_distrib_v_01_02_x32.zip
  SDK_MC7601_URL = http://www.module.ru/mb7707/NeuroMatrix/boards/mc7601_distrib_non_official.zip
  NMSDK_URL      = http://www.module.ru/mb7707/toolchains-neuromatrix/nmsdk306en_20150611.zip
  VSHELL32_URL   = http://www.module.ru/mb7707/NeuroMatrix/VSHELL32.ZIP
  VSHELL32_DIST  = http://www.module.ru/mb7707/NeuroMatrix/VSHELL32_1.0.0.26.exe
  DOWNLOADS-LIBS = $(notdir $(NMPROFILER_URL)) $(notdir$(NMPP_URL)) $(notdir $(VSHELL32_URL))
  DOWNLOADS-SDK  = $(notdir $(SDK_MB7707_URL)) $(notdir $(SDK_MC5103_URL)) $(notdir $(SDK_MC7601_URL)) $(notdir $(NMSDK_URL))

install-libs: nmprofiler nmpp vshell32

install-sdk:  mc5103sdk mb7707sdk mc7601sdk nmsdk

else
  SDK_MC5103_URL = http://www.module.ru/mb7707/NeuroMatrix/boards/mc5103_distrib_v_01_01.tar.gz
  SDK_MB7707_URL = http://www.module.ru/mb7707/NeuroMatrix/boards/mb7707_distrib_v_01_00.tar.gz
  NMSDK_URL      = http://www.module.ru/mb7707/toolchains-neuromatrix/nmsdk.tar.gz
  DOWNLOADS-LIBS = $(notdir $(NMPROFILER_URL)) $(notdir$(NMPP_URL))
  DOWNLOADS-SDK  = $(notdir $(SDK_MB7707_URL)) $(notdir $(SDK_MC5103_URL))  $(notdir $(NMSDK_URL))
  
install-libs: nmprofiler nmpp 

install-sdk:  mc5103sdk mb7707sdk nmsdk
  
endif



all: download install



DOWNLOADS      = $(DOWNLOADS-LIBS) $(DOWNLOADS-SDK)


install: install-libs install-sdk


#------------------------- package installation  --------------------



mc5103sdk: $(notdir $(SDK_MC5103_URL))
	-mkdir $(@)
	$(OS_TAR) $(<) $(OS_TODIR) $(@)
	
mb7707sdk: $(notdir $(SDK_MB7707_URL))
	-mkdir $(@)
	$(OS_TAR) $(<) $(OS_TODIR) $(@) 

mc7601sdk: $(notdir $(SDK_MC7601_URL))
	-mkdir $(@)
	$(OS_TAR) $(<) $(OS_TODIR) $(@) 

nmsdk: $(notdir $(NMSDK_URL))
	-mkdir $(@)
	$(OS_TAR) $(<) 

vshell32: $(notdir $(VSHELL32_URL))
	$(OS_UNZIP) $(<) 

nmprofiler: $(notdir $(NMPROFILER_URL))
	$(OS_UNZIP) $(<)

nmpp: $(notdir $(NMPP_URL))
	$(OS_UNZIP) $(<)
	$(MAKE) -C $(NMPP)/make/pc/vs80 
	$(MAKE) -C $(NMPP)/make/pc/vs13
	

#------------------------- download of depended URLs from www.module.ru --------------------


download: $(DOWNLOADS)

$(DOWNLOADS): 
	$(OS_WGET) 	\
		$(SDK_MC5103_URL) \
		$(SDK_MB7707_URL) \
		$(SDK_MC7601_URL) \
		$(NMSDK_URL)      \
		$(VSHELL32_URL)   \
		$(VSHELL32_DIST)  \
		$(NMPP_URL)       \
		$(NMPROFILER_URL) 
	
	
	
	
	
png:	
	$(OS_WGET) http://savepic.ru/7691336.png

zip:
	$(OS_UNZIP) nmprofiler_2015-06-26.zip 


#------------------------------------------------------------------------------------	
clean:
	-$(OS_RM) *.zip *.exe
	-$(OS_RD) mb7707sdk mc5103sdk mc7601sdk nmpp nmprofiler nmsdk vshell32 
	