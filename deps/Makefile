#ifeq ($(OS),Windows_NT)
	

ROOT = ..
-include $(ROOT)/global.mk

VDU7707_URL        = http://www.module.ru/mb7707/NeuroMatrix/vdu7707_2015-10-27.zip
NMPP_URL           = https://github.com/RC-MODULE/nmpp/archive/master.zip
#NMPROFILER_URL     = http://www.module.ru/mb7707/NeuroMatrix/nmprofiler_2015-06-26.zip
DEVPACK_URL        = https://github.com/RC-MODULE/dev-pack/archive/master.zip
  
NMC_URLS = \
	$(VDU7707_URL) \
	$(NMPP_URL)  


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
	$(OS_WGET) $(DEVPACK_URL)

#------------------------- download of depended URLs from www.module.ru --------------------

download: 
	$(OS_WGET) 	\
		$(VDU7707_URL) \
		$(NMPP_URL) \
		$(DEVPACK_URL)

#------------------------------------------------------------------------------------	
clean:
	-$(OS_RM) *.zip *.exe *.tgz *.gz
	-$(OS_RD) dev-pack-master nmpp-master vdu7707

#else
#$(MAKECMDGOALS): 
#	$(MAKE) -f Makefile.lnx $(MAKECMDGOALS)
#endif
	