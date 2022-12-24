#include <stdio.h>
#include "pi.h"

float Pi_V(long long K){
	float pi = 1;
	for (long long i = 1; i<K; i++){
		pi = pi * (2*i *2*i) / (double)((2*i-1)*(2*i+1));
	} 
	return pi*2;

}
float Pi_L(long long K){
	float pi_leibnec = 0;
	int u = 0;
	for (long long j = 0; j < K; j++) {
		pi_leibnec += 2/(double)((4*j+1)*(4*j+3));
	}
	return pi_leibnec *4;
}
