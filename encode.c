#include <stdio.h>
#include <stdlib.h>
#include <b64/cencode.h>  // Include the libb64 encoding library

// Function to encode file contents to Base64
char* encode_file_to_base64(const char *file_path) {
    // Open the file in binary mode
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file %s\n", file_path);
        return NULL;
    }

    // Determine file size
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file data
    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    // Read file contents into buffer
    fread(buffer, 1, file_size, file);
    fclose(file);

    // Calculate size for the Base64 encoded output
    size_t encoded_size = 4 * ((file_size + 2) / 3);
    char *encoded_data = (char *)malloc(encoded_size + 1);  // +1 for null terminator
    if (!encoded_data) {
        fprintf(stderr, "Memory allocation error\n");
        free(buffer);
        return NULL;
    }

    // Encode to Base64
    base64_encodestate state;
    base64_init_encodestate(&state);
    int output_size = base64_encode_block((const char*)buffer, file_size, encoded_data, &state);
    output_size += base64_encode_blockend(encoded_data + output_size, &state);
    encoded_data[output_size] = '\0';  // Null-terminate the encoded string

    // Free the original file buffer
    free(buffer);

    return encoded_data;
}

int main() {
    const char *file_path = "recording.wav";  // Path to your .wav file
    
    // Encode the file to Base64
    char *encoded_audio = encode_file_to_base64(file_path);
    if (!encoded_audio) {
        fprintf(stderr, "Failed to encode file\n");
        return 1;
    }

    // Print Base64 encoded data
    printf("Base64 Encoded Audio:\n%s\n", encoded_audio);

    // Free the Base64 encoded string
    free(encoded_audio);
    return 0;
}
