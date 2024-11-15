#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to load CSS and define 'green' and 'red' classes
static void load_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    const gchar *css_data =
        ".green {"
        "   background-color: green;"
        "   color: white;"
        "}"
        ".red {"
        "   background-color: red;"
        "   color: white;"
        "}";
    
    gtk_css_provider_load_from_data(provider, css_data, -1, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
    g_object_unref(provider);
}

// Function to set the button color to green
void set_button_color_green(GtkWidget *button) {
    GtkStyleContext *context = gtk_widget_get_style_context(button);
    gtk_style_context_remove_class(context, "red"); // Remove red if previously added
    gtk_style_context_add_class(context, "green");  // Add green class
}

// Function to set the button color to red
void set_button_color_red(GtkWidget *button) {
    GtkStyleContext *context = gtk_widget_get_style_context(button);
    gtk_style_context_remove_class(context, "green"); // Remove green if previously added
    gtk_style_context_add_class(context, "red");      // Add red class
}

// Callback function for the "Start VA" button
static void on_start_va_clicked(GtkWidget *widget, gpointer data) {
    // Set button color to red in the main thread
    set_button_color_red(widget);

    pid_t pid = fork();
    
    if (pid == 0) {  // Child process
        // Path to your shell script
        const char *script_path = "/home/akarsh/Desktop/OS_Project/run.sh";
        
        // Execute the shell script in a new terminal, keeping the terminal open
        execlp("gnome-terminal", 
               "gnome-terminal", 
               "--", 
               "bash", 
               "-c", 
               "/home/akarsh/Desktop/OS_Project/run.sh", 
               NULL);
        
        // If execlp fails
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {  // Parent process
        int status;
        
        // Wait for the child process to finish
        waitpid(pid, &status, 0);
        
        // Reset the button color to green after the script execution is complete
        set_button_color_green(widget);
    } else {
        // Fork failed
        g_print("Fork failed!\n");
        set_button_color_green(widget); // Reset color in case of failure
    }
}

// Callback function for the "User Guide" button
static void on_user_guide_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *guide_window;
    GtkWidget *label;

    // Change the button color to red when clicked
    set_button_color_red(widget);

    // Create a new window for the User Guide
    guide_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(guide_window), "User Guide");
    gtk_window_set_default_size(GTK_WINDOW(guide_window), 400, 200);
    gtk_window_set_transient_for(GTK_WINDOW(guide_window), GTK_WINDOW(data)); // Set parent window

    // Create a label with some placeholder text
    label = gtk_label_new("User Guide content will be here in the future.");
    gtk_container_add(GTK_CONTAINER(guide_window), label);

    // Show the new window
    gtk_widget_show_all(guide_window);

    // Connect the "destroy" signal to reset button color when window is closed
    g_signal_connect(guide_window, "destroy", G_CALLBACK(set_button_color_green), widget);
}

// Callback function for the "Add Custom Command" button
static void on_add_command_clicked(GtkWidget *widget, gpointer data) {
    // Placeholder for future functionality
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "Add Custom Command functionality is not implemented yet.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Callback function to handle key press event for the shortcut
static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    // Check if Shift + S is pressed
    if ((event->state & GDK_SHIFT_MASK) && (event->keyval == GDK_KEY_S || event->keyval == GDK_KEY_s)) {
        // Trigger the "Start VA" button click when Shift + S is pressed
        on_start_va_clicked(GTK_WIDGET(data), NULL);
        return TRUE; // Stop further processing of the event
    }
    return FALSE; // Continue with normal event handling
}

// Main function to create the GUI
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *button_start_va;
    GtkWidget *button_add_command;
    GtkWidget *button_user_guide;

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Load CSS for button colors
    load_css();

    // Create a new window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "VA for Linux");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box to hold the label and buttons
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a label with text overlay "VA for Linux"
    label = gtk_label_new("<span font='16' weight='bold'>VA for Linux</span>");
    gtk_label_set_use_markup(GTK_LABEL(label), TRUE); // Enable markup for styling
    gtk_label_set_xalign(GTK_LABEL(label), 0.5); // Center align the text
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 10);

    // Create "Start VA" button
    button_start_va = gtk_button_new_with_label("Start VA");
    g_signal_connect(button_start_va, "clicked", G_CALLBACK(on_start_va_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button_start_va, FALSE, FALSE, 10);

    // Create "Add Custom Command" button
    button_add_command = gtk_button_new_with_label("Add Custom Command");
    g_signal_connect(button_add_command, "clicked", G_CALLBACK(on_add_command_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button_add_command, FALSE, FALSE, 10);

    // Create "User Guide" button
    button_user_guide = gtk_button_new_with_label("User Guide");
    g_signal_connect(button_user_guide, "clicked", G_CALLBACK(on_user_guide_clicked), window);
    gtk_box_pack_start(GTK_BOX(vbox), button_user_guide, FALSE, FALSE, 10);

    // Set the initial button colors to green
    set_button_color_green(button_start_va);
    set_button_color_green(button_add_command);
    set_button_color_green(button_user_guide);

    // Connect the key press event to the window to listen for Shift + S
    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), button_start_va);

    // Show all widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();

    return 0;
}
