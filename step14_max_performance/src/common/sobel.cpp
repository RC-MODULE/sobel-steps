#include "nmplv.h"
#include "nmpls.h"
#include "malloc32.h"
#include "sobel.h"
#pragma code_section ".text_sobel"

#include "sobelCore.h"

//int sobelInitAlloc(int width, int height, SobelCoreSpec* spec, int sliceHeight=0){
//
//	spec->height=height;
//	if (sliceHeight==0){
//		for(int sliceHeight=(height+29)/30*30; sliceHeight>=30; sliceHeight-=30)
//			if (sobelCoreInitAlloc(Width, sliceHeight,&spec->coreSpec))
//				return 1;
//	}
//	else {
//		if (sobelCoreInitAlloc(Width, sliceHeight,&spec->coreSpec)){
//			return 1;
//		}
//	}
//	return 0;
//}
extern "C"{

void sobel( const nm8u *source, nm8u *result, int height, SobelCoreSpec* spec){
	int  residualHeight=height;
	int& coreHeight=spec->height;
	nm8u* src = nmppsAddr_8u(source, spec->width);
	nm8u* dst = nmppsAddr_8u(result, spec->width);
	
	sobelCore(src,dst,spec,coreHeight-1);	// first sobel with skipping first source line 
	residualHeight-=coreHeight;
	
	src = nmppsAddr_8u(source, spec->size);
	dst = nmppsAddr_8u(result, spec->size);

	while (residualHeight>coreHeight){
		sobelCore(src,dst,spec,0);
		src = nmppsAddr_8u(src, spec->size);
		dst = nmppsAddr_8u(dst, spec->size);
		residualHeight-=coreHeight;
	}
	if (residualHeight>0){
		sobelCore(src,dst,spec,coreHeight-1);	// last sobel with skipping last source line 
	}
}


};
//void sobelFree(SobelCoreSpec* spec){
//	sobelCoreFree(spec);
//}
