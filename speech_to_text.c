// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include <curl/curl.h>

// // #define AUDIO_FILE "./audio_base64.txt"
// // #define API_URL "https://speech.googleapis.com/v1/speech:recognize?key=346563263215-r9uk8pvd2llfvfunqb8hmqt0oh1liao2.apps.googleusercontent.com"

// // // Function to read file into memory
// // void escape_json_string(const char *input, char *output) {
// //     char *out_ptr = output;
// //     while (*input) {
// //         if (*input == '\"' || *input == '\\') {
// //             *out_ptr++ = '\\';  // Escape the special character
// //         }
// //         *out_ptr++ = *input++;
// //     }
// //     *out_ptr = '\0';  // Null terminate the string
// // }
// // static char *read_file(const char *filename, long *size)
// // {
// //     FILE *file = fopen(filename, "rb");
// //     if (!file)
// //     {
// //         perror("Failed to open file");
// //         return NULL;
// //     }

// //     fseek(file, 0, SEEK_END);
// //     *size = ftell(file);
// //     rewind(file);

// //     char *buffer = malloc(*size + 1); // +1 for null terminator
// //     if (!buffer)
// //     {
// //         perror("Failed to allocate memory");
// //         fclose(file);
// //         return NULL;
// //     }

// //     fread(buffer, 1, *size, file);
// //     buffer[*size] = '\0'; // Null terminate the string
// //     fclose(file);
// //     // printf("Reached here\n");
// //     return buffer;
// // }

// // int main()
// // {
// //     CURL *curl;
// //     CURLcode res;

// //     // Initialize CURL
// //     curl_global_init(CURL_GLOBAL_ALL);
// //     curl = curl_easy_init();
// //     if (!curl)
// //     {
// //         fprintf(stderr, "Failed to initialize CURL\n");
// //         return 1;
// //     }

// //     long audio_size;
// //     char *audio_data = read_file(AUDIO_FILE, &audio_size);
// //     if (!audio_data)
// //     {
// //         curl_easy_cleanup(curl);
// //         return 1;
// //     }

// //     // JSON payload for Google Speech-to-Text API
// //     // Make sure audio_data is Base64-encoded, and correctly inserted into the JSON
// //     char json_payload[8192]; // Adjust size based on the expected length of your JSON
// //     char escaped_audio_data[8192];
// //     escape_json_string(audio_data, escaped_audio_data);

// //     // Create the JSON payload
// //     snprintf(json_payload, sizeof(json_payload),
// //              "{\"config\":{\"encoding\":\"LINEAR16\",\"sampleRateHertz\":44100,\"languageCode\":\"en-US\"},"
// //              "\"audio\":{\"content\":\"%s\"}}",
// //              escaped_audio_data);

// //     struct curl_slist *headers = NULL;
// //     headers = curl_slist_append(headers, "Content-Type: application/json");

// //     curl_easy_setopt(curl, CURLOPT_URL, API_URL);
// //     curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
// //     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

// //     // Perform the request
// //     res = curl_easy_perform(curl);
// //     if (res != CURLE_OK)
// //     {
// //         fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
// //     }
// //     // printf("Payload: %s\n", json_payload);

// //     // Clean up
// //     free(audio_data);
// //     curl_slist_free_all(headers);
// //     curl_easy_cleanup(curl);
// //     curl_global_cleanup();

// //     return 0;
// // }
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <curl/curl.h>
// #include <ctype.h>

// #define AUDIO_FILE "audio_base64.txt"
// // Replace with your actual API key from Google Cloud
// #define API_URL "https://speech.googleapis.com/v1/speech:recognize?key=AIzaSyChIFkQKR5V7IJ9VFh4TkmNI0Orwc5UO5k"

// // Function to read file into memory
// static char *read_file(const char *filename, long *size)
// {
//     FILE *file = fopen(filename, "rb");
//     if (!file)
//     {
//         perror("Failed to open file");
//         return NULL;
//     }

