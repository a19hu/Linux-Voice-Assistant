#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <ctype.h>

#define AUDIO_FILE "audio_base64.txt"
#define API_URL "https://speech.googleapis.com/v1/speech:recognize?key=AIzaSyChIFkQKR5V7IJ9VFh4TkmNI0Orwc5UO5k"
#define OUTPUT_FILE "transcription.txt"

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