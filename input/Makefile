ROOT = ..
-include $(ROOT)/environment.mk

# [11MB]
VIDEO1 = http://www.module.ru/mb7707/NeuroMatrix/sobel/bugs720x576x20.avi 

# [21MB]
VIDEO2 = http://www.module.ru/mb7707/NeuroMatrix/sobel/disney1920x1080x8.avi

# [68MB]
VIDEO3 = http://www.module.ru/mb7707/NeuroMatrix/sobel/bugs720x576.avi

# [720MB]
VIDEO4 = http://www.module.ru/mb7707/NeuroMatrix/sobel/disney1920x1080.avi


VIDEOS = $(notdir $(VIDEO1)) $(notdir $(VIDEO2)) $(notdir $(VIDEO3)) $(notdir $(VIDEO4))

avi:  $(VIDEOS)

$(VIDEOS): 
	$(OS_WGET) \
		$(VIDEO1) \
		$(VIDEO2) \
		$(VIDEO3) \
		$(VIDEO4)
	
local:
	copy \\dragon\distrib\streams\video\720x576\bugs720x576x20.avi
	copy \\dragon\distrib\streams\video\1920x1080\disney1920x1080x8.avi
	copy \\dragon\distrib\streams\video\720x576\bugs720x576.avi
	copy \\dragon\distrib\streams\video\1920x1080\disney1920x1080.avi
	
	
	
	
	
	
	
	
	
	