/*
 * Yorl Packager (ylp) - Standalone packager
 * Packages Yorl programs as executables for all platforms
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH 4096
#define MAX_COMMAND 16384
#define VERSION "1.0.0"

void print_usage(const char* prog) {
    printf("Yorl Packager (ylp) v%s\n", VERSION);
    printf("Package Yorl programs as standalone executables\n\n");
    printf("Usage: %s [options] <input.yorl> -o <output>\n\n", prog);
    printf("Options:\n");
    printf("  -o <output>     Output executable name (required)\n");
    printf("  -p <platform>   Target: linux, windows, macos, all (default: linux)\n");
    printf("  -g, --gui       Enable GUI for whiteboard class\n");
    printf("  --version       Show version\n");
    printf("  --help          Show help\n\n");
    printf("Examples:\n");
    printf("  ylp app.yorl -o myapp\n");
    printf("  ylp app.yorl -o myapp -p all\n");
    printf("  ylp gui.yorl -o gui-app --gui\n");
}

int file_exists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0;
}

char* read_file(const char* path, size_t* size) {
    FILE* fp = fopen(path, "rb");
    if (!fp) return NULL;
    
    fseek(fp, 0, SEEK_END);
    *size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    char* content = malloc(*size + 1);
    fread(content, 1, *size, fp);
    content[*size] = '\0';
    fclose(fp);
    
    return content;
}

char* escape_for_c(const char* str, size_t len) {
    char* escaped = malloc(len * 4 + 1);
    size_t j = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '"' || str[i] == '\\') {
            escaped[j++] = '\\';
            escaped[j++] = str[i];
        } else if (str[i] == '\n') {
            escaped[j++] = '\\';
            escaped[j++] = 'n';
        } else if (str[i] == '\r') {
            escaped[j++] = '\\';
            escaped[j++] = 'r';
        } else if (str[i] == '\t') {
            escaped[j++] = '\\';
            escaped[j++] = 't';
        } else {
            escaped[j++] = str[i];
        }
    }
    escaped[j] = '\0';
    return escaped;
}

int create_linux_executable(const char* yorl_content, const char* output, int gui) {
    FILE* fp = fopen(output, "w");
    if (!fp) return 1;
    
    fprintf(fp, "#!/bin/bash\n");
    fprintf(fp, "# Yorl Packaged Application\n");
    fprintf(fp, "YORL_DATA=$(cat << 'YORL_EOF'\n");
    fprintf(fp, "%s", yorl_content);
    fprintf(fp, "\nYORL_EOF\n");
    fprintf(fp, ")\n\n");
    
    if (gui) {
        fprintf(fp, "# GUI mode - requires yolex\n");
        fprintf(fp, "if command -v yolex &> /dev/null; then\n");
        fprintf(fp, "    echo \"$YORL_DATA\" | yolex /dev/stdin\n");
        fprintf(fp, "else\n");
        fprintf(fp, "    echo \"Error: yolex not found. Install Yorl SDK.\"\n");
        fprintf(fp, "    exit 1\n");
        fprintf(fp, "fi\n");
    } else {
        fprintf(fp, "echo \"$YORL_DATA\"\n");
    }
    
    fclose(fp);
    chmod(output, 0755);
    return 0;
}

int create_windows_executable(const char* yorl_content, size_t content_len, const char* output, int gui) {
    char temp_c[MAX_PATH];
    snprintf(temp_c, sizeof(temp_c), "/tmp/ylp_%d.c", getpid());
    
    FILE* fp = fopen(temp_c, "w");
    if (!fp) return 1;
    
    char* escaped = escape_for_c(yorl_content, content_len);
    
    if (gui) {
        fprintf(fp, "#include <windows.h>\n");
        fprintf(fp, "#include <stdio.h>\n\n");
        fprintf(fp, "const char yorl_data[] = \"%s\";\n\n", escaped);
        fprintf(fp, "int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow) {\n");
        fprintf(fp, "    MessageBoxA(NULL, \"Yorl GUI Application\\n\\nData embedded.\", \"Yorl App\", MB_OK | MB_ICONINFORMATION);\n");
        fprintf(fp, "    return 0;\n");
        fprintf(fp, "}\n");
    } else {
        fprintf(fp, "#include <stdio.h>\n\n");
        fprintf(fp, "const char yorl_data[] = \"%s\";\n\n", escaped);
        fprintf(fp, "int main() {\n");
        fprintf(fp, "    printf(\"%%s\\n\", yorl_data);\n");
        fprintf(fp, "    return 0;\n");
        fprintf(fp, "}\n");
    }
    
    fclose(fp);
    free(escaped);
    
    char cmd[MAX_COMMAND];
    char win_output[MAX_PATH];
    snprintf(win_output, sizeof(win_output), "%s.exe", output);
    
    snprintf(cmd, sizeof(cmd), "x86_64-w64-mingw32-gcc \"%s\" -o \"%s\" %s 2>/dev/null",
             temp_c, win_output, gui ? "-mwindows" : "");
    
    int result = system(cmd);
    unlink(temp_c);
    
    if (result == 0) {
        printf("Created: %s\n", win_output);
        return 0;
    }
    return 1;
}

int create_macos_executable(const char* yorl_content, const char* output) {
    char mac_output[MAX_PATH];
    snprintf(mac_output, sizeof(mac_output), "%s-macos", output);
    
    FILE* fp = fopen(mac_output, "w");
    if (!fp) return 1;
    
    fprintf(fp, "#!/bin/bash\n");
    fprintf(fp, "# Yorl Packaged Application for macOS\n");
    fprintf(fp, "cat << 'YORL_EOF'\n");
    fprintf(fp, "%s", yorl_content);
    fprintf(fp, "\nYORL_EOF\n");
    
    fclose(fp);
    chmod(mac_output, 0755);
    printf("Created: %s\n", mac_output);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    char* input = NULL;
    char* output = NULL;
    char* platform = "linux";
    int gui = 0;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--version") == 0) {
            printf("ylp v%s\n", VERSION);
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output = argv[++i];
        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            platform = argv[++i];
        } else if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--gui") == 0) {
            gui = 1;
        } else if (!input) {
            input = argv[i];
        }
    }
    
    if (!input) {
        fprintf(stderr, "Error: No input file\n");
        return 1;
    }
    
    if (!output) {
        fprintf(stderr, "Error: No output file (-o required)\n");
        return 1;
    }
    
    if (!file_exists(input)) {
        fprintf(stderr, "Error: File '%s' not found\n", input);
        return 1;
    }
    
    printf("Yorl Packager v%s\n", VERSION);
    printf("Input: %s\n", input);
    printf("Output: %s\n", output);
    printf("Platform: %s\n", platform);
    if (gui) printf("GUI: enabled\n");
    printf("\n");
    
    size_t content_size;
    char* yorl_content = read_file(input, &content_size);
    if (!yorl_content) {
        fprintf(stderr, "Error: Cannot read input file\n");
        return 1;
    }
    
    printf("Packaging...\n");
    
    int success = 0;
    
    if (strcmp(platform, "linux") == 0 || strcmp(platform, "all") == 0) {
        if (create_linux_executable(yorl_content, output, gui) == 0) {
            printf("Created: %s\n", output);
            success = 1;
        }
    }
    
    if (strcmp(platform, "windows") == 0 || strcmp(platform, "all") == 0) {
        if (create_windows_executable(yorl_content, content_size, output, gui) == 0) {
            success = 1;
        }
    }
    
    if (strcmp(platform, "macos") == 0 || strcmp(platform, "all") == 0) {
        if (create_macos_executable(yorl_content, output) == 0) {
            success = 1;
        }
    }
    
    free(yorl_content);
    
    if (success) {
        printf("\nPackaging complete!\n");
        printf("\nNote: Packaged apps contain embedded Yorl source.\n");
        printf("      Use with yolex to execute or view data.\n");
        return 0;
    }
    
    fprintf(stderr, "Error: Packaging failed\n");
    return 1;
}
