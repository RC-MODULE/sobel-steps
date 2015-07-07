#ifndef MALLOC32_DEFINED
#define MALLOC32_DEFINED

#define INT_BANK0 1
#define INT_BANK1 2
#define INT_BANK2 4
#define INT_BANK3 8
#define EXT_BANK0 16 
#define EXT_BANK1 32 
#define SHARED_MEM EXT_BANK0
#define WRAP_SIZE 1920/2+2

void* malloc32 (unsigned size_int32 );
void* malloc32 (unsigned size_int32, unsigned bank_mask);
void  free32(void* p);

void* wrap_malloc32 (unsigned size_int32);
void  wrap_free32(void* p);

inline void* internal_malloc32 (unsigned size_int32)
{
	return malloc32(size_int32, INT_BANK1|INT_BANK2|INT_BANK3);
}

inline void* shared_malloc32 (unsigned size_int32)
{
	return malloc32(size_int32, EXT_BANK0);
}


typedef void (*t_free_func)(void*);

#endif