#ifndef __BUFFER__
#define __BUFFER__

#include <stdint.h>
#include <stdlib.h>

typedef struct buffer{
		uint8_t *base;
		size_t len; //the value of a base
		size_t size; //memory occupied by the base
}buffer_t;

buffer_t* buffer_create(size_t size);

int buffer_fread(buffer_t *buffer, const char *file_path);
int buffer_fwrite(buffer_t *buffer, const char *file_path, const char *write_mode);
int buffer_write(buffer_t *buffer, const char *data);

void buffer_empty(buffer_t *buffer);
void buffer_dump(buffer_t *buffer);

void buffer_free(buffer_t *buffer);

#endif
