#ifndef __BUFFER__
#define __BUFFER__

#include <stdint.h>
#include <stdlib.h>

typedef struct buffer{
		uint8_t *base;
		size_t len; //lengt of the content written in base
		size_t size; //total size of the buffer
}buffer_t;

/*
 *	@desc Create a buffer of size bytes
 * 	@param size: Size of the buffer
 * 	@return pointer to a heap allocated buffer_t
 */	
buffer_t* buffer_create(size_t size);

/*
 *	@desc read the content of a file into a buffer 
 * 	@param buffer: buffer where the file content will be written
 * 	@param file_path: static file path to the file to be read
 * 	@param write_mode: buffer write mode\na:append to the buffer\no:overwrite the buffer 
 * 	@return 0: file successfully read\n1: error while reading the file 
 */	
int buffer_fread(buffer_t *buffer, const char *file_path, const char write_mode);

/*
 *	desc write the content of a buffer to a file
 * 	@param buffer: buffer which content has to be written to the file 
 * 	@param file_path: static file path to the file to be written to 
 * 	@param write_mode: file write mode\na:append to the file\no:overwrite the file 
 * 	@return 0: file successfully written\n1: error while writting into the file 
 */
int buffer_fwrite(buffer_t *buffer, const char *file_path, const char *write_mode);

/*
 *	desc write txt to the buffer 
 * 	@param buffer: buffer which content has to be written to
 * 	@param txt: content to be written to the buffer 
 * 	@param write_mode: buffer write mode\na:append to the buffer\no:overwrite the buffer 
 * 	@return 0: successfully written\n1: error while writting into the buffer 
 */
int buffer_write(buffer_t *buffer, const char *txt, size_t len, const char write_mode);

/*
 *	desc empty the content of a buffer 
 * 	@param buffer: buffer which content has to be emptied
 * 	@return void
 */
void buffer_empty(buffer_t *buffer);

/*
 *	desc dump the content of a buffer into the standart output 
 * 	@param buffer: buffer which content has to be dumped
 * 	@return void
 */
void buffer_dump(buffer_t *buffer);

/*
 *	desc delete a buffer 
 * 	@param buffer: buffer which has to be deleted
 * 	@return void
 */
void buffer_free(buffer_t *buffer);

#endif
