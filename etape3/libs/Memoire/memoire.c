#include "../inc/memoire.h"

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

// A ajouter les #ifdef pour les mutex
/*
int allocateMemory(size_t size){

	size_m = size;
	//on va allouer une espace de taille size
	buff = malloc(size);

	if(buff == NULL) //cas si allocation failed
		return -1;

	//fill mem with a constant byte "0"
	memset(buff, 0, size);
	return 0;

}

int writeMemory(void* data, uint8_t size){

  

        int ecrits;
	if(write_ind != read_ind){

		//test case of error, si la donnee(s) peuvent etre stockee dans 
		//l'espace de la memoire allouee et initialisee
		//cad que la zone de memoire dispo peut heberger la donnee

		if(((write_ind < read_ind) && (read_ind - write_ind < size)) || 
				((write_ind - read_ind < size) && (read_ind < write_ind)))
			return -1;

	}

	//maitenant on va affecter la taille a une zone dans notre buffer
	//mais buffer et la taille sont des types differentes, d'ou 
	//l'interet du cast 
		
	((uint8_t*)buff)[write_ind] = size;
	 write_ind += 1;
	 write_ind = write_ind % size_m;

	 
	 if((int)size_m < (size + write_ind + 1)){
		 ecrits = size_m - write_ind;
		 memcpy(write_ind + buff, data, ecrits);
		 memcpy(buff, data+ ecrits, size - ecrits); 
		 write_ind = size - ecrits;
	 }
	 else{
		 memcpy(write_ind + buff, data, size);
		 write_ind +=size;
		 write_ind %=size_m;
	 }
	 return 0;
}


	 
void *readMemory(uint8_t* size){

	//la zone ou on est posi en lecture dans notre buffer
	//elle va etre stocke dans le size de cette fct
	//pourque grace a size pouvoir alloue une zone memoire dediee a
	//la donnee d'une taille qui correspond a la taille size
	int lire;
	
	*size = ((uint8_t*)buff)[read_ind];
	void *donne = malloc(*size); 
	

	if((int)size_m >= 1+ *size + read_ind){
	
		memcpy(donne, read_ind + buff, *size);
		read_ind = read_ind + 1;
		read_ind = read_ind % size_m;
		
	}
	else{
		lire = size_m - read_ind;
		memcpy(donne, buff + read_ind, lire);
		memcpy((*size - lire) + donne, buff, (*size) - lire);
		read_ind = (*size) - lire;

	}
	//on renvoie la donnee lue
	fflush(stdout);
	return donne;
} 	
*/

void freeMemory(){

        free(bf_c->espace);
        free(bf_c->fin);
	free(bf_c);
}
