#RUN_OPT_MC5103 = --send_file_name=$(ROOT)/input/Lena224x240.pgm --send_sect=.data_shared_src.bss --recv_file_name=Sobel.pgm --recv_sect=.data_shared_dst.bss --recv_size=0x348a
RUN_OPT_MC5103 = --send_file_name=$(ROOT)/input/Bikesgray.pgm --send_sect=.data_shared_src.bss --recv_file_name=Sobel.pgm --recv_sect=.data_shared_dst.bss --recv_size=0x12C00
RUN_OPT_MB7707 = --send_file_name=$(ROOT)/input/Bikesgray.pgm --send_sect=.data_shared_src.bss --recv_file_name=Sobel.pgm --recv_sect=.data_shared_dst.bss  --recv_size=0x12C00
	
SRC_DEPS = $(ROOT)/deps/EasyPGM