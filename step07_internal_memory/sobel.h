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
	NmppsFrame_8s   signedFrame;
	NmppsFrame_16s  horizontTmpFrame;
	nm8s*  signedImg;
	nm16s* horizontTmpUpLine;
	nm16s* horizontTmp;
	nm16s* horizontTmpDnLine;
	nm16s* horizontOut;	// Allocate temporary buffer 
	nm16s* verticalOut;	// Allocate temporary buffer

	NmppsFIRState* pFIRState121;
	NmppsFIRState* pFIRState101;


public:
	int wrapSize;				// size of image with 2 boundary lines
	int size;					// image size 
	int width;
	int height;
	bool isReady;				// memory allocation status

	CBaseSobel();
	CBaseSobel(int Width, int Height);
	~CBaseSobel();
	int init(int Width, int Height);
	int filter( const nm8u *source, nm8u *result);
};

class CSobel: public CBaseSobel {
	int			sliceCount;		// count of slices which source image is split into
	
public:
	CSobel();
	CSobel(int Width, int Height);
	~CSobel();
	int init(int Width, int Height);
	int filter( const nm8u *source, nm8u *result);
};

#endif
