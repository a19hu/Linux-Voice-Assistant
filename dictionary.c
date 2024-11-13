#include <stdio.h>
#include <string.h>

// Define a struct to hold the mapping between natural language and Linux commands
typedef struct {
    char *natural_language_command;
    char *linux_command;
} CommandMapping;

// Function to search for a Linux command based on a natural language command
const char* get_linux_command(const char *nl_command, CommandMapping *mappings, size_t num_mappings) {
    for (size_t i = 0; i < num_mappings; ++i) {
        if (strcmp(nl_command, mappings[i].natural_language_command) == 0) {
            return mappings[i].linux_command;
        }
    }
    return "Command not found";
}

int main() {
    // Define the mappings between natural language commands and Linux commands
    CommandMapping mappings[] = {
        {"Open [App Name]", "firefox"},
        {"Close [App Name]", "pkill <app_name> "},
        {"List files in [Directory]", "ls -lh <directory>"},
        {"Create a new file named [File Name]", "touch <filename>"},
        {"Delete the file [File Name]", "rm -rf <filename>"},
        {"Move [File] to [Directory]", "mv <source> <destination>"},
        {"Copy [File] to [Directory]", "cp <source> <destination>"},
        {"Increase volume by [X]%", "pactl set-sink-volume @DEFAULT_SINK@ +<percentage>%"},
        {"Decrease volume by [X]%", "pactl set-sink-volume @DEFAULT_SINK@ -<percentage>%"},
        {"Mute/Unmute volume", "amixer set Master toggle"},
        {"Check battery status", "acpi"},
        {"Increase brightness by [X]%", "Sudo brightnessctl set 50%"},
        {"Decrease brightness by [X]%", "Sudo brightnessctl set 50%"},
        {"What’s the date/time?", "date"},
        {"Take a screenshot", "gnome-screenshot or scrot"},
        {"Search  web for [query]", "xdg-open \"https://www.google.com/search?q=<query>\""},
        {"Play media", "playerctl play"},
        {"Pause media", "playerctl pause"},
        {"Check CPU status", "Top htop"},
        {"Check memory usage", "free -h, df -h ."},
        {"Check network status", "ifconfig or ip a"},
        {"Execute [Custom Command]", "subprocess.run(<command>) in Python"},
        {"Authenticate", "sudo -v"}
    };

    size_t num_mappings = sizeof(mappings) / sizeof(mappings[0]);

    // Example: search for a command
    const char *nl_command = "Increase volume by [X]%";
    const char *linux_command = get_linux_command(nl_command, mappings, num_mappings);

    // Output the corresponding Linux command
    printf("Linux command for '%s' is: %s\n", nl_command, linux_command);

    return 0;
}
