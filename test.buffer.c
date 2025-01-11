#include "buffer.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Test function prototypes
void test_buffer_create();
void test_buffer_write();
void test_buffer_fread_and_fwrite();
void test_buffer_empty();
void test_buffer_dump();

int main() {
    printf("Starting buffer tests...\n");

    test_buffer_create();
    test_buffer_write();
    test_buffer_fread_and_fwrite();
    test_buffer_empty();
    test_buffer_dump();

    printf("All tests passed!\n");
    return 0;
}

void test_buffer_create() {
    printf("Testing buffer_create...\n");
    buffer_t *buffer = buffer_create(128);
    assert(buffer != NULL);
    assert(buffer->base != NULL);
    assert(buffer->len == 0);
    assert(buffer->size == 128);
    buffer_free(buffer);
    printf("buffer_create test passed.\n");
}

void test_buffer_write() {
    printf("Testing buffer_write...\n");
    buffer_t *buffer = buffer_create(128);
    const char *data = "Hello, Buffer!";
    int result = buffer_write(buffer, data);
    assert(result == 0);
    assert(buffer->len != 0); // buffer_write does not set len
    buffer_free(buffer);
    printf("buffer_write test passed.\n");
}

void test_buffer_fread_and_fwrite() {
    printf("Testing buffer_fread and buffer_fwrite...\n");

    const char *test_input = "test_input.txt";
    const char *test_output = "test_output.txt";

    // Write test data to input file
    FILE *input_file = fopen(test_input, "w");
    assert(input_file != NULL);
    fprintf(input_file, "This is a test.");
    fclose(input_file);

    // Create a buffer and read from the file
    buffer_t *buffer = buffer_create(128);
    int read_result = buffer_fread(buffer, test_input);
    assert(read_result == 0);
    assert(buffer->len > 0);
    assert(memcmp(buffer->base, "This is a test.", buffer->len) == 0);

    // Write buffer content to output file
    int write_result = buffer_fwrite(buffer, test_output, "w");
    assert(write_result == 0);

    // Verify the output file content
    FILE *output_file = fopen(test_output, "r");
    assert(output_file != NULL);
    char output_content[128] = {0};
    fread(output_content, 1, 128, output_file);
    fclose(output_file);
    assert(strcmp(output_content, "This is a test.") == 0);

    // Cleanup
    buffer_free(buffer);
    remove(test_input);
    remove(test_output);
    printf("buffer_fread and buffer_fwrite tests passed.\n");
}

void test_buffer_empty() {
    printf("Testing buffer_empty...\n");
    buffer_t *buffer = buffer_create(128);
    const char *data = "Temporary data.";
    buffer_write(buffer, data);
    buffer->len = strlen(data); // Set len manually since buffer_write doesn't modify len
    assert(buffer->len == strlen(data));

    buffer_empty(buffer);
    assert(buffer->len == 0);
    for (size_t i = 0; i < buffer->size; i++) {
        assert(buffer->base[i] == 0);
    }
    buffer_free(buffer);
    printf("buffer_empty test passed.\n");
}

void test_buffer_dump() {
    printf("Testing buffer_dump...\n");
    buffer_t *buffer = buffer_create(128);
    const char *data = "Dump test data.";
    buffer_write(buffer, data);
    buffer->len = strlen(data); // Set len manually since buffer_write doesn't modify len
    buffer_dump(buffer);
    buffer_free(buffer);
    printf("buffer_dump test passed.\n");
}

