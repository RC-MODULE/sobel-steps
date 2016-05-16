ROOT = ..
-include $(ROOT)/global.mk

# [11MB]
VIDEO1_URL = http://www.module.ru/mb7707/NeuroMatrix/sobel/bugs720x576x20.avi 

# [21MB]
VIDEO2_URL = http://www.module.ru/mb7707/NeuroMatrix/sobel/disney1920x1080x8.avi

# [68MB]
VIDEO3_URL = http://www.module.ru/mb7707/NeuroMatrix/sobel/bugs720x576.avi

# [720MB]
VIDEO4_URL = http://www.module.ru/mb7707/NeuroMatrix/sobel/disney1920x1080.avi


VIDEOS = $(notdir $(VIDEO1_URL)) $(notdir $(VIDEO2_URL)) $(notdir $(VIDEO3_URL)) $(notdir $(VIDEO4_URL))


video:
	$(OS_WGET) $(VIDEO1_URL) $(VIDEO2_URL) $(VIDEO3_URL) $(VIDEO4_URL)

avi:  $(VIDEOS)

$(VIDEOS): 
	$(OS_WGET) \
		$(VIDEO1) \
		$(VIDEO2) \
		$(VIDEO3) \
		$(VIDEO4)
	
	
	
	
	
	
	
	
	
	
	