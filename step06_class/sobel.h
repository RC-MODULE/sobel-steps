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

#ifndef  __SOBEL_H_INCLUDED__
#define  __SOBEL_H_INCLUDED__

#include "nmplv.h"
#include "nmpls.h"


class CBaseSobel {

	int size;
	int width;
	int height;
	bool isReady;
	NmppsFrame_16s frame;
	nm16s* horizontTmp;
	nm16s* horizontOut;	// Allocate temporary buffer 
	nm16s* verticalOut;	// Allocate temporary buffer

	NmppsFIRState* pFIRState121;
	NmppsFIRState* pFIRState101;


public:
	CBaseSobel();
	CBaseSobel(int Width, int Height);
	~CBaseSobel();
	int init(int Width, int Height);
	int filter( const unsigned char *source, unsigned char *result);
};


#endif
