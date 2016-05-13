mb7707run -i -a%1 %2 --recv_file_name=size.txt   --recv_sect=.data_shared_dst.bss  --recv_size=0x1
set /p  size= <size.txt 
mb7707run -r -a%1 %2 --recv_file_name=stdout.txt --recv_sect=.data_shared_dst.bss  --recv_size=0x%size% --recv_disp=0x2
