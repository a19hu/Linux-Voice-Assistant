#include <stdio.h>

struct Command {
    char *action;
    char *command;
};

int main() {
        FILE *file;
    char buffer[256]; // Buffer to hold each line of text
    
    // Open the file in read mode
    file = fopen("line.txt", "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read and print each line until the end of the file
    // printf("File content:\n");
    int number;
  fscanf(file, "%d", &number);
    // printf("%d", number);
    // Close the file
    fclose(file);
    struct Command commands[] = {
        {"Open [App Name]", "firefox"},
        {"Close [App Name]", "pkill <app_name>, but all app_name closed"},
        {"List files in [Directory]", "ls "},
        {"Create a new file named [File Name]", "touch <filename>"},
        {"Delete the file [File Name]", "rm -rf <filename>"},
        {"Move [File] to [Directory]", "mv <source> <destination>"},
        {"Copy [File] to [Directory]", "cp <source> <destination>"},
        {"Increase volume by [X]%", "pactl set-sink-volume @DEFAULT_SINK@ +10%"},
        {"Decrease volume by [X]%", "pactl set-sink-volume @DEFAULT_SINK@ -10%"},
        {"Mute/Unmute volume", "amixer set Master toggle"},
        {"Check battery status", "acpi"},
        {"Increase brightness by [X]%", "sudo brightnessctl set +10%"},
        {"Decrease brightness by [X]%", "sudo brightnessctl set -10%"},
        {"What’s the date/time?", "date"},
        {"Take a screenshot", "gnome-screenshot or scrot"},
        {"Search the web for [query]", "xdg-open \"https://www.google.com/search?q=<query>\""},
        {"Play media", "playerctl play"},
        {"Pause media", "playerctl pause"},
        {"Check CPU status", "top"},
        {"Check memory usage", "free -h, df -h"},
        {"Check network status", "ifconfig or ip a"},
        {"Execute [Custom Command]", "subprocess.run(<command>) in Python"},
        {"Authenticate", "sudo -v"}
    };
    printf("%s\n", commands[number-1].command);
    // int size = sizeof(commands) / sizeof(commands[0]);
    // for (int i = 0; i < size; i++) {
    //     printf("Action: %s\nCommand: %s\n\n", commands[i].action, commands[i].command);
    // }

    return 0;
}
