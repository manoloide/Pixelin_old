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