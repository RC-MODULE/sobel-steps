#ifndef EASY_PGM_DEFINED
#define EASY_PGM_DEFINED

/**
 *  \brief Parse pgm-header 
 *  
 *  \param [in] header address of pgm-header 
 *  \param [out] width  width of image
 *  \param [out] height height of image 
 *  \return returns length of pgm-header in bytes
 *  
 *  \details Details
 */
int read_pgm_header(void* header, int& width, int& height);


/**
 *  \brief Create pgm-header in memory
 *  
 *  \param [in] header - starting address where pgm-header must be located
 *  \param [in] width  - width of image 
 *  \param [in] height - height of image
 *  \param [in] copyright - text
 *  
 *  \return length of pgm-header in bytes
 *  
 *  \details Details
 */
 int save_pgm_header(void* header, int  width, int  height, char* copyright);

#endif