#include "utilities.h"

int min(int v1, int v2){
	int aux = v1;
	if(aux > v2){
		aux = v2;
	}
	return aux;
}

int max(int v1, int v2){
	int aux = v1;
	if(aux < v2){
		aux = v2;
	}
	return aux;
}

int constrain(int v, int mn, int mx){
	return min(mx, max(v, mn));
}

float map(float v, float min1, float max1, float min2, float max2){
	return min2 + (max2 - min2) * ((v - min1) / (max1 - min1));
}