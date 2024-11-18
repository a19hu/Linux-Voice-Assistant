// // #include <stdio.h>
// // #include <string.h>
// // struct Command {
// //     char *action;
// //     char *command;
// // };

// // int main() {
// //         FILE *file;
// //     char buffer[256]; // Buffer to hold each line of text
    
// //     // Open the file in read mode
// //     file = fopen("line.txt", "r");

// //     // Check if the file was opened successfully
// //     if (file == NULL) {
// //         perror("Error opening file");
// //         return 1;
// //     }
// //       FILE *file2;
// //     char buffer2[256]; // Buffer to hold each line of text
    
// //     // Open the file in read mode
// //     file2 = fopen("extractedWords.log", "r");

// //     // Check if the file was opened successfully
// //     if (file2 == NULL) {
// //         perror("Error opening file");
// //         return 1;
// //     }
// //     char documents[100][256];
// //     int num_documents = 0;
// //     while(fgets(buffer2, sizeof(buffer2), file2) != NULL ){
// //         // Remove newline character
// //         buffer2[strcspn(buffer2, "\n")] = 0;
// //          strcpy(documents[num_documents++], buffer2);
// //         printf("%s\n", buffer2);
// //     }
// //     // Read and print each line until the end of the file
// //     // printf("File content:\n");
// //     // printf("%s",documents[0]);
// //     // printf("%s",documents[1]);
// //     int number;
// //   fscanf(file, "%d", &number);
// //     // printf("%d", number);
// //     // Close the file
// //     fclose(file);
// //     struct Command commands[] = {
// //         {"Open [App Name]", "<source>"},
// //         {"Close [App Name]", "pkill <source>"},
// //         {"List files in [Directory]", "ls "},
// //         {"Create a new file named [File Name]", "touch <source>"},
// //         {"Delete the file [File Name]", "rm -rf <source>"},
// //         {"Move [File] to [Directory]", "mv <source> <destination> "},
// //         {"Copy [File] to [Directory]", "cp <source> <destination>"},
// //         {"Increase volume by [X]%", "pactl set-sink-volume @DEFAULT_SINK@ +10%"},
// //         {"Decrease volume by [X]%", "pactl set-sink-volume @DEFAULT_SINK@ -10%"},
// //         {"Mute/Unmute volume", "amixer set Master toggle"},
// //         {"Check battery status", "acpi"},
// //         {"Increase brightness by [X]%", "sudo brightnessctl set +10%"},
// //         {"Decrease brightness by [X]%", "sudo brightnessctl set -10%"},
// //         {"What’s the date/time?", "date"},
// //         {"Take a screenshot", "gnome-screenshot"},
// //         {"Search the web for [query]", "xdg-open \"https://www.google.com/search?q=<query>\""},
// //         {"Play media", "playerctl play"},
// //         {"Pause media", "playerctl pause"},
// //         {"Check CPU status", "top"},
// //         {"Check memory usage", "free -h"},
// //         {"Check network status", "ifconfig"},
// //         {"Execute [Custom Command]", "subprocess.run(<command>) in Python"},
// //         {"Authenticate", "sudo -v"}
// //     };
// //     printf("%s\n", commands[number-1].command);
// //     // int size = sizeof(commands) / sizeof(commands[0]);
// //     // for (int i = 0; i < size; i++) {
// //     //     printf("Action: %s\nCommand: %s\n\n", commands[i].action, commands[i].command);
// //     // }

// //     return 0;
// // }
// // #include <stdio.h>
// // #include <string.h>

// // struct Command {
// //     char *action;
// //     char *command;
// // };

// // // Function to replace placeholders in a string
// // void replace_placeholder(const char *template, char *output, const char *placeholder, const char *value) {
// //     const char *pos;
// //     char buffer[512];
// //     output[0] = '\0'; // Initialize output string

// //     while ((pos = strstr(template, placeholder)) != NULL) {
// //         // Copy text before the placeholder
// //         strncat(output, template, pos - template);
// //         // Add the replacement value
// //         strcat(output, value);
// //         // Move past the placeholder
// //         template = pos + strlen(placeholder);
// //     }
// //     // Copy remaining text
// //     strcat(output, template);
// // }

// // int main() {
// //     FILE *file;
// //     char buffer[256]; // Buffer to hold each line of text

// //     // Open the file in read mode
// //     file = fopen("line.txt", "r");

// //     // Check if the file was opened successfully
// //     if (file == NULL) {
// //         perror("Error opening file");
// //         return 1;
// //     }

