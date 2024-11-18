#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Callback function to handle form submission
static void on_submit_command(GtkWidget *widget, gpointer data)
{
    GtkWidget **entries = (GtkWidget **)data;
    if (entries == NULL)
    {
        g_print("Error: entries array is NULL.\n");
        return;
    }

    // Retrieve text from entry widgets
    const char *nl_command = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const char *lx_command = gtk_entry_get_text(GTK_ENTRY(entries[1]));

    if (nl_command == NULL || lx_command == NULL)
    {
        g_print("Error: Command inputs are NULL.\n");
        return;
    }

    g_print("Natural Language Command: %s\n", nl_command);
    g_print("Linux Command: %s\n", lx_command);

    // Write to file, each pair on a new line
    FILE *file = fopen("commands.txt", "a");
    if (file == NULL)
    {
        g_print("Error: Could not open commands.txt for writing.\n");
        return;
    }

    // Write the commands with a newline after each pair
    fprintf(file, "%s,%s\n", nl_command, lx_command);
    fclose(file);

    g_print("Commands written to commands.txt\n");

    // Close the form window after submission
    GtkWidget *form_window = gtk_widget_get_toplevel(widget);
    if (form_window != NULL)
    {
        gtk_widget_destroy(form_window);
    }

    // Clear entries (optional)
    gtk_entry_set_text(GTK_ENTRY(entries[0]), "");
    gtk_entry_set_text(GTK_ENTRY(entries[1]), "");

    // Keep the main window and application running
    // No need to exit or destroy the main window
}

// Function to load CSS styles
static void load_css()
{
    GtkCssProvider *provider = gtk_css_provider_new();
    const gchar *css_data =
        ".gen_button {"
        "   background-color: green;"
        "   color: grey;"
        "   border-radius: 10px;"
        "   padding: 2px;"
        "   min-width: 130px;"
        "   min-height: 40px;"
        "}"
        ".install_lib_button {"
        "   background-color: blue;"
        "   color: grey;"
        "   border-radius: 8px;"
        "   padding: 3px;"
        "   min-width: 80px;"
        "   min-height: 30px;"
        "}";

    gtk_css_provider_load_from_data(provider, css_data, -1, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}

static pid_t va_pid = -1;  // Store the process ID of the terminal

static void on_start_va_clicked(GtkWidget *widget, gpointer data)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process: launch the voice assistant and auto-close after 10 seconds
        execlp("gnome-terminal", "gnome-terminal", "--", "bash", "-c", "./run.sh; sleep 10; exit;", NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        // Parent process: wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);
    }
    else
    {
        g_print("Fork failed!\n");
    }
}

// Callback function to handle the library installation
static void on_install_libraries_clicked(GtkWidget *widget, gpointer data)
{
    // Run the installation command in the terminal using `gnome-terminal`
    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process: launch the terminal and run the install command
        execlp("gnome-terminal", "gnome-terminal", "--", "bash", "-c", 
               "sudo apt update && sudo apt install -y alsa-utils pactl xdg-utils playerctl brightnessctl; exit;", NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        // Parent process: Successfully launched terminal with installation command
        g_print("Library installation started in terminal with PID: %d\n", pid);
    }
    else
    {
        g_print("Fork failed!\n");
    }
}