//     fseek(file, 0, SEEK_END);
//     *size = ftell(file);
//     rewind(file);

//     char *buffer = malloc(*size + 1); // +1 for null terminator
//     if (!buffer)
//     {
//         perror("Failed to allocate memory");
//         fclose(file);
//         return NULL;
//     }

//     fread(buffer, 1, *size, file);
//     buffer[*size] = '\0'; // Null terminate the string
//     fclose(file);

//     return buffer;
// }

// int main()
// {
//     CURL *curl;
//     CURLcode res;

//     // Initialize CURL
//     curl_global_init(CURL_GLOBAL_ALL);
//     curl = curl_easy_init();
//     if (!curl)
//     {
//         fprintf(stderr, "Failed to initialize CURL\n");
//         return 1;
//     }

//     long audio_size;
//     char *audio_data = read_file(AUDIO_FILE, &audio_size);
//     if (!audio_data)
//     {
//         curl_easy_cleanup(curl);
//         return 1;
//     }

//     // Calculate buffer size for JSON payload
//     size_t json_size = strlen("{\"config\":{\"encoding\":\"LINEAR16\",\"sampleRateHertz\":44100,\"languageCode\":\"en-US\"},"
//                               "\"audio\":{\"content\":\"");
//     json_size += audio_size * 4 / 3 + 3; // Base64-encoded size estimate (Base64 expands the data size by ~33%)
//     json_size += strlen("\"}}");

//     char *json_payload = malloc(json_size);
//     if (!json_payload)
//     {
//         perror("Failed to allocate memory for JSON payload");
//         free(audio_data);
//         curl_easy_cleanup(curl);
//         return 1;
//     }
//     // Remove newlines from the Base64 string
// char *ptr = audio_data;
// while (*ptr) {
//     if (*ptr == '\n') {
//         memmove(ptr, ptr + 1, strlen(ptr)); // Shift the rest of the string back by 1
//     } else {
//         ptr++;
//     }
// }


//     // Create the JSON payload (no need to escape the Base64-encoded data)
//     snprintf(json_payload, json_size,
//              "{\"config\":{\"encoding\":\"LINEAR16\",\"sampleRateHertz\":44100,\"languageCode\":\"en-US\"},"
//              "\"audio\":{\"content\":\"%s\"}}",
//              audio_data);

//     struct curl_slist *headers = NULL;
//     headers = curl_slist_append(headers, "Content-Type: application/json");

//     curl_easy_setopt(curl, CURLOPT_URL, API_URL);
//     curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
//     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

//     // Perform the request
//     res = curl_easy_perform(curl);
//     if (res != CURLE_OK)
//     {
//         fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
//     }
    
//     // Optionally print the response
//     // printf("Payload: %s\n", json_payload);

//     // Clean up
//     free(audio_data);
//     free(json_payload);
//     curl_slist_free_all(headers);
//     curl_easy_cleanup(curl);
//     curl_global_cleanup();

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <curl/curl.h>
// #include <json-c/json.h>  // Include json-c library

// #define AUDIO_FILE "audio_base64.txt"
// #define API_URL "https://speech.googleapis.com/v1/speech:recognize?key=AIzaSyChIFkQKR5V7IJ9VFh4TkmNI0Orwc5UO5k"

// // Function to read file into memory
// static char *read_file(const char *filename, long *size) {
//     FILE *file = fopen(filename, "rb");
//     if (!file) {
//         perror("Failed to open file");
//         return NULL;
//     }

//     fseek(file, 0, SEEK_END);
//     *size = ftell(file);
//     rewind(file);

//     char *buffer = malloc(*size + 1); // +1 for null terminator
//     if (!buffer) {
//         perror("Failed to allocate memory");
//         fclose(file);
//         return NULL;
//     }

//     fread(buffer, 1, *size, file);
//     buffer[*size] = '\0'; // Null terminate the string
//     fclose(file);

