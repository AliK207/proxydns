#include "../inc/memoire.h"

struct buffer_circulaire * bf_c; 

int allocateMemory(size_t size){

	bf_c = malloc(sizeof(struct buffer_circulaire));
	
	bf_c->espace = malloc(size);
        bf_c->fin = malloc(size);
	bf_c->init_size = size;
	bf_c->size_left = size;
	bf_c->head = 0;

	if(!bf_c->espace || !bf_c->espace){
		
		return -1;
	}

	return 0;

}   

int writeMemory(void* data , uint8_t size){

	//si on a un probleme
	if(size >= bf_c->init_size)
		return -1;
	if(bf_c->size_left > size){
	
		bf_c->espace[bf_c->head] = size;
		memcpy(&(bf_c->espace[(bf_c->head) + 1]), data, size);
	}
	else{
		bf_c->espace[bf_c->head] = size;
		memcpy(&(bf_c->espace[(bf_c->head) + 1]), data, (bf_c->size_left) - 1);
		memcpy(&(bf_c->espace[0]), &(((char*)data)[(bf_c->size_left) - 1]),size - ((bf_c->size_left)-1));
			

	}
	return 0;
}

void *readMemory(uint8_t *size){

	*size = bf_c->espace[bf_c->head];

	if(*size > bf_c->size_left){
	
		memcpy(bf_c->fin, &(bf_c->espace[(bf_c->head) + 1]), bf_c->size_left-1);
		memcpy(&(bf_c->fin[bf_c->size_left-1]), &(bf_c->espace[0]), *size - ((bf_c->size_left) - 1));
	}	else
			memcpy(bf_c->fin,&(bf_c->espace[bf_c->head+1]), *size);
		
		bf_c->size_left -= (*size+1);

		if(bf_c->size_left <= 0)
			bf_c->size_left += bf_c->init_size;
		bf_c->head = bf_c->init_size - bf_c->size_left;

		

		return bf_c->fin;
		
	
}

void freeMemory(){

        free(bf_c->espace);
        free(bf_c->fin);
	free(bf_c);
}
