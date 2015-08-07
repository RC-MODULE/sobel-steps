-include proxy.mk
# http_proxy = http://username:password@proxy:80/
include $(ROOT)/env.mk

all: bugs720x576x20.avi disney1920x1080x8.avi bugs720x576.avi disney1920x1080.avi

bugs720x576x20.avi:
	@echo Copying $(@) [11MB] from WAN ...
	@wget http://www.module.ru/mb7707/NeuroMatrix/sobel/$(@) ||	echo Copying $(@) [11MB] from LAN, wait... && copy \\dragon\distrib\streams\video\720x576\$(@)
	
disney1920x1080x8.avi:
	@echo Copying $(@) [21MB] from WAN ...
	@wget http://www.module.ru/mb7707/NeuroMatrix/sobel/$(@)  || echo Copying $(@) [21MB] from LAN, wait... && copy \\dragon\distrib\streams\video\1920x1080\$(@)

bugs720x576.avi:
	@echo Copying $(@) [68MB] from WAN ...
	@wget http://www.module.ru/mb7707/NeuroMatrix/sobel/$(@)  || echo Copying $(@) [68MB] from LAN, wait... && copy \\dragon\distrib\streams\video\720x576\$(@)

disney1920x1080.avi:
	@echo Copying $(@) [720MB] from WAN ...
	@wget http://www.module.ru/mb7707/NeuroMatrix/sobel/$(@)  || echo Copying $(@) [720MB] from LAN, wait... && copy \\dragon\distrib\streams\video\1920x1080\$(@)

	

	