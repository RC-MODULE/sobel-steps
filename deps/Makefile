#ifeq ($(OS),Windows_NT)
	

ROOT = ..
-include $(ROOT)/global.mk
-include proxy.mk

NMSDK_URL          = http://www.module.ru/mb7707/toolchains-neuromatrix/nmsdk_2016-04-19_non_official.zip
NMCALC_URL         = http://www.module.ru/mb7707/NeuroMatrix/nmcalculator.zip 
NM_IO_URL          = http://www.module.ru/mb7707/NeuroMatrix/nm_io.zip
VDU7707_URL        = http://www.module.ru/mb7707/NeuroMatrix/vdu7707_2015-10-27.zip
NMPP_URL           = https://github.com/RC-MODULE/nmpp/archive/master.zip
NMPROFILER_URL     = http://www.module.ru/mb7707/NeuroMatrix/nmprofiler_2015-06-26.zip
VSHELL32_URL       = http://www.module.ru/mb7707/NeuroMatrix/VSHELL32.ZIP

# Pure NMC Board support:
SDK_MC5103_URL     = http://www.module.ru/mb7707/NeuroMatrix/boards/mc5103_distrib_v_01_01_with_printf_non_official.zip
SDK_MC7601_URL     = http://www.module.ru/mb7707/NeuroMatrix/boards/mc7601_distrib_non_official.zip
SDK_MB7707_URL     = http://www.module.ru/mb7707/NeuroMatrix/boards/mb7707_distrib_v_01_02_x32.zip
WINPCAP_URL        = https://www.winpcap.org/install/bin/WinPcap_4_1_3.exe
# ARM-NMC MB7707 support :
EDCLTOOL_URL       = http://www.module.ru/mb7707/edcltool-bin/edcltool-20042015-win32.tgz
LUA_URL            = http://downloads.sourceforge.net/project/luabinaries/5.2.4/Tools%20Executables/lua-5.2.4_Win32_bin.zip

  
NMC_URLS = \
	$(SDK_MC5103_URL) \
	$(SDK_MC7601_URL) \
	$(SDK_MB7707_URL) \
	$(NMSDK_URL)      \
	$(WINPCAP_URL)	\
	$(EDCLTOOL_URL)	\
	$(NMCALC_URL) \
	$(VDU7707_URL) \
	$(NMPP_URL)  \
	$(NMPROFILER_URL)

install: install-dev-nmc install-nmpp vdu7707 

install-nmpp: nmpp-master nmpp-master/lib/nmpp-nmc3.lib

nmpp-master: nmpp-master.zip
	$(OS_UNZIP) nmpp-master.zip 
	
nmpp-master.zip:	
	$(OS_WGET)  $(NMPP_URL)
	
nmpp-master/lib/nmpp-nmc3.lib:
	$(MAKE) -C  nmpp-master/make/nmpp-nmc3 all
	$(MAKE) -C  nmpp-master/make/pc/vs80
	$(MAKE) -C  nmpp-master/make/pc/vs13	
	
vdu7707: 
	$(OS_WGET)  $(VDU7707_URL)
	$(OS_UNZIP) $(notdir $(VDU7707_URL))


install-dev-arm: dev-pack-master dev-pack-master/rootfs
	$(MAKE) -C dev-pack-master download-arm
	$(MAKE) -C dev-pack-master install-arm

install-dev-nmc: dev-pack-master dev-pack-master/module-nmc

dev-pack-master/module-nmc:
	$(MAKE) -C dev-pack-master download-nmc
	$(MAKE) -C dev-pack-master install-nmc
	$(MAKE) -C dev-pack-master lua
	
	
dev-pack-master: dev-pack-master.zip	
	$(OS_UNZIP) dev-pack-master.zip	

dev-pack-master.zip:
	$(OS_WGET)  https://github.com/RC-MODULE/dev-pack/archive/master.zip

	
#module-nmc:
#	$(OS_WGET)  $(NMSDK_URL) 
#	$(OS_UNZIP) $(notdir $(NMSDK_URL)) -d module-nmc
#
#mc5103sdk:
#	$(OS_WGET)  $(SDK_MC5103_URL) 
#	$(OS_UNZIP) $(notdir $(SDK_MC5103_URL)) -d mc5103sdk
#
#mc7601sdk:
#	$(OS_WGET)  $(SDK_MC7601_URL) 
#	$(OS_UNZIP) $(notdir $(SDK_MC7601_URL)) -d mc7601sdk
#
#mb7707sdk:
#	$(OS_WGET)  $(SDK_MB7707_URL) 
#	$(OS_WGET)  $(WINPCAP_URL)
#	$(OS_WGET)  $(EDCLTOOL_URL)
#	$(OS_UNZIP) $(notdir $(SDK_MB7707_URL)) -d mb7707sdk
#
#nmcalculator:
#	$(OS_WGET)  $(NMCALC_URL) 
#	$(OS_UNZIP) $(notdir $(NMCALC_URL))
#
#	
#nmprofiler: 
#	$(OS_WGET)  $(NMPROFILER_URL)
#	$(OS_UNZIP) $(notdir $(NMPROFILER_URL))
#
#	
#
#vshell: 
#	$(OS_WGET)  $(VSHELL32_URL)
#	$(OS_UNZIP) $(notdir $(VSHELL32_URL))
#
#lua:
#	$(OS_WGET)  $(LUA_URL)
#	-mkfir lua
#	$(OS_UNZIP) $(notdir $(LUA_URL)) -d lua
#		

	
	
	
#------------------------- download of depended URLs from www.module.ru --------------------


download: 
	$(OS_WGET) 	\
		$(NMSDK_URL) \
		$(NMCALC_URL) \
		$(NM_IO_URL) \
		$(VDU7707_URL) \
		$(NMPP_URL) \
		$(NMPROFILER_URL) \
		$(SDK_MC5103_URL) \
		$(SDK_MC7601_URL) \
		$(SDK_MB7707_URL) \
		$(WINPCAP_URL) \
		$(EDCLTOOL_URL)



#------------------------------------------------------------------------------------	
clean:
	-$(OS_RM) *.zip *.exe *.tgz *.gz
	-$(OS_RD) dev-pack-master nmpp-master

#else
#$(MAKECMDGOALS): 
#	$(MAKE) -f Makefile.lnx $(MAKECMDGOALS)
#endif
	