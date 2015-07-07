#include "nmplv.h"
void VEC_Add2VW (nm16s *pSrcVec0,nm16s *pSrcVec1, nm16s *pSrcVec2, nm16s *pDstVec, int nSize) {
	
	for(int i=0;i<nSize;i++,pSrcVec0++,pSrcVec1++, pSrcVec2++ , pDstVec++)
	{
		int x=(*pSrcVec0)*2+(*pSrcVec1)+(*pSrcVec2);
		*pDstVec=x;
	}
}