#define PGM_OK 0

struct s_pgm_header{
	int width;
	int height;
	int max_gray;
	unsigned* data;
	unsigned  disp;
	int header_length;
};

int read_pgm_header(void* addr32, s_pgm_header* header);