static void on_user_guide_clicked(GtkWidget *widget, gpointer data)
{
    // Create a new window for the user guide
    GtkWidget *guide_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(guide_window), "User Guide");
    gtk_window_set_default_size(GTK_WINDOW(guide_window), 800, 700);
    gtk_window_set_transient_for(GTK_WINDOW(guide_window), GTK_WINDOW(data));
    
    // Set padding around the window
    gtk_container_set_border_width(GTK_CONTAINER(guide_window), 10);

    // Create a vertical box (vbox) to hold the label and button
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(guide_window), vbox);

    // Create the label with the user guide text
    GtkWidget *label = gtk_label_new(
    "\t\t\t  User Guide for KABUTAR-Voice Assistant for Linux\n\n"
    "Default voice lines for common commands:\n\n"
    "VOICE LINE                                    LINUX COMMAND\n"
    "--------------------------------------         ------------------------------\n"
    "open [app name],                              <source>\n"
    "close [app name],                             pkill <source>\n"
    "list files in [directory],                    ls\n"
    "create a new file named [file name],          touch <source>\n"
    "delete the file [file name],                  rm -rf <source>\n"
    "move [file] to [directory],                   mv <source> <destination>\n"
    "copy [file] to [directory],                   cp <source> <destination>\n"
    "current folder,                               pwd\n"
    "increase volume,                              pactl set-sink-volume @default_sink@ +10%\n"
    "decrease volume,                              pactl set-sink-volume @default_sink@ -10%\n"
    "mute,                                         pactl set-sink-mute @DEFAULT_SINK@ 1\n"
    "unmute,                                       pactl set-sink-mute @DEFAULT_SINK@ 0\n"
    "check battery status,                         acpi\n"
    "increase brightness,                          sudo brightnessctl set +10%\n"
    "decrease brightness,                          sudo brightnessctl set -10%\n"
    "what’s the date/time?,                        date\n"
    "take a screenshot,                            gnome-screenshot\n"
    "search the web for [query],                   xdg-open \"https://www.google.com/search?q=<source>\"\n"
    "play media,                                   playerctl play\n"
    "pause media,                                  playerctl pause\n"
    "check cpu status,                             top\n"
    "check memory usage,                           free -h\n"
    "check network status,                         ifconfig\n"
    "execute [custom command],                     subprocess.run(<command>) in python\n"
    "authenticate,                                 sudo -v\n"
    "shut down,                                    shutdown now\n"
    "restart,                                      reboot\n"
    "\n\n"
    "More Custom Commands can be added using the [Add Custom Command] button!\n\n"
    "Note:Ensure that the following libraries are installed on your system for proper functioning of all\n"
    "commands: alsa-utils, pactl, xdg-utils, playerctl, brightnessctl\n"
    "If not installed, you can install them in one click using the button below:\n\n"
    );

    // Set monospaced font using the newer Pango API
    PangoFontDescription *font_desc = pango_font_description_from_string("Monospace 10");
    gtk_widget_override_font(label, font_desc);

    // Add the label to the vbox
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 5);

    // Create the "Install Libraries" button
    GtkWidget *install_button = gtk_button_new_with_label("Install Required Libraries");
    
    gtk_style_context_add_class(gtk_widget_get_style_context(install_button), "install_lib_button");
    
    // Fix alignment and packing
    gtk_widget_set_halign(install_button, GTK_ALIGN_CENTER);
    
    // Adjust space between the label and button
    gtk_box_pack_start(GTK_BOX(vbox), install_button, FALSE, FALSE, 5);

    // Connect button to its callback function
    g_signal_connect(install_button, "clicked", G_CALLBACK(on_install_libraries_clicked), NULL);

    // Create second label with footer information
    GtkWidget *label2 = gtk_label_new("*OS Project by: Ashutosh, Sahani, KP, Aakarsh!\n");

    // Add the second label to the vbox with reduced expansion
    gtk_box_pack_start(GTK_BOX(vbox), label2, FALSE, FALSE, 5);

    // Show all the widgets in the window
    gtk_widget_show_all(guide_window);
}

// Callback for the "Add Custom Command" button
static void on_add_command_clicked(GtkWidget *widget, gpointer data)
{
    GtkWidget *form_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(form_window), "Add Custom Command");
    gtk_window_set_default_size(GTK_WINDOW(form_window), 400, 200);
    gtk_window_set_transient_for(GTK_WINDOW(form_window), GTK_WINDOW(data));

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    gtk_container_add(GTK_CONTAINER(form_window), vbox);

    GtkWidget *label_nl_command = gtk_label_new("Enter Natural Language Command:");
    gtk_box_pack_start(GTK_BOX(vbox), label_nl_command, FALSE, FALSE, 5);

    GtkWidget *entry_nl_command = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry_nl_command, FALSE, FALSE, 5);

    GtkWidget *label_lx_command = gtk_label_new("Enter Linux Command:");
    gtk_box_pack_start(GTK_BOX(vbox), label_lx_command, FALSE, FALSE, 5);

    GtkWidget *entry_lx_command = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry_lx_command, FALSE, FALSE, 5);

    // Dynamically allocate entries array
    GtkWidget **entries = g_malloc(2 * sizeof(GtkWidget *));
    entries[0] = entry_nl_command;
    entries[1] = entry_lx_command;

    GtkWidget *submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_command), entries);
    gtk_box_pack_start(GTK_BOX(vbox), submit_button, FALSE, FALSE, 10);

    g_signal_connect(form_window, "destroy", G_CALLBACK(g_free), entries); // Free memory when window is destroyed

    gtk_widget_show_all(form_window);
}

// Main function
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    load_css();

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Kabutar");
    gtk_window_set_default_size(GTK_WINDOW(window), 150, 150);
    gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *label = gtk_label_new("<span font='16' weight='bold'>Kabutar - VA for Linux</span>");
    gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 3);

    GtkWidget *button_start_va = gtk_button_new_with_label("Start VA");
    g_signal_connect(button_start_va, "clicked", G_CALLBACK(on_start_va_clicked), NULL);
    gtk_style_context_add_class(gtk_widget_get_style_context(button_start_va), "gen_button");
    gtk_box_pack_start(GTK_BOX(vbox), button_start_va, FALSE, FALSE, 3);

    GtkWidget *button_add_command = gtk_button_new_with_label("Add Custom Command");
    g_signal_connect(button_add_command, "clicked", G_CALLBACK(on_add_command_clicked), NULL);
    gtk_style_context_add_class(gtk_widget_get_style_context(button_add_command), "gen_button");
    gtk_box_pack_start(GTK_BOX(vbox), button_add_command, FALSE, FALSE, 3);

    GtkWidget *button_user_guide = gtk_button_new_with_label("User Guide");
    g_signal_connect(button_user_guide, "clicked", G_CALLBACK(on_user_guide_clicked), window);
    gtk_style_context_add_class(gtk_widget_get_style_context(button_user_guide), "gen_button");
    gtk_box_pack_start(GTK_BOX(vbox), button_user_guide, FALSE, FALSE, 3);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
