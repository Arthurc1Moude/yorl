/*
 * Version information for Yorl Executive Tools
 */
#include <stdio.h>
#include <string.h>
#include "version.h"

/* Get the full version string */
const char* get_yorl_version(void) {
    static char version[64];
    snprintf(version, sizeof(version), "%d.%d.%d-%d", 
             YORL_VERSION_MAJOR, 
             YORL_VERSION_MINOR, 
             YORL_VERSION_PATCH, 
             YORL_VERSION_BUILD);
    return version;
}

/* Get build date (this would typically be set during build) */
const char* get_build_date(void) {
    return __DATE__ " " __TIME__;
}

/* Get compiler information */
const char* get_compiler_info(void) {
#ifdef __clang__
    return "clang";
#elif defined(__GNUC__)
    return "gcc";
#elif defined(_MSC_VER)
    return "msvc";
#else
    return "unknown";
#endif
}

/* Get full version string */
const char* get_full_version(void) {
    static char full_version[256];
    snprintf(full_version, sizeof(full_version), 
             "Yorl Executive Tools v%s (Built: %s with %s)", 
             get_yorl_version(), get_build_date(), get_compiler_info());
    return full_version;
}

/* Get version as a string for display */
const char* get_version_string(void) {
    static char version_str[100];
    snprintf(version_str, sizeof(version_str), 
             "Yorl v%d.%d.%d-%d", 
             YORL_VERSION_MAJOR, 
             YORL_VERSION_MINOR, 
             YORL_VERSION_PATCH, 
             YORL_VERSION_BUILD);
    return version_str;
}

/* Get version as integer for comparisons */
unsigned long get_version_number(void) {
    return (YORL_VERSION_MAJOR << 24) | 
           (YORL_VERSION_MINOR << 16) | 
           (YORL_VERSION_PATCH << 8) | 
           (YORL_VERSION_BUILD);
}

/* Check if version is at least the specified version */
int version_at_least(int major, int minor, int patch) {
    if (YORL_VERSION_MAJOR > major) return 1;
    if (YORL_VERSION_MAJOR < major) return 0;
    if (YORL_VERSION_MINOR > minor) return 1;
    if (YORL_VERSION_MINOR < minor) return 0;
    return YORL_VERSION_PATCH >= patch;
}

/* Get version as a string for Yorl files */
const char* get_yorl_version_declaration(void) {
    static char yorl_version[50];
    snprintf(yorl_version, sizeof(yorl_version), 
             "^yorl %d.%d.%d-%d\\", 
             YORL_VERSION_MAJOR, 
             YORL_VERSION_MINOR, 
             YORL_VERSION_PATCH, 
             YORL_VERSION_BUILD);
    return yorl_version;
}

/* Get version info for display */
void print_version_info(void) {
    printf("Yorl Executive Tools (yolex) v%s\n", get_version_string());
    printf("Build: %s\n", get_build_date());
    printf("Compiler: %s\n", get_compiler_info());
    printf("Yorl Language Version: %s\n", get_yorl_version());
    printf("Yorl Declaration: %s\n", get_yorl_version_declaration());
}

/* Get full version string (matches yorl.y expectation) */
const char* get_yorl_full_version(void) {
    static char full_version[256];
    snprintf(full_version, sizeof(full_version), 
             "Yorl Executive Tools v%s (Built: %s with %s)", 
             get_yorl_version(), get_build_date(), get_compiler_info());
    return full_version;
}

/* Get version info for display (matches yorl.y expectation) */
const char* get_version_info(void) {
    static char version_info[512];
    snprintf(version_info, sizeof(version_info), 
             "Yorl Executive Tools (yolex) v%s\n"
             "Build: %s\n"
             "Compiler: %s\n"
             "Yorl Language Version: %s\n"
             "Yorl Declaration: %s", 
             get_version_string(), 
             get_build_date(), 
             get_compiler_info(), 
             get_yorl_version(), 
             get_yorl_version_declaration());
    return version_info;
}