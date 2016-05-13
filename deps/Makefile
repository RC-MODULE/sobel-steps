ROOT = ..
-include $(ROOT)/global.mk
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



DEVPACK_URL      = https://github.com/RC-MODULE/dev-pack/archive/master.zip
NMPP_URL         = https://github.com/RC-MODULE/nmpp/archive/master.zip
NMPROFILER_URL   = http://www.module.ru/mb7707/NeuroMatrix/nmprofiler_2015-06-26.zip
VDU7707_URL      = http://www.module.ru/mb7707/NeuroMatrix/vdu7707_2015-10-27.zip



all: download install



DOWNLOADS      = $(DOWNLOADS-LIBS) $(DOWNLOADS-SDK)



#------------------------- package installation  --------------------



dev-pack: dev-pack.zip
	$(OS_UNZIP) $(<) 
	$(OS_MV) dev-pack-master dev-pack
	$(MAKE) -C dev-pack install-nmc 

dev-pack.zip:
	$(OS_WGET) $(DEVPACK_URL)
	$(OS_MV) $(notdir $(DEVPACK_URL)) dev-pack.zip
	
nmprofiler: $(notdir $(NMPROFILER_URL))
	$(OS_UNZIP) $(<)

nmpp: nmpp.zip
	$(OS_UNZIP) $(<)
	$(OS_MV) nmpp-master nmpp
#	$(MAKE) -C $(NMPP)/make DEVMAKE=
	
nmpp.zip: 
	$(OS_WGET) $(NMPP_URL)
	$(OS_MV) $(notdir $(NMPP_URL)) nmpp.zip
	
vdu7707: $(notdir $(VDU7707_URL))
	$(OS_UNZIP) $(<)
	

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
		$(NMPROFILER_URL) \
		$(VDU7707_URL)
	
	
	
	
png:	
	$(OS_WGET) http://savepic.ru/7691336.png

zip:
	$(OS_UNZIP) nmprofiler_2015-06-26.zip 


#------------------------------------------------------------------------------------	
clean:
	-$(OS_RM) *.zip *.exe
	-$(OS_RD) mb7707sdk mc5103sdk mc7601sdk nmpp nmprofiler nmsdk vshell32 
	