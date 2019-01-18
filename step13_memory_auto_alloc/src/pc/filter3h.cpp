extern "C" {
	
long long sobel_weights121[1];
long long sobel_weights101[1];

void filter3h ( const char *source, short *result, int size, void* weights){
		
		if (weights==sobel_weights121)
			for(int i=0; i<size; i++){
				result[i]=source[i-1]+2*source[i]+source[i+1];
			}
		else if (weights==sobel_weights101)
			for(int i=0; i<size; i++){
				result[i]=source[i-1]-source[i+1];
			}

}
};