//     return buffer;
// }

// // Callback function to capture response
// static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
//     size_t total_size = size * nmemb;
//     strncat(userdata, ptr, total_size);
//     return total_size;
// }

// int main() {
//     CURL *curl;
//     CURLcode res;

//     // Initialize CURL
//     curl_global_init(CURL_GLOBAL_ALL);
//     curl = curl_easy_init();
//     if (!curl) {
//         fprintf(stderr, "Failed to initialize CURL\n");
//         return 1;
//     }

//     long audio_size;
//     char *audio_data = read_file(AUDIO_FILE, &audio_size);
//     if (!audio_data) {
//         curl_easy_cleanup(curl);
//         return 1;
//     }

//     // Remove newlines from the Base64 string
//     char *ptr = audio_data;
//     while (*ptr) {
//         if (*ptr == '\n') {
//             memmove(ptr, ptr + 1, strlen(ptr)); // Shift the rest of the string back by 1
//         } else {
//             ptr++;
//         }
//     }

//     // Calculate buffer size for JSON payload
//     size_t json_size = strlen("{\"config\":{\"encoding\":\"LINEAR16\",\"sampleRateHertz\":44100,\"languageCode\":\"en-US\"},"
//                               "\"audio\":{\"content\":\"");
//     json_size += audio_size * 4 / 3 + 3; // Base64-encoded size estimate
//     json_size += strlen("\"}}");

//     char *json_payload = malloc(json_size);
//     if (!json_payload) {
//         perror("Failed to allocate memory for JSON payload");
//         free(audio_data);
//         curl_easy_cleanup(curl);
//         return 1;
//     }

//     // Create the JSON payload
//     snprintf(json_payload, json_size,
//              "{\"config\":{\"encoding\":\"LINEAR16\",\"sampleRateHertz\":44100,\"languageCode\":\"en-US\"},"
//              "\"audio\":{\"content\":\"%s\"}}",
//              audio_data);

//     struct curl_slist *headers = NULL;
//     headers = curl_slist_append(headers, "Content-Type: application/json");

//     // Response buffer
//     char response[8192] = {0};  // Adjust size as necessary

//     // Set CURL options
//     curl_easy_setopt(curl, CURLOPT_URL, API_URL);
//     curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
//     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
//     curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

//     // Perform the request
//     res = curl_easy_perform(curl);
//     if (res != CURLE_OK) {
//         fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
//     } else {
//         // Parse JSON response
//         struct json_object *parsed_json;
//         struct json_object *results;
//         struct json_object *alternatives;
//         struct json_object *transcript;

//         parsed_json = json_tokener_parse(response);

//         // Check for 'results' array in the response
//         if (json_object_object_get_ex(parsed_json, "results", &results)) {
//             struct json_object *first_result = json_object_array_get_idx(results, 0);
//             if (json_object_object_get_ex(first_result, "alternatives", &alternatives)) {
//                 struct json_object *first_alternative = json_object_array_get_idx(alternatives, 0);
//                 if (json_object_object_get_ex(first_alternative, "transcript", &transcript)) {
//                     printf(" %s\n", json_object_get_string(transcript));
//                 }
//             }
//         } else {
//             printf("No transcription found in the response.\n");
//         }
        
//         // Free JSON objects
//         json_object_put(parsed_json);
//     }

//     // Clean up
//     free(audio_data);
//     free(json_payload);
//     curl_slist_free_all(headers);
//     curl_easy_cleanup(curl);
//     curl_global_cleanup();

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <curl/curl.h>
// #include <json-c/json.h>  // Include json-c library

// #define AUDIO_FILE "audio_base64.txt"
// #define API_URL "https://speech.googleapis.com/v1/speech:recognize?key=AIzaSyChIFkQKR5V7IJ9VFh4TkmNI0Orwc5UO5k"

