extern "C" {
	

long long sobel_weights101v[1];
long long sobel_weights121v[1];
void filter3v( const short *source, short *result, int width, int height, void* weights){


		int size=width*height;
		if (weights==sobel_weights121v)
			//for(int i=width; i<size-width; i++){
			for(int i=0; i<size; i++){
				//result[i]=source[i-width]+2*source[i]+source[i+width];
				result[i]=source[i]+2*source[i]+source[i+2*width];
			}
		else if (weights==sobel_weights101v)
			//for(int i=width; i<size-width; i++){
			for(int i=0; i<size; i++){
				//result[i]=source[i-width]-source[i+width];
				result[i]=source[i]-source[i+2*width];
			}


			
}
	

};