#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 100
#define MAX_TEXT_LENGTH 1000
#define MAX_DOCUMENTS 50 


typedef struct {
    char word[MAX_WORD_LENGTH];
    double idf;
} Vocabulary;

void to_lowercase(char *str) {
    for(int i=0; str[i]; i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + ('a' - 'A');
        }
    }
}


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


int tokenize(char *text, char tokens[][MAX_WORD_LENGTH]) {
    int count = 0;
    char *token = strtok(text, " ");
    while(token != NULL && count < MAX_WORDS) {
        strcpy(tokens[count++], token);
        token = strtok(NULL, " ");
    }
    return count;
}


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


void calculate_tf(char tokens[][MAX_WORDS][MAX_WORD_LENGTH], int *counts, double tf[][MAX_WORDS], Vocabulary *vocab, int vocab_count, int num_documents) {
    for(int i=0; i<num_documents; i++) {
       
        for(int j=0; j<vocab_count; j++) {
            tf[i][j] = 0.0;
        }
        
        for(int j=0; j<counts[i]; j++) {
            for(int k=0; k<vocab_count; k++) {
                if(strcmp(tokens[i][j], vocab[k].word) == 0){
                    tf[i][k] += 1.0;
                    break;
                }
            }
        }
       
        for(int j=0; j<vocab_count; j++) {
            if(counts[i] > 0){
                tf[i][j] /= counts[i];
            }
        }
    }
}


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
       
        vocab[i].idf = log( ((double)(num_documents) + 1.0) / ((double)(doc_count) + 1.0) ) + 1.0;
    }
}


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

    // printf("Reaching here");
    FILE *file;
    char filename[] = "commands.txt";
    char line[MAX_TEXT_LENGTH];
    char documents[MAX_DOCUMENTS][MAX_TEXT_LENGTH];
    int num_documents = 0;
char input_text[MAX_TEXT_LENGTH];
    // printf("THis is ");


    char customText[]="transcription.txt";
    file = fopen(customText, "r");
    if(file == NULL){
        printf("Error opening file '%s'. Ensure the file exists in the current directory.\n", customText);
        return 1;
    }

   
    while(fgets(line, sizeof(line), file) != NULL && num_documents < MAX_DOCUMENTS){
       
        line[strcspn(line, "\n")] = 0;
       
        strcpy(input_text, line);
    }
    file = fopen(filename, "r");
    if(file == NULL){
        printf("Error opening file '%s'. Ensure the file exists in the current directory.\n", filename);
        return 1;
    }

    
    while(fgets(line, sizeof(line), file) != NULL && num_documents < MAX_DOCUMENTS){
   
    line[strcspn(line, "\n")] = 0;

 
    char *comma_pos = strchr(line, ',');

   
    if (comma_pos != NULL) {
        *comma_pos = 0; 
    }

    
    strcpy(documents[num_documents++], line);
}

    fclose(file);

    if(num_documents == 0){
        printf("No documents found in '%s'.\n", filename);
        return 1;
    }


    input_text[strcspn(input_text, "\n")] = 0;

    for(int i=0; i<num_documents; i++) {
        to_lowercase(documents[i]);
        remove_punctuation(documents[i]);
    }
    to_lowercase(input_text);
    remove_punctuation(input_text);

    // Tokenize texts
    char tokens[MAX_DOCUMENTS +1][MAX_WORDS][MAX_WORD_LENGTH]; 
    int counts[MAX_DOCUMENTS +1]; 

    for(int i=0; i<num_documents; i++) {
        counts[i] = tokenize(documents[i], tokens[i]);
    }

    counts[num_documents] = tokenize(input_text, tokens[num_documents]);

    int total_documents = num_documents + 1;


    Vocabulary vocab[MAX_WORDS];
    int vocab_count = build_vocabulary(tokens, counts, total_documents, vocab);
    if(vocab_count == 0){
        printf("No vocabulary built. Check the input texts.\n");
        return 1;
    }

   
    calculate_idf(vocab, vocab_count, tokens, counts, total_documents);

    double tf[MAX_DOCUMENTS +1][MAX_WORDS]; 
    calculate_tf(tokens, counts, tf, vocab, vocab_count, total_documents);

   
    double tfidf[MAX_DOCUMENTS +1][MAX_WORDS];
    for(int i=0; i<total_documents; i++) {
        for(int j=0; j<vocab_count; j++) {
            tfidf[i][j] = tf[i][j] * vocab[j].idf;
        }
    }

  
    double similarities[num_documents];
    for(int i=0; i<num_documents; i++) {
        similarities[i] = cosine_similarity_func(tfidf[i], tfidf[num_documents], vocab_count) * 100.0;
    }

    double max_similarity = similarities[0];
    int max_index = 0;
    for(int i=1; i<num_documents; i++) {
        if(similarities[i] > max_similarity){
            max_similarity = similarities[i];
            max_index = i;
        }
    }

    printf("%d", max_index +1);
   

    return 0;
}