// // Function to read file into memory
// static char *read_file(const char *filename, long *size) {
//     FILE *file = fopen(filename, "rb");
//     if (!file) {
//         perror("Failed to open file");
//         return NULL;
//     }

//     fseek(file, 0, SEEK_END);
//     *size = ftell(file);
//     rewind(file);

//     // Cast malloc to `char*`
//     char *buffer = (char*) malloc(*size + 1); // +1 for null terminator
//     if (!buffer) {
//         perror("Failed to allocate memory");
//         fclose(file);
//         return NULL;
//     }

//     fread(buffer, 1, *size, file);
//     buffer[*size] = '\0'; // Null terminate the string
//     fclose(file);

//     return buffer;
// }

// // Callback function to capture response
// static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
//     size_t total_size = size * nmemb;
//     // Cast `ptr` and `userdata` to `char*`
//     strncat((char*)userdata, (const char*)ptr, total_size);
//     return total_size;
// }

// int main() {
//     CURL *curl;
//     CURLcode res;

//     // Initialize CURL
//     curl_global_init(CURL_GLOBAL_ALL);
//     curl = curl_easy_init();
//     if (!curl) {
//         fprintf(stderr, "Failed to initialize CURL\n");
//         return 1;
//     }

//     long audio_size;
//     char *audio_data = read_file(AUDIO_FILE, &audio_size);
//     if (!audio_data) {
//         curl_easy_cleanup(curl);
//         return 1;
//     }

//     // Remove newlines from the Base64 string
//     char *ptr = audio_data;
//     while (*ptr) {
//         if (*ptr == '\n') {
//             memmove(ptr, ptr + 1, strlen(ptr)); // Shift the rest of the string back by 1
//         } else {
//             ptr++;
//         }
//     }

//     // Calculate buffer size for JSON payload
//     size_t json_size = strlen("{\"config\":{\"encoding\":\"LINEAR16\",\"sampleRateHertz\":44100,\"languageCode\":\"en-US\"},"
//                               "\"audio\":{\"content\":\"");
//     json_size += audio_size * 4 / 3 + 3; // Base64-encoded size estimate
//     json_size += strlen("\"}}");

//     // Cast malloc to `char*`
//     char *json_payload = (char*) malloc(json_size);
//     if (!json_payload) {
//         perror("Failed to allocate memory for JSON payload");
//         free(audio_data);
//         curl_easy_cleanup(curl);
//         return 1;
//     }

//     // Create the JSON payload
//     snprintf(json_payload, json_size,
//              "{\"config\":{\"encoding\":\"LINEAR16\",\"sampleRateHertz\":44100,\"languageCode\":\"en-US\"},"
//              "\"audio\":{\"content\":\"%s\"}}",
//              audio_data);

//     struct curl_slist *headers = NULL;
//     headers = curl_slist_append(headers, "Content-Type: application/json");

//     // Response buffer
//     char response[8192] = {0};  // Adjust size as necessary

//     // Set CURL options
//     curl_easy_setopt(curl, CURLOPT_URL, API_URL);
//     curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
//     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
//     curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

//     // Perform the request
//     res = curl_easy_perform(curl);
//     if (res != CURLE_OK) {
//         fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
//     } else {
//         // Parse JSON response
//         struct json_object *parsed_json;
//         struct json_object *results;
//         struct json_object *alternatives;
//         struct json_object *transcript;

//         parsed_json = json_tokener_parse(response);

//         // Check for 'results' array in the response
//         if (json_object_object_get_ex(parsed_json, "results", &results)) {
//             struct json_object *first_result = json_object_array_get_idx(results, 0);
//             if (json_object_object_get_ex(first_result, "alternatives", &alternatives)) {
//                 struct json_object *first_alternative = json_object_array_get_idx(alternatives, 0);
//                 if (json_object_object_get_ex(first_alternative, "transcript", &transcript)) {
//                     printf("%s\n", json_object_get_string(transcript));
//                 }
//             }
//         } else {
//             printf("No transcription found in the response.\n");
//         }
        