// //     FILE *file2;
// //     char buffer2[256]; // Buffer to hold each line of text

// //     // Open the file in read mode
// //     file2 = fopen("extractedWords.log", "r");

// //     // Check if the file was opened successfully
// //     if (file2 == NULL) {
// //         perror("Error opening file");
// //         return 1;
// //     }

// //     char documents[100][256];
// //     int num_documents = 0;
// //     while (fgets(buffer2, sizeof(buffer2), file2) != NULL) {
// //         // Remove newline character
// //         buffer2[strcspn(buffer2, "\n")] = 0;
// //         strcpy(documents[num_documents++], buffer2);
// //     }

// //     fclose(file2); // Close file after reading

// //     int number;
// //     fscanf(file, "%d", &number);
// //     fclose(file); // Close file after reading

// //     struct Command commands[] = {
// //         {"Open [App Name]", "<source>"},
// //         {"Close [App Name]", "pkill <source>"},
// //         {"List files in [Directory]", "ls "},
// //         {"Create a new file named [File Name]", "touch <source>"},
// //         {"Delete the file [File Name]", "rm -rf <source>"},
// //         {"Move [File] to [Directory]", "mv <source> <destination>"},
// //         {"Copy [File] to [Directory]", "cp <source> <destination>"},
// //         {"Increase volume by [X]%", "pactl set-sink-volume @DEFAULT_SINK@ +10%"},
// //         {"Decrease volume by [X]%", "pactl set-sink-volume @DEFAULT_SINK@ -10%"},
// //         {"Mute/Unmute volume", "amixer set Master toggle"},
// //         {"Check battery status", "acpi"},
// //         {"Increase brightness by [X]%", "sudo brightnessctl set +10%"},
// //         {"Decrease brightness by [X]%", "sudo brightnessctl set -10%"},
// //         {"What’s the date/time?", "date"},
// //         {"Take a screenshot", "gnome-screenshot"},
// //         {"Search the web for [query]", "xdg-open \"https://www.google.com/search?q=<query>\""},
// //         {"Play media", "playerctl play"},
// //         {"Pause media", "playerctl pause"},
// //         {"Check CPU status", "top"},
// //         {"Check memory usage", "free -h"},
// //         {"Check network status", "ifconfig"},
// //         {"Execute [Custom Command]", "subprocess.run(<command>) in Python"},
// //         {"Authenticate", "sudo -v"}
// //     };

// //     // Prepare the final command
// //     char final_command[512];
// //     replace_placeholder(commands[number - 1].command, final_command, "<source>", documents[0]);
// //     replace_placeholder(final_command, final_command, "<destination>", documents[1]);

// //     // Print the final command
// //     printf("Final Command: %s\n", final_command);
// //     printf("%s\n", commands[number-1].command);

// //     return 0;
// // }
// #include <stdio.h>
// #include <string.h>

// struct Command {
//     char *action;
//     char *command;
// };

// // Function to replace placeholders in a string
// void replace_placeholder(const char *template, char *output, const char *placeholder, const char *value) {
//     const char *pos;
//     char buffer[512];
//     buffer[0] = '\0'; // Initialize buffer

//     while ((pos = strstr(template, placeholder)) != NULL) {
//         // Copy text before the placeholder
//         strncat(buffer, template, pos - template);
//         // Add the replacement value
//         strcat(buffer, value);
//         // Move past the placeholder
//         template = pos + strlen(placeholder);
//     }
//     // Copy remaining text
//     strcat(buffer, template);
//     strcpy(output, buffer); // Copy final result to output
// }

// int main() {
//     FILE *file;
//     char buffer[256]; // Buffer to hold each line of text

//     // Open the file in read mode
//     file = fopen("line.txt", "r");

//     // Check if the file was opened successfully
//     if (file == NULL) {
//         perror("Error opening file");
//         return 1;
//     }

//     FILE *file2;
//     char buffer2[256]; // Buffer to hold each line of text

//     // Open the file in read mode
//     file2 = fopen("extractedWords.log", "r");

//     // Check if the file was opened successfully
//     if (file2 == NULL) {
//         perror("Error opening file");
//         return 1;
//     }

//     char documents[100][256];
//     int num_documents = 0;
//     while (fgets(buffer2, sizeof(buffer2), file2) != NULL) {
//         // Remove newline character
//         buffer2[strcspn(buffer2, "\n")] = 0;
//         strcpy(documents[num_documents++], buffer2);
//     }

