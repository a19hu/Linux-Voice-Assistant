#include <stdio.h>
#include <string.h>

#define MAX_COMMANDS 100
#define MAX_LINE_LENGTH 512

struct Command {
    char action[256];
    char command[256];
};

// Function to replace placeholders in a string
void replace_placeholder(const char *template, char *output, const char *placeholder, const char *value) {
    const char *pos;
    char buffer[512];
    buffer[0] = '\0'; // Initialize buffer

    while ((pos = strstr(template, placeholder)) != NULL) {
        // Copy text before the placeholder
        strncat(buffer, template, pos - template);
        // Add the replacement value
        strcat(buffer, value);
        // Move past the placeholder
        template = pos + strlen(placeholder);
    }

    strcat(buffer, template);
    strcpy(output, buffer); 
}

int main() {
    FILE *file;
    char buffer[256]; 
    struct Command commands[MAX_COMMANDS];
    int num_commands = 0;

   
    file = fopen("commands.txt", "r");

    
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

  
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
       
        buffer[strcspn(buffer, "\n")] = 0;

        
        char *comma_pos = strchr(buffer, ',');
        if (comma_pos != NULL) {
            *comma_pos = '\0'; 
            strcpy(commands[num_commands].action, buffer);
            strcpy(commands[num_commands].command, comma_pos + 1);
            num_commands++;
        }
    }

    fclose(file);

   
    FILE *file2;
    int number;
    file2 = fopen("line.txt", "r");
    if (file2 == NULL) {
        perror("Error opening file");
        return 1;
    }
    fscanf(file2, "%d", &number);
    fclose(file2);

    
    if (number < 1 || number > num_commands) {
        printf("Invalid command number: %d\n", number);
        return 1;
    }

    
    char final_command[512];
    char documents[100][256];
    
    
    FILE *file3;
    file3 = fopen("extractedWords.log", "r");
    int num_documents = 0;
    while (fgets(documents[num_documents], sizeof(documents[num_documents]), file3) != NULL) {
        documents[num_documents][strcspn(documents[num_documents], "\n")] = 0; // Remove newline character
        num_documents++;
    }
    fclose(file3);

    
    replace_placeholder(commands[number - 1].command, final_command, "<source>", documents[0]);
    replace_placeholder(final_command, final_command, "<destination>", documents[1]);

    
    printf("%s", final_command);

    return 0;
}