//         // Free JSON objects
//         json_object_put(parsed_json);
//     }

//     // Clean up
//     free(audio_data);
//     free(json_payload);
//     curl_slist_free_all(headers);
//     curl_easy_cleanup(curl);
//     curl_global_cleanup();

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <ctype.h>

#define AUDIO_FILE "audio_base64.txt"
#define API_URL "https://speech.googleapis.com/v1/speech:recognize?key=AIzaSyChIFkQKR5V7IJ9VFh4TkmNI0Orwc5UO5k"
#define OUTPUT_FILE "transcription.sh"

// Function to read file into memory
static char *read_file(const char *filename, long *size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    rewind(file);

    char *buffer = (char*) malloc(*size + 1); // +1 for null terminator
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, *size, file);
    buffer[*size] = '\0'; // Null terminate the string
    fclose(file);

    return buffer;
}

// Callback function to capture response
static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    strncat((char*)userdata, (const char*)ptr, total_size);
    return total_size;
}

// Function to convert a string to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

int main() {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return 1;
    }

    long audio_size;
    char *audio_data = read_file(AUDIO_FILE, &audio_size);
    if (!audio_data) {
        curl_easy_cleanup(curl);
        return 1;
    }

    char *ptr = audio_data;
    while (*ptr) {
        if (*ptr == '\n') {
            memmove(ptr, ptr + 1, strlen(ptr)); // Shift the rest of the string back by 1
        } else {
            ptr++;
        }
    }

    size_t json_size = strlen("{\"config\":{\"encoding\":\"LINEAR16\",\"sampleRateHertz\":44100,\"languageCode\":\"en-US\"},"
                              "\"audio\":{\"content\":\"");
    json_size += audio_size * 4 / 3 + 3; // Base64-encoded size estimate
    json_size += strlen("\"}}");

    char *json_payload = (char*) malloc(json_size);
    if (!json_payload) {
        perror("Failed to allocate memory for JSON payload");
        free(audio_data);
        curl_easy_cleanup(curl);
        return 1;
    }

    snprintf(json_payload, json_size,
             "{\"config\":{\"encoding\":\"LINEAR16\",\"sampleRateHertz\":44100,\"languageCode\":\"en-US\"},"
             "\"audio\":{\"content\":\"%s\"}}",
             audio_data);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    char response[8192] = {0};

    curl_easy_setopt(curl, CURLOPT_URL, API_URL);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        struct json_object *parsed_json;
        struct json_object *results;
        struct json_object *alternatives;
        struct json_object *transcript;

        parsed_json = json_tokener_parse(response);

        if (json_object_object_get_ex(parsed_json, "results", &results)) {
            struct json_object *first_result = json_object_array_get_idx(results, 0);
            if (json_object_object_get_ex(first_result, "alternatives", &alternatives)) {
                struct json_object *first_alternative = json_object_array_get_idx(alternatives, 0);
                if (json_object_object_get_ex(first_alternative, "transcript", &transcript)) {
                    const char *original_text = json_object_get_string(transcript);
                    char lowercase_text[1024];
                    strncpy(lowercase_text, original_text, sizeof(lowercase_text) - 1);
                    lowercase_text[sizeof(lowercase_text) - 1] = '\0';
                    to_lowercase(lowercase_text);

                    // Write to file
                    FILE *file = fopen(OUTPUT_FILE, "w");
                    if (file) {
                        fprintf(file, "%s\n", lowercase_text);
                        fclose(file);
                        printf("Transcription written in lowercase to '%s'.\n", OUTPUT_FILE);
                    } else {
                        printf("Failed to open file for writing.\n");
                    }
                }
            }
        } else {
            printf("No transcription found in the response.\n");
        }
        
        json_object_put(parsed_json);
    }

    free(audio_data);
    free(json_payload);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}
