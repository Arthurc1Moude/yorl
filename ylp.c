/*
 * Yorl Packager (ylp) - Package Yorl programs as standalone executables
 * Version 1.0.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "version.h"

#define MAX_PATH 4096
#define MAX_COMMAND 8192

void print_usage(const char* prog) {
    printf("Yorl Packager (ylp) v%s\n", YORL_VERSION_STRING);
    printf("Package Yorl programs as standalone executables\n\n");
    printf("Usage: %s [options] <input.yorl> -o <output>\n\n", prog);
    printf("Options:\n");
    printf("  -o <output>     Output executable name\n");
    printf("  -p <platform>   Target platform: linux, windows, macos, all (default: current)\n");
    printf("  --version       Show version\n");
    printf("  --help          Show this help\n\n");
    printf("Examples:\n");
    printf("  %s myapp.yorl -o myapp\n", prog);
    printf("  %s myapp.yorl -o myapp -p all\n", prog);
    printf("  %s myapp.yorl -o myapp -p windows\n", prog);
}

int file_exists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0;
}

char* get_temp_dir() {
    char* tmp = getenv("TMPDIR");
    if (!tmp) tmp = getenv("TEMP");
    if (!tmp) tmp = getenv("TMP");
    if (!tmp) tmp = "/tmp";
    return tmp;
}

int compile_yorl(const char* input, const char* json_output) {
    char cmd[MAX_COMMAND];
    snprintf(cmd, sizeof(cmd), "yolex \"%s\" > \"%s\"", input, json_output);
    return system(cmd);
}

int create_executable(const char* json_file, const char* output, const char* platform) {
    char wrapper[MAX_COMMAND * 4];
    char cmd[MAX_COMMAND];
    FILE* fp;
    
    // Read JSON content
    fp = fopen(json_file, "r");
    if (!fp) {
        fprintf(stderr, "Error: Cannot read compiled JSON\n");
        return 1;
    }
    
    fseek(fp, 0, SEEK_END);
    long json_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    char* json_content = malloc(json_size + 1);
    fread(json_content, 1, json_size, fp);
    json_content[json_size] = '\0';
    fclose(fp);
    
    // Escape quotes in JSON
    char* escaped_json = malloc(json_size * 2 + 1);
    int j = 0;
    for (int i = 0; i < json_size; i++) {
        if (json_content[i] == '"') {
            escaped_json[j++] = '\\';
        }
        escaped_json[j++] = json_content[i];
    }
    escaped_json[j] = '\0';
    
    if (strcmp(platform, "windows") == 0 || strcmp(platform, "all") == 0) {
        // Windows executable
        char win_output[MAX_PATH];
        snprintf(win_output, sizeof(win_output), "%s.exe", output);
        
        snprintf(wrapper, sizeof(wrapper),
            "#include <stdio.h>\n"
            "#include <stdlib.h>\n"
            "int main() {\n"
            "    const char* json = \"%s\";\n"
            "    printf(\"%%s\\n\", json);\n"
            "    return 0;\n"
            "}\n", escaped_json);
        
        char temp_c[MAX_PATH];
        snprintf(temp_c, sizeof(temp_c), "%s/ylp_temp.c", get_temp_dir());
        fp = fopen(temp_c, "w");
        fprintf(fp, "%s", wrapper);
        fclose(fp);
        
        snprintf(cmd, sizeof(cmd), "x86_64-w64-mingw32-gcc \"%s\" -o \"%s\" 2>/dev/null", temp_c, win_output);
        if (system(cmd) == 0) {
            printf("Created: %s\n", win_output);
        }
        unlink(temp_c);
    }
    
    if (strcmp(platform, "linux") == 0 || strcmp(platform, "all") == 0 || strcmp(platform, "current") == 0) {
        // Linux executable
        snprintf(wrapper, sizeof(wrapper),
            "#!/bin/bash\n"
            "cat << 'YORL_JSON_EOF'\n"
            "%s\n"
            "YORL_JSON_EOF\n", json_content);
        
        fp = fopen(output, "w");
        fprintf(fp, "%s", wrapper);
        fclose(fp);
        chmod(output, 0755);
        printf("Created: %s\n", output);
    }
    
    if (strcmp(platform, "macos") == 0 || strcmp(platform, "all") == 0) {
        // macOS executable (same as Linux for now)
        char mac_output[MAX_PATH];
        snprintf(mac_output, sizeof(mac_output), "%s-macos", output);
        
        snprintf(wrapper, sizeof(wrapper),
            "#!/bin/bash\n"
            "cat << 'YORL_JSON_EOF'\n"
            "%s\n"
            "YORL_JSON_EOF\n", json_content);
        
        fp = fopen(mac_output, "w");
        fprintf(fp, "%s", wrapper);
        fclose(fp);
        chmod(mac_output, 0755);
        printf("Created: %s\n", mac_output);
    }
    
    free(json_content);
    free(escaped_json);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    char* input = NULL;
    char* output = NULL;
    char* platform = "current";
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            printf("ylp v%s\n", YORL_VERSION_STRING);
            return 0;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                output = argv[++i];
            }
        } else if (strcmp(argv[i], "-p") == 0) {
            if (i + 1 < argc) {
                platform = argv[++i];
            }
        } else if (!input) {
            input = argv[i];
        }
    }
    
    if (!input) {
        fprintf(stderr, "Error: No input file specified\n");
        print_usage(argv[0]);
        return 1;
    }
    
    if (!output) {
        fprintf(stderr, "Error: No output file specified (-o)\n");
        return 1;
    }
    
    if (!file_exists(input)) {
        fprintf(stderr, "Error: Input file '%s' not found\n", input);
        return 1;
    }
    
    // Validate platform
    if (strcmp(platform, "linux") != 0 && strcmp(platform, "windows") != 0 && 
        strcmp(platform, "macos") != 0 && strcmp(platform, "all") != 0 && 
        strcmp(platform, "current") != 0) {
        fprintf(stderr, "Error: Invalid platform '%s'\n", platform);
        return 1;
    }
    
    printf("Yorl Packager v%s\n", YORL_VERSION_STRING);
    printf("Input: %s\n", input);
    printf("Platform: %s\n", platform);
    printf("\n");
    
    // Compile Yorl to JSON
    char json_temp[MAX_PATH];
    snprintf(json_temp, sizeof(json_temp), "%s/ylp_%d.json", get_temp_dir(), getpid());
    
    printf("Compiling Yorl...\n");
    if (compile_yorl(input, json_temp) != 0) {
        fprintf(stderr, "Error: Failed to compile Yorl file\n");
        return 1;
    }
    
    printf("Creating executable(s)...\n");
    int result = create_executable(json_temp, output, platform);
    
    unlink(json_temp);
    
    if (result == 0) {
        printf("\nPackaging complete!\n");
    }
    
    return result;
}
