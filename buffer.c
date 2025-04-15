#include "./buffer.h"
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef __BUFFER_THREAD_SAFE__
#include <pthread.h>
pthread_mutex_t Lock = PTHREAD_MUTEX_INITIALIZER;
#endif




buffer_t* buffer_create(size_t size){
	buffer_t *new_buffer = calloc(1, sizeof(buffer_t));
	if(new_buffer == NULL){
		fprintf(stderr, "Unable to create buffer: %s\n", strerror(errno));
		return NULL;
	}
	new_buffer->base = calloc(size, sizeof(uint8_t));
	if(new_buffer->base == NULL){
		fprintf(stderr, "Unable to create buffer base: %s\n", strerror(errno));
		free(new_buffer);
		return NULL;
	}
	new_buffer->len = 0;
	new_buffer->size = size;
	return new_buffer;
}

int buffer_write(buffer_t *buffer, const char *txt, size_t len, const char write_mode){
	if(!buffer ||!buffer->base){
		fputs("Buffer is NULL or uninitialized\n", stderr);
		return 1;
	}
	if(len > buffer->size){
		fputs("Unsufficient buffer size\n", stderr);
		return 1;
	}
	void* tmp = NULL;
	switch(write_mode){
		case 'a':
			if(len > (buffer->size - buffer->len)){
				fputs("Unsufficient buffer size\n", stderr);
				return 1;
			}	
			#ifdef __BUFFER_THREAD_SAFE__
				pthread_mutex_lock(&Lock);
			#endif

			tmp = memcpy((buffer->base + buffer->len), txt ,len);
			buffer->len += len;
			#ifdef __BUFFER_THREAD_SAFE__
				pthread_mutex_unlock(&Lock);
			#endif
			return (tmp == NULL);
			break;
		case 'w':
			#ifdef __BUFFER_THREAD_SAFE__
				pthread_mutex_lock(&Lock);
			#endif
			tmp = memcpy(buffer->base, txt ,len);
			buffer->len = len;
			#ifdef __BUFFER_THREAD_SAFE__
				pthread_mutex_unlock(&Lock);
			#endif
			return (tmp == NULL);
			break;
		default:
			fputs("Invalid write mode\n", stderr);
			return 1;
	}
	return 0;
}

int buffer_fread(buffer_t *buffer, const char *file_path, const char write_mode){
	FILE *file_ptr = NULL;
	uint8_t* start = buffer->base;
	switch(write_mode){
		case 'a':
			start += buffer->len;
			break;
		case 'w':
			break;
		default:
			fputs("Invalid write mode\n", stderr);
			return 1;
	}
	file_ptr = fopen(file_path, "r");
	if(file_ptr == NULL){
		fprintf(stderr, "Unable to open file %s: %s", file_path, strerror(errno));
		return 1;
	}
	#ifdef __BUFFER_THREAD_SAFE__
		pthread_mutex_lock(&Lock);
	#endif
	size_t len = fread(start, sizeof(uint8_t), buffer->size, file_ptr);
	buffer->len = len;
	#ifdef __BUFFER_THREAD_SAFE__
		pthread_mutex_unlock(&Lock);
	#endif
	if (ferror(file_ptr)){
		fputs("failed reading the file", stderr);
		fclose(file_ptr);
		return 1;
	}
	fclose(file_ptr);
	return 0;
}

int buffer_fwrite(buffer_t *buffer, const char *file_path, const char *write_mode){
	FILE *file_ptr = fopen(file_path, write_mode);
	if(file_ptr == NULL){
		fprintf(stderr, "Unable to open file %s: %s", file_path, strerror(errno));
		return 1;
	}
	size_t write_count = fwrite(buffer->base, sizeof(uint8_t), buffer->len, file_ptr);
	if (write_count != buffer->len){
		fputs("failed write into the file", stderr);
		fclose(file_ptr);
		return 1;
	}
	fclose(file_ptr);
	return 0;
}

void buffer_empty(buffer_t *buffer){
	#ifdef __BUFFER_THREAD_SAFE__
		pthread_mutex_lock(&Lock);
	#endif
	//memset(buffer->base, '\0', buffer->len);
	buffer->len = 0;
	#ifdef __BUFFER_THREAD_SAFE__
		pthread_mutex_unlock(&Lock);
	#endif
	return;
}


void buffer_dump(buffer_t *buffer) {
	if (!buffer || !buffer->base) {
		fputs("Buffer is NULL or uninitialized\n", stderr);
		return;
	}

	printf("Buffer Dump (len: %zu, size: %zu):\n", buffer->len, buffer->size);

	// Print as text
	printf("Text: %*s", (int)buffer->len ,(char*)buffer->base);
	putchar('\n');
	// Print as hex
	printf("Hex: ");
	for (size_t i = 0; i < buffer->len; i++) {
		printf("%02X ", buffer->base[i]);
	}
	putchar('\n');
}

void buffer_free(buffer_t *buffer){
	if(!buffer || !buffer->base)
		return;
	#ifdef __BUFFER_THREAD_SAFE__
		pthread_mutex_lock(&Lock);
	#endif
	free(buffer->base);
	free(buffer);
	#ifdef __BUFFER_THREAD_SAFE__
		pthread_mutex_unlock(&Lock);
	#endif
	return;
}
