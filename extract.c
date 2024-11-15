#include <stdio.h>
#include <string.h>

// Function to handle the commands and extract details
void processCommand(const char *line) {
    char command[50], arg1[100], arg2[100];
    
    // Initialize arg2 to handle commands without the second argument
    arg2[0] = '\0';

    // Parse the command and arguments
    if (strstr(line, "create a new file named")) {
        sscanf(line, "create a new file named %[^\n]", arg1);
        printf("%s\n", arg1);
    } else if (strstr(line, "delete the file")) {
        sscanf(line, "delete the file %[^\n]", arg1);
        printf("%s\n", arg1);
    }
    else if (strstr(line, "delete file")) {
        sscanf(line, "delete file %[^\n]", arg1);
        printf("%s\n", arg1);
    }  else if (strstr(line, "move")) {
        sscanf(line, "move %s to %s", arg1, arg2);
        printf("%s\n%s\n", arg1, arg2);
    } else if (strstr(line, "copy")) {
        sscanf(line, "copy %s to %s", arg1, arg2);
        printf("%s\n%s\n", arg1, arg2);
    } else if (strstr(line, "open")) {
        sscanf(line, "open %[^\n]", arg1);
        printf("%s\n", arg1);
    } else if (strstr(line, "close")) {
        sscanf(line, "close %[^\n]", arg1);
        printf("%s\n", arg1);
    } else {
        printf("Invalid command!\n");
    }
}

int main() {
    char line[200];
    
         FILE *file;
    char buffer[256]; // Buffer to hold each line of text
    
    // Open the file in read mode
    file = fopen("transcription.sh", "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    int num_documents = 0;
     while(fgets(line, sizeof(line), file) != NULL ){
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        
        strcpy(buffer, line);
    }

    // Read and print each line until the end of the file
    // printf("File content:\n");
    
    
    // printf("%d", number);
    // Close the file
    fclose(file);

        // fgets(line, sizeof(line), stdin); // Read the input line
        // line[strcspn(line, "\n")] = '\0'; // Remove the newline character
        
    // printf("%s",buffer);
        
        // Process the command
        processCommand(buffer);
    
    
    return 0;
}