#ifndef _MEMOIRE_H_
#define _MEMOIRE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
/*
typedef struct circular_buffer{
	char* buffer;
	size_t size;
	int write_index;
	int read_index;
}circular_buffer_t;

circular_buffer_t *buffercirc;
*/
struct buffer_circulaire{

	char *espace;
	char *fin;
	int init_size;
	int size_left;
	int head;
};

struct buffer_circulaire * bf_c; 

int allocateMemory(size_t);
int writeMemory(void*,uint8_t);
void *readMemory(uint8_t*);
void freeMemory();
bool memoryIsEmpty(void);
bool memoryIsFull(void);

#endif