//     fclose(file2); // Close file after reading

//     int number;
//     fscanf(file, "%d", &number);
//     fclose(file); // Close file after reading

//     struct Command commands[] = {
//         {"Open [App Name]", "<source>"},
//         {"Close [App Name]", "pkill <source>"},
//         {"List files in [Directory]", "ls "},
//         {"Create a new file named [File Name]", "touch <source>"},
//         {"Delete the file [File Name]", "rm -rf <source>"},
//         {"Move [File] to [Directory]", "mv <source> <destination>"},
//         {"Copy [File] to [Directory]", "cp <source> <destination>"},
//         {"Increase volume by [X]%", "pactl set-sink-volume @DEFAULT_SINK@ +10%"},
//         {"Decrease volume by [X]%", "pactl set-sink-volume @DEFAULT_SINK@ -10%"},
//         {"Mute/Unmute volume", "amixer set Master toggle"},
//         {"Check battery status", "acpi"},
//         {"Increase brightness by [X]%", "sudo brightnessctl set +10%"},
//         {"Decrease brightness by [X]%", "sudo brightnessctl set -10%"},
//         {"What’s the date/time?", "date"},
//         {"Take a screenshot", "gnome-screenshot"},
//         {"Search the web for [query]", "xdg-open \"https://www.google.com/search?q=<source>\""},
//         {"Play media", "playerctl play"},
//         {"Pause media", "playerctl pause"},
//         {"Check CPU status", "top"},
//         {"Check memory usage", "free -h"},
//         {"Check network status", "ifconfig"},
//         {"Execute [Custom Command]", "subprocess.run(<command>) in Python"},
//         {"Authenticate", "sudo -v"}
//     };

//     // Ensure the command index is valid
//     int num_commands = sizeof(commands) / sizeof(commands[0]);
//     if (number < 1 || number > num_commands) {
//         printf("Invalid command number: %d\n", number);
//         return 1;
//     }

//     // Prepare the final command
//     char final_command[512];
//     replace_placeholder(commands[number - 1].command, final_command, "<source>", documents[0]);
//     replace_placeholder(final_command, final_command, "<destination>", documents[1]);

//     // Print the final command
//     printf("%s", final_command);

//     return 0;
// }

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
    // Copy remaining text
    strcat(buffer, template);
    strcpy(output, buffer); // Copy final result to output
}

int main() {
    FILE *file;
    char buffer[256]; // Buffer to hold each line of text
    struct Command commands[MAX_COMMANDS];
    int num_commands = 0;

    // Open the file containing commands in read mode
    file = fopen("commands.txt", "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read commands from the file and store them in the array
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;

        // Parse the action and command from the line
        char *comma_pos = strchr(buffer, ',');
        if (comma_pos != NULL) {
            *comma_pos = '\0'; // Null-terminate the action
            strcpy(commands[num_commands].action, buffer);
            strcpy(commands[num_commands].command, comma_pos + 1);
            num_commands++;
        }
    }

    fclose(file); // Close file after reading

    // Print the loaded commands (optional)
    // printf("Loaded commands:\n");
    // for (int i = 0; i < num_commands; i++) {
    //     printf("Action: %s\nCommand: %s\n", commands[i].action, commands[i].command);
    // }

    // Example: Read the command number from a file
    FILE *file2;
    int number;
    file2 = fopen("line.txt", "r");
    if (file2 == NULL) {
        perror("Error opening file");
        return 1;
    }
    fscanf(file2, "%d", &number);
    fclose(file2);

    // Validate the command number
    if (number < 1 || number > num_commands) {
        printf("Invalid command number: %d\n", number);
        return 1;
    }

    // Prepare the final command by replacing placeholders
    char final_command[512];
    char documents[100][256];
    
    // Read placeholders from another file (e.g., extractedWords.log)
    FILE *file3;
    file3 = fopen("extractedWords.log", "r");
    int num_documents = 0;
    while (fgets(documents[num_documents], sizeof(documents[num_documents]), file3) != NULL) {
        documents[num_documents][strcspn(documents[num_documents], "\n")] = 0; // Remove newline character
        num_documents++;
    }
    fclose(file3);

    // Replace placeholders with values from documents
    replace_placeholder(commands[number - 1].command, final_command, "<source>", documents[0]);
    replace_placeholder(final_command, final_command, "<destination>", documents[1]);

    // Print the final command
    printf("%s", final_command);

    return 0;
}