/*
 * Yorl Compiler Installer for Linux
 * GUI installer using GTK4
 */

#include <gtk/gtk.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <thread>

const std::string YOLEX_URL = "https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/yolex-linux-x64";
const std::string VERSION = "1.0.0";

GtkWidget *window;
GtkWidget *progress_bar;
GtkWidget *status_label;
GtkWidget *install_button;
GtkWidget *close_button;

std::string getHomeDir() {
    const char* home = getenv("HOME");
    if (!home) {
        struct passwd* pw = getpwuid(getuid());
        home = pw->pw_dir;
    }
    return std::string(home);
}

bool createDirectory(const std::string& path) {
    return mkdir(path.c_str(), 0755) == 0 || errno == EEXIST;
}

int downloadFile(const std::string& url, const std::string& output) {
    std::string cmd = "curl -L -o \"" + output + "\" \"" + url + "\" 2>/dev/null";
    return system(cmd.c_str());
}

bool makeExecutable(const std::string& path) {
    return chmod(path.c_str(), 0755) == 0;
}

void update_status(const char* message, double progress) {
    gtk_label_set_text(GTK_LABEL(status_label), message);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), progress);
    while (g_main_context_pending(NULL)) g_main_context_iteration(NULL, FALSE);
}

void show_error_dialog(const char* message) {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               "%s", message);
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), NULL);
    gtk_widget_show(dialog);
}

void show_success_dialog(const char* message) {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "%s", message);
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), NULL);
    gtk_widget_show(dialog);
}

void install_yolex() {
    gtk_widget_set_sensitive(install_button, FALSE);
    
    std::string homeDir = getHomeDir();
    std::string localBin = homeDir + "/.local/bin";
    std::string yolexPath = localBin + "/yolex";
    
    // Check curl
    update_status("Checking dependencies...", 0.1);
    if (system("which curl > /dev/null 2>&1") != 0) {
        show_error_dialog("curl is not installed. Please install curl first.");
        gtk_widget_set_sensitive(install_button, TRUE);
        return;
    }
    
    // Create directory
    update_status("Creating installation directory...", 0.2);
    createDirectory(homeDir + "/.local");
    createDirectory(localBin);
    
    // Download
    update_status("Downloading yolex from GitHub...", 0.4);
    if (downloadFile(YOLEX_URL, yolexPath) != 0) {
        show_error_dialog("Failed to download yolex. Check your internet connection.");
        gtk_widget_set_sensitive(install_button, TRUE);
        return;
    }
    
    // Make executable
    update_status("Setting permissions...", 0.8);
    makeExecutable(yolexPath);
    
    // Complete
    update_status("Installation complete!", 1.0);
    
    std::string msg = "Yorl compiler installed successfully!\n\nLocation: " + yolexPath + "\n\nRun 'yolex --version' to verify.";
    show_success_dialog(msg.c_str());
    
    gtk_widget_set_sensitive(close_button, TRUE);
}

void on_install_clicked(GtkWidget *widget, gpointer data) {
    std::thread(install_yolex).detach();
}

void on_close_clicked(GtkWidget *widget, gpointer data) {
    GtkWindow *win = GTK_WINDOW(data);
    gtk_window_destroy(win);
}

static void activate(GtkApplication *app, gpointer user_data) {
    // Create window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Yorl Compiler Installer");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 250);
    
    // Create vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_start(vbox, 20);
    gtk_widget_set_margin_end(vbox, 20);
    gtk_widget_set_margin_top(vbox, 20);
    gtk_widget_set_margin_bottom(vbox, 20);
    gtk_window_set_child(GTK_WINDOW(window), vbox);
    
    // Title
    GtkWidget *title = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title), "<span size='x-large' weight='bold'>Yorl Compiler Installer</span>");
    gtk_box_append(GTK_BOX(vbox), title);
    
    // Version
    GtkWidget *version = gtk_label_new(("Version " + VERSION).c_str());
    gtk_box_append(GTK_BOX(vbox), version);
    
    // Description
    GtkWidget *desc = gtk_label_new("This will install the Yorl compiler (yolex) to ~/.local/bin");
    gtk_box_append(GTK_BOX(vbox), desc);
    
    // Status label
    status_label = gtk_label_new("Ready to install");
    gtk_box_append(GTK_BOX(vbox), status_label);
    
    // Progress bar
    progress_bar = gtk_progress_bar_new();
    gtk_box_append(GTK_BOX(vbox), progress_bar);
    
    // Button box
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(button_box, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(vbox), button_box);
    
    // Install button
    install_button = gtk_button_new_with_label("Install");
    gtk_widget_set_size_request(install_button, 100, 40);
    g_signal_connect(install_button, "clicked", G_CALLBACK(on_install_clicked), NULL);
    gtk_box_append(GTK_BOX(button_box), install_button);
    
    // Close button
    close_button = gtk_button_new_with_label("Close");
    gtk_widget_set_size_request(close_button, 100, 40);
    gtk_widget_set_sensitive(close_button, FALSE);
    g_signal_connect(close_button, "clicked", G_CALLBACK(on_close_clicked), window);
    gtk_box_append(GTK_BOX(button_box), close_button);
    
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("com.yorl.installer", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
