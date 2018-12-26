/******************************************************************************
*    RC Module
*    NeuroMatrix(r) NM6406 Software
*
*    Image Processing Library 
*    Software design:    S.Mushkaev
*
*    Contents:           Sobel operator
*
*
******************************************************************************/
#include "nmtype.h"
#ifndef  __SOBEL_H_INCLUDED__
#define  __SOBEL_H_INCLUDED__

int sobel( const nm8u *source, nm8u *result,int width,int height);

#endif
