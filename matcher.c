#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 100
#define MAX_TEXT_LENGTH 1000
#define MAX_DOCUMENTS 50  // Assuming mapping.txt has up to 1000 lines

// Structure to hold the vocabulary
typedef struct {
    char word[MAX_WORD_LENGTH];
    double idf;
} Vocabulary;

// Function to convert a string to lowercase
void to_lowercase(char *str) {
    for(int i=0; str[i]; i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + ('a' - 'A');
        }
    }
}

// Function to remove punctuation from a string
void remove_punctuation(char *str) {
    int i, j;
    char temp[MAX_TEXT_LENGTH];
    j = 0;
    for(i=0; str[i] != '\0'; i++) {
        if( (str[i] >= 'a' && str[i] <= 'z') ||
            (str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= '0' && str[i] <= '9') ||
            (str[i] == ' ') ) {
            temp[j++] = str[i];
        }
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

// Function to tokenize a text into words
int tokenize(char *text, char tokens[][MAX_WORD_LENGTH]) {
    int count = 0;
    char *token = strtok(text, " ");
    while(token != NULL && count < MAX_WORDS) {
        strcpy(tokens[count++], token);
        token = strtok(NULL, " ");
    }
    return count;
}

// Function to build the vocabulary from all documents and the input
int build_vocabulary(char tokens[][MAX_WORDS][MAX_WORD_LENGTH], int *counts, int num_documents, Vocabulary *vocab) {
    int vocab_count = 0;
    for(int i=0; i<num_documents; i++) {
        for(int j=0; j<counts[i]; j++) {
            int exists = 0;
            for(int k=0; k<vocab_count; k++) {
                if(strcmp(tokens[i][j], vocab[k].word) == 0){
                    exists = 1;
                    break;
                }
            }
            if(!exists){
                strcpy(vocab[vocab_count].word, tokens[i][j]);
                vocab[vocab_count].idf = 0.0;
                vocab_count++;
                if(vocab_count >= MAX_WORDS){
                    printf("Vocabulary limit reached.\n");
                    return vocab_count;
                }
            }
        }
    }
    return vocab_count;
}

// Function to calculate term frequency
void calculate_tf(char tokens[][MAX_WORDS][MAX_WORD_LENGTH], int *counts, double tf[][MAX_WORDS], Vocabulary *vocab, int vocab_count, int num_documents) {
    for(int i=0; i<num_documents; i++) {
        // Initialize TF array for document i
        for(int j=0; j<vocab_count; j++) {
            tf[i][j] = 0.0;
        }
        // Count term frequencies
        for(int j=0; j<counts[i]; j++) {
            for(int k=0; k<vocab_count; k++) {
                if(strcmp(tokens[i][j], vocab[k].word) == 0){
                    tf[i][k] += 1.0;
                    break;
                }
            }
        }
        // Normalize TF by total number of terms in the document
        for(int j=0; j<vocab_count; j++) {
            if(counts[i] > 0){
                tf[i][j] /= counts[i];
            }
        }
    }
}

// Function to calculate IDF
void calculate_idf(Vocabulary *vocab, int vocab_count, char tokens[][MAX_WORDS][MAX_WORD_LENGTH], int *counts, int num_documents) {
    for(int i=0; i<vocab_count; i++) {
        int doc_count = 0;
        for(int j=0; j<num_documents; j++) {
            for(int k=0; k<counts[j]; k++) {
                if(strcmp(vocab[i].word, tokens[j][k]) == 0){
                    doc_count++;
                    break;
                }
            }
        }
        // IDF formula: log((N + 1) / (df + 1)) + 1 to prevent division by zero
        vocab[i].idf = log( ((double)(num_documents) + 1.0) / ((double)(doc_count) + 1.0) ) + 1.0;
    }
}

// Function to compute cosine similarity
double cosine_similarity_func(double *vec1, double *vec2, int size){
    double dot_product = 0.0;
    double norm_vec1 = 0.0;
    double norm_vec2 = 0.0;
    for(int i=0; i<size; i++){
        dot_product += vec1[i] * vec2[i];
        norm_vec1 += vec1[i] * vec1[i];
        norm_vec2 += vec2[i] * vec2[i];
    }
    if(norm_vec1 == 0.0 || norm_vec2 == 0.0){
        return 0.0;
    }
    return dot_product / (sqrt(norm_vec1) * sqrt(norm_vec2));
}

int main() {

    // printf("huga");
    FILE *file;
    char filename[] = "commands.txt";
    char line[MAX_TEXT_LENGTH];
    char documents[MAX_DOCUMENTS][MAX_TEXT_LENGTH];
    int num_documents = 0;
char input_text[MAX_TEXT_LENGTH];
    // printf("THis is ");

    // Open the file
    char customText[]="transcription.sh";
    file = fopen(customText, "r");
    if(file == NULL){
        printf("Error opening file '%s'. Ensure the file exists in the current directory.\n", customText);
        return 1;
    }

    // Read lines from the file
    while(fgets(line, sizeof(line), file) != NULL && num_documents < MAX_DOCUMENTS){
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        // printf("%s",line);
        strcpy(input_text, line);
    }
    file = fopen(filename, "r");
    if(file == NULL){
        printf("Error opening file '%s'. Ensure the file exists in the current directory.\n", filename);
        return 1;
    }

    // Read lines from the file
        // while(fgets(line, sizeof(line), file) != NULL && num_documents < MAX_DOCUMENTS){
        //     // Remove newline character
        //     line[strcspn(line, "\n")] = 0;
            
        //     strcpy(documents[num_documents++], line);
        // }
    // while(fgets(line, sizeof(line), file) != NULL && num_documents < MAX_DOCUMENTS){
    // // Remove newline character
    // line[strcspn(line, "\n")] = 0;

    // // Check for a comma in the line
    // if (strchr(line, ',') != NULL) {
    //     break; // Stop reading when a comma is found
    // }

    // // Store the line in the documents array
    // strcpy(documents[num_documents++], line);
    // }
    while(fgets(line, sizeof(line), file) != NULL && num_documents < MAX_DOCUMENTS){
    // Remove newline character
    line[strcspn(line, "\n")] = 0;

    // Find the position of the comma
    char *comma_pos = strchr(line, ',');

    // If a comma is found, terminate the string at the comma
    if (comma_pos != NULL) {
        *comma_pos = 0;  // Null-terminate the string at the comma
    }

    // Store the line (left of the comma) in the documents array
    strcpy(documents[num_documents++], line);
}

    fclose(file);

    if(num_documents == 0){
        printf("No documents found in '%s'.\n", filename);
        return 1;
    }

    // Read user input
    
    // printf("Enter your sentence: ");
    // if(fgets(input_text, sizeof(input_text), stdin) == NULL){
    //     printf("Error reading input.\n");
    //     return 1;
    // }
    // Remove newline character
    input_text[strcspn(input_text, "\n")] = 0;

    // Preprocess texts: convert to lowercase and remove punctuation
    for(int i=0; i<num_documents; i++) {
        to_lowercase(documents[i]);
        remove_punctuation(documents[i]);
    }
    to_lowercase(input_text);
    remove_punctuation(input_text);

    // Tokenize texts
    char tokens[MAX_DOCUMENTS +1][MAX_WORDS][MAX_WORD_LENGTH]; // +1 for input
    int counts[MAX_DOCUMENTS +1]; // +1 for input

    for(int i=0; i<num_documents; i++) {
        counts[i] = tokenize(documents[i], tokens[i]);
    }
    // Tokenize input sentence
    counts[num_documents] = tokenize(input_text, tokens[num_documents]);

    int total_documents = num_documents + 1; // Including input

    // Build vocabulary
    Vocabulary vocab[MAX_WORDS];
    int vocab_count = build_vocabulary(tokens, counts, total_documents, vocab);
    if(vocab_count == 0){
        printf("No vocabulary built. Check the input texts.\n");
        return 1;
    }

    // Calculate IDF
    calculate_idf(vocab, vocab_count, tokens, counts, total_documents);

    // Calculate TF for all documents
    double tf[MAX_DOCUMENTS +1][MAX_WORDS]; // TF vectors
    calculate_tf(tokens, counts, tf, vocab, vocab_count, total_documents);

    // Compute TF-IDF vectors
    double tfidf[MAX_DOCUMENTS +1][MAX_WORDS];
    for(int i=0; i<total_documents; i++) {
        for(int j=0; j<vocab_count; j++) {
            tfidf[i][j] = tf[i][j] * vocab[j].idf;
        }
    }

    // Compute cosine similarity between input and each document
    double similarities[num_documents];
    for(int i=0; i<num_documents; i++) {
        similarities[i] = cosine_similarity_func(tfidf[i], tfidf[num_documents], vocab_count) * 100.0;
    }

    // Find the document with maximum similarity
    double max_similarity = similarities[0];
    int max_index = 0;
    for(int i=1; i<num_documents; i++) {
        if(similarities[i] > max_similarity){
            max_similarity = similarities[i];
            max_index = i;
        }
    }

    // Output the result
    // printf("Most similar line:\n");
    printf("%d", max_index +1);
    // printf("Similarity: %.2lf%%\n", max_similarity);

    return 0;
}


//documents[max_index]