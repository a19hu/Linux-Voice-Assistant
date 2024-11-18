#include <stdio.h>
#include <string.h>


void processCommand(const char *line) {
    char command[50], arg1[100], arg2[100];
    
    
    arg2[0] = '\0';


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
    }
    else if(strstr(line,"search the web for")){
        sscanf(line,"search the web for %[^\n]",arg1);
        printf("%s\n",arg1);
    } else {
        printf("Invalid command!\n");
    }
}

int main() {
    char line[200];
    
         FILE *file;
    char buffer[256]; 
   
    file = fopen("transcription.txt", "r");

    
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

    // printf("%d", number);
    // Close the file
    fclose(file);

 
        processCommand(buffer);
    
    
    return 0;